//
// Created by NiJoL on 07.04.2021.
//

#include "Powers.h"

int main() {
#if 0
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "testing pow_naive!\n";
    std::cout << pow_naive(2, 3) << std::endl;
    std::cout << "steps : " << ctr_naive << std::endl;
    ctr_naive = 0;
    std::cout << pow_naive(3, 8) << std::endl;
    std::cout << "steps : " << ctr_naive << std::endl;
    ctr_naive = 0;
    std::cout << pow_naive(5, 20) << std::endl;
    std::cout << "steps : " << ctr_naive << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "testing pow_rec1!\n";
    std::cout << pow_rec1(2, 3) << std::endl;
    std::cout << "steps : " << ctr_rec1 << std::endl;
    ctr_rec1 = 0;
    std::cout << pow_rec1(3, 8) << std::endl;
    std::cout << "steps : " << ctr_rec1 << std::endl;
    ctr_rec1 = 0;
    std::cout << pow_rec1(5, 20) << std::endl;
    std::cout << "steps : " << ctr_rec1 << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "testing pow_rec2!\n";
    std::cout << pow_rec2(2, 3) << std::endl;
    std::cout << "steps : " << ctr_rec2 << std::endl;
    ctr_rec2 = 0;
    std::cout << pow_rec2(3, 8) << std::endl;
    std::cout << "steps : " << ctr_rec2 << std::endl;
    ctr_rec2 = 0;
    std::cout << pow_rec2(5, 20) << std::endl;
    std::cout << "steps : " << ctr_rec2 << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "testing pow_it!\n";
    std::cout << pow_it(2, 3) << std::endl;
    std::cout << "steps : " << ctr_it << std::endl;
    ctr_it = 0;
    std::cout << pow_it(3, 8) << std::endl;
    std::cout << "steps : " << ctr_it << std::endl;
    ctr_it = 0;
    std::cout << pow_it(5, 20) << std::endl;
    std::cout << "steps : " << ctr_it << std::endl;
#endif

    for (int i = 0; i < 100; i++) {
        printf("10^i = %i\n", pow_it(10,i));

    }



    return 0;
}