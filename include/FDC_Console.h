/**
 * @file
 * @brief Console object.
 */

#ifndef INCLUDE_FDC_CONSOLE_H_
#define INCLUDE_FDC_CONSOLE_H_

#include "FDC_Error.h"
#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Struct representing a console buffer implemented as an array in memory.
 */
typedef struct{

} FDC_ConsoleBufferVirtual;


/**
 * @brief Struct representing a console buffer.
 */
typedef struct{
#ifdef _WIN32
	HANDLE handle;
#elif defined(__linux__)
	int fd;
#endif
} FDC_ConsoleBuffer;

/**
 * @brief Struct representing the system console.
 */
typedef struct{
	FDC_ConsoleBuffer * active_buffer; //!< Pointer to the buffer currently in the screen.
	FDC_ConsoleBuffer * secondary_buffer; //!< Pointer to the secondary buffer, if any.
	FDC_ConsoleBuffer buffers[2]; //!< Buffers.
} FDC_Console;

#define FDC_CONSOLE_ESCAPE_STR "\033"

/**
 * @self Initialize the console.
 *
 * @param self Console.
 *
 * @return Status value.
 */
FDC_Error FDC_Console_init(FDC_Console * self);

/**
 * @self Release the resources allocated to the console.
 *
 * @param self Console.
 *
 * @return Status value.
 */
FDC_Error FDC_Console_destroy(FDC_Console * self);

/**
 * @brief Write to the console buffer.
 *
 * @param self Console.
 * @param size Size of the written text.
 * @param text Text to write.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBuffer_write(FDC_ConsoleBuffer * self, size_t size, char text[size]);

/**
 * @brief Sets the cursor position in the console buffer.
 *
 * @param self Console.
 * @param x X coordinate.
 * @param y Y coordinate.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBuffer_setCursorPosition(FDC_Console * self, size_t x, size_t y);

#endif /* INCLUDE_FDC_CONSOLE_H_ */
