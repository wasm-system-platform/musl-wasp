#define LDSO_ARCH "wasm"

#define TPOFF_K 0

#define REL_SYMBOLIC    R_WASM_64
#define REL_PLT         R_WASM_JUMP_SLOT
#define REL_RELATIVE    R_WASM_RELATIVE
#define REL_COPY        R_WASM_COPY
#define REL_DTPMOD      R_WASM_TLS_DTPMOD64
#define REL_DTPOFF      R_WASM_TLS_DTPREL64
#define REL_TPOFF       R_WASM_TLS_TPREL64

#define CRTJMP(pc,sp) abort()
