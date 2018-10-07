/**
 * @file
 * @brief Console object.
 */

#include "FDC_Console.h"
#include <stdio.h>
#ifdef _WIN32
#include "windows.h"

// MinGW does not have this flag
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

FDC_Error FDC_Console_init(FDC_Console * self)
{
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		//return GetLastError();
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to get console handle");
	}
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		//return GetLastError();
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to get console mode");
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
#else
	abort();
#endif
}

FDC_Error FDC_ConsoleBuffer_write(FDC_ConsoleBuffer * self, size_t size, char text[size])
{
#ifdef _WIN32
	//WriteConsole();
#else
	abort();
#endif
}

FDC_Error FDC_ConsoleBuffer_setCursorPosition(FDC_Console * self, size_t x, size_t y)
{
	printf(FDC_CONSOLE_ESCAPE_STR "[%zu;%zuH", x + 1, y + 1);
	return FDC_OK;

#ifdef _WIN32
	COORD coords = {.X=x, .Y=y};
	BOOL err = SetConsoleCursorPosition(self->secondary_buffer, coords);
	if(err)
	{
		return FDC_ERROR_UNKNOWN;
	}
	else
	{
		return FDC_OK;
	}
#else
	abort();
#endif
}


