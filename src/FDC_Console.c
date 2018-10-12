/**
 * @file
 * @brief Console object.
 */

#include "FDC_Console.h"
#include "FDC_String.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include "windows.h"

// MinGW does not have this flag
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

FDC_Error FDC_ConsoleBufferVirtual_init(FDC_ConsoleBufferVirtual * self, size_t n_rows, size_t n_columns)
{
	return FDC_ConsoleBufferVirtual_resize(self, n_rows, n_columns);
}

FDC_Error FDC_ConsoleBufferVirtual_destroy(FDC_ConsoleBufferVirtual * self)
{
	self->n_rows = 0;
	self->n_columns = 0;

	free(self->cells);
	self->cells = NULL;

	return FDC_OK;
}

FDC_Error FDC_ConsoleBufferVirtual_resize(FDC_ConsoleBufferVirtual * self, size_t n_rows, size_t n_columns)
{
	self->n_rows = 0;
	self->n_columns = 0;

	if(self->cells != NULL)
	{
		free(self->cells);
	}

	self->cells = calloc(n_rows * n_columns, sizeof(self->cells[0]));
	if(self->cells == NULL)
	{
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_NOMEMORY, "Not enough memory for creating the buffer.");
	}

	self->n_rows = n_rows;
	self->n_columns = n_columns;

	FDC_ConsoleBufferVirtualCell (*cells)[self->n_rows][self->n_columns] = (void*)self->cells;
	for(size_t row = 0; row < self->n_rows; row++)
	{
		for(size_t column = 0; column < self->n_columns; column++)
		{
			(*cells)[row][column].grapheme[0] = ' ';
			(*cells)[row][column].grapheme_size = 1;
			memset((*cells)[row][column].rgb_fg, 0xFF, 3);
		}
	}

	return FDC_OK;
}

FDC_Error FDC_ConsoleBufferVirtual_setCellGrapheme(FDC_ConsoleBufferVirtual * self, size_t row, size_t column,
		size_t grapheme_size, char grapheme[grapheme_size])
{
	FDC_ConsoleBufferVirtualCell (*cells)[self->n_rows][self->n_columns] = (void*)self->cells;

	if(grapheme_size >= FDC_CONSOLE_GRAPHEME_MAX_LEN)
	{
		FDC_ERROR_RAISE(FDC_ERROR_PARAM, "Grapheme cluster has length %zu, but maximum grapheme length is %zu.",
				grapheme_size, FDC_CONSOLE_GRAPHEME_MAX_LEN);
	}

	memcpy((*cells)[row][column].grapheme, grapheme, grapheme_size);
	(*cells)[row][column].grapheme[grapheme_size] = '\0';

	(*cells)[row][column].grapheme_size = grapheme_size;

	return FDC_OK;
}

FDC_Error FDC_ConsoleBufferVirtual_setCellColors(FDC_ConsoleBufferVirtual * self, size_t row, size_t column, char rgb_bg[3], char rgb_fg[3])
{
	FDC_ConsoleBufferVirtualCell (*cells)[self->n_rows][self->n_columns] = (void*)self->cells;

	memcpy((*cells)[row][column].rgb_bg, rgb_bg, 3);
	memcpy((*cells)[row][column].rgb_fg, rgb_fg, 3);

	return FDC_OK;
}

