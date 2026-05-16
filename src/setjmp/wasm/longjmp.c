#include <setjmp.h>

__attribute__((noreturn))
int __env_restore(jmp_buf env, unsigned long env_size)
    __attribute__((import_module("env"), import_name("restore")));

extern int __env_save_ret;

void longjmp(jmp_buf env, int val) {
    __env_save_ret = val == 0 ? 1 : val;
    __env_restore(env->__jb, sizeof(__jmp_buf));
    __builtin_unreachable();
}
