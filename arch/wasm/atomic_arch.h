#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
	__atomic_compare_exchange_n(p, &t, s, (_Bool)0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
	return t;
}

#define a_crash a_crash
static inline void a_crash()
{
	__builtin_trap();
	__builtin_unreachable();
}
