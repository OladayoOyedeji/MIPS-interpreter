#include <iostream>

int main()
{
    int x, y, i, t;
    std::cin >> x >> y >> i >> t;
    
    std::cout << x << y << i << t << std::endl;
        
    return 0;
}

// # printing
//         move    $a0, s0         # print_s0
//         li      $v0, 1
//         syscall

//         la      $a0, SPACE      # prints space
//         li      $v0, 4
//         syscall
        
//         move    $a0, s1         # print_s0
//         li      $v0, 1
//         syscall

//         la      $a0, SPACE      # prints space
//         li      $v0, 4
//         syscall
        
//         move    $a0, s2         # print_s0
//         li      $v0, 1
//         syscall

//         la      $a0, SPACE      # prints space
//         li      $v0, 4
//         syscall
    

