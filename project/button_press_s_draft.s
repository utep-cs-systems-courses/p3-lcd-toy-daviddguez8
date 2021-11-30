	.data
COLOR_GREEN:	.word 0x07E0
COLOR_RED:	.word 0x001f
	
	.text
	.global button_press
	.extern state
	.extern light
	.extern check_player_move
	.extern check_red_move
	.extern to_shoot

 			; start of code section
	.balign 2
	
jt:
	.word default
	.word case_1
	.word default
	.word default
	; pressed_button in r12
button_press:
	; range check, state>=4
	cmp #4, &state
	jc end_switch

	 mov &state, r15 		; to save the value of state
	;; mov #jt, r13
	add r15, r15 		; handles 2 byte words
	;; add r15, r13	
	mov jt(r15), pc
	
case_1:
	mov #light, r14

	cmp &COLOR_GREEN, 8(r14) ;; should be light.color 
	jnz else

 	; parameter is already set
	call #check_player_move
	jmp end_switch

else:
	mov #2, &state 		; state = 2
	;; parameter already set
	call #check_red_move	
	mov r12, &to_shoot 	; to_shoot = check_red_move(pressed_button)
	jmp end_switch
default:
end_switch:	
	ret

