#include "wapix.h"

#define WASM_PAGE_SIZE (0x10000L)

int __main_argc_argv(int argc, char *argv[]);

int main(int argc, char *argv[], char *envp[])
{
    (void)envp;
    return __main_argc_argv(argc, argv);
}

__attribute__((import_module("sys"), import_name("execve_stack")))
void * __execve_stack();

__attribute__((export_name("_start")))
void _start () {
    

#ifndef SHARED
    void _start_c();
    _start_c((long *)__execve_stack());
#else
    void _dlstart_c();
    _dlstart_c((long *)__execve_stack());
#endif
}
