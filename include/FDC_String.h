

#ifndef INCLUDE_FDC_STRING_H_
#define INCLUDE_FDC_STRING_H_

#include "FDC_Error.h"

#if __has_include(<uchar.h>)
#include <uchar.h>
#else
#include <stdint.h>
#define char16_t uint16_t
#endif

#define FDC_STRING_U8_TO_U16_SIZE(UTF8_SIZE) UTF8_SIZE

FDC_Error FDC_String_u8_to_u16(size_t u8_size, char u8[u8_size], size_t u16_buffer_size, char16_t u16_buffer[u16_buffer_size], size_t * u16_size);

#endif /* INCLUDE_FDC_STRING_H_ */
