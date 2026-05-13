#define _GNU_SOURCE
#include <string.h>
#include "pthread_impl.h"
#include "syscall.h"

hidden long __cancel()
{
	pthread_t self = __pthread_self();
	if (self->canceldisable == PTHREAD_CANCEL_ENABLE || self->cancelasync)
		pthread_exit(PTHREAD_CANCELED);
	self->canceldisable = PTHREAD_CANCEL_DISABLE;
	return -ECANCELED;
}

hidden long __syscall_cp_asm0(volatile void *, syscall_arg_t);
hidden long __syscall_cp_asm1(volatile void *, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_asm2(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_asm3(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_asm4(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_asm5(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_asm6(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);

long __syscall_cp_asm0(volatile void *, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm1(volatile void *, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm2(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm3(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm4(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm5(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }
long __syscall_cp_asm6(volatile void *, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t) { abort(); /* TODO */ }

hidden long __syscall_cp_c0(syscall_arg_t);
hidden long __syscall_cp_c1(syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_c2(syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_c3(syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_c4(syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_c5(syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);
hidden long __syscall_cp_c6(syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t, syscall_arg_t);

/* It's a TODO to handle this... */
/*
#define SYSCALL_CP_C(num, ...) do {\
		pthread_t self; \
		long r; \
		int st; \
		\
		if ((st=(self=__pthread_self())->canceldisable) \
			&& (st==PTHREAD_CANCEL_DISABLE || nr==SYS_close)) \
			return __syscall(__VA_ARGS__); \
		\
		r = __syscall_cp_asm##num(&self->cancel, __VA_ARGS__); \
		if (r==-EINTR && nr!=SYS_close && self->cancel && \
			self->canceldisable != PTHREAD_CANCEL_DISABLE) \
			r = __cancel(); \
		return r; \
	} while(0)
*/
#define SYSCALL_CP_C(num, ...) do {\
		return __syscall(__VA_ARGS__); \
	} while(0)

long __syscall_cp_c0(syscall_arg_t nr)
{
	SYSCALL_CP_C(0, nr);
}

long __syscall_cp_c1(syscall_arg_t nr, syscall_arg_t u)
{
	SYSCALL_CP_C(1, nr, u);
}

long __syscall_cp_c2(syscall_arg_t nr, syscall_arg_t u, syscall_arg_t v)
{
	SYSCALL_CP_C(2, nr, u, v);
}

long __syscall_cp_c3(syscall_arg_t nr, syscall_arg_t u, syscall_arg_t v, syscall_arg_t w)
{
	SYSCALL_CP_C(3, nr, u, v, w);
}

long __syscall_cp_c4(syscall_arg_t nr, syscall_arg_t u, syscall_arg_t v, syscall_arg_t w, syscall_arg_t x)
{
	SYSCALL_CP_C(4, nr, u, v, w, x);
}

long __syscall_cp_c5(syscall_arg_t nr, syscall_arg_t u, syscall_arg_t v, syscall_arg_t w, syscall_arg_t x, syscall_arg_t y)
{
	SYSCALL_CP_C(5, nr, u, v, w, x, y);
}

long __syscall_cp_c6(syscall_arg_t nr, syscall_arg_t u, syscall_arg_t v, syscall_arg_t w, syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
	SYSCALL_CP_C(6, nr, u, v, w, x, y, z);
}

static void _sigaddset(sigset_t *set, int sig)
{
	unsigned s = sig-1;
	set->__bits[s/8/sizeof *set->__bits] |= 1UL<<(s&8*sizeof *set->__bits-1);
}

extern hidden const char __cp_begin[1], __cp_end[1], __cp_cancel[1];

static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{
	pthread_t self = __pthread_self();
	ucontext_t *uc = ctx;
	uintptr_t pc;

	a_barrier();
	if (!self->cancel || self->canceldisable == PTHREAD_CANCEL_DISABLE) return;

	_sigaddset(&uc->uc_sigmask, SIGCANCEL);

	if (self->cancelasync) {
		pthread_sigmask(SIG_SETMASK, &uc->uc_sigmask, 0);
		__cancel();
	}

#ifdef MC_PC
	pc = uc->uc_mcontext.MC_PC;
	if (pc >= (uintptr_t)__cp_begin && pc < (uintptr_t)__cp_end) {
		uc->uc_mcontext.MC_PC = (uintptr_t)__cp_cancel;
#ifdef CANCEL_GOT
		uc->uc_mcontext.MC_GOT = CANCEL_GOT;
#endif
		return;
	}
#else
	/* TODO: handle this. */
	abort();
#endif

	__syscall(SYS_tkill, self->tid, SIGCANCEL);
}

void __testcancel()
{
	pthread_t self = __pthread_self();
	if (self->cancel && !self->canceldisable)
		__cancel();
}

static void init_cancellation()
{
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO | SA_RESTART | SA_ONSTACK,
		.sa_sigaction = cancel_handler
	};
	memset(&sa.sa_mask, -1, _NSIG/8);
	__libc_sigaction(SIGCANCEL, &sa, 0);
}

int pthread_cancel(pthread_t t)
{
	static int init;
	if (!init) {
		init_cancellation();
		init = 1;
	}
	a_store(&t->cancel, 1);
	if (t == pthread_self()) {
		if (t->canceldisable == PTHREAD_CANCEL_ENABLE && t->cancelasync)
			pthread_exit(PTHREAD_CANCELED);
		return 0;
	}
	return pthread_kill(t, SIGCANCEL);
}
