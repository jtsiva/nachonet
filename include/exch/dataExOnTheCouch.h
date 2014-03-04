/*******************************************************************************
File:				dataExOnTheCouch.h
Author: 		Josh Siva
Date:				3/3/14
Project:		NachoNet
Purpose:		Defines the interface to the data exchange module on the couch. This
						extends the data exchange module to work with CouchDB
*******************************************************************************/

#pragma once
#include "dataEx.h"

class dataExOnTheCouch : public dataEx
{
	public:
		dataExOnTheCouch ();
		virtual ~dataExOnTheCouch ();

		virtual void addNode (node newNode);
    virtual void dropNode (int id);
    virtual void addDevice (device newDev);
    virtual void dropDevice (std::string id);

    virtual void pingAll (Message message); //send msg to everyone in net
    virtual void ping (Message message); //push msg and pull to check
    virtual void pushUpdates ();
    virtual void pullUpdates ();
	private:


};
