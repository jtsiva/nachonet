/*******************************************************************************
File:				stdCollect.cpp
Author: 		Josh Siva
Date:				1/26/14
Project:		NachoNet
Purpose:		Defines the behavior of the stdCollect module which utilizes
						libpcap to sniff the network
*******************************************************************************/

#include "../../include/collect/stdCollect.h"
#include "../../extern/radiotapParser/radiotap-parser.h"
#include <iostream>
#include <cstring>

const std::string stdCollect::DEFAULT_IFACE = "wlan0";

/******************************************************************************
 * Constructor: stdCollect
 *
 * Description: Initialize the interface and pass of the debug variable to the
 * 							parent class
 *
 * Parameters:	interface - the name of the interface to capture on
 * 							debug			- true if in debug mode, false otherwise
 *
 * Returned:		None
 *****************************************************************************/
stdCollect::stdCollect (std::string interface, bool debug) : dataCollect (debug)
{
	this->interface = interface;
}

/******************************************************************************
 * Method: 		  packetLoop
 *
 * Description: This method grabs numPackets packets and analyzes them. The
 * 							signal strength and MAC address from the packets will be saved
 * 							in a data structure
 *
 * Parameters:	pHandle - the pcap handle to the network device
 * 							numPackets - the number of packets to capture,
 *
 * Returned:		None
 *****************************************************************************/
void stdCollect::packetLoop (pcap *pHandle, int numPackets)
{
	const u_char * pPacket;
	struct pcap_pkthdr *pPacketHeader;
	struct ieee80211_radiotap_iterator radiotapIter;
	struct ieee80211_radiotap_header * pRadiotapHeader;
	const u_char * pAddr;
	char converted [(ETHERNET_ADDR_LEN * 2) + 1];
	std::string currentDevID;
	int returnVal, channel = 0, ss = ERROR;

	for (int i = 0; i < numPackets; i++)
	{
		if (0 <= pcap_next_ex (pHandle, &pPacketHeader, &pPacket))
		{
			pRadiotapHeader = (struct ieee80211_radiotap_header * ) pPacket;

			if (isDebug ())
			{
				ieee80211_radiotap_iterator_init (&radiotapIter, pRadiotapHeader,
							pRadiotapHeader->it_len);

				std::cout << "available fields: ";
				do
				{
					returnVal = ieee80211_radiotap_iterator_next (&radiotapIter);
					std::cout << radiotapIter.this_arg_index << " ";

				} while (returnVal >= 0);

				std::cout << "\n";
			}

			ieee80211_radiotap_iterator_init (&radiotapIter, pRadiotapHeader,
									pRadiotapHeader->it_len);
			do
			{
				returnVal = ieee80211_radiotap_iterator_next (&radiotapIter);

				if (returnVal >= 0)
				{
					switch (radiotapIter.this_arg_index)
					{
						case IEEE80211_RADIOTAP_CHANNEL:
							channel = le16_to_cpu (* (uint16_t *)radiotapIter.this_arg);

							if (isDebug ())
							{
								std::cout << "\nhit channel\n";
							}

							break;

						case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
							ss = (int) ((signed char)*radiotapIter.this_arg);

							if (isDebug ())
							{
								std::cout << "\nhit ss\n";
							}
							break;

						default:
							if (isDebug ())
							{
								std::cout << "\n-----arg: " << returnVal << "\n";
							}

							break;
					}
				}

			} while (returnVal >= 0);

			pAddr = (pPacket + pRadiotapHeader->it_len + MAC_ADDR_OFFSET);

			for (int i = 0; i < ETHERNET_ADDR_LEN; i++)
			{
				sprintf (&converted[i * 2], "%02X", pAddr[i]);
			}

			currentDevID.assign(converted);

			if (isDebug ())
			{
				std::cout << channel << "   " << ss << "   " << currentDevID << "\n";
			}

			if (ERROR != ss)
			{
				update (currentDevID, ss);
			}

		}
	}

}

/******************************************************************************
 * Method: 			readFromNetwork
 *
 * Description: Prepares the device to be read from and then grabs
 * 							PACKETS_TO_GRAB packets to analyze.
 *
 * Parameters:	None
 *
 * Returned:		None
 *****************************************************************************/
void stdCollect::readFromNetwork ()
{
	pcap_t * pHandle;
	char errorBuffer[PCAP_ERRBUF_SIZE];
	int numPackets;

	pHandle = pcap_create (interface.c_str(), errorBuffer);
	if (NULL != pHandle)
	{
		if (pcap_can_set_rfmon (pHandle))
		{
			if (isDebug ())
			{
				std::cout << "Can use monitor mode\n";
			}

			if (0 == pcap_set_rfmon (pHandle, 1))
			{
				if (isDebug ())
				{
					std::cout << "Monitor mode enabled\n";
				}
			}
		}

		pcap_set_snaplen (pHandle, CAPTURE_LENGTH); //bytes to capture from packet
		pcap_set_promisc (pHandle, 0);							//disable promiscuous mode
		pcap_set_timeout (pHandle, TIMEOUT);				//set timeout
		pcap_activate (pHandle);

		if (isDebug ())
		{
			if (pcap_datalink (pHandle) == DLT_IEEE802_11)
			{
				std::cout << "DLT_IEEE802_11\n";
			}
			else if (pcap_datalink (pHandle) == DLT_IEEE802_11_RADIO)
			{
				std::cout << "DLT_IEEE802_11_RADIO\n";
			}
			else if (pcap_datalink (pHandle) == DLT_EN10MB)
			{
				std::cout << "DLT_EN10MB\n";
			}
			else
			{
				std::cout << "something else: " << pcap_datalink (pHandle) << "\n";
			}
		}

		if (isDebug ())
		{
			numPackets = DEBUG_PACKETS_TO_GRAB;
		}
		else
		{
			numPackets = PACKETS_TO_GRAB;
		}


		packetLoop (pHandle, numPackets);


		pcap_close (pHandle);
	}
	else
	{
		std::cout << "Failed to open device: " << errorBuffer << std::endl;
	}
}


