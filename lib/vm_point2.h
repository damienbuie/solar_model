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
 
#ifndef POINT2_H
#define POINT2_H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_tuple2.h>

BEGIN_NAMESPACE

TEMPLATE
class Point2 : public Tuple2T {

public:
    /**
      * Constructs and initializes a Point2 from the specified xy coordinates.
      * @param x the x coordinate
      * @param y the y coordinate
      */
    Point2(T x, T y): Tuple2T(x, y) { }

    /**
      * Constructs and initializes a Point2 from the specified array.
      * @param p the array of length 2 containing xy in order
      */
    Point2(const T p[]): Tuple2T(p) { }

    /**
      * Constructs and initializes a Point2 from the specified Tuple2.
      * @param t1 the Tuple2 containing the initialization x y data
      */
    Point2(const Tuple2T& t1): Tuple2T(t1) { }

    /**
      * Constructs and initializes a Point2 to (0,0).
      */
    Point2(): Tuple2T() { }

    /**
      * Computes the square of the distance between this point and point p1.
      * @param  p1 the other point
      */
    T distanceSquared(const Point2& p1) const {
        T dx = this->x - p1.x;
        T dy = this->y - p1.y;
        return dx*dx + dy*dy;
    }

    /**
      * Computes the distance between this point and point p1.
      * @param p1 the other point
      */
    T distance(const Point2& p1) const {
        return UtilT::sqrt(distanceSquared(p1));
    }

    /**
      * Computes the L-1 (Manhattan) distance between this point and point p1.
      * The L-1 distance is equal to abs(x1-x2) + abs(y1-y2).
      * @param p1 the other point
      */
    T distanceL1(const Point2& p1) const {
        return UtilT::abs(this->x-p1.x) + UtilT::abs(this->y-p1.y);
    }

    /**
      * Computes the L-infinite distance between this point and point p1.
      * The L-infinite distance is equal to MAX[abs(x1-x2), abs(y1-y2)].
      * @param p1 the other point
      */
    T distanceLinf(const Point2& p1) const {
        return UtilT::max(UtilT::abs(this->x-p1.x), UtilT::abs(this->y-p1.y));
    }

    // copy constructor and operator = is made by complier

    Point2& operator=(const Tuple2T& t) {
        Tuple2T::operator=(t);
        return *this;
    }
};

END_NAMESPACE

#ifdef USE_IO
TEMPLATE inline
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Point2T& t1) {
    return operator<<(o, (const NAMESPACE::Tuple2T&)t1);
}
#endif

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Point2<double> Point2d;
typedef Point2<float> Point2f;
#else
typedef Point2 Point2d;
typedef Point2 Point2f;
#endif

END_NAMESPACE

#endif /* POINT2_H */