FDC_Error FDC_ConsoleBufferVirtual_writeToConsole(FDC_ConsoleBufferVirtual * self, FDC_Console * console)
{
	/* TODO: Instead of errors, it could be possible to output the buffer and reset the space. That
	would cause a visible update, but its better than nothing. */

	FDC_ConsoleBufferVirtualCell (*cells)[self->n_rows][self->n_columns] = (void*)self->cells;

	char buffer[FDC_CONSOLE_PRINT_SEQUENCE_MAX_LEN];
	size_t used = 0;

	for(size_t row = 0; row < self->n_rows; row++)
	{
		// Position the cursor
		int len = snprintf(buffer + used, sizeof(buffer) - used,
				FDC_CONSOLE_ESCAPE_STR "[%zu;%zuH", row, (size_t)0);
		if(len < 0 || (size_t)len > sizeof(buffer) - used)
		{
			FDC_ERROR_RAISE(FDC_ERROR_PARAM, "Not enough buffer space for writing to the console. Used: %zu. Available: %zu. Required: %d",
					used, sizeof(buffer) - used, len);
		}
		used += len;

		for(size_t column = 0; column < self->n_columns; column++)
		{
			// Change background color if necessary
			char * rgb_bg = (*cells)[row][column].rgb_bg;
			len = snprintf(buffer + used, sizeof(buffer) - used,
					FDC_CONSOLE_ESCAPE_STR "[48;2;%d;%d;%dm", rgb_bg[0], rgb_bg[1], rgb_bg[2]);
			if(len < 0 || (size_t)len > sizeof(buffer) - used)
			{
				FDC_ERROR_RAISE(FDC_ERROR_PARAM, "Not enough buffer space for writing to the console. Used: %zu. Available: %zu. Required: %d",
						used, sizeof(buffer) - used, len);
			}
			used += len;

			// Change foreground color if necessary
			char * rgb_fg = (*cells)[row][column].rgb_fg;
			len = snprintf(buffer + used, sizeof(buffer) - used,
					FDC_CONSOLE_ESCAPE_STR "[38;2;%d;%d;%dm", rgb_fg[0], rgb_fg[1], rgb_fg[2]);
			if(len < 0 || (size_t)len > sizeof(buffer) - used)
			{
				FDC_ERROR_RAISE(FDC_ERROR_PARAM, "Not enough buffer space for writing to the console. Used: %zu. Available: %zu. Required: %d",
						used, sizeof(buffer) - used, len);
			}
			used += len;

			// Write grapheme
			if((*cells)[row][column].grapheme_size > sizeof(buffer) - used)
			{
				FDC_ERROR_RAISE(FDC_ERROR_PARAM, "Not enough buffer space for writing to the console. Used: %zu. Available: %zu. Required: %zu",
						used, sizeof(buffer) - used, (*cells)[row][column].grapheme_size);
			}

			memcpy(buffer + used, (*cells)[row][column].grapheme, (*cells)[row][column].grapheme_size);
			used += (*cells)[row][column].grapheme_size;
		}
	}

	return FDC_ConsoleBuffer_write(console->active_buffer, used, buffer);
}

FDC_Error FDC_Console_init(FDC_Console * self)
{
#ifdef _WIN32

	self->active_buffer = INVALID_HANDLE_VALUE;

	AllocConsole(); /* If this call fails, and the process does not have a
	                   console, CreateFileA will return an error */

	HANDLE hOut = CreateFileA(
		"CONOUT$",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL, /* Do not inherit */
		OPEN_EXISTING,
		0, /* Ignored */
		INVALID_HANDLE_VALUE /* Ignored */
	);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		//return GetLastError();
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to get console handle.");
	}
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		//return GetLastError();
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to get console mode.");
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		//return GetLastError();
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to set console mode");
	}

	self->active_buffer = hOut;

	return FDC_OK;

#else
	abort();
#endif
}

FDC_Error FDC_Console_destroy(FDC_Console * self)
{
#ifdef _WIN32

	CloseHandle(self->active_buffer);
	self->active_buffer = INVALID_HANDLE_VALUE;

	return FDC_OK;
#else
	abort();
#endif
}

FDC_Error FDC_Console_getActiveBuffer(FDC_Console * self, FDC_ConsoleBuffer ** buffer)
{
	*buffer = self->active_buffer;

	return FDC_OK;
}

FDC_Error FDC_ConsoleBuffer_write(FDC_ConsoleBuffer * self, size_t size, char text[size])
{
#ifdef _WIN32

	char16_t u16_buffer[FDC_STRING_U8_TO_U16_SIZE(size)];
	size_t u16_size;

	FDC_Error error = FDC_String_u8_to_u16(size, text, sizeof(u16_buffer), u16_buffer, &u16_size);
	if(error != FDC_OK)
	{
		return error;
	}

	if(!WriteConsoleW(self, u16_buffer, u16_size, NULL, NULL))
	{
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to write to the console buffer.");
	}

	return FDC_OK;
#else
	abort();
#endif
}


