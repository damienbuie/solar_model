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
 
#ifndef QUAT4__H
#define QUAT4__H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple4.h>
#include <vm_matrix4.h>

BEGIN_NAMESPACE
TEMPLATE
class Quat4 : public Tuple4T {

public:
    /**
     * Constructs and initializes a Quat4 from the specified xyzw coordinates.
     * @param x the x coordinate
     * @param y the y coordinate
     * @param z the z coordinate
     * @param w the w scalar component
     */
    Quat4(T x, T y, T z, T w): Tuple4T(x, y, z, w) { }
  
    /**
     * Constructs and initializes a Quat4 from the array of length 4.
     * @param v the array of length 4 containing xyzw in order
     */
    Quat4(const T v[]): Tuple4T(v) { }


    /**
      * Constructs and initializes a Quat4 from the specified Tuple4d.
      * @param t1 the Tuple4d containing the initialization x y z w data
      */
    Quat4(const Tuple4T& t1): Tuple4T(t1) { }

#if 0
    /**
     * Constructs and initializes a Quat4 from the specified Quat4f.
     * @param q1 the Quat4f containing the initialization x y z w data
     */
    Quat4(Quat4f q1) {
	super(q1);
    }

    /**
      * Constructs and initializes a Quat4 from the specified Tuple4f.
      * @param t1 the Tuple4f containing the initialization x y z w data
      */
    Quat4(Tuple4f t1) {
	super(t1);
    }
#endif

    /**
     * Constructs and initializes a Quat4 to (0,0,0,0).
     */
    Quat4(): Tuple4T() { }

    /**
      * Sets the value of this tuple to the value of tuple t1.
      * note: other set methods hides this set.
      * @param t1 the tuple to be copied
      */
    void set(const Tuple4T& t1) {
        Tuple4T::set(t1);
    }

    /**
      * Sets the value of this tuple to the specified xyzw coordinates.
      * note: other set methods hides this set.
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      * @param w the w coordinate
      */
    void set(T x, T y, T z, T w) {
        Tuple4T::set(x, y, z, w);
    }


    /**
     * Sets the value of this quaternion to the conjugate of quaternion q1.
     * @param q1 the source vector
     */
    void conjugate(const Quat4& q1) {
        this->x = -q1.x;
        this->y = -q1.y;
        this->z = -q1.z;
        this->w = q1.w;
    }

    /**
     * Negate the value of of each of this quaternion's x,y,z coordinates 
     *  in place.
     */
    void conjugate() {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
    }

    /**
     * Sets the value of this quaternion to the quaternion product of
     * quaternions q1 and q2 (this = q1 * q2).  
     * Note that this is safe for aliasing (e.g. this can be q1 or q2).
     * @param q1 the first quaternion
     * @param q2 the second quaternion
     */
    void mul(const Quat4& q1, const Quat4& q2);

    /**
     * Sets the value of this quaternion to the quaternion product of
     * itself and q1 (this = this * q1).
     * @param q1 the other quaternion
     */
    void mul(const Quat4& q1);

    /**
     *
     * Multiplies quaternion q1 by the inverse of quaternion q2 and places
     * the value into this quaternion.  The value of both argument quaternions 
     * is preservered (this = q1 * q2^-1).
     * @param q1 the left quaternion
     * @param q2 the right quaternion
     */
    void mulInverse(const Quat4& q1, const Quat4& q2);

    /**
     * Multiplies this quaternion by the inverse of quaternion q1 and places
     * the value into this quaternion.  The value of the argument quaternion
     * is preserved (this = this * q^-1).
     * @param q1 the other quaternion
     */
    void mulInverse(const Quat4& q1);

protected:
    T norm() const {
        return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
    }
    void setFromMat(T m00, T m01, T m02,
		       T m10, T m11, T m12,
		       T m20, T m21, T m22);

public:
    /**
     * Sets the value of this quaternion to quaternion inverse of quaternion q1.
     * @param q1 the quaternion to be inverted
     */
    void inverse(const Quat4& q1) {
        T n = q1.norm();
        // zero-div may occur.
        this->x = -q1.x/n;
        this->y = -q1.y/n;
        this->z = -q1.z/n;
        this->w = q1.w/n;
    }

    /**
     * Sets the value of this quaternion to the quaternion inverse of itself.
     */
    void inverse() {
        T n = norm();
        // zero-div may occur.
        this->x = -this->x/n;
        this->y = -this->y/n;
        this->z = -this->z/n;
        this->w /= n;
    }

    /**
     * Sets the value of this quaternion to the normalized value
     * of quaternion q1.
     * @param q1 the quaternion to be normalized.
     */
    void normalize(const Quat4& q1) {
        T n = UtilT::sqrt(q1.norm());
        // zero-div may occur.
        this->x = q1.x/n;
        this->y = q1.y/n;
        this->z = q1.z/n;
        this->w = q1.w/n;
    }

