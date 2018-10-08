
#include "FDC_String.h"

#ifdef _WIN32
#include <windows.h>
#endif

FDC_Error FDC_String_u8_to_u16(size_t u8_size, char u8[u8_size], size_t u16_buffer_size, char16_t u16_buffer[u16_buffer_size], size_t * u16_size)
{
	*u16_size = 0;

#ifdef _WIN32
	int required_size = MultiByteToWideChar(
		CP_UTF8,
		MB_ERR_INVALID_CHARS,
		u8, u8_size,
		u16_buffer, u16_buffer_size
	);
	if(required_size == 0)
	{
		FDC_ERROR_RAISE_LITERAL(FDC_ERROR_UNKNOWN, "UTF8 to UTF16 conversion error");
	}

	*u16_size = required_size;

	return FDC_OK;
#else
	abort();
#endif
}

