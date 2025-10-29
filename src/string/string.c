// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	size_t n = strlen(source);
	size_t i = 0;
	while (i < n) {
		*(destination + i) = *(source + i);
		i++;
	}
	*(destination + n) = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	size_t i = 0;
	while (i <= len) {
		*(destination + i) = *(source + i);
		i++;
	}
	*(destination + len + 1) = '\0';
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	size_t n = strlen(source);
	size_t m = strlen(destination);
	size_t i = 0;
	while (i < n) {
		*(destination + i + m) = *(source + i);
		i++;
	}
	*(destination + n + m) = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	size_t m = strlen(destination);
	size_t n = strlen(source);
	size_t i = 0;
	if (len <= n) {
		while (i <= len)
		{
			*(destination + i + m) = *(source + i);
			i++;
		}
		*(destination + len + m) = '\0';
	} else {
		while (i <= n) {
			*(destination + i + m) = *(source + i);
			i++;
		}
		while (i <= len) {
			*(destination + i + m) = '\n';
			i++;
		}
		*(destination + len + m) = '\0';
	}
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	size_t i = 0;
	while (str1[i] == str2[i]) {
		if (str1[i] == '\0' && str1[i] == '\0')
			return 0;
		i++;
	}
	return str1[i] - str2[i];
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	size_t i = 0;
	while (str1[i] == str2[i] && i < len) {
		if (str1[i] == '\0' && str1[i] == '\0')
			return 0;
		i++;
	}
	if (i < len)
		return str1[i] - str2[i];
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	size_t n = strlen(str);
	size_t i = 0;
	while (i < n) {
		if (*(str + i) == c)
			return (char *)(str + i);
		i++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	size_t n = strlen(str);
	size_t i = 0;
	char *ap = NULL;
	while (i < n) {
		if (*(str + i) == c)
			ap = (char *)(str + i);
		i++;
	}
	return ap;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	size_t n = strlen(haystack);
	size_t m = strlen(needle);
	size_t i = m;
	while (i < n) {
		if (!strncmp(haystack + i - m, needle, m))
			return (char *)(haystack + i - m);
		i++;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	size_t n = strlen(haystack);
	size_t m = strlen(needle);
	size_t i = m;
	char *ap = NULL;
	while (i < n) {
		if (!strncmp(haystack + i - m, needle, m))
			ap = (char *)(haystack + i - m);
		i++;
	}
	return ap;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	// am apelat strncpy pentru ca face acelasi lucru si oricum trebuie sa ii fac cast la char*
	strncpy(destination, source, num);
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	// am apelat strncpy pentru ca face acelasi lucru si oricum trebuie sa ii fac cast la char*
	strncpy(destination, source, num);
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	// am apelat strncmp pentru ca face acelasi lucru si oricum trebuie sa ii fac cast la char*
	return strncmp(ptr1, ptr2, num);
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	size_t i = 0;
	while (i < num) {
		*(char *)(source + i) = value;
		i++;
	}
	return source;
}
