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
 
#ifndef TUPLE3_H
#define TUPLE3_H

#include <vm_configure.h>
#include <vm_utility.h>

BEGIN_NAMESPACE

TEMPLATE
class Tuple3 {

public:
    /**
     * the type for values
     */
    typedef T value_type;
    /**
     * the type for index
     */
    typedef size_t size_type;
    /**
     * dimension
     */
    enum { DIMENSION = 3 };
    /**
     * The x coordinate.
     */
    T x;

    /**
     * The y coordinate.
     */
    T y;

    /**
     * The z coordinate.
     */
    T z;

    /**
      * Constructs and initializes a Tuple3 from the specified xyz coordinates.
      * @param xvalue the x coordinate
      * @param yvalue the y coordinate
      * @param zvalue the z coordinate
      */
    Tuple3(T xvalue, T yvalue, T zvalue): x(xvalue), y(yvalue), z(zvalue) { }

    /**
      * Constructs and initializes a Tuple3 from the specified array.
      * @param t the array of length 3 containing xyz in order
      */
    Tuple3(const T t[]): x(t[0]), y(t[1]), z(t[2]) { }

    /**
      * Constructs and initializes a Tuple3 to (0,0,0).
      */
    Tuple3(): x(0), y(0), z(0) { }

    /**
      * Sets the value of this tuple to the specified xyz coordinates.
      * @param xvalue the x coordinate
      * @param yvalue the y coordinate
      * @param zvalue the z coordinate
      */
    void set(T xvalue, T yvalue, T zvalue) {
        x = xvalue;
        y = yvalue;
        z = zvalue;
    }

    /**
      * Sets the value of this tuple from the 3 values specified in the array.
      * @param t the array of length 3 containing xyz in order
      */
    void set(const T t[]) {
        x = t[0];
        y = t[1];
        z = t[2];
    }

    /**
      * Sets the value of this tuple to the value of the Tuple3 argument.
      * @param t1 the tuple to be copied
      */
    void set(const Tuple3& t1) {
        x = t1.x;
        y = t1.y;
        z = t1.z;
    }

    /**
      * Copies the value of the elements of this tuple into the array t[]. 
      * @param t the array that will contain the values of the vector
      */
    void get(T t[]) const {
        t[0] = x;
        t[1] = y;
        t[2] = z;
    }

    /**
      * Gets the value of this tuple and copies the values into the Tuple3.
      * @param t Tuple3 object into which that values of this object are copied
      */
    void get(Tuple3* t) const _THROW_ERROR
	{
        if (!t) NO_ALLOCATION;
		t->x = x;
        t->y = y;
        t->z = z;
    }

    /**
      * Sets the value of this tuple to the vector sum of tuples t1 and t2.
      * @param t1 the first tuple
      * @param t2 the second tuple
      */
    void add(const Tuple3& t1, const Tuple3& t2) {
        x = t1.x + t2.x;
        y = t1.y + t2.y;
        z = t1.z + t2.z;
    }

    /**
      * Sets the value of this tuple to the vector sum of itself and tuple t1.
      * @param t1  the other tuple
      */
    void add(const Tuple3& t1) {
        x += t1.x;
        y += t1.y;
        z += t1.z;
    }


    /**
      * Sets the value of this tuple to the vector difference of tuple t1 and t2 (this = t1 - t2).
      * @param t1 the first tuple
      * @param t2 the second tuple
      */
    void sub(const Tuple3& t1, const Tuple3& t2) {
        x = t1.x - t2.x;
        y = t1.y - t2.y;
        z = t1.z - t2.z;
    }

    /**
      * Sets the value of this tuple to the vector difference of itself and tuple t1 (this = this - t1).
      * @param t1 the other tuple
      */
    void sub(const Tuple3& t1) {
        x -= t1.x;
        y -= t1.y;
        z -= t1.z;
    }

    /**
      * Sets the value of this tuple to the negation of tuple t1. 
      * @param t1 the source vector
      */
    void negate(const Tuple3& t1) {
        x = -t1.x;
        y = -t1.y;
        z = -t1.z;
    }

