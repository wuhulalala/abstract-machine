#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  const char *a = s;
  for (; *s; s++);
  return s-a;
}

size_t strnlen(const char *s, size_t n) {
  const char *a = s;
  for (; *s; s++);
  if (s - a <= n) return s - a;
  return n;
}
char *strcpy(char *dst, const char *src) {
  char* a = dst;	
  for (; (*dst=*src); src++, dst++){}
  return a;
}

char *strncpy(char *dst, const char *src, size_t n) {
	char *a = dst;
  for (; n && (*dst=*src); n--, src++, dst++){}
	memset(dst, 0, n);
	return a;
}

char *strcat(char *dst, const char *src) {
  strcpy(dst + strlen(dst), src);
	return dst;
}

int strcmp(const char *s1, const char *s2) {
  for (; *s1==*s2 && *s1; s1++, s2++){}
	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  const unsigned char *l=(void *)s1, *r=(void *)s2;
	if (!n--) return 0;
	for (; *l && *r && n && *l == *r ; l++, r++, n--){};
	return *l - *r;
}

void *memset(void *src, int c, size_t n) {
  unsigned char *s = src;

	/* Fill head and tail with minimal branching. Each
	 * conditional ensures that all the subsequently used
	 * offsets are well-defined and in the dest region. */

	if (!n) return src;
	s[0] = c;
	s[n-1] = c;
	if (n <= 2) return src;
	s[1] = c;
	s[2] = c;
	s[n-2] = c;
	s[n-3] = c;
	if (n <= 6) return src;
	s[3] = c;
	s[n-4] = c;
	if (n <= 8) return src;

	for (; n; n--, s++) *s = c;
	return src;
}

void *memmove(void *dst, const void *src, size_t n) {
  char *d = dst;
	const char *s = src;

	if (d==s) return d;
	if ((uintptr_t)s-(uintptr_t)d-n <= -2*n) return memcpy(d, s, n);

	if (d<s) {
		for (; n; n--) *d++ = *s++;
	} else {
		while (n) n--, d[n] = s[n];
	}

	return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *d = out;
	const unsigned char *s = in;
	for (; n; n--) *d++ = *s++;
	return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *l=s1, *r=s2;
	for (; n && *l == *r; n--, l++, r++){}
	return n ? *l-*r : 0;
}

#endif
