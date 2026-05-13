typedef unsigned long __jmp_buf[64];

struct __jmp_buf_tag;
int sigsetjmp(struct __jmp_buf_tag*, int) __attribute__((import_module("env"), import_name("sigsetjmp")));
