#include <setjmp.h>

void __longjmp(jmp_buf, int status) __attribute__((import_module("env"), import_name("longjmp")));

_Noreturn void longjmp(jmp_buf jb, int status) {
    __longjmp(jb, status);
    __builtin_unreachable();
}

extern void __sigsetjmp_prologue(jmp_buf jb, int status);
extern void __sigsetjmp_epilogue(jmp_buf jb, int ret);

hidden void *__dummy_sigsetjmp_prologue_ref = __sigsetjmp_prologue;
hidden void *__dummy_sigsetjmp_epilogue_ref = __sigsetjmp_epilogue;
