#include <setjmp.h>

extern int __sigsetjmp_tail(sigjmp_buf env, int ret);

int sigsetjmp(sigjmp_buf env, int savesigs) {
    int ret = setjmp(env);

    if (!savesigs)
        return ret;

    return __sigsetjmp_tail(env, ret);
}