    /**
     * Normalizes the value of this quaternion in place.
     */
    void normalize() {
        T n = UtilT::sqrt(norm());
        // zero-div may occur.
        this->x /= n;
        this->y /= n;
        this->z /= n;
        this->w /= n;
    }

#if 0
    /**
     * Sets the value of this quaternion to the rotational component of
     * the passed matrix.
     * @param m1 the matrix4f
     */
    void set(Matrix4f m1) {
	setFromMat(
	    m1.m00, m1.m01, m1.m02,
	    m1.m10, m1.m11, m1.m12,
	    m1.m20, m1.m21, m1.m22
	    );
    }

    /**
     * Sets the value of this quaternion to the rotational component of
     * the passed matrix.
     * @param m1 the matrix3f
     */
    void set(Matrix3f m1) {
	setFromMat(
	    m1.m00, m1.m01, m1.m02,
	    m1.m10, m1.m11, m1.m12,
	    m1.m20, m1.m21, m1.m22
	    );
    }

    /**
     * Sets the value of this quaternion to the equivalent rotation of teh
     * AxisAngle argument.
     * @param a1 the axis-angle
     */
    void set(AxisAngle4f a1) {
	x = a1.x;
	y = a1.y;
	z = a1.z;
	T n = Math.sqrt(x*x + y*y + z*z);
	// zero-div may occur.
	T s = Math.sin(0.5*a1.angle)/n;
	x *= s;
	y *= s;
	z *= s;
	w = Math.cos(0.5*a1.angle);
    }

#endif

    /**
     * Sets the value of this quaternion to the rotational component of
     * the passed matrix.
     * @param m1 the matrix4d
     */
    void set(const Matrix4T& m1);

    /**
     * Sets the value of this quaternion to the rotational component of
     * the passed matrix.
     * @param m1 the matrix3d
     */
    void set(const Matrix3T& m1);


    /**
     * Sets the value of this quaternion to the equivalent rotation of teh
     * AxisAngle argument.
     * @param a1 the axis-angle
     */
    void set(const AxisAngle4T& a1);

    /**
      * Performs a great circle interpolation between this quaternion and the
      * quaternion parameter and places the result into this quaternion.
      * @param q1 the other quaternion
      * @param alpha the alpha interpolation parameter
      */
    void interpolate(const Quat4& q1, T alpha);

    /**
      * Performs a great circle interpolation between quaternion q1 and
      * quaternion q2 and places the result into this quaternion.
      * @param q1 the first quaternion
      * @param q2 the second quaternion
      * @param alpha the alpha interpolation parameter
      */
    void interpolate(const Quat4& q1, const Quat4& q2, T alpha);

    // copy constructor and operator = is made by complier

    Quat4& operator*=(const Quat4& m1);
    Quat4 operator*(const Quat4& m1) const;
};

TEMPLATE
void Quat4T::mul(const Quat4& q1, const Quat4& q2) {
    // store on stack for aliasing-safty
    set(
        q1.x*q2.w + q1.w*q2.x + q1.y*q2.z - q1.z*q2.y,
        q1.y*q2.w + q1.w*q2.y + q1.z*q2.x - q1.x*q2.z,
        q1.z*q2.w + q1.w*q2.z + q1.x*q2.y - q1.y*q2.x,
        q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
        );
}

TEMPLATE
void Quat4T::mul(const Quat4& q1) {
    // store on stack for aliasing-safty
    set(
        this->x*q1.w + this->w*q1.x + this->y*q1.z - this->z*q1.y,
        this->y*q1.w + this->w*q1.y + this->z*q1.x - this->x*q1.z,
        this->z*q1.w + this->w*q1.z + this->x*q1.y - this->y*q1.x,
        this->w*q1.w - this->x*q1.x - this->y*q1.y - this->z*q1.z
        );
}

TEMPLATE
void Quat4T::mulInverse(const Quat4& q1, const Quat4& q2) {
    T n = norm();
    // zero-div may occur.
    n = 1/n;
    // store on stack once for aliasing-safty
    set(
        (q1.x*q2.w - q1.w*q2.x - q1.y*q2.z + q1.z*q2.y)*n,
        (q1.y*q2.w - q1.w*q2.y - q1.z*q2.x + q1.x*q2.z)*n,
        (q1.z*q2.w - q1.w*q2.z - q1.x*q2.y + q1.y*q2.x)*n,
        (q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z)*n
        );
}


