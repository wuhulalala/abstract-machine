#include "stdio_impl.h"
#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#pragma GCC diagnostic ignored "-Wunused-variable"
struct iovec {
    void *iov_base;	/* Pointer to data.  */
    size_t iov_len;	/* Length of data.  */
};

size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
	struct iovec iovs[2] = {
		{ .iov_base = f->wbase, .iov_len = f->wpos-f->wbase },
		{ .iov_base = (void *)buf, .iov_len = len }
	};
	struct iovec *iov = iovs;
	size_t rem = iov[0].iov_len + iov[1].iov_len;
	int iovcnt = 2;
	int cnt;
    char *io = (char*)iov[0].iov_base;
    for (int i = 0; i < iov[0].iov_len; i++) {
        putch(io[i]);
    }
    io = (char*)iov[1].iov_base;
    for (int i = 0; i < iov[1].iov_len; i++) {
        putch(io[i]);
    }
    f->wend = f->buf + f->buf_size;
    f->wpos = f->wbase = f->buf;
    return len;
}
