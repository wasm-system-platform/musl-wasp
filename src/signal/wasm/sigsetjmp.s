.globaltype __stack_pointer, i32

.export_name __sigsetjmp_prologue, sigsetjmp_prologue
.export_name __sigsetjmp_epilogue, sigsetjmp_epilogue

.functype __sigsetjmp_tail(i32, i32) -> (i32)

.section	.text.__sigsetjmp_prologue,"",@
.hidden __sigsetjmp_prologue
.globl  __sigsetjmp_prologue
.type	__sigsetjmp_prologue,@function
__sigsetjmp_prologue:
    .functype __sigsetjmp_prologue(i32, i32) -> ()

    /* store stackpointer in __jb[0] */ 
    local.get 0
    global.get __stack_pointer
    i32.store 0

    /* store savesigs in __jb[1] */
    local.get 0
    local.get 1
    i32.store 4

    end_function

.hidden __sigsetjmp_epilogue
.globl  __sigsetjmp_epilogue
.type	__sigsetjmp_epilogue,@function
__sigsetjmp_epilogue:
    .functype __sigsetjmp_epilogue(i32, i32) -> ()

    /* restore stackpointer from __jb[0] */
    local.get 0
    i32.load 0
    global.set __stack_pointer

    /* load savesigs from __jb[1] */
    local.get 0
    i32.load 4
    
    if
        local.get 0
        local.get 1
        call __sigsetjmp_tail
        drop
    end_if

    end_function
