/**
 * @file
 * @brief File for the graphics engine.
 */

#ifndef INCLUDE_FDC_GRAPHICSENGINE_H_
/**
 * @file
 * @brief File for the graphics engines.
 */

#define INCLUDE_FDC_GRAPHICSENGINE_H_

#include "FDC_Error.h"
#include "FDC_ScreenInfo.h"
#include "FDC_Console.h"

/**
 * @brief Graphics engine.
 *
 * A graphics engine displays the state of the game.
 */
typedef struct{

} FDC_GraphicsEngine;

/**
 * @brief Console graphics engine.
 *
 * A graphics engine that displays the state of the game in the console.
 */
typedef struct{
	FDC_GraphicsEngine super; //!< Parent struct.
	FDC_Console console;
} FDC_ConsoleGraphicsEngine;

/**
 * @brief Repaints the window.
 *
 * @param self Graphics engine.
 * @param screen_info Information about the area to paint.
 *
 * @return Status value.
 */
FDC_Error FDC_GraphicsEngine_repaint(FDC_GraphicsEngine * self, FDC_ScreenInfo * screen_info);

#endif /* INCLUDE_FDC_GRAPHICSENGINE_H_ */
