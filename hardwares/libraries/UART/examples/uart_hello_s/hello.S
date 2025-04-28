.text
.align	2
.globl	printhello
.ent	printhello
######################################
# This is the main function
######################################
printhello:
.set noreorder
.set noat
nop
nop
addiu	$sp,$sp,-4
sw	$ra,0($sp)
li $20, 0x1f800002 # uart write port
B1_:
nop
ori $4, $0, 'H' # H
jal uart_write_
nop
ori $4, $0, 'e' # E
jal uart_write_
nop
ori $4, $0, 'l' # L
jal uart_write_
nop
ori $4, $0, 'l' # L
jal uart_write_
nop
ori $4, $0, 'o' # O
jal uart_write_
nop
ori $4, $0, '!' # !
jal uart_write_
nop
ori $4, $0, '\r' # <\R> letter
jal uart_write_
nop
ori $4, $0, '\n' # <CR> letter
jal uart_write_
nop
lw $ra,0($sp)

jr $ra
addiu	$sp,$sp,4
nop
# END
# uart write sub
uart_write_:
li $20, 0x1f800000
li $5, 1
nop
nop
nop
uwait_:
lw $2, 1($20)
and $2, $5, $2
bgtz $2, uwait_
nop
sb $4, 2($20)
j $31
nop
nop
nop
# END
.set reorder
.end printhello
