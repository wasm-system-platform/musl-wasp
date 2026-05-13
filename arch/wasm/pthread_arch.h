#include <stdint.h>

/*
 * Wasm (as compiled with LLVM) handles TLS data directly, instead of the
 * indirect approach used for ELF targets (where musl manages all TLS). There is
 * still a pthread TLS area to keep track of, and musl manages that by these
 * functions. In other words, __musl_tp will point to a struct pthread.
 */

extern _Thread_local uintptr_t __musl_tp;

static inline uintptr_t __get_tp(void)
{
	return __musl_tp;
}
