/**
 * @file	Controller.h
 * @brief	Controller
 * @authors VuLong DuyKhanh
 */
 
 
#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "include.h"
 


#define RADIUS_BALL 		(BALLSIZE_1)					// mm
#define BALLSIZE_1 			(120)										// mm
#define BALLSIZE_2 			()										// mm
#define BALLSIZE_3 			()										// mm
#define BALLSIZE_4 			()										// mm
#define BALLSIZE_5 			()										// mm

#define RADIUS_WHEELS 		(25)											// mm
#define RADIUS_ROBOT 		()										// mm
#define HEIGHT_OF_THE_CENTER		()						// mm

#define MASS_OF_ROBOT						()						// kg
#define MASS_OF_BALL						()						// kg
#define MASS_OF_WHEELS					()						// kg

#define INERTIA_OF_BALL					()						// kg.m^2
#define INERTIA_XY							()						// kg.m^2
#define INERTIA_XZ_YZ						()						// kg.m^2
#define INERTIA_ROBOT						()						// kg.m^2
#define INERTIA_ROBOT_XY				()						// kg.m^2


extern float globalTheta[3];
extern float globalthetaDot[3];


#endif
