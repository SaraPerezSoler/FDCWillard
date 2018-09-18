/*
 * FDC_Error.h
 *
 *  Created on: 18 sept. 2018
 *      Author: Carlos
 */

#ifndef INCLUDE_FDC_ERROR_H_
#define INCLUDE_FDC_ERROR_H_

#include <stddef.h>

/**
 * @brief Compact representation of an error.
 */
typedef struct FDC_Error {
	char * id; //!< Error id.
	char * name; //!< Error display name.
	const struct FDC_Error * parent; //!< Parent of the error.
	const struct FDC_Error * next; //!< Next error in the nested list of errors.
} FDC_Error;

/**
 * @brief List of every error.
 */
extern const FDC_Error * FDC_ERROR_LIST;

/**
 * @brief Iterate a variable for every error.
 */
#define FOREACH_ERROR(NAME) for(const FDC_Error * NAME = FDC_ERROR_LIST; NAME != NULL; NAME = NAME->next)

/**
 * @brief Macro for defining new error types.
 */
#define FDC_ERROR_CREATE(ID, NAME, PARENT) \
	static FDC_Error ID ## _struct = {.id=#ID, .name=NAME, .parent=PARENT}; \
	const FDC_Error * const ID = &ID ## _struct; \
	__attribute__((constructor)) \
	static void ID ## _constructor() \
	{ \
		ID ## _struct.next = FDC_ERROR_LIST; \
		FDC_ERROR_LIST = ID; \
	}

extern const FDC_Error * const FDC_OK; //!< No error has occurred.
extern const FDC_Error * const FDC_UNKNOWN; //!< Unknown error.
extern const FDC_Error * const FDC_NOMEMORY; //!< No memory error.

#endif /* INCLUDE_FDC_ERROR_H_ */
