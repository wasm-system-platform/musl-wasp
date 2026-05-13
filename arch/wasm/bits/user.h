struct user_regs_struct {
	unsigned long stack_pointer;
	unsigned long tls;
};

typedef unsigned long elf_greg_t;
typedef struct user_regs_struct elf_gregset_t;
#define ELF_NGREG (sizeof(elf_gregset_t) / sizeof(elf_greg_t))
