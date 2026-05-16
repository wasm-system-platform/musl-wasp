#include <setjmp.h>

__asm__(
    ".globaltype __stack_pointer, i32\n"
);

int __env_save(jmp_buf env, unsigned long env_size)
    __attribute__((import_module("env"), import_name("save")));

int __env_save_ret;

int setjmp(jmp_buf env) {
    int save_ret;

    __env_save_ret = 0;

    __asm__ __volatile__(
        "global.get __stack_pointer\n"

        "local.get %1\n"
        "local.get %2\n"
		"local.get %3\n"
        "call_indirect (i32, i32) -> (i32)\n"
        "local.set %0\n"

        "global.set __stack_pointer\n"
        : "=r"(save_ret)
        : "r"(env->__jb), "r"(sizeof(__jmp_buf)), "r"(__env_save)
        : "memory"
    );

    if (save_ret != 0)
        __builtin_trap();

    return __env_save_ret;
}