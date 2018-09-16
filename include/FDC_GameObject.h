/**
 * @file
 * @brief File for the game objects.
 */

#ifndef INCLUDE_FDC_GAMEOBJECT_H_
#define INCLUDE_FDC_GAMEOBJECT_H_

#include <stddef.h>

#include "FDC_TileData.h"

/**
 * @brief Generic game object data.
 */
typedef struct{
	char * name; //!< Object name.
	char * description; //!< Object description.
	float x; //!< Object position in X axis.
	float y; //!< Object position in Y axis.
	FDC_TileDataGrid tiles; //!< Tile information.
} GameObject;

#endif /* INCLUDE_FDC_GAMEOBJECT_H_ */
