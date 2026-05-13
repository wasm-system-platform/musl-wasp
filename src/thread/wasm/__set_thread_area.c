#include "pthread_impl.h"

_Thread_local uintptr_t __musl_tp = 0U;

int __set_thread_area(void *p)
{
	__musl_tp = (uintptr_t)p;
	return 0;
}
