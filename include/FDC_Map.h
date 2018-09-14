/**
 * @file
 * @brief File for the map information.
 */

#ifndef INCLUDE_FDC_MAP_H_
#define INCLUDE_FDC_MAP_H_

#include <stddef.h>

/**
 * @brief Collision status.
 */
typedef enum{
	FDC_COLLISION_NONE, //!< The object has not collisions.
	FDC_COLLISION_SOLID  //!< The object has collisions with other solid objects.
} FDC_Collision;

/**
 * @brief Information about the space of a tile.
 */
typedef struct{
	FDC_Collision collision; //!< The collision of the tile.
} FDC_TileSpace;

/**
 * @brief Map information.
 */
typedef struct{
	size_t n_rows; //!< Number of rows of this map.
	size_t n_cols; //!< Number of columns of this map.
	FDC_TileSpace * board; //!< A n_rows x n_cols array containing information for all tiles.
} FDC_Map;

#endif /* INCLUDE_FDC_MAP_H_ */
