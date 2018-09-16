/**
 * @file
 * @brief File for the game engine.
 */

#ifndef INCLUDE_FDC_GAMEENGINE_H_
#define INCLUDE_FDC_GAMEENGINE_H_

/**
 * @brief Game engine.
 *
 * The game engine coordinates all actions in the game.
 */
typedef struct{

} FDC_GameEngine;

/**
 * @brief Run the main loop.
 *
 * @param self Game engine.
 */
void FDC_GameEngine_mainLoop(FDC_GameEngine * self);

#endif /* INCLUDE_FDC_GAMEENGINE_H_ */