    /**
      * Negates the value of this vector in place.
      */
    void negate() {
        x = -x;
        y = -y;
        z = -z;
    }
      

    /**
      * Sets the value of this tuple to the scalar multiplication of tuple t1.
      * @param s the scalar value
      * @param t1 the source tuple
      */
    void scale(T s, const Tuple3& t1) {
        x = s*t1.x;
        y = s*t1.y;
        z = s*t1.z;
    }

    /**
      * Sets the value of this tuple to the scalar multiplication of itself.
      * @param s the scalar value
      */
    void scale(T s) {
        x *= s;
        y *= s;
        z *= s;
    }

    /**
      * Sets the value of this tuple to the scalar multiplication of tuple t1 and then
      * adds tuple t2 (this = s*t1 + t2).
      * @param s the scalar value
      * @param t1 the tuple to be multipled
      * @param t2 the tuple to be added
      */
    void scaleAdd(T s, const Tuple3& t1, const Tuple3& t2) {
        x = s*t1.x + t2.x;
        y = s*t1.y + t2.y;
        z = s*t1.z + t2.z;
    }

    /**
      * Sets the value of this tuple to the scalar multiplication of itself and then
      * adds tuple t1 (this = s*this + t1).
      * @param s the scalar value
      * @param t1 the tuple to be added
      */
    void scaleAdd(T s, const Tuple3& t1) {
        x = s*x + t1.x;
        y = s*y + t1.y;
        z = s*z + t1.z;
    }

    /**
      * Returns a hash number based on the data values in this object. 
      * Two different Tuple3 objects with identical data  values
      * (ie, returns true for equals(Tuple3) ) will return the same hash number.
      * Two vectors with different data members may return the same hash value,
      * although this is not likely.
      */
    size_t hashCode() const {
        return UtilT::hashCode(sizeof *this, this);
    }

    /**
      * Returns true if all of the data members of Tuple3 t1 are equal to the corresponding
      * data members in this
      * @param t1 the vector with which the comparison is made.
      */
    bool equals(const Tuple3& t1) const {
        return t1.x == x && t1.y == y && t1.z == z;
    }

    /**
      * Returns true if the L-infinite distance between this tuple and tuple t1 is
      * less than or equal to the epsilon parameter, otherwise returns false. The L-infinite
      * distance is equal to MAX[abs(x1-x2), abs(y1-y2)].
      * @param t1 the tuple to be compared to this tuple
      * @param epsilon the threshold value
      */
    bool epsilonEquals(const Tuple3& t1, T epsilon) const {
        return (UtilT::abs(t1.x - x) <= epsilon) &&
            (UtilT::abs(t1.y - y) <= epsilon) &&
            (UtilT::abs(t1.z - z) <= epsilon);
    }

    /**
      * Sets each component of the tuple parameter to its absolute value and
      * places the modified values into this tuple.
      * @param t the source tuple, which will not be modified
      */
    void absolute(const Tuple3& t) {
        set(t);
        absolute();
    }

    /**
      * Sets each component of this tuple to its absolute value.
      */
    void absolute() {
        if (x < 0.0)
            x = -x;
        if (y < 0.0)
            y = -y;
        if (z < 0.0)
            z = -z;
    }

    /**
      * Clamps this tuple to the range [low, high].
      * @param min the lowest value in this tuple after clamping
      * @param max the highest value in this tuple after clamping
      */
    void clamp(T min, T max) {
        clampMin(min);
        clampMax(max);
    }

    /**
      * Clamps the tuple parameter to the range [low, high] and places the values
      * into this tuple.
      * @param min the lowest value in the tuple after clamping
      * @param max the highest value in the tuple after clamping
      * @param t the source tuple, which will not be modified
      */
    void clamp(T min, T max, const Tuple3& t) {
        set(t);
        clamp(min, max);
    }
      
    /**
      * Clamps the minimum value of this tuple to the min parameter.
      * @param min the lowest value in this tuple after clamping
      */
    void clampMin(T min) {
        if (x < min)
            x = min;
        if (y < min)
            y = min;
        if (z < min)
            z = min;
    }

