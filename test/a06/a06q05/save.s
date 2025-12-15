   
test_strcmpy:
        li      $s0, 0

        # save s0, ra 
        addiu   $sp, $sp, -4
        sw      $ra, 0($sp)
        
test_strcmpy_for:
        #=====================================================================
        # the number of test cases are 9 so we run a for loop from address 1 -
        # 9
        #=====================================================================
        li      $t0, 9
        bge     $s0, $t0, test_strcmpy_end

        #=====================================================================
        # print "Test "
        #=====================================================================
        la      $a0, test
        jal     print_str

        # print i + 1
        add     $a0, $s0, 1
        jal     print_int

        # print ": "
        la      $a0, colon
        jal     print_str

        # print "a0->first", "a0->second", a0->third
        #=====================================================================
        la      $a1, test_cases

        add     $t0, $s0, $s0
        add     $t0, $t0, $t0
        addu    $a1, $a1, $t0

        lw      $a0, 0($a1)
        lw      $a0, 0($a0)
        jal     print_in_quotes
        jal     print_comma_space

        lw      $a0, 0($a1)
        lw      $a0, 4($a0)
        jal     print_in_quotes
        jal     print_comma_space
        
        lw      $a0, 0($a1)
        lw      $a0, 8($a0)
        jal     print_int
        jal     print_space
        #=====================================================================

        jal     print_output_message
        
        #=====================================================================
        # each a0 has the pointer to three places we need to put them in
        # a0 and a1 and a2
        #=====================================================================
        
        # put values (a0.first, a0.second, a0.third) in a0, a1 and a2 and call
        # strcmpy
        #=====================================================================
        lw      $a0, 0($a1)
        lw      $a0, 0($a0)
        
        lw      $a2, 0($a1)
        lw      $a2, 8($a2)
        
        lw      $a1, 0($a1)
        lw      $a1, 4($a1)
        jal     strcmpy
        #=====================================================================

        # time to call passfail, a1 has the correct values so we compare with
        # v0
        #=====================================================================
        move    $t2, $v0

        la      $a1, correct_answers
        
        add     $t0, $s0, $s0
        add     $t0, $t0, $t0
        addu    $a1, $a1, $t0
        
        lw      $a0, 0($a1)
        move    $a1, $a0
        jal     print_int
        jal     print_space
        jal     print_elipses
        jal     print_space

        seq     $a0, $t2, $a1
        jal     passfail
        jal     print_newline
        addi    $s0, $s0, 1
        j       test_strcmpy_for

test_strcmpy_end:
        lw      $ra, 0($sp)
        addiu   $sp, $sp, 4
        jr      $ra

