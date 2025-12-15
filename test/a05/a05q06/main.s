#================================================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - size/state
# $s1 - array
# $s2 – array + size
# $s3 – state
#================================================================
        .text
        .globl main

main:   li      $v0, 5
        syscall
        move    $s0, $v0
        
        la      $s1, array
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

        li      $s0, 0
for:
        bge     $s1, $s2, end   # if x > (array + n)
        lw      $s3, 0($s1)     # *p
        
        la      $s4, jtable1    # y = jumptable1
        
        addi    $s3, $s3, -2    # set an offset for val case
        
        bltz    $s0, continue   # if state < 0 go back to for
        li      $t0, 1
        bgt     $s0, $t0, continue # if state > 1 go back to for
        add     $t0, $s0, $s0
        add     $t0, $t0, $t0   # y += 4
        addu    $s4, $s4, $t0
        
        lw      $s4, 0($s4)
        
        jr      $s4             # go to y
s1:
        la      $s4, jtable2    # y = jtable2
        bltz    $s3, continue   # if val < 0 goto continue
        li      $t0, 1
        bgt     $s3, $t0, continue # if val > 1 goto continue
        add     $t0, $s3, $s3   
        add     $t0, $t0, $t0
        addu    $s4, $s4, $t0        # y += 4
        
        lw      $s4, 0($s4)
        
        jr      $s4            # go to y

s2:
        la      $s4, jtable2    # y = jtable2
        bltz    $s3, continue   # if val < 0 goto continue
        li      $t0, 1
        bgt     $s3, $t0, continue # if val > 1 goto continue
        add     $t0, $s3, $s3   
        add     $t0, $t0, $t0
        addu    $s4, $s4, $t0        # y += 4
        
        lw      $s4, 0($s4)
        
        jr      $s4            # go to y


v1:     li      $s0, 1
        j       continue

v2:     li      $s0, 0
        j       continue

continue:       addiu   $s1, $s1, 4
        j       for

end:
        move    $a0, $s0
        
        li      $v0, 1
        syscall

        la      $a0, newline
        li      $v0, 4
        syscall
        
        li      $v0, 10
        syscall

        .data
jtable1:        .word s1 s2
jtable2:        .word v1 v2

newline:        .asciiz "\n"
fucklyoo:       .asciiz "fuckleyoo"
        
array:  .word 0
