// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	size_t *addr = mmap(0, size + sizeof(size_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	*addr = size + sizeof(size_t);
	return (void *)(addr + 1);
}

void *calloc(size_t nmemb, size_t size)
{
	void *addr = malloc(nmemb * size);
	memset(addr, 0, nmemb * size);
	return addr;
	/* TODO: Implement calloc(). */
}

void free(void *ptr)
{
	size_t *addr = (size_t *)ptr - 1;
	size_t len = *addr;
	munmap(addr, len);
	/* TODO: Implement free(). */
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	size_t *adr = (size_t *)ptr - 1;
	void *p = malloc(size);
	memcpy(p, ptr, *adr);
	return p;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return realloc(ptr, nmemb * size);
}