    /**
      * Clamps the minimum value of the tuple parameter to the min parameter
      * and places the values into this tuple.
      * @param min the lowest value in the tuple after clamping
      * @parm t the source tuple, which will not be modified
      */
    void clampMin(T min, const Tuple3& t) {
        set(t);
        clampMin(min);
    }

    /**
      * Clamps the maximum value of the tuple parameter to the max parameter and
      * places the values into this tuple.
      * @param max the highest value in the tuple after clamping
      * @param t the source tuple, which will not be modified
      */
    void clampMax(T max, const Tuple3& t) {
        set(t);
        clampMax(max);
    }
      

    /**
      * Clamps the maximum value of this tuple to the max parameter.
      * @param max the highest value in the tuple after clamping
      */
    void clampMax(T max) {
        if (x > max)
            x = max;
        if (y > max)
            y = max;
        if (z > max)
            z = max;
    }

    /**
      * Linearly interpolates between tuples t1 and t2 and places the
      * result into this tuple: this = (1-alpha)*t1 + alpha*t2.
      * @param t1 the first tuple
      * @param t2 the second tuple
      * @param alpha the alpha interpolation parameter
      */
    void interpolate(const Tuple3& t1, const Tuple3& t2, T alpha) {
        set(t1);
        interpolate(t2, alpha);
    }


    /**
      * Linearly interpolates between this tuple and tuple t1 and places the
      * result into this tuple: this = (1-alpha)*this + alpha*t1.
      * @param t1 the first tuple
      * @param alpha the alpha interpolation parameter
      */
    void interpolate(const Tuple3& t1, T alpha) {
        T beta = 1 - alpha;
        x = beta*x + alpha*t1.x;
        y = beta*y + alpha*t1.y;
        z = beta*z + alpha*t1.z;
    }

    /**
      * Returns a string that contains the values of this Tuple3. The form is (x,y,z).
      * @return the String representation
      */
#ifdef USE_TOSTRING
    STD::string toString() const {
        VM_TOSTRING
    }
#endif

    // copy constructor and operator = is made by complier

    bool operator==(const Tuple3& t1) const {
        return equals(t1);
    }

#ifdef USE_SUBSCRIPTION_OPERATOR
    T operator[](size_t index) const _THROW_ERROR
	{
        if ( index >= size_t(DIMENSION) ) OUT_OF_RANGE ;

        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
    }
    T& operator[](size_t index) _THROW_ERROR{

        if ( index >= size_t(DIMENSION) ) OUT_OF_RANGE ;
		
        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
    }
#endif

    Tuple3& operator=(const Tuple3& t1) {
        set(t1);
        return *this;
    }

    Tuple3& operator+=(const Tuple3& t1) {
        add(t1);
        return *this;
    }
    Tuple3& operator-=(const Tuple3& t1) {
        sub(t1);
        return *this;
    }
    Tuple3& operator*=(T s) {
        scale(s);
        return *this;
    }
    Tuple3 operator+(const Tuple3& t1) const {
        return (Tuple3(*this)).operator+=(t1);
    }
    Tuple3 operator-(const Tuple3& t1) const {
        return (Tuple3(*this)).operator-=(t1);
    }
    Tuple3 operator*(T s) const {
        return (Tuple3(*this)).operator*=(s);
    }

};

END_NAMESPACE

#ifdef USE_IO
TEMPLATE
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Tuple3T& t1) {
    return o << "(" << t1.x << "," << t1.y << "," << t1.z << ")";
}
#endif

TEMPLATE inline
NAMESPACE::Tuple3T operator*(T s, const NAMESPACE::Tuple3T& t1) {
    return (NAMESPACE::Tuple3T(t1)).operator*=(s);
}

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Tuple3<double> Tuple3d;
typedef Tuple3<float> Tuple3f;
#else
typedef Tuple3 Tuple3d;
typedef Tuple3 Tuple3f;
#endif

END_NAMESPACE

#endif /* TUPLE3_H */
