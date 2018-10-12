#include "FDC_Error.h"
#include <stdio.h>
#include <string.h>

_Thread_local FDC_ErrorMessage FDC_error_message;

FDC_Error FDC_ERROR_LIST = NULL;

const FDC_Error FDC_OK = NULL;
FDC_ERROR_CREATE(FDC_ERROR_UNKNOWN, u8"Unknown error", NULL);
FDC_ERROR_CREATE(FDC_ERROR_NOMEMORY, u8"Not enough memory", NULL);
FDC_ERROR_CREATE(FDC_ERROR_PARAM, u8"Invalid parameter", NULL);

void FDC_ErrorMessage_clean(FDC_ErrorMessage * self)
{
	if(self == NULL)
	{
		self = &FDC_error_message;
	}

	self->size_used = 0;
	self->buffer[0] = '\0';
}

void FDC_ErrorMessage_append(FDC_ErrorMessage * self, size_t msg_size, char msg[msg_size])
{
	if(self == NULL)
	{
		self = &FDC_error_message;
	}

	size_t new_size = self->size_used + msg_size;

	if(new_size >= FDC_ERROR_MEMORY_SIZE)
	{
		fprintf(stderr, "Error message too big\n");
		return;
	}

	memcpy(self->buffer + self->size_used, msg, msg_size);
	self->buffer[new_size] = '\0';

	self->size_used = new_size;
}

void FDC_ErrorMessage_vappendFormatted(FDC_ErrorMessage * self, char * format_str, va_list v)
{
	va_list v_copy;

	va_copy(v_copy, v);

	int len = vsnprintf(NULL, 0, format_str, v);
	if(len < 0)
	{
		fprintf(stderr, "Error in vsnprintf\n");
		va_end(v_copy);
		return;
	}

	char buffer[len+1];
	vsnprintf(buffer, len+1, format_str, v_copy);

	va_end(v_copy);

	FDC_ErrorMessage_append(self, len, buffer);
}

void FDC_ErrorMessage_appendFormatted(FDC_ErrorMessage * self, char * format_str, ...)
{
	va_list v;

	va_start(v, format_str);
	FDC_ErrorMessage_vappendFormatted(self, format_str, v);
	va_end(v);
}
