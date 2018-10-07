/*
 * FDC_Screen.h
 *
 *  Created on: 18 sept. 2018
 *      Author: Carlos
 */

#ifndef INCLUDE_FDC_SCREENINFO_H_
#define INCLUDE_FDC_SCREENINFO_H_

#include "FDC_Map.h"

typedef struct {
	FDC_Map * map; //!< Displayed map.
	float x; //!< X position of the upper left corner.
	float y; //!< X position of the upper left corner.
	float height; //!< Screen height.
	float width; //!< Screen width.
} FDC_ScreenInfo;

#endif /* INCLUDE_FDC_SCREENINFO_H_ */
