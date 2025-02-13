#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <stdio_impl.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int vfprintf(FILE *restrict f, const char *restrict fmt, va_list ap);
int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap);


int printf(const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return ret;
}


int vsprintf(char *out, const char *fmt, va_list ap)
{
	return vsnprintf(out, INT_MAX, fmt, ap);
}

int sprintf(char *out, const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vsprintf(out, fmt, ap);
	va_end(ap);
	return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vsnprintf(out, n, fmt, ap);
	va_end(ap);
	return ret;
}



#endif
