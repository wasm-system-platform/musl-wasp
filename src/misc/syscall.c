#define _BSD_SOURCE
#include <unistd.h>
#include "syscall.h"
#include <stdarg.h>

#undef syscall

long syscall(long count, long n, ...)
{
	va_list ap;
	syscall_arg_t a,b,c,d,e,f;
	va_start(ap, n);
	switch (count) {
		case 0:
			va_end(ap);
			return __syscall_ret(__syscall(n));
		case 1:
			a =  va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a));
		case 2:
			a = va_arg(ap, syscall_arg_t);
			b = va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a, b));
		case 3:
			a = va_arg(ap, syscall_arg_t);
			b = va_arg(ap, syscall_arg_t);
			c = va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a, b, c));
		case 4:
			a = va_arg(ap, syscall_arg_t);
			b = va_arg(ap, syscall_arg_t);
			c = va_arg(ap, syscall_arg_t);
			d = va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a, b, c, d));
		case 5:
			a = va_arg(ap, syscall_arg_t);
			b = va_arg(ap, syscall_arg_t);
			c = va_arg(ap, syscall_arg_t);
			d = va_arg(ap, syscall_arg_t);
			e = va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a, b, c, d, e));
		case 6:
			a = va_arg(ap, syscall_arg_t);
			b = va_arg(ap, syscall_arg_t);
			c = va_arg(ap, syscall_arg_t);
			d = va_arg(ap, syscall_arg_t);
			e = va_arg(ap, syscall_arg_t);
			f = va_arg(ap, syscall_arg_t);
			va_end(ap);
			return __syscall_ret(__syscall(n, a, b, c, d, e, f));
		default:
			break;
	}
	va_end(ap);
	return -ENOSYS;
}
