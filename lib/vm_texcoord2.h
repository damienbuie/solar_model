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
 
#ifndef TEXCOORD2_H
#define TEXCOORD2_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple2.h>

BEGIN_NAMESPACE

TEMPLATE
class TexCoord2 : public Tuple2T {

public:
    /**
      * Constructs and initializes a TexCoord2 from the specified xy coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      */
    TexCoord2(T x, T y):  Tuple2T(x, y) { }

    /**
      * Constructs and initializes a TexCoord2 from the specified array.
      * @param p the array of length 2 containing xy in order
      */
    TexCoord2(const T v[]): Tuple2T(v) { }

    /**
      * Constructs and initializes a TexCoord2 to (0,0).
      */
    TexCoord2(): Tuple2T() { }

};

#ifdef USE_TEMPLATE
typedef TexCoord2<float> TexCoord2f;
typedef TexCoord2<double> TexCoord2d;
#else
typedef TexCoord2 TexCoord2f;
typedef TexCoord2 TexCoord2d;
#endif

END_NAMESPACE

#endif /* TEXCOORD2_H */
