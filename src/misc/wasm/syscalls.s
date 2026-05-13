.functype __wasm_syscall(i32, i32, i32, i32, i32, i32, i32) -> (i32)
.import_module	__wasm_syscall, sys
.import_name	__wasm_syscall, call

#define haxx

.globl __syscall0
.hidden __syscall0
__syscall0:
	.functype __syscall0(i32) -> (i32)

	local.get 0
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall1
.hidden __syscall1
__syscall1:
	.functype __syscall1(i32, i32) -> (i32)

	local.get 0
	local.get 1
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall2
.hidden __syscall2
__syscall2:
	.functype __syscall2(i32, i32, i32) -> (i32)

	local.get 0
	local.get 1
	local.get 2
	i32.const 0
	i32.const 0
	i32.const 0
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall3
.hidden __syscall3
__syscall3:
	.functype __syscall3(i32, i32, i32, i32) -> (i32)

	local.get 0
	local.get 1
	local.get 2
	local.get 3
	i32.const 0
	i32.const 0
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall4
.hidden __syscall4
__syscall4:
	.functype __syscall4(i32, i32, i32, i32, i32) -> (i32)

	local.get 0
	local.get 1
	local.get 2
	local.get 3
	local.get 4
	i32.const 0
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall5
.hidden __syscall5
__syscall5:
	.functype __syscall5(i32, i32, i32, i32, i32, i32) -> (i32)

	local.get 0
	local.get 1
	local.get 2
	local.get 3
	local.get 4
	local.get 5
	i32.const 0

	call __wasm_syscall

	end_function

.globl __syscall6
.hidden __syscall6
__syscall6:
	.functype __syscall6(i32, i32, i32, i32, i32, i32, i32) -> (i32)

	local.get 0
	local.get 1
	local.get 2
	local.get 3
	local.get 4
	local.get 5
	local.get 6

	call __wasm_syscall

	end_function
