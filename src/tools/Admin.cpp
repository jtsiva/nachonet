/*******************************************************************************
File:				Admin.cpp
Author: 		Josh Siva
Date:				3/18/14
Project:		NachoNet
Purpose:		Implements the basic functionality required by our admin tool
*******************************************************************************/

#include "../../include/tools/Admin.h"

std::ostream* Admin::pOut = NULL;

/*******************************************************************************
 * Constructor:	Admin
 *
 * Description:	Initializes the output stream to and grab the pointer to the
 * 							NachoNet object
 *
 * Parameters:	None
 *
 * Returned:		None
 ******************************************************************************/
Admin::Admin (NachoNet *pNacho)
{
	pOut = &std::cout;
	this->pNacho = pNacho;
}

/*******************************************************************************
 * Destroyer!:	~Admin
 *
 * Description:	Does nothing!
 *
 * Parameters:	None
 *
 * Returned:		None
 ******************************************************************************/
Admin::~Admin ()
{
}

/*******************************************************************************
 * Method:			options
 *
 * Description:	Prints a message notifying the user that this functionality has
 * 							not been defined yet.
 *
 * Parameters:	None
 *
 * Returned:		None
 ******************************************************************************/
void Admin::options ()
{
	std::cout << "\nNo option behavior has been defined\n";
}

/*******************************************************************************
 * Method:			test
 *
 * Description:	The default function is to setup a place for output to go for
 * 							the testing method
 *
 * Parameters:	None
 *
 * Returned:		None
 ******************************************************************************/
void Admin::test ()
{
	std::ofstream outFile;
	std::string outFileName;
	char choice;

	do
	{
		std::cout << "Would you like to capture the output in a file? (y/n): ";
		std::cin >> choice;
	} while(YES != choice && NO != choice);

	if(YES == choice)
	{
		std::cout << "Please enter an output file name: ";
		std::cin >> outFileName;

		outFile.open(outFileName.c_str());

		if (!outFile.fail())
		{
			pOut = &outFile;
		}
		else
		{
			std::cout << "\nFailed to open file!\n";
		}
	}
	else
	{
		pOut = &std::cout;
	}
}

/*******************************************************************************
 * Method:			configure
 *
 * Description:	Prints a message notifying the user that this functionality has
 * 							not been defined yet.
 *
 * Parameters:	None
 *
 * Returned:		None
 ******************************************************************************/
void Admin::configure ()
{
	std::cout << "\nNo configuration behavior has been defined.\n";
}

/*static std::ostream& Admin::out ()
{
	return *pOut;
}*/



