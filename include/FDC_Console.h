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
 * @brief Maximum length of a console glyph
 */
#define FDC_CONSOLE_GRAPHEME_MAX_LEN ((size_t)10)

/**
 * @brief Maximum length of a console print sequence.
 */
#define FDC_CONSOLE_PRINT_SEQUENCE_MAX_LEN ((size_t)4096)

/**
 * @brief ::FDC_ConsoleBufferVirtual cell information.
 *
 * @private
 */
typedef struct {
	size_t grapheme_size; //!< Size of the grapheme.
	char grapheme[FDC_CONSOLE_GRAPHEME_MAX_LEN]; //!< Grapheme cluster in this cell.
	char rgb_bg[3]; //!< RGB color for the background.
	char rgb_fg[3]; //!< RGB color for the foreground.
} FDC_ConsoleBufferVirtualCell;

/**
 * @brief Struct representing a console buffer implemented as an array in memory.
 */
typedef struct{
	size_t n_rows; //!< Number of rows.
	size_t n_columns; //!< Number of columns.
	FDC_ConsoleBufferVirtualCell * cells; //!< Cells.
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
} FDC_Console;

#define FDC_CONSOLE_ESCAPE_STR "\033"

/**
 * @brief Initialize a virtual console buffer.
 *
 * @param self Buffer.
 * @param n_rows Number of rows.
 * @param n_columns Number of columns.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_init(FDC_ConsoleBufferVirtual * self, size_t n_rows, size_t n_columns);

/**
 * @brief Release the resources associated with the buffer.
 *
 * @param self Buffer.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_destroy(FDC_ConsoleBufferVirtual * self);

/**
 * @brief Resize a virtual console buffer.
 *
 * @param self Buffer.
 * @param n_rows Number of rows.
 * @param n_columns Number of columns.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_resize(FDC_ConsoleBufferVirtual * self, size_t n_rows, size_t n_columns);

/**
 * @brief Set the grapheme cluster of a virtual console buffer cell.
 *
 * @param self Buffer.
 * @param row Row to change.
 * @param column Column to change.
 * @param grapheme_size Size of the grapheme cluster.
 * @param grapheme New grapheme.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_setCellGrapheme(FDC_ConsoleBufferVirtual * self, size_t row, size_t column,
		size_t grapheme_size, char grapheme[grapheme_size]);

/**
 * @brief Set the glyph of a virtual console buffer cell.
 *
 * @param self Buffer.
 * @param row Row to change.
 * @param column Column to change.
 * @param rgb_bg New background color.
 * @param rgb_fg New foreground color.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_setCellColors(FDC_ConsoleBufferVirtual * self, size_t row, size_t column, char rgb_bg[3], char rgb_fg[3]);

/**
 * @brief Write the buffer to a console.
 *
 * @param self Buffer.
 * @param console Console.
 *
 * @return Status value.
 */
FDC_Error FDC_ConsoleBufferVirtual_writeToConsole(FDC_ConsoleBufferVirtual * self, FDC_Console * console);


/**
 * @brief Initialize the console.
 *
 * @param self Console.
 *
 * @return Status value.
 */
FDC_Error FDC_Console_init(FDC_Console * self);

/**
 * @brief Release the resources allocated to the console.
 *
 * @param self Console.
 *
 * @return Status value.
 */
FDC_Error FDC_Console_destroy(FDC_Console * self);

/**
 * @brief Obtains the active console buffer.
 *
 * @param self
 * @param buffer
 * @return
 */
FDC_Error FDC_Console_getActiveBuffer(FDC_Console * self, FDC_ConsoleBuffer ** buffer);

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

#endif /* INCLUDE_FDC_CONSOLE_H_ */
