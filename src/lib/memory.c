#include "lib/memory.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "logger/logger.h"

#define M_HEAP_SIZE      2048
#define MAX_OBJ          64
#define M_POINTERS_SIZE  MAX_OBJ * 2

typedef uint16_t offset_t;  // Must be a type that holds M_HEAP_SIZE + 2

static char* Mem_GetStartPtr(int i);
static char* Mem_GetEndPtr(int i);

static void Mem_SetStartPtr(int i, char* ptr);
static void Mem_SetEndPtr(int i, char* ptr);

static void Mem_AddPtr(char* ptr, size_t size);

static char memory_[M_HEAP_SIZE];
static offset_t m_pointers_[M_POINTERS_SIZE] = { 0 };

void* Mem_Alloc(size_t size) {
	// First iteration is used for memory start.
	for (int i = -1; i < MAX_OBJ; i++) {
		// An end pointer is taken as the start.
		char* start_ptr = Mem_GetEndPtr(i);
		if (start_ptr == NULL) {
			continue;
		}
		// End ptr is an exclusive end.
		char* end_ptr = &memory_[M_HEAP_SIZE - 1] + 1;
		size_t free_space = end_ptr - start_ptr;
		// Find the first next taken area, and space between them.
		for (int j = 0; j < MAX_OBJ; j++) {
			char * next_start_ptr = Mem_GetStartPtr(j);
			if (next_start_ptr == NULL) {
				continue;
			}
			int offset = next_start_ptr - start_ptr;
			if (offset >= 0 && offset < free_space) {
				free_space = offset;
				end_ptr = next_start_ptr;
			}
		}

		// If the space is big enough, take it.
		if (free_space >= size) {
			Mem_AddPtr(start_ptr, size);
			return start_ptr;
		}
	}
	Logger_AtError("Could not find enough free space to alloc.");
	return NULL;
}

void Mem_Free(void* start_ptr) {
	if (start_ptr == NULL) {
		Logger_AtError("Pointer to free is null.");
	}
	for (int i = 0; i < MAX_OBJ; i++) {
		if (Mem_GetStartPtr(i) == start_ptr) {
			Mem_SetStartPtr(i, &memory_[0] - 1);
			Mem_SetEndPtr(i, &memory_[0] - 1);
			return;
		}
	}
	Logger_AtError("Cannot free a space not reserved.");
}

char* Mem_GetStartPtr(int i) {
	return m_pointers_[i * 2] + &memory_[0] - 1;
}

char* Mem_GetEndPtr(int i) {
	if (i == -1) {
		return &memory_[0];
	}
	return m_pointers_[i * 2 + 1] + &memory_[0] - 1;
}

void Mem_SetStartPtr(int i, char* ptr) {
	m_pointers_[i * 2] = ptr - &memory_[0] + 1;
}

void Mem_SetEndPtr(int i, char* ptr) {
	m_pointers_[i * 2 + 1] = ptr - &memory_[0] + 1;
}

void Mem_AddPtr(char* ptr, size_t size) {
	// Find first empty space in m_pointers_ array.
	int i = 0;
	while (i < MAX_OBJ) {
		if (!m_pointers_[i]) {
			break;
		}
		i += 2;
	}
	if (i >= MAX_OBJ) {
		Logger_AtError("Max number of objects supported in memory reached.");
		return;
	}
	Mem_SetStartPtr(i / 2, ptr);
	Mem_SetEndPtr(i / 2, ptr + size);
}

void Mem_Print() {
	// TODO: Implement printf?
	printf("Memory:");
	for (int i = 0; i < M_HEAP_SIZE; i++) {
		if (i % 100 == 0) {
			printf("\n");
		}
		printf("%c", memory_[i]);
	}
	printf("\n");
}

void Mem_PrintPtrs() {
	printf("Pointers:\n");
	for (int i = 0; i < MAX_OBJ; i++) {
		printf("%d\n", (m_pointers_[i] - 1));
	}
	printf("\n");
}

