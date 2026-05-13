.globl setjmp
setjmp:
	.functype setjmp(i32) -> ()
	# We allow this, but do nothing. longjmp() is forbidden though.
	end_function
