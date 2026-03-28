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
 
#ifndef VECTOR3_H
#define VECTOR3_H

#include <vm_configure.h>

#include <vm_tuple3.h>

BEGIN_NAMESPACE
TEMPLATE
class Vector3 : public Tuple3T {

public:
    /**
      * Constructs and initializes a Vector3 from the specified xyz coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      */
    Vector3(T x, T y, T z): Tuple3T(x, y, z) { }

    /**
      * Constructs and initializes a Vector3 from the specified array of length 3.
      * @param v the array of length 3 containing xyz in order
      */
    Vector3(const T v[]): Tuple3T(v) {  }

    /**
      * Constructs and initializes a Vector3 from the specified Tuple3d.
      * @param t1 the Tuple3d containing the initialization x y z data
      */
    Vector3(const Tuple3T& t1): Tuple3T(t1) { }

    /**
      * Constructs and initializes a Vector3 to (0,0,0).
      */
    Vector3(): Tuple3T() {   }

    /**
      * Sets this vector to be the vector cross product of vectors v1 and v2.
      * @param v1 the first vector
      * @param v2 the second vector
      */
    void cross(const Vector3& v1, const Vector3& v2) {
        // store on stack once for aliasing-safty
        // i.e. safe when a.cross(a, b)
        set(
            v1.y*v2.z - v1.z*v2.y,
            v1.z*v2.x - v1.x*v2.z,
            v1.x*v2.y - v1.y*v2.x
            );
    }
    

    /**
      * Sets the value of this vector to the normalization of vector v1.
      * @param v1 the un-normalized vector
      */
    void normalize(const Vector3& v1) {
        set(v1);
        normalize();
    }

    /**
      * Normalizes this vector in place.
      */
    void normalize() {
        T d = length();

        // zero-div may occur.
        this->x /= d;
        this->y /= d;
        this->z /= d;
    }

    /**
      * Computes the dot product of the this vector and vector v1.
      * @param  v1 the other vector
      */
    T dot(const Vector3& v1) const {
        return this->x*v1.x + this->y*v1.y + this->z*v1.z;
    }


    /**
      * Returns the squared length of this vector.
      * @return the squared length of this vector
      */
    T lengthSquared() const {
        return this->x*this->x + this->y*this->y + this->z*this->z;
    }

    /**
      * Returns the length of this vector.
      * @return the length of this vector
      */
    T length() const {
        return UtilT::sqrt(lengthSquared());
    }

    /**
      * Returns the angle in radians between this vector and
      * the vector parameter; the return value is constrained to the
      * range [0,PI].
      * @param v1  the other vector
      * @return the angle in radians in the range [0,PI]
      */
    T angle(const Vector3& v1) const {
        // return (double)Math.acos(dot(v1)/v1.length()/v.length());
        // Numerically, near 0 and PI are very bad condition for acos.
        // In 3-space, |atan2(sin,cos)| is much stable.
        Vector3 c;
        c.cross(*this, v1);
        T sin = c.length();

        return UtilT::abs(UtilT::atan2(sin, dot(v1)));
    }

    // copy constructor and operator = is made by complier

    Vector3& operator=(const Tuple3T& t) {
        Tuple3T::operator=(t);
        return *this;
    }
};

END_NAMESPACE

TEMPLATE inline
NAMESPACE::Vector3T operator*(T s, const NAMESPACE::Vector3T& t1) {
    return operator*(s, (const NAMESPACE::Tuple3T&)t1);
}

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Vector3T& t1) {
    return operator<<(o, (const NAMESPACE::Tuple3T&)t1);
}
#endif

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
#else
typedef Vector3 Vector3d;
typedef Vector3 Vector3f;
#endif

END_NAMESPACE

#endif /* VECTOR3_H */
