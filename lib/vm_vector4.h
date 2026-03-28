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
 
#ifndef VECTOR4_H
#define VECTOR4_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple3.h>
#include <vm_tuple4.h>

BEGIN_NAMESPACE
TEMPLATE 
class Vector4 : public Tuple4T {

public:

    /**
      * Constructs and initializes a Vector4 from the specified xyzw coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      * @param w the w coordinate
      */
    Vector4(T x, T y, T z, T w): Tuple4T(x, y, z, w) { }

    /**
      * Constructs and initializes a Vector4 from the specified array of length 4.
      * @param v the array of length 4 containing xyzw in order
      */
    Vector4(const T v[]): Tuple4T(v) { }

    /**
      * Constructs and initializes a Vector4 from the specified Tuple4d.
      * @param t1 the Tuple4d containing the initialization x y z w data
      */
    Vector4(const Tuple4T& t1): Tuple4T(t1) { }

    /**
      * Constructs and initializes a Vector4 to (0,0,0,0).
      */
    Vector4(): Tuple4T() { }

    /**
     * Constructs and initializes a Vector4 from the specified Tuple3.
     * The x,y,z  components of this point are set to the corresponding
     * components
     * of tuple t1. The w component of this point is set to 0.
     *
     * @param t1 the tuple to be copied
     * @since Java3D 1.2
     */
    Vector4(const Tuple3T& t1): Tuple4T(t1.x, t1.y, t1.z, 0) { }

    /**
     * Sets the x,y,z components of this point to the corresponding
     * components of tuple t1. The w component of this point is set to 1.
     *
     * NOTE: 
     * This method's name should be 'set'. Newer compilers support
     * 'using Tuple4T::set;' and use the name 'set'.
     * but for now, renamed to 'set3'.
     *
     * @param t1 the tuple to be copied
     * @since Java3D 1.2
     */
    void set3(const Tuple3T& t1) {
        this->x = t1.x;
        this->y = t1.y;
        this->z = t1.z;
        this->w = 0;
    }

		void reflect(Vector4T t1){
			T d = dot(t1);	
			t1.scale(2*d);
			t1.sub(*this);
			Tuple4T::set(t1);
		}


    /**
      * Returns the squared length of this vector.
      * @return the squared length of this vector
      */
    T lengthSquared() const {
//        return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
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
     * Computes the dot product of the this vector and vector v1.
     * @param  v1 the other vector
     * @return the dot product of this vector and vector v1
     */
    T dot(const Vector4& v1) const {
        return this->x*v1.x + this->y*v1.y + this->z*v1.z + this->w*v1.w;
    }

		void dottimes(const Vector4& v1) {
			this->x *= v1.x;
			this->y *= v1.y;
			this->z *= v1.z;
			this->w *= v1.w;
		}

    /**
      * Sets the value of this vector to the normalization of vector v1.
      * @param v1 the un-normalized vector
      */
    void normalize(const Vector4& v1) {
        Tuple4T::set(v1);
        normalize();
    }

    /**
      * Sets the value of this vector to the normalization of vector v1.
      * @param v1 the un-normalized vector (for Australians)
      */
    void normalise(const Vector4& v1) {
        Tuple4T::set(v1);
        normalize();
    }

    /**
      * Normalizes this vector in place.
      */
    void normalize() _THROW_ERROR
	{
        T d = length();

		if ( d == 0)
			DIVIDE_BY_ZERO

        // zero-div may occur.
        this->x /= d;
        this->y /= d;
        this->z /= d;
        this->w /= d;
    }

    /**
      * Normalizes this vector in place.
      */
    void normalise() _THROW_ERROR
	{
		normalize();
    }

    /**
      * Returns the (4-space) angle in radians between this vector and
      * the vector parameter; the return value is constrained to the
      * range [0,PI].
      * @param v1  the other vector
      * @return the angle in radians in the range [0,PI]
      */
    T angle(const Vector4& v1) const _THROW_ERROR
	{

        T d = dot(v1);
        T v1_length = v1.length();
        T v_length = length();

		if (v_length == 0 || v1_length == 0)
			REPORT_ERROR("ERROR: Vector has no length")

        // numerically, domain error may occur
        return T(acos(d/v1_length/v_length));
    }

    /**
      * Returns the cross product of two 4 vectors
      */
    void cross(const Vector4& v1, const Vector4& v2) {
        // store on stack once for aliasing-safty
	// i.e. safe when a.cross(a, b)
	this->set(
	  v1.y*v2.z - v1.z*v2.y,
	  v1.z*v2.x - v1.x*v2.z,
	  v1.x*v2.y - v1.y*v2.x,
	  0 );
    }

    // copy constructor and operator = is made by complier

    Vector4& operator=(const Tuple4T& t) {
        Tuple4T::operator=(t);
        return *this;
    }
};

END_NAMESPACE

TEMPLATE inline
NAMESPACE::Vector4T operator*(T s, const NAMESPACE::Vector4T& t1) {
    return operator*(s, (const NAMESPACE::Tuple4T&)t1);
}

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Vector4T& t1) {
    return operator<<(o, (const NAMESPACE::Tuple4T&)t1);
}
#endif

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Vector4<double> Vector4d;
typedef Vector4<float> Vector4f;
#else
typedef Vector4 Vector4d;
typedef Vector4 Vector4f;
#endif

END_NAMESPACE


#endif /* VECTOR4_H */
