#ifndef LIB_MEMORY_H_
#define LIB_MEMORY_H_

#include <stddef.h>

/* Alloc a portion of memory of the given size. */
void* Mem_Alloc(size_t size);

/* Free the corresponding portion of memory that starts at `start_ptr`. */
void Mem_Free(void* start_ptr);

/* Debugging function to show pointers list. */
void Mem_PrintPtrs();

/* Debugging function to show all reserved memory. */
void Mem_Print();

#endif  // LIB_MEMORY_H_
