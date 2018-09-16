/**
 * @file
 * @brief File for the map information.
 */

#ifndef INCLUDE_FDC_MAP_H_
#define INCLUDE_FDC_MAP_H_

#include <stddef.h>
#include "FDC_TileData.h"

/**
 * @brief Map information.
 */
typedef struct{
	FDC_TileDataGrid tiles;
} FDC_Map;

#endif /* INCLUDE_FDC_MAP_H_ */
