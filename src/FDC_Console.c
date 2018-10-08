/**
 * @file
 * @brief Console object.
 */

#include "FDC_Console.h"
#include "FDC_String.h"
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

	CloseHandle(self->active_buffer);
	self->active_buffer = INVALID_HANDLE_VALUE;

	return FDC_OK;
#else
	abort();
#endif
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
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "Unable to write to the console buffer");
	}

	return FDC_OK;
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


