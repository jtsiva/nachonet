/*******************************************************************************
File:				DistMeasureAdmin.h
Author: 		Josh Siva
Date:				3/18/14
Project:		NachoNet
Purpose:		Defines the interface to the admin tool that will be used with the
						Distance Measurement object
*******************************************************************************/

#pragma once
#include "Admin.h"
#include "../dist/dist.h"
#include "../dist/fsPathLoss.h"
#include "../dist/logNormalShadow.h"
#include "../dist/pathLoss.h"
#include "../util/EZConfig.h"

class DistMeasureAdmin : public Admin
{
	public:
		DistMeasureAdmin (NachoNet *pNacho);
		virtual void options ();
		virtual void configure ();
		virtual void test ();

		typedef enum DIST_EQN
		{
			PATH_LOSS = 1,
			FREE_SPACE_PATH_LOSS,
			LOG_NORMAL_SHADOW
		}DIST_EQN;

	private:
		EZConfig distConfig;
};

