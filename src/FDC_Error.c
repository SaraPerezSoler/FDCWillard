#include "FDC_Error.h"

const FDC_Error * FDC_ERROR_LIST = NULL;

const FDC_Error * const FDC_OK = NULL;
FDC_ERROR_CREATE(FDC_UNKNOWN, u8"Unknown error", NULL);
FDC_ERROR_CREATE(FDC_NOMEMORY, u8"Not enough memory", NULL);
