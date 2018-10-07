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
 * @brief Size of the memory reserved for each thread error messages.
 */
#define FDC_ERROR_MEMORY_SIZE 1024

/**
 * @brief Compact representation of an error.
 */
typedef struct FDC_Error {
	char * id; //!< Error id.
	char * name; //!< Error display name.
	const struct FDC_Error * parent; //!< Parent of the error.
	const struct FDC_Error * next; //!< Next error in the nested list of errors.
} FDC_ErrorStruct;

/**
 * @brief Actual error returned by functions.
 */
typedef const FDC_ErrorStruct * FDC_Error;

/**
 * @brief Struct for composing error messages.
 */
typedef struct {
	char buffer[FDC_ERROR_MEMORY_SIZE]; //!< Buffer holding the memory.
	size_t size_used; //!< Memory size used.
} FDC_ErrorMessage;

/**
 * @brief List of every error.
 */
extern FDC_Error FDC_ERROR_LIST;

/**
 * @brief Iterate a variable for every error.
 */
#define FDC_FOREACH_ERROR(NAME) for(FDC_Error NAME = FDC_ERROR_LIST; NAME != NULL; NAME = NAME->next)

/**
 * @brief Macro for defining new error types.
 */
#define FDC_ERROR_CREATE(ID, NAME, PARENT) \
	static FDC_ErrorStruct ID ## _struct = {.id=#ID, .name=NAME, .parent=PARENT}; \
	const FDC_Error ID = &ID ## _struct; \
	__attribute__((constructor)) \
	static void ID ## _constructor() \
	{ \
		ID ## _struct.next = FDC_ERROR_LIST; \
		FDC_ERROR_LIST = ID; \
	}

/**
 * @brief Memory used for error messages.
 */
extern _Thread_local FDC_ErrorMessage FDC_error_message;

extern const FDC_Error FDC_OK; //!< No error has occurred.
extern const FDC_Error FDC_ERROR_UNKNOWN; //!< Unknown error.
extern const FDC_Error FDC_ERROR_NOMEMORY; //!< No memory error.

/**
 * @brief Clean the error message.
 *
 * @param self Memory to clean. If NULL, is the thread-local one.
 */
void FDC_ErrorMessage_clean(FDC_ErrorMessage * self);

/**
 * @brief Append a text to an error message.
 *
 * @param self Message to append text to. If NULL, is the thread-local one.
 * @param msg_size Size of the message.
 * @param msg Message.
 */
void FDC_ErrorMessage_append(FDC_ErrorMessage * self, size_t msg_size, char msg[msg_size]);

/**
 * @brief Raise an error.
 */
#define FDC_ERROR_RAISE(ERROR, SIZE, MSG) \
		do { \
			FDC_ErrorMessage_clean(NULL); \
			FDC_ErrorMessage_append(NULL, SIZE, MSG);\
			return ERROR; \
		} while(0)

/**
 * @brief Raise an error with a literal msg.
 */
#define FDC_ERROR_RAISE_LITERAL(ERROR, MSG) \
		FDC_ERROR_RAISE(ERROR, sizeof(MSG), MSG)

#endif /* INCLUDE_FDC_ERROR_H_ */
