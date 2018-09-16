/**
 * @file
 * @brief File for collisions information.
 */

#ifndef INCLUDE_FDC_COLLISION_H_
#define INCLUDE_FDC_COLLISION_H_

/**
 * @brief Collision status.
 */
typedef enum{
	FDC_COLLISION_NONE, //!< The object has not collisions.
	FDC_COLLISION_SOLID  //!< The object has collisions with other solid objects.
} FDC_Collision;

#endif /* INCLUDE_FDC_COLLISION_H_ */
