/** This code was initially written by 
 *  Kenji Hiranabe, Eiwa System Management, Inc.
 *
 *  Please see his copyright notice within vm_copyright.h
 *
 *  This software was altered at the University of Sydney
 *  by Damien Buie and is not subject to copyright protection
 *  provided it meets the terms of the file vm_copyright.h
 *  and is in the public domain. The University of Sydney and
 *  Damien Buie assumes no responsibility whatsoever for
 *  its use by other parties, and makes no guarantees, expressed or implied,
 *  about its quality, reliability, or any other characteristic.
 */
 
#ifndef UTILITY_H
#define UTILITY_H

#include <vm_configure.h>

BEGIN_NAMESPACE
TEMPLATE
struct Util {
    // prefer to cmath for portability
    static T abs(T t) { return t > 0 ? t : -t; }
    static T max(T a, T b) { return a < b ? b : a; }
    static T max(T a, T b, T c) { return max(max(a, b), c); }
    static T max(T a, T b, T c, T d) { return max(max(a, b), max(c, d)); }
    static T min(T a, T b) { return a < b ? a : b; }
    static T min(T a, T b, T c) { return min(min(a, b), c); }
    static T min(T a, T b, T c, T d) { return min(min(a, b), min(c, d)); }
    static T sin(T x) { return T(STD::sin(x)); }
    static T cos(T x) { return T(STD::cos(x)); }
    static T atan2(T y, T x) { return T(STD::atan2(y, x)); }
    static T acos(T x) { return T(STD::acos(x)); }
    static T sqrt(T x) { return T(STD::sqrt(x)); }
    static T pow(T x, T y) { return T(STD::pow(x, y)); }
    static size_t hashCode(size_t size, const void* ptr) {
        // idea is from Bjarne Stroustrup 3rd $17.6.2.3
        size_t res = 0;
        const char* p = (const char*)ptr;  // reinterpret_cast
        while (size--)
            res = (res << 1) ^ *p++;
        return res;
    }

};

END_NAMESPACE

#endif // End UTILITY_H

