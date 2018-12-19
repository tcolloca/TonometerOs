/**
 * GENERAL UTILITY FUNCTIONS.
 */
#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <stdlib.h>

/* Macros to set and clear a bit from a register */

#define SET(reg, bit) 	            reg |= (1 << bit)
#define SET_MASK(reg, mask)         reg |= mask
#define CLEAR(reg, bit)    		    reg &= ~(1 << bit)
#define CLEAR_MASK(reg, mask)       reg &= ~mask

/* Macros to check if a bit from a register is set or clear */

#define IS_SET(reg, bit)    (reg & (1 << bit))
#define IS_CLEAR(reg, bit)  (!IS_SET(reg, bit))

/* OOP utils */

#define NEW(type)  ((type *) malloc(sizeof(type)))
#define FREE(ptr)  (free(ptr))

/* Array utils */

#define LENGTH(array)  sizeof(array)/sizeof(array[0])

/* Other utils */

/* Returns the max unsigned value that fits into the variable. */
#define MAX_UVALUE(var) (((size_t) (1 << (8 * sizeof(var) - 1))) \
	                     | (((size_t) (1 << (8 * sizeof(var) - 1)) - 1)))

/* Concatenate two strings */
#define CAT(x, y) CAT_(x, y)
#define CAT_(x, y) x ## y

#endif  // UTIL_UTIL_H_
