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
 


#ifndef VECTOR2_H
#define VECTOR2_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple2.h>

BEGIN_NAMESPACE

TEMPLATE
class Vector2 : public Tuple2T {

public:
    /**
      * Constructs and initializes a Vector2 from the specified xy coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      */
    Vector2(T x, T y) : Tuple2T(x, y) { }

    /**
      * Constructs and initializes a Vector2 from the specified array.
      * @param v the array of length 2 containing xy in order
      */
    Vector2(const T v[]) : Tuple2T(v) {  }

    /**
      * Constructs and initializes a Vector2 from the specified Tuple2.
      * @param t1 the Tuple2 containing the initialization x y data
      */
    Vector2(const Tuple2T& t1) : Tuple2T(t1) { }

    /**
      * Constructs and initializes a Vector2 to (0,0).
      */
    Vector2(): Tuple2T() { }

    /**
      * Computes the dot product of the this vector and vector v1.
      * @param  v1 the other vector
      */
    T dot(const Vector2& v1) const {
        return this->x*v1.x + this->y*v1.y;
    }

    /**
      * Returns the squared length of this vector.
      * @return the squared length of this vector
      */
    T lengthSquared() const {
        return this->x*this->x + this->y*this->y;
    }

    /**
      * Returns the length of this vector.
      * @return the length of this vector
      */
    T length() const {
        return UtilT::sqrt(lengthSquared());
    }

    /**
      * Normalizes this vector in place.
      */
    void normalize() {
        T d = length();

        // zero-div may occur.
        this->x /= d;
        this->y /= d;
    }

    /**
      * Sets the value of this vector to the normalization of vector v1.
      * @param v1 the un-normalized vector
      */
    void normalize(const Vector2& v1) {
        set(v1);
        normalize();
    }

    /**
      * Returns the angle in radians between this vector and
      * the vector parameter; the return value is constrained to the
      * range [0,PI].
      * @param v1  the other vector
      * @return the angle in radians in the range [0,PI]
      */
    T angle(const Vector2& v1) const {
        // stabler than acos
        return UtilT::abs(UtilT::atan2(this->x*v1.y - this->y*v1.x , dot(v1)));
    }

    // copy constructor and operator = is made by complier

    Vector2& operator=(const Tuple2T& t) {
        Tuple2T::operator=(t);
        return *this;
    }

};

/*
 * 0. value_type typedef added
 * 1. copy constructo, oeprator = are delegated to compiler
 * 4. typdef value type
 * 7. typedefs for <float>, <double>
 * removed construction from Vector2f
 */

END_NAMESPACE

TEMPLATE inline
NAMESPACE::Vector2T operator*(T s, const NAMESPACE::Vector2T& t1) {
    return operator*(s, (const NAMESPACE::Tuple2T&)t1);
}

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Vector2T& t1) {
    return operator<<(o, (const NAMESPACE::Tuple2T&)t1);
}
#endif

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
#else
typedef Vector2 Vector2d;
typedef Vector2 Vector2f;
#endif


END_NAMESPACE



#endif /* VECTOR2_H */
