#===============================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - size
# $s1 - &x
# $s2 - &(x + size)
# $t0 – *p
# $t1 – *q
#===============================================

        .text
        .globl main

main:   li      $v0, 5
        syscall
        move    $s0, $v0        # size = input_int()

        la      $s1, array      # x = new int[size]
        move    $s2, $s1

        li      $s3, 0

while_input:
        beq     $s0, $s3, END
        li      $v0, 5          # x[i] = input
        syscall
        sw      $v0, 0($s2)
        
        addiu   $s2, $s2, 4          # x[i++]
        addi    $s3, $s3, 1
        j       while_input
        
END:
        addiu   $t0, $s2, -4
        
bubblesort:
        blt     $t0, $s1, end
        move    $t1, $s1

for1:   bge     $t1, $t0, end1

        lw      $t2, 0($t1)
        lw      $t3, 4($t1)

        bge     $t3, $t2, continue
        sw      $t3, 0($t1)
        sw      $t2, 4($t1)

continue:
        addiu   $t1, $t1, 4
        j       for1
end1:   
        addiu   $t0, $t0, -4
        j       bubblesort

end:   
print:  beq     $s1, $s2, end_print
        lw      $a0, 0($s1)
        li      $v0, 1
        syscall
        
        la      $a0, space
        li      $v0, 4
        syscall

        addiu   $s1, $s1, 4
        j       print
        

end_print:      
        la      $a0, newline
        li      $v0, 4
        syscall
     
        
        li      $v0, 10
        syscall

        .data
space:  .asciiz " "
newline:     .asciiz "\n"
array:  .word 0   
