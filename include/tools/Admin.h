/*******************************************************************************
File:				Admin.h
Author: 		Josh Siva
Date:				3/18/14
Project:		NachoNet
Purpose:		Defines the interface to a generic tool used for testing,
						configuring, etc. the pieces of the NachoNet
*******************************************************************************/

#pragma once
#include <fstream>
#include "../nacho/NachoNet.h"

class Admin
{
	public:
		Admin (NachoNet *pNacho);
		virtual ~Admin ();
		virtual void options ();
		virtual void test ();
		virtual void configure ();

		static const char YES = 'y';
		static const char NO = 'n';

	protected:
		std::ostream os;
		NachoNet *pNacho;

};