TEMPLATE
void Quat4T::mulInverse(const Quat4& q1) {
    T n = norm();
    // zero-div may occur.
    n = 1/n;
    // store on stack once for aliasing-safty
    set(
        (this->x*q1.w - this->w*q1.x - this->y*q1.z + this->z*q1.y)*n,
        (this->y*q1.w - this->w*q1.y - this->z*q1.x + this->x*q1.z)*n,
        (this->z*q1.w - this->w*q1.z - this->x*q1.y + this->y*q1.x)*n,
        (this->w*q1.w + this->x*q1.x + this->y*q1.y + this->z*q1.z)*n
        );
}


TEMPLATE
void Quat4T::set(const Matrix4T& m1) {
	setFromMat(
               m1.m00, m1.m01, m1.m02,
               m1.m10, m1.m11, m1.m12,
               m1.m20, m1.m21, m1.m22
               );
}


TEMPLATE
void Quat4T::set(const Matrix3T& m1) {
	setFromMat(
               m1.m00, m1.m01, m1.m02,
               m1.m10, m1.m11, m1.m12,
               m1.m20, m1.m21, m1.m22
               );
}


TEMPLATE
void Quat4T::set(const AxisAngle4T& a1) {
	this->x = a1.x;
	this->y = a1.y;
	this->z = a1.z;
	T n = UtilT::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	// zero-div may occur.
	T s = UtilT::sin(0.5*a1.angle)/n;
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w = UtilT::cos(0.5*a1.angle);
}


TEMPLATE
void Quat4T::interpolate(const Quat4& q1, T alpha) {
	// From Hoggar.
	normalize();
	T n1 = UtilT::sqrt(q1.norm());
	// zero-div may occur.
	T x1 = q1.x/n1;
	T y1 = q1.y/n1;
	T z1 = q1.z/n1;
	T w1 = q1.w/n1;

	// t is cosine (dot product)
	T t = this->x*x1 + this->y*y1 + this->z*z1 + this->w*w1;

	// same quaternion (avoid domain error)
	if (1.0 <= UtilT::abs(t))
	    return;

	// t is now theta
	t = UtilT::acos(t);

	T sin_t = UtilT::sin(t);

	// same quaternion (avoid zero-div)
	if (sin_t == 0.0)
	    return;

	T s = UtilT::sin((1.0-alpha)*t)/sin_t;
	t = UtilT::sin(alpha*t)/sin_t;

	// set values
	this->x = s*this->x + t*x1;
	this->y = s*this->y + t*y1;
	this->z = s*this->z + t*z1;
	this->w = s*this->w + t*w1;
}

TEMPLATE
void Quat4T::interpolate(const Quat4& q1, const Quat4& q2, T alpha) {
    set(q1);
    interpolate(q2, alpha);
}


TEMPLATE
void Quat4T::setFromMat(T m00, T m01, T m02,
                          T m10, T m11, T m12,
                          T m20, T m21, T m22) {
	// From Ken Shoemake
	// (ftp://ftp.cis.upenn.edu/pub/graphics/shoemake)

	T s;
	T tr = m00 + m11 + m22;
	if (tr >= 0.0) {
	    s = UtilT::sqrt(tr + 1.0);
	    this->w = s*0.5;
	    s = 0.5/s;
	    this->x = (m21 - m12)*s;
	    this->y = (m02 - m20)*s;
	    this->z = (m10 - m01)*s;
	} else {
	    T maxm = UtilT::max(m00, m11, m22);
	    if (maxm == m00) {
            s = UtilT::sqrt(m00 - (m11 + m22) + 1.0);
            this->x = s*0.5;
            s = 0.5/s;
            this->y = (m01 + m10)*s;
            this->z = (m20 + m02)*s;
            this->w = (m21 - m12)*s;
	    } else if (maxm == m11) {
            s = UtilT::sqrt(m11 - (m22 + m00) + 1.0);
            this->y = s*0.5;
            s = 0.5/s;
            this->z = (m12 + m21)*s;
            this->x = (m01 + m10)*s;
            this->w = (m02 - m20)*s;
	    } else {
            s = UtilT::sqrt(m22 - (m00 + m11) + 1.0);
            this->z = s*0.5;
            s = 0.5/s;
            this->x = (m20 + m02)*s;
            this->y = (m12 + m21)*s;
            this->w = (m10 - m01)*s;
	    }
	}
}

TEMPLATE
Quat4T& Quat4T::operator*=(const Quat4& m1) {
    mul(m1);
    return *this;
}

TEMPLATE
Quat4T Quat4T::operator*(const Quat4& m1) const {
    return (Quat4(*this)).operator*=(m1);
}

END_NAMESPACE

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Quat4T& q1) {
    return operator<<(o, (const NAMESPACE::Tuple4T&)q1);
}
#endif
BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Quat4<double> Quat4d;
typedef Quat4<float> Quat4f;
#else
typedef Quat4 Quat4d;
typedef Quat4 Quat4f;
#endif

END_NAMESPACE


#endif /* QUAT4__H */
