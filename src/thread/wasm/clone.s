.globaltype __stack_pointer, i32
.globaltype __tls_base, i32
.functype __syscall1(i32, i32) -> (i32)
.functype __syscall5(i32, i32, i32, i32, i32, i32) -> (i32)

.globl __get_tls_base
__get_tls_base:
	.functype __get_tls_base() -> (i32)
	global.get __tls_base
	end_function

# The runtime expects to be able to set __tls_base as part of it's clone setup.
.globl __set_tls_base
__set_tls_base:
	.functype __set_tls_base(i32) -> ()
	local.get 0
	global.set __tls_base
	end_function

.globl _Clone
_Clone:
	# int _Clone(fn, stack, flags, arg, ptid, tls, ctid);
	#            0   1      2      3    4     5    6
	.functype _Clone(i32, i32, i32, i32, i32, i32, i32) -> (i32)
	.local i32 /* 7: child_stack */

	# We save fn+arg on the stack. There are two distincs cases for stack:
	# * stack is NULL: the kernel will in this special case copy the value
	#   of __stack_pointer to the new task. This means we should fill in fn
	#   and arg on our stack. This also implies that the caller uses
	#   CLONE_VFORK which pauses the calling task (or it does not care about
	#   the stack being corrupted in the caller, which is a very odd case).
	# * stack is not NULL: the kernel will in this case set the stack
	#   pointer of the new task to the value of the stack argument.
	#
	# In either case we don't really need to "allocate" space on these
	# stacks, but we do it anyway, should the syscall wrappers change in the
	# future to call C code. In that case we also need to align the stack.

	# If stack was NULL, store into __stack_pointer instead. The kernel will
	# in this special case copy the value of the stack pointer to the new
	# task in the clone syscall. (Allocating space on these stacks is not
	# strictly necessary but a nice thing if the syscall function changes
	# to a C function in the future - in that case we should also align the
	# stack to 16 bytes.) To be consistent, also allocate on non-NULL stack.
	block
		local.get 1
		br_if 0 # if (stack != NULL): break to block 0;
		# else if (stack == NULL):

		global.get __stack_pointer
		i32.const 16
		i32.sub
		local.tee 7
		global.set __stack_pointer
	end_block

	block
		local.get 1
		i32.eqz
		br_if 0 # if (stack == NULL): break to block 0;
		# else if (stack != NULL):

		local.get 1
		i32.const 16
		i32.sub
		local.tee 7
		local.set 1
	end_block

	/*
	 * At this point:
	 * local 1 contains the decremented stack address or NULL.
	 * local 7 contains the decremented stack address (never NULL).
	 * i.e. we don't pass the decremented __stack_pointer if stack == NULL.
	 */

	# Store fn at the lowest address.
	local.get 7
	local.get 0
	i32.store 0

	# Store arg at the next-lowest address.
	local.get 7
	i32.const 4
	i32.add
	local.get 3
	i32.store 0

	# syscall(SYS_clone, clone_flags, newsp, parent_tidptr, child_tidptr, tls)
	i32.const 220 # SYS_clone
	local.get 2 # clone_flags
	local.get 1 # newsp (maybe NULL)
	local.get 4 # ptid
	local.get 6 # ctid
	local.get 5 # tls
	call __syscall5

	# TODO: the following comment is wrong now.
	# On Wasm, we don't end up returning twice - instead wasm_clone_callback
	# is called and we can extract fn and arg from __stack_pointer. This
	# means that we for sure currently are in the parent when returning.

	block
		local.get 1
		br_if 0 # if (stack != NULL): break to block 0;
		# else if(stack == NULL):

		global.get __stack_pointer
		i32.const 16
		i32.add
		global.set __stack_pointer
	end_block

	# (Pass on return value from the above syscall to the caller.)
	end_function
