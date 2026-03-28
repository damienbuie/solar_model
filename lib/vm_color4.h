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
 
#ifndef COLOR4_H
#define COLOR4_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple4.h>

BEGIN_NAMESPACE

TEMPLATE
class Color4 : public Tuple4T {

public:
    /**
      * Constructs and initializes a Color4 from the specified xyzw
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      * @param w the w coordinate
      */
    Color4(T x, T y, T z, T w): Tuple4T(x, y, z, w) { }

    /**
      * Constructs and initializes a Color4 from input array of length 4.
      * @param c the array of length 4 containing xyzw in order
      */
    Color4(const T c[]): Tuple4T(c) { }

    /**
      * Constructs and initializes a Color4 from the specified Tuple4d.
      * @param t1 the Tuple4d containing the initialization x y z w data
      */
    Color4(const Tuple4T& t1): Tuple4T(t1) {  }

#if 0
    /**
      * Constructs and initializes a Color4 from the specified Tuple4.
      * @param t1 the Tuple4 containing the initialization x y z w data
      */
    Color4(Tuple4 t1) {
	Tuple4T(t1);
    }
#endif

    /**
      * Constructs and initializes a Color4 to (0,0,0,0).
      */
    Color4(): Tuple4T() { }
};

#ifdef USE_TEMPLATE
typedef Color4<float> Color4f;
typedef Color4<double> Color4d;
typedef Color4<unsigned char> Color4b;
#else
typedef Color4 Color4f;
typedef Color4 Color4d;
typedef Color4 Color4b;
#endif

END_NAMESPACE

#endif /* COLOR4_H */
