	.file	"button_press.c"
.text
	.balign 2
	.global	button_press
	.type	button_press, @function
button_press:
; start of function
; framesize_regs:     0
; framesize_locals:   2
; framesize_outgoing: 0
; framesize:          2
; elim ap -> fp       2
; elim fp -> sp       2
; saved regs:(none)
	; start of prologue
	SUB.W	#2, R1
	; end of prologue
	MOV.W	R12, @R1
	MOV.W	&state, R12
	CMP.W	#1, R12 { JEQ	.L2
	CMP.W	#0, R12 { JEQ	.L8
	BR	#.L10
.L2:
	MOV.W	&light+8, R12
	CMP.W	#2016, R12 { JNE	.L6
	MOV.W	@R1, R12
	CALL	#check_player_move
	BR	#.L9
.L6:
	MOV.W	&light+8, R12
	CMP.W	#31, R12 { JNE	.L9
	MOV.W	#2, &state
	MOV.W	@R1, R12
	CALL	#check_red_move
	MOV.W	R12, &to_shoot
	BR	#.L9
.L8:
	NOP
	BR	#.L10
.L9:
	NOP
.L10:
	NOP
	; start of epilogue
	ADD.W	#2, R1
	RET
	.size	button_press, .-button_press
	.ident	"GCC: (Mitto Systems Limited - msp430-gcc 8.2.0.52) 8.2.0"
