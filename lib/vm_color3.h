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
 
#ifndef COLOR3_H
#define COLOR3_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple3.h>

BEGIN_NAMESPACE

TEMPLATE
class Color3 : public Tuple3T {

public:
    /**
      * Constructs and initializes a Color3 from the specified xyz
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      */
    Color3(T x, T y, T z): Tuple3T(x, y, z) { }

    /**
      * Constructs and initializes a Color3 from input array of length 3.
      * @param c the array of length 3 containing xyz in order
      */
    Color3(const T c[]): Tuple3T(c) { }

    /**
      * Constructs and initializes a Color3 from the specified Tuple3d.
      * @param t1 the Tuple3d containing the initialization x y z data
      */
    Color3(const Tuple3T& t1): Tuple3T(t1) { }

#if 0
    /**
      * Constructs and initializes a Color3 from the specified Tuple3f.
      * @param t1 the Tuple3f containing the initialization x y z data
      */
    Color3(Tuple3f t1) {
	super(t1);
    }
#endif

    /**
      * Constructs and initializes a Color3 to (0,0,0).
      */
    Color3(): Tuple3T() { }
};


#ifdef USE_TEMPLATE
typedef Color3<float> Color3f;
typedef Color3<double> Color3d;
typedef Color3<unsigned char> Color3b;
#else
typedef Color3 Color3f;
typedef Color3 Color3d;
typedef Color3 Color3b;
#endif


END_NAMESPACE

#endif /* COLOR3_H */
