/**
 * @file
 * @brief File for the game engine.
 */

#ifndef INCLUDE_FDC_GAMEENGINE_H_
#define INCLUDE_FDC_GAMEENGINE_H_

#include "FDC_GraphicsEngine.h"
#include "FDC_ScreenInfo.h"

/**
 * @brief Game engine.
 *
 * The game engine coordinates all actions in the game.
 */
typedef struct{
	FDC_ScreenInfo screen_info; //!< Screen.
	FDC_GraphicsEngine * graphics; //!< Graphics engine.
} FDC_GameEngine;

/**
 * @brief Run the main loop.
 *
 * @param self Game engine.
 */
void FDC_GameEngine_mainLoop(FDC_GameEngine * self);

#endif /* INCLUDE_FDC_GAMEENGINE_H_ */
