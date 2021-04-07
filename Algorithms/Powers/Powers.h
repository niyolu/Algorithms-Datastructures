//
// Created by Niyol on 07.04.2021.
//

#ifndef POWERS_POWERS_H
#define POWERS_POWERS_H

#endif //POWERS_POWERS_H

// Powers.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

double ctr_naive = 0, ctr_rec1 = 0, ctr_rec2 = 0, ctr_it = 0;

using ll = unsigned long long;
/**
* @param b base
* @param n exponent
*/
double pow_naive(double a, double b) {
    double result = 1;
    while(b-- > 0) {
        ctr_naive++;
        result *= a;
    }
    return result;
}

//              {   pow(a*a,b/2)     if b even
// pow(a,b) =   {   pow(a*a,b/2)*a   if b odd
//


ll pow_rec1(ll a, ll b) {
    ctr_rec1++;
    if (b == 0) return 1;
    return ((b & 0x1) == 0x0 ? 1 : a) * pow_rec1(a * a, b / 2);
}

ll pow_rec2(ll a, ll b) {
    ctr_rec2++;
    if (b == 0) return 1;
    ll tmp = pow_rec2(a, b / 2);
    ll result = tmp * tmp;
    if ((b & 0x1) == 0x1) result *= a;
    return result;
}

ll pow_it(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        ctr_it++;
        if (b % 2 == 1) result *= a;
        a *= a;
        b /= 2;
    }
    return result;
}

// this implements the binary exponentiation algorithm
// b = 11 = 1011
//ll pow_bin
