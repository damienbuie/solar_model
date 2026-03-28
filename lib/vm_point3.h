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
 
#ifndef POINT3_H
#define POINT3_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple3.h>
#include <vm_point4.h>

BEGIN_NAMESPACE

TEMPLATE
class Point3 : public Tuple3T {

    /**
      * Constructs and initializes a Point3 from the specified xyz coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      * @param z the z coordinate
      */
public:
    Point3(T x, T y, T z): Tuple3T(x, y, z) { }

    /**
      * Constructs and initializes a Point3 from the specified array.
      * @param p the array of length 3 containing xyz in order
      */
    Point3(const T p[]): Tuple3T(p) { }

    /**
      * Constructs and initializes a Point3 from the specified Tuple3d.
      * @param t1 the Tuple3d containing the initialization x y z data
      */
    Point3(const Tuple3T& t1): Tuple3T(t1) { }

    /**
      * Constructs and initializes a Point3 to (0,0,0).
      */
    Point3(): Tuple3T() { }

    /**
      * Computes the square of the distance between this point and point p1.
      * @param  p1 the other point
      * @return the square of distance between these two points as a float
      */
    T distanceSquared(const Point3& p1) const {
        T dx = this->x - p1.x;
        T dy = this->y - p1.y;
        T dz = this->z - p1.z;
        return dx*dx + dy*dy + dz*dz;
    }

    /**
      * Returns the distance between this point and point p1.
      * @param p1 the other point
      * @return the distance between these two points as a float
      */
    T distance(const Point3& p1) const {
        return UtilT::sqrt(distanceSquared(p1));
    }

    /**
      * Computes the L-1 (Manhattan) distance between this point and point p1.
      * The L-1 distance is equal to abs(x1-x2) + abs(y1-y2).
      * @param p1 the other point
      */
    T distanceL1(const Point3& p1) const {
        return UtilT::abs(this->x-p1.x) + UtilT::abs(this->y-p1.y) + UtilT::abs(this->z-p1.z);
    }

    /**
      * Computes the L-infinite distance between this point and point p1.
      * The L-infinite distance is equal to MAX[abs(x1-x2), abs(y1-y2)].
      * @param p1 the other point
      */
    T distanceLinf(const Point3& p1) const {
        return UtilT::max(UtilT::abs(this->x-p1.x), UtilT::abs(this->y-p1.y), UtilT::abs(this->z-p1.z));
    }

    /**
     * Multiplies each of the x,y,z components of the Point4 parameter
     * by 1/w and places the projected values into this point.
     * @param p1 the source Point4, which is not modified
     */
    void project(const Point4T& p1) {
        // zero div may occur.
        this->x = p1.x/p1.w;
        this->y = p1.y/p1.w;
        this->z = p1.z/p1.w;
    }

    // copy constructor and operator = is made by complier

    Point3& operator=(const Tuple3T& t) {
        Tuple3T::operator=(t);
        return *this;
    }
};

END_NAMESPACE

TEMPLATE inline
NAMESPACE::Point3T operator*(T s, const NAMESPACE::Point3T& t1) {
    return operator*(s, (const NAMESPACE::Tuple3T&)t1);
}

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Point3T& t1) {
    return operator<<(o, (const NAMESPACE::Tuple3T&)t1);
}
#endif

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
#else
typedef Point3 Point3d;
typedef Point3 Point3f;
#endif


END_NAMESPACE


#endif /* POINT3_H */
