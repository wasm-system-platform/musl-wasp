.globaltype __stack_pointer, i32
.globaltype __tls_base, i32
.functype __syscall0(i32) -> (i32)

.globl __restore_rt
.hidden __restore_rt
__restore_rt:
	.functype __restore_rt() -> ()

	i32.const 139 # SYS_rt_sigreturn
	call __syscall0
	unreachable

	end_function

.globl __restore
.hidden __restore
__restore:
	.functype __restore() -> ()

	call __restore_rt

	end_function

/* TODO: Move this to a better place... */
.globl __libc_handle_signal
__libc_handle_signal:
	.functype __libc_handle_signal() -> ()
	/* 0: sig_param */
	/* 1: info_param */
	/* 2: uc_param */
	/* 3: sa_handler */
	.local i32, i32, i32, i32

	/* sig_param */
	global.get __stack_pointer
	i32.load 0
	/*
	 * LLVM complains for some reason if we leave this on the Wasm stack. We
	 * put it in a local instead and then everything works, somehow...
	 */
	local.set 0

	/* info_param */
	global.get __stack_pointer
	i32.const 4
	i32.add
	i32.load 0
	local.set 1

	/* uc_param */
	global.get __stack_pointer
	i32.const 8
	i32.add
	i32.load 0
	local.set 2

	/* sa_handler */
	global.get __stack_pointer
	i32.const 12
	i32.add
	i32.load 0
	local.set 3

	/* (__stack_pointer is already 16-byte aligned by the kernel.) */

	/* !SA_SIGINFO */
	block
		local.get 1
		br_if 0

		local.get 0 /* sig_param */
		local.get 3 /* sa_handler cast to handler */
		/* handler(sig) */
		call_indirect (i32) -> ()
	end_block

	/* SA_SIGINFO */
	block
		local.get 1
		i32.eqz
		br_if 0

		local.get 0 /* sig _param*/
		local.get 1 /* info_param */
		local.get 2 /* uc_param */
		local.get 3 /* sa_handler cast to sigaction */
		/* sigaction(sig_param, info_param, uc_param) */
		call_indirect (i32, i32, i32) -> ()
	end_block

	call __restore_rt
	unreachable

	end_function
