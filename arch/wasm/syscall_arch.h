#define __SYSCALL_LL_E(x) \
((union { long long ll; long l[2]; }){ .ll = x }).l[0], \
((union { long long ll; long l[2]; }){ .ll = x }).l[1]
#define __SYSCALL_LL_O(x) __SYSCALL_LL_E((x))

extern long __syscall0(long n);
extern long __syscall1(long n, long a);
extern long __syscall2(long n, long a, long b);
extern long __syscall3(long n, long a, long b, long c);
extern long __syscall4(long n, long a, long b, long c, long d);
extern long __syscall5(long n, long a, long b, long c, long d, long e);
extern long __syscall6(long n, long a, long b, long c, long d, long e, long f);
