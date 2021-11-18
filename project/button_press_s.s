	.text
	.balign 2

	.word button_press
	.text

	.extern state
	.extern work_to_be_done
	.extern light
	.extern COLOR_GREEN
	.extern COLOR_RED
	.extern check_player_move
	.extern check_red_move
	.extern to_shoot
	
jt:
	.word #default
	.word #case_1
	.word #default
	.word #default
	
	; state in r12
button_press:
	;; range check, state>=4
	cmp #4, r12
	jnc end_switch

	mov r12, r15 		; to save the value of pressed_button
	mov jt, r13
	add r12, r12 		; handles 2 byte words
	add r12, r13
	mov (0)r13, pc

case_1:
	mov light, r14

	cmp &COLOR_GREEN, (8)r14 ; should be light.color
	jnz else

	mov r15, r12 		; setup parameter
	call #check_player_move
	jmp end_switch

else:
	mov #2, &state 		; state = 2
	mov r15, r12
	call #check_red_move	
	mov r12, &to_shoot 	; to_shoot = check_red_move(pressed_button)
	jmp end_switch
default:
end_switch:	
	RETI
