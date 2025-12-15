        .text
        .globl main

main:
        # get input
        # if the input is < than 2 return false
        # checks if input is divisible by [2: sqrt(input)]
        # now how do we do sqrt(input) on mips ?????
        # you dont need to
        # just i^2 <= n
        li      $v0, 5
        syscall

        move    $s0, $v0
        li      $s1, 2
        blt     $s0, $s1, false
FOR:    mul     $t0, $s1, $s1
        blt     $s0, $t0, true
        div     $s0, $s1
        mfhi    $t1
        beqz    $t1, false
        addi    $s1, $s1, 1
        j       FOR
false:  li      $a0, 0
        j       print
true:   li      $a0, 1
print:  li      $v0, 1
        syscall
        la      $a0, newline
        li      $v0, 4
        syscall

        li      $v0, 10
        syscall

        .data
newline: .asciiz "\n"
