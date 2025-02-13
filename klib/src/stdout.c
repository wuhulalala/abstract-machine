#include "stdio_impl.h"

#undef stdout

static unsigned char buf[BUFSIZ+UNGET];
FILE __stdout_FILE = {
	.buf = buf+UNGET,
	.buf_size = sizeof buf-UNGET,
	.fd = 1,
	.flags = F_PERM | F_NORD,
	.lbf = '\n',
	.write = __stdout_write,
	.lock = -1,
};
FILE *const stdout = &__stdout_FILE;