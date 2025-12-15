#================================================================
# Filename: main.s
# Author: Oladayo Oyedeji
# Date: 09/16/2025
#
# Description
#
# Register usage:
# $s0 - year
# $s1 – month
# $s2 – day
#================================================================
#################################################################
# #
# text segment #
# #
#################################################################

        .text
        .globl main
main:   # input
        li      $v0, 5          # input
        syscall

        # get year, month, day
        li      $t0, 10000
        div     $v0, $t0        # year = x / 10000
        mflo    $s0

        li      $t0, 100
        div     $v0, $t0       # month = x / 100
        mflo    $s1

        li      $t0, 100
        div     $s1, $t0         # month %= 100
        mfhi    $s1
        
        li      $t0, 100
        div     $v0, $t0        # day = x % 100
        mfhi    $s2

        move    $a0, $s0
        li      $v0, 1
        syscall
        
        la      $a0, space
        li      $v0, 4
        syscall
        
        move    $a0, $s1
        li      $v0, 1
        syscall
        
        la      $a0, space
        li      $v0, 4
        syscall
        
        move    $a0, $s2
        li      $v0, 1
        syscall
        
        la      $a0, space
        li      $v0, 4
        syscall

        #========================================
        # exit cases for months which is s1 i put
        # in t1 = s2 - 1
        #========================================
        addi    $t1, $s1, -1
        
        bltz    $t1, false       # if days < 0 goto exit
        li      $t0, 11         # if
        bgt     $t1, $t0, false  # if days > 11
        la      $s3, jtable
        
        add     $t1, $t1, $t1   # t = jtable[days-1]
        add     $t1, $t1, $t1
        addu    $s3, $s3, $t1

        lw      $s3, 0($s3)
        
        jr      $s3

#================================================
# month conditions
#================================================
january: 
                li      $v0, 4
                syscall
                j       december
        
febuary:        
                li      $v0, 4
                syscall
        
                li      $t0, 29
                bgt     $s2, $t0, false         # if day > 29 goto false
                li      $t0, 4
                div     $s0, $t0
                mfhi    $t0
                bne     $t0, $0, elif           # if year % 4 != 0 goto elif
        
                li      $t0, 100                
                div     $s0, $t0
                mfhi    $t0
                bnez    $t0, continue           # if year % 100 == 0 goto or
                li      $t0, 400
                div     $s0, $t0
                mfhi    $t0
                bnez    $t0, elif
                
continue:       li      $t0, 29
                bne     $s2, $t0, elif
                j       true                   # if day % 100 != 0 && day % 4 == 0 goto true
        
elif:           
                li      $t0, 28                 # if day == 29 goto true
                ble     $s2, $t0, true
                j       false
        
march:          
                j       december
        
april:          
                j       november
        
may:            
                j       december
        
june:           
                j       november
        
july:           
                j       december
        
august:         
                j       december
        
september:      
                j       november
        
october:        
                j       december
        
november:       
                li      $t0, 30
                j       execute
        
december:       
                li      $t0, 31
                j       execute
        
execute:        
                bgt     $s2, $t0, false
                j       true

        
true:           li      $a0, 1
                j       print
false:          li      $a0, 0

print:
                li      $v0, 1
                syscall
        
                li      $v0, 10
                syscall


        .data
space:  .asciiz " "  
jtable: .word   january febuary march april may june
        .word   july august september october november december
        
