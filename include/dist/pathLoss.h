/******************************************************************************
File:				pathLoss.h
Author: 		Josh Siva
Date:				11/15/13
Project:		NachoNet
Purpose:		The file defines the interface to the pathLoss module which will
						implement the following path loss equation:
						d = 10^((P - P_d0) / (10 * n))
******************************************************************************/

#pragma once
#include "dist.h"

class pathLoss : public distMeasure
{
	public:
		pathLoss(bool debug = false, EZConfig *pConfig = NULL);
		virtual ~pathLoss();
		virtual void init(EZConfig *pConfig);
		virtual distMeasurement measure(ssMeasurement devSS);
		virtual std::vector<std::string> getVariables ();

		//These values have been chosen by looking at an example graph in
		// [Pu et. al. 2011]
		const float DEFAULT_ENV_VAL = 2.25;
		static const int DEFAULT_POW_AT_REF = -38; //the power at 1m (unobstructed)

	private:
		//n
		float envVal; //environmental characterization value
		//P_d0
		int powerAtRefDist;

		bool debug;
};

