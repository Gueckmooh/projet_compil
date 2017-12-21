	.bss
	.align	4
	.type	__min_caml_array, %object
	.size	__min_caml_array, 4
__min_caml_array:
	.space	4096
	.text
	.align	2
	.global __mem_init
	.type 	__mem_init, %function
__mem_init:
	ldr 	r4, .__min_caml_array_addr
	ldr 	r4, [r4]
	mov 	r5, r4
	bx	lr
.__min_caml_array_addr:
	.word 	__min_caml_array
	.align 	2
	.global	__mem_new
	.type 	__mem_new, %function
__mem_new:
	str 	fp, [sp, #4]!
	add 	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	mov 	r2, r5
	ldr  	r3, [fp, #-8]
	add	r2, r2, r3
	cmp 	r2, #4096
	bge	.M1
	mov 	r0, r5
	add 	r5, r5, r3
	b	.M2
.M1:
	mov 	r0, #0
.M2:
	sub	sp, fp, #0
	ldr	fp, [sp], #4
	bx 	lr
