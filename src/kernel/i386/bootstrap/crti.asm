section .init
global _init:function (_init.end - _init)
bits 32
_init:
	push ebp
	mov ebp, esp
	;/* gcc will nicely put the contents of crtbegin.o's .init section here. */
.end:

section .fini
global _fini:function (_fini.end - _fini)
bits 32
_fini:
	push ebp
	mov ebp, esp
	;/* gcc will nicely put the contents of crtbegin.o's .fini section here. */
.end:    