struct wapix_string {
  unsigned len;
  char data[];
};

struct wapix_list_string {
  unsigned count;
  char data[];
};

__attribute__((import_module("env"), import_name("args_size_get")))
int args_size_get(unsigned* num_args, unsigned* size);

__attribute__((import_module("env"), import_name("args_get")))
int args_get(struct wapix_list_string *buffer);

__attribute__((import_module("env"), import_name("env_size_get")))
int env_size_get(unsigned* num_envptrs, unsigned* size);

__attribute__((import_module("env"), import_name("env_get")))
int env_get(struct wapix_list_string *buffer);
