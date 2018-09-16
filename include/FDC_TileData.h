/**
 * @file
 * @brief File for the tile information.
 */

#ifndef INCLUDE_FDC_TILEDATA_H_
#define INCLUDE_FDC_TILEDATA_H_

#include "FDC_Collision.h"

/**
 * @brief Data associated with a tile.
 */
typedef struct{
	FDC_Collision collision; //!< The collision of the tile.
} FDC_TileData;

/**
 * @brief Data associated with a grid of tiles.
 */
typedef struct{
	size_t n_rows; //!< Number of rows of this grid of tiles.
	size_t n_cols; //!< Number of columns of this grid of tiles.
	FDC_TileData * grid; //!< A n_rows x n_cols array containing information for all tiles.
} FDC_TileDataGrid;

#endif /* INCLUDE_FDC_TILEDATA_H_ */
