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
 
#ifndef MATRIX3__H
#define MATRIX3__H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_point3.h>
#include <vm_vector3.h>

BEGIN_NAMESPACE

TEMPLATE class Quat4;
TEMPLATE class AxisAngle4;

TEMPLATE
class Matrix3 {
protected:
    static T abs(T t) { return UtilT::abs(t); }
    static T sin(T t) { return UtilT::sin(t); }
    static T cos(T t) { return UtilT::cos(t); }

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
     * the type for tuple
     */
    typedef Tuple3T tuple_type;
    /**
     * the type for vector
     */
    typedef Vector3T vector_type;
    /**
     * the type for point
     */
    typedef Point3T point_type;

    /**
      * The first element of the first row.
      */
    T m00;

    /**
      * The second element of the first row.
      */
    T m01;

    /**
      * third element of the first row.
      */
    T m02;

    /**
      * The first element of the second row.
      */
    T m10;

    /**
      * The second element of the second row.
      */
    T m11;

    /**
      * The third element of the second row.
      */
    T m12;

    /**
      * The first element of the third row.
      */
    T m20;

    /**
      * The second element of the third row.
      */
    T m21;

    /**
      * The third element of the third row.
      */
    T m22;

    /**
      * Constrcts and initializes a Matrix3 from the specified nine values.
      * @param m00 the [0][0] element
      * @param m01 the [0][1] element
      * @param m02 the [0][2] element
      * @param m10 the [1][0] element
      * @param m11 the [1][1] element
      * @param m12 the [1][2] element
      * @param m20 the [2][0] element
      * @param m21 the [2][1] element
      * @param m22 the [2][2] element
      */
    Matrix3(T m00, T m01, T m02,
            T m10, T m11, T m12,
            T m20, T m21, T m22);

    /**
      * Constructs and initializes a Matrix3 from the specified 9
      * element array.  this.m00 =v[0], this.m01=v[1], etc.
      * @param  v the array of length 9 containing in order
      */
    Matrix3(const T v[]);

    /**
      * Constructs and initializes a Matrix3 from the specified 3x3
      * element array.  this.m00 =m[0][0], this.m01=m[0][1], etc.
      * @param  m the array of 3 x 3 containing in order
      */
#ifdef USE_CONVERSION_FROM_2DARRAY
    Matrix3(const T m[][3]);
#endif

#if 0
    /**
      * Constructs a new matrix with the same values as the Matrix3f parameter.
      * @param m1 The source matrix.
      */
    Matrix3(Matrix3f m1): 
        m00(m1.m00), m01(m1.m01), m02(m1.m02),
        m10(m1.m10), m11(m1.m11), m12(m1.m12),
        m20(m1.m20), m21(m1.m21), m22(m1.m22) { }
#endif

    /**
      * Constructs and initializes a Matrix3 to all zeros.
      */
    Matrix3();

    /**
      * Sets 9 values	
      * @param m00 the [0][0] element
      * @param m01 the [0][1] element
      * @param m02 the [0][2] element
      * @param m10 the [1][0] element
      * @param m11 the [1][1] element
      * @param m12 the [1][2] element
      * @param m20 the [2][0] element
      * @param m21 the [2][1] element
      * @param m22 the [2][2] element
      */
    void set(T m00, T m01, T m02,
             T m10, T m11, T m12,
             T m20, T m21, T m22);

    /**
      * Sets the value of this matrix to the value of the Matrix3
      * argument.
      * @param m1 The source matrix.
      */
    void set(const Matrix3& m1);

    /**
      * Sets the values in this Matrix3 equal to the row-major array parameter
      * (ie, the first four elements of the array will be copied into the first
      * row of this matrix, etc.).
      * @param  m the array of length 9 containing in order
      */
    void set(const T m[]);

    /**
      * Sets the values in this Matrix3 equal to the row-major array parameter
      * (ie, the first four elements of the array will be copied into the first
      * row of this matrix, etc.).
      * @param  m the array of 3x3 containing in order (T m[3][3]) 
      */
#ifdef USE_CONVERSION_FROM_2DARRAY
    void set(const T m[][3]);
#endif

    /**
     * Sets this Matrix3 to identity.
     */
    void setIdentity();

    /**
      * Sets the scale component of the current matrix by factoring out the
      * current scale (by doing an SVD) from the rotational component and
      * multiplying by the new scale.
      * @param scale the new scale amount
      */
    void setScale(T scale);

    /**
     * Sets the specified element of this matrix3d to the value provided.
     * @param row  the row number to be modified (zero indexed)
     * @param column  the column number to be modified (zero indexed)
     * @param value the new value
     */
    void setElement(size_type row, size_type column, T value) _THROW_ERROR;

    /**
     * Retrieves the value at the specified row and column of this matrix.
     * @param row  the row number to be retrieved (zero indexed)
     * @param column  the column number to be retrieved (zero indexed)
     * @return the value at the indexed element
     */
    T getElement(size_type row, size_type column) const _THROW_ERROR;

    /**
     * Retrieves the lvalue at the specified row and column of this matrix.
     * @param row  the row number to be retrieved (zero indexed)
     * @param column  the column number to be retrieved (zero indexed)
     * @return the lvalue at the indexed element
     */
    T& getElementReference(size_type row, size_type column) _THROW_ERROR;

    /**
     * Sets the specified row of this matrix3d to the three values provided.
     * @param row  the row number to be modified (zero indexed)
     * @param x the first column element
     * @param y the second column element
     * @param z the third column element
     */
    void setRow(size_type row, T x, T y, T z);

    /**
     * Sets the specified row of this matrix3d to the Vector provided.
     * @param row the row number to be modified (zero indexed)
     * @param v the replacement row
     */
    void setRow(size_type row, const Vector3T& v);

    /**
      * Sets the specified row of this matrix3 to the four values provided.
      * @param row the row number to be modified (zero indexed)
      * @param v the replacement row
      */
    void setRow(size_type row, const T v[]);

    /**
      * Copies the matrix values in the specified row into the
      * array parameter.
      * @param row the matrix row
      * @param v The array into which the matrix row values will be copied
      */
    void getRow(size_type row, T v[]) const;

    /**
      * Copies the matrix values in the specified row into the
      * vector parameter.
      * @param row the matrix row
      * @param v The vector into which the matrix row values will be copied
      */
    void getRow(size_type row, Vector3T* v) const;

    /**
      * Sets the specified column of this matrix3 to the three values provided.
      * @param  column the column number to be modified (zero indexed)
      * @param x the first row element
      * @param y the second row element
      * @param z the third row element
      */
    void setColumn(size_type column, T x, T y, T z);

    /**
      * Sets the specified column of this matrix3d to the vector provided.
      * @param column the column number to be modified (zero indexed)
      * @param v the replacement column
      */
    void setColumn(size_type column, const Vector3T& v);

    /**
      * Sets the specified column of this matrix3d to the four values provided. 
      * @param column  the column number to be modified (zero indexed) 
      * @param v       the replacement column 
      */
    void setColumn(size_type column,  const T v[]);

    /**
      * Copies the matrix values in the specified column into the vector 
      * parameter.
      * @param column the matrix column
      * @param v The vector into which the matrix row values will be copied
      */
    void getColumn(size_type column, Vector3T* v) const;

    /**
      * Copies the matrix values in the specified column into the array
      * parameter.
      * @param column the matrix column
      * @param v The array into which the matrix row values will be copied
      */
    void getColumn(size_type column,  T v[]) const;

    /**
      * Performs an SVD normalization of this matrix to calculate and return the
      * uniform scale factor. This matrix is not modified.
      * @return the scale factor of this matrix
      */
    T getScale() const;

    /**
      * Adds a scalar to each component of this matrix.
      * @param scalar The scalar adder.
      */
    void add(T scalar);

    /**
      * Substracts a scalar from each component of this matrix.
      * @param scalar The scalar adder.
      */
    void sub(T scalar);

    /**
      * Adds a scalar to each component of the matrix m1 and places
      * the result into this. Matrix m1 is not modified.
      * note this method is alias-safe.
      * @param scalar The scalar adder.
      * @parm m1 The original matrix values.
      */
    void add(T scalar, const Matrix3& m1);

    /**
     * Sets the value of this matrix to the matrix sum of matrices m1 and m2. 
     * note this method is alias-safe.
     * @param m1 the first matrix 
     * @param m2 the second matrix 
     */
    void add(const Matrix3& m1, const Matrix3& m2);

    /**
     * Sets the value of this matrix to sum of itself and matrix m1. 
     * @param m1 the other matrix 
     */
    void add(const Matrix3& m1);

    /**
      * Sets the value of this matrix to the matrix difference
      * of matrices m1 and m2. 
      * note this method is alias-safe.
      * @param m1 the first matrix 
      * @param m2 the second matrix 
      */
    void sub(const Matrix3& m1, const Matrix3& m2);

    /**
     * Sets the value of this matrix to the matrix difference of itself
     * and matrix m1 (this = this - m1). 
     * @param m1 the other matrix 
     */
    void sub(const Matrix3& m1);

    /**
      * Sets the value of this matrix to its transpose. 
      */
    void transpose();

    /**
     * Sets the value of this matrix to the transpose of the argument matrix.
     * note this method is alias-safe
     * @param m1 the matrix to be transposed 
     */
    void transpose(const Matrix3& m1);

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * quaternion argument. 
      * @param q1 the quaternion to be converted 
      */
    void set(const Quat4T& q1);   // moved to the implementation file

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * axis and angle argument. 
      * @param a1 the axis and angle to be converted 
      */
    void set(const AxisAngle4T& a1);    // moved to the implementation file

#if 0
    /**
     * Sets the value of this matrix to the matrix conversion of the
     * single precision quaternion argument. 
     * @param q1 the quaternion to be converted 
     */
    void set(Quat4f q1)  {
        setFromQuat(q1.x, q1.y, q1.z, q1.w);
    }

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * single precision axis and angle argument. 
      * @param a1 the axis and angle to be converted 
      */
    void set(AxisAngle4f a1) {
        setFromAxisAngle(a1.x, a1.y, a1.z, a1.angle);
    }
    /**
      * Sets the value of this matrix to the double value of the Matrix3f
      * argument.
      * @param m1 the matrix3f to be converted to double
      */
    void set(Matrix3f m1)  {
        m00 = m1.m00; m01 = m1.m01; m02 = m1.m02;
        m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
        m20 = m1.m20; m21 = m1.m21; m22 = m1.m22;
    }

#endif

    /**
     * Sets the value of this matrix to the matrix inverse
     * of the passed matrix m1. 
     * @param m1 the matrix to be inverted 
     */
    void invert(const Matrix3& m1);

    /**
     * Sets the value of this matrix to its inverse.
     */
    void invert();

    /**
     * Computes the determinant of this matrix. 
     * @return the determinant of the matrix 
     */
    T determinant() const;

    /**
     * Sets the value of this matrix to a scale matrix with the
     * passed scale amount. 
     * @param scale the scale factor for the matrix 
     */
    void set(T scale);

    /**
     * Sets the value of this matrix to a rotation matrix about the x axis
     * by the passed angle. 
     * @param angle the angle to rotate about the X axis in radians 
     */
    void rotX(T angle);

    /**
     * Sets the value of this matrix to a rotation matrix about the y axis
     * by the passed angle. 
     * @param angle the angle to rotate about the Y axis in radians 
     */
    void rotY(T angle);

    /**
     * Sets the value of this matrix to a rotation matrix about the z axis
     * by the passed angle. 
     * @param angle the angle to rotate about the Z axis in radians 
     */
    void rotZ(T angle);

    /**
      * Multiplies each element of this matrix by a scalar.
      * @param scalar The scalar multiplier.
      */
    void mul(T scalar);

    /**
      * Multiplies each element of matrix m1 by a scalar and places the result
      * into this. Matrix m1 is not modified.
      * @param scalar The scalar multiplier.
      * @param m1 The original matrix.
      */
    void mul(T scalar, const Matrix3& m1);

    /**
     * Sets the value of this matrix to the result of multiplying itself
     * with matrix m1. 
     * @param m1 the other matrix 
     */
    void mul(const Matrix3& m1);

    /**
     * Sets the value of this matrix to the result of multiplying
     * the two argument matrices together. 
     * note this method is alias-safe.
     * @param m1 the first matrix 
     * @param m2 the second matrix 
     */
    void mul(const Matrix3& m1, const Matrix3& m2);

    /**
      * Multiplies this matrix by matrix m1, does an SVD normalization of the
      * result, and places the result back into this matrix this =
      * SVDnorm(this*m1).
      * @param m1 the matrix on the right hand side of the multiplication
      */
    void mulNormalize(const Matrix3& m1) {
        mul(m1);
        SVD(this);
    }


    /**
      * Multiplies matrix m1 by matrix m2, does an SVD normalization of the
      * result, and places the result into this matrix this = SVDnorm(m1*m2).
      * @param m1  the matrix on the left hand side of the multiplication
      * @param m2  the matrix on the right hand side of the multiplication
      */
    void mulNormalize(const Matrix3& m1, const Matrix3& m2) {
        mul(m1, m2);
        SVD(this);
    }

    /**
      * Multiplies the transpose of matrix m1 times the transpose of matrix m2,
      * and places the result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeBoth(const Matrix3& m1, const Matrix3& m2) {
        mul(m2, m1);
        transpose();
    }

    /**
      * Multiplies matrix m1 times the transpose of matrix m2, and places the
      * result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeRight(const Matrix3& m1, const Matrix3& m2);
    
    /**
      * Multiplies the transpose of matrix m1 times matrix m2, and places the
      * result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeLeft(const Matrix3& m1, const Matrix3& m2);

    /**
      * Performs singular value decomposition normalization of this matrix.
      */
    void normalize() {
        SVD(this);
    }

    /**
      * Perform singular value decomposition normalization of matrix m1 and
      * place the normalized values into this.
      * @param m1 Provides the matrix values to be normalized
      */
    void normalize(const Matrix3& m1) {
        set(m1);
        SVD(this);
    }

    /**
      * Perform cross product normalization of this matrix.
      */
    void normalizeCP() {
        T s = UtilT::pow(UtilT::abs(determinant()), T(-1.0/3.0));
        mul(s);
    }
      
    /**
      * Perform cross product normalization of matrix m1 and place the
      * normalized values into this.
      * @param m1 Provides the matrix values to be normalized
      */
    void normalizeCP(const Matrix3& m1) {
        set(m1);
        normalizeCP();
    }



    /**
     * Returns true if all of the data members of Matrix3 m1 are
     * equal to the corresponding data members in this Matrix3. 
     * @param m1 The matrix with which the comparison is made. 
     * @return true or false 
     */
    bool equals(const Matrix3& m1) const;

    /**
      * Returns true if the L-infinite distance between this matrix and matrix
      * m1 is less than or equal to the epsilon parameter, otherwise returns
      * false. The L-infinite distance is equal to MAX[i=0,1,2,3 ; j=0,1,2,3 ;
      * abs(this.m(i,j) - m1.m(i,j)]
      * @param m1 The matrix to be compared to this matrix
      * @param epsilon the threshold value
      */
    bool epsilonEquals(const Matrix3& m1, T epsilon) const;

    /**
     * Sets this matrix to all zeros. 
     */
    void setZero();

    /**
      * Negates the value of this matrix: this = -this.
      */
    void negate();

    /**
      * Sets the value of this matrix equal to the negation of of the Matrix3
      * parameter.
      * @param m1 The source matrix
      */
    void negate(const Matrix3& m1) {
        set(m1);
        negate();
    }

    /**
     * Transform the vector vec using this Matrix3 and place the
     * result back into vec.
     * @param t the vector to be transformed
     */
    void transform(Tuple3T* t) const {
        transform(*t, t);
    }

    /**
     * Transform the vector vec using this Matrix3 and place the
     * result into vecOut.
     * note this method is alias-safe
     * @paramt the double precision vector to be transformed
     * @param result the vector into which the transformed values are placed
     */
    void transform(const Tuple3T& t, Tuple3T* result) const;

    /**
     * Returns a hash number based on the data values in this
     * object.  Two different Matrix3 objects with identical data values
     * (ie, returns true for equals(Matrix3) ) will return the same hash
     * number.  Two objects with different data members may return the
     * same hash value, although this is not likely.
     * @return the integer hash value 
     */
    size_t hashCode() const {
        return UtilT::hashCode(sizeof *this, this);
    }

  /**
    * Returns a string that contains the values of this Matrix3.
    * @return the String representation
    */
#ifdef USE_TOSTRING
STD::string toString() const;
#endif

protected:
    /**
      * Performs SVD on this matrix and gets scale and rotation.
      * Rotation is placed into rot.
      * @param rot the rotation factor. if null, ignored
      * @return scale factor
      */
    T SVD(Matrix3* rot) const;

    /**
     * Sets this from a Quat4 elements
     */
    void setFromQuat(T x, T y, T z, T w);

    /**
     * Sets this from a Quat4 elements
     */
    void setFromAxisAngle(T x, T y, T z, T angle);

public:
    // copy constructor and operator = is made by complier

    bool operator==(const Matrix3& m1) const {
        return equals(m1);
    }
#ifdef USE_SUBSCRIPTION_OPERATOR
    T operator()(size_t row, size_t col) const {
        return getElement(row, col);
    }
    T& operator()(size_t row, size_t col) {
        return getElementReference(row, col);
    }
#endif

    Matrix3& operator+=(const Matrix3& m1) {
        add(m1);
        return *this;
    }
    Matrix3& operator-=(const Matrix3& m1) {
        sub(m1);
        return *this;
    }
    Matrix3& operator*=(const Matrix3& m1) {
        mul(m1);
        return *this;
    }
    Matrix3& operator*=(T s) {
        mul(s);
        return *this;
    }
    Matrix3 operator+(const Matrix3& m1) const {
        return (Matrix3(*this)).operator+=(m1);
    }
    Matrix3 operator-(const Matrix3& m1) const {
        return (Matrix3(*this)).operator-=(m1);
    }
    Matrix3 operator*(const Matrix3& m1) const {
        return (Matrix3(*this)).operator*=(m1);
    }
    Matrix3 operator*(T s) const {
        return (Matrix3(*this)).operator*=(s);
    }

};

TEMPLATE
inline
Matrix3T operator*(T s, const Matrix3T& m) {
    return (Matrix3T(m)).operator*=(s);
}

TEMPLATE
inline
Matrix3T operator*(const Matrix3T& m1, const Matrix3T& m2) {
    return (Matrix3T(m1)).operator*=(m2);
}

TEMPLATE
inline
Tuple3T operator*(const Matrix3T& m, const Tuple3T& t) {
    Tuple3T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE
inline
Vector3T operator*(const Matrix3T& m, const Vector3T& t) {
    return operator*(m, (const Tuple3T&)t);
}

TEMPLATE
inline
Point3T operator*(const Matrix3T& m, const Point3T& t) {
    return operator*(m, (const Tuple3T&)t);
}

TEMPLATE
Matrix3T::Matrix3(T n00, T n01, T n02,
                         T n10, T n11, T n12,
                         T n20, T n21, T n22):
    m00(n00), m01(n01), m02(n02),
    m10(n10), m11(n11), m12(n12),
    m20(n20), m21(n21), m22(n22) { }

TEMPLATE
Matrix3T::Matrix3(const T v[]): 
    m00(v[ 0]), m01(v[ 1]), m02(v[ 2]),
    m10(v[ 3]), m11(v[ 4]), m12(v[ 5]),
    m20(v[ 6]), m21(v[ 7]), m22(v[ 8]) { }

#ifdef USE_CONVERSION_FROM_2DARRAY
TEMPLATE
Matrix3T::Matrix3(const T v[][3]): 
    m00(v[0][0]), m01(v[0][1]), m02(v[0][2]),
    m10(v[1][0]), m11(v[1][1]), m12(v[1][2]),
    m20(v[2][0]), m21(v[2][1]), m22(v[2][2]) { }
#endif

TEMPLATE
Matrix3T::Matrix3():
        m00(0), m01(0), m02(0),
        m10(0), m11(0), m12(0),
        m20(0), m21(0), m22(0) { }

TEMPLATE
void Matrix3T::set(T m00, T m01, T m02,
                     T m10, T m11, T m12,
                     T m20, T m21, T m22) {
    this->m00 = m00; this->m01 = m01; this->m02 = m02;
    this->m10 = m10; this->m11 = m11; this->m12 = m12;
    this->m20 = m20; this->m21 = m21; this->m22 = m22;
}

TEMPLATE
void Matrix3T::set(const Matrix3& m1) {
    m00 = m1.m00; m01 = m1.m01; m02 = m1.m02;
    m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
    m20 = m1.m20; m21 = m1.m21; m22 = m1.m22;
}

TEMPLATE
void Matrix3T::set(const T v[]) {
    assert(v != 0);
    m00 = v[ 0]; m01 = v[ 1]; m02 = v[ 2];
    m10 = v[ 3]; m11 = v[ 4]; m12 = v[ 5];
    m20 = v[ 6]; m21 = v[ 7]; m22 = v[ 8];
}

#ifdef USE_CONVERSION_FROM_2DARRAY
TEMPLATE
void Matrix3T::set(const T m[][3]) {
    assert(m != 0);
    m00 = m[0][0]; m01 = m[0][1]; m02 = m[0][2];
    m10 = m[1][0]; m11 = m[1][1]; m12 = m[1][2];
    m20 = m[2][0]; m21 = m[2][1]; m22 = m[2][2];
}
#endif

TEMPLATE
void Matrix3T::setIdentity() {
    m00 = 1.0; m01 = 0.0; m02 = 0.0;
    m10 = 0.0; m11 = 1.0; m12 = 0.0;
    m20 = 0.0; m21 = 0.0; m22 = 1.0;
}

TEMPLATE
void Matrix3T::setScale(T scale) {
    SVD(this);
    m00 *= scale;
    m11 *= scale;
    m22 *= scale;
}


TEMPLATE
void Matrix3T::set(const Quat4T& q1) {
    setFromQuat(q1.x, q1.y, q1.z, q1.w);
}

TEMPLATE
void Matrix3T::set(const AxisAngle4T& a1) {
    setFromAxisAngle(a1.x, a1.y, a1.z, a1.angle);
}

TEMPLATE
void Matrix3T::setElement(size_t row, size_t column, T value) _THROW_ERROR {

	if ( row >= 3 || column >= 3)
		REPORT_ERROR("Error: Out of Range Matrix3");

	const size_t index(column + 3 * row);

	switch (index){
		case 0:
			m00 = value;
			break;
		case 1:
			m01 = value;
			break;
		case 2:
			m02 = value;
			break;
		case 3:
			m10 = value;
			break;
		case 4:
			m11 = value;
			break;
		case 5:
			m12 = value;
			break;
		case 6:
			m20 = value;
			break;
		case 7:
			m21 = value;
			break;
		case 8:
			m22 = value;
			break;
	}
}

TEMPLATE
T Matrix3T::getElement(size_t row, size_t column) const _THROW_ERROR {

	if ( row >= 3 || column >= 3)
		REPORT_ERROR("Error: Out of Range Matrix3");

	const size_t index(column + 3 * row);

	T value = 0;

	switch (index){
		case 0:
			value = m00;
			break;
		case 1:
			value = m01;
			break;
		case 2:
			value = m02;
			break;
		case 3:
			value = m10;
			break;
		case 4:
			value = m11;
			break;
		case 5:
			value = m12;
			break;
		case 6:
			value = m20;
			break;
		case 7:
			value = m21;
			break;
		case 8:
			value = m22;
			break;
	}

	return value;
}

TEMPLATE
T& Matrix3T::getElementReference(size_t row, size_t column) _THROW_ERROR{

	if ( row >= 3 || column >= 3)
		REPORT_ERROR("Error: Out of Range Matrix3");

	const size_t index(column + 3 * row);

	switch (index){
		case 0:
			return m00;
			break;
		case 1:
			return m01;
			break;
		case 2:
			return m02;
			break;
		case 3:
			return m10;
			break;
		case 4:
			return m11;
			break;
		case 5:
			return m12;
			break;
		case 6:
			return m20;
			break;
		case 7:
			return m21;
			break;
		case 8:
			return m22;
			break;
	}

	static T dummy;
	return dummy;
}

TEMPLATE
void Matrix3T::setRow(size_t row, T x, T y, T z) {
    assert(row < 3);
    if (row == 0) {
        m00 = x;
        m01 = y;
        m02 = z;
    } else if (row == 1) {
        m10 = x;
        m11 = y;
        m12 = z;
    } else if (row == 2) {
        m20 = x;
        m21 = y;
        m22 = z;
    } else {

    }
}

TEMPLATE
void Matrix3T::setRow(size_t row, const Vector3T& v) {
    assert(row < 3);
    if (row == 0) {
        m00 = v.x;
        m01 = v.y;
        m02 = v.z;
    } else if (row == 1) {
        m10 = v.x;
        m11 = v.y;
        m12 = v.z;
    } else if (row == 2) {
        m20 = v.x;
        m21 = v.y;
        m22 = v.z;
    } else {
    }
}

TEMPLATE
void Matrix3T::setRow(size_t row, const T v[]) {
    assert(v != 0);
    assert(row < 3);
    if (row == 0) {
        m00 = v[0];
        m01 = v[1];
        m02 = v[2];
    } else if (row == 1) {
        m10 = v[0];
        m11 = v[1];
        m12 = v[2];
    } else if (row == 2) {
        m20 = v[0];
        m21 = v[1];
        m22 = v[2];
    } else {
    }
}

TEMPLATE
void Matrix3T::getRow(size_t row, T v[]) const {
    assert(v != 0);
    assert(row < 3);
    if (row == 0) {
        v[0] = m00;
        v[1] = m01;
        v[2] = m02;
    } else if (row == 1) {
        v[0] = m10;
        v[1] = m11;
        v[2] = m12;
    } else if (row == 2) {
        v[0] = m20;
        v[1] = m21;
        v[2] = m22;
    } else {
    }
}

TEMPLATE
void Matrix3T::getRow(size_t row, Vector3T* v) const {
    assert(v != 0);
    assert(row < 3);
    if (row == 0) {
        v->x = m00;
        v->y = m01;
        v->z = m02;
    } else if (row == 1) {
        v->x = m10;
        v->y = m11;
        v->z = m12;
    } else if (row == 2) {
        v->x = m20;
        v->y = m21;
        v->z = m22;
    } else {
    }
}

TEMPLATE
void Matrix3T::setColumn(size_t column, T x, T y, T z) {
    assert(column < 3);
    if (column == 0) {
        m00 = x;
        m10 = y;
        m20 = z;
    }  else if (column == 1) {
        m01 = x;
        m11 = y;
        m21 = z;
    } else if (column == 2) {
        m02 = x;
        m12 = y;
        m22 = z;
    } else {
    }
}

TEMPLATE
void Matrix3T::setColumn(size_t column, const Vector3T& v) {
    assert(column < 3);
    if (column == 0) {
        m00 = v.x;
        m10 = v.y;
        m20 = v.z;
    } else if (column == 1) {
        m01 = v.x;
        m11 = v.y;
        m21 = v.z;
    } else if (column == 2) {
        m02 = v.x;
        m12 = v.y;
        m22 = v.z;
    } else {
    }
}

TEMPLATE
void Matrix3T::setColumn(size_t column,  const T v[]) {
    assert(v != 0);
    assert(column < 3);
    if (column == 0) {
        m00 = v[0];
        m10 = v[1];
        m20 = v[2];
    } else if (column == 1) {
        m01 = v[0];
        m11 = v[1];
        m21 = v[2];
    } else if (column == 2) {
        m02 = v[0];
        m12 = v[1];
        m22 = v[2];
    } else {
    }
}


TEMPLATE
void Matrix3T::getColumn(size_t column, Vector3T* v) const {
    assert(column < 3);
    assert(v != 0);
    if (column == 0) {
        v->x = m00;
        v->y = m10;
        v->z = m20;
    } else if (column == 1) {
        v->x = m01;
        v->y = m11;
        v->z = m21;
    } else if (column == 2) {
        v->x = m02;
        v->y = m12;
        v->z = m22;
    } else {
    }
}

TEMPLATE
void Matrix3T::getColumn(size_t column,  T v[]) const {
    assert(column < 3);
    assert(v != 0);
    if (column == 0) {
        v[0] = m00;
        v[1] = m10;
        v[2] = m20;
    } else if (column == 1) {
        v[0] = m01;
        v[1] = m11;
        v[2] = m21;
    } else if (column == 2) {
        v[0] = m02;
        v[1] = m12;
        v[2] = m22;
    } else {
    }
}

TEMPLATE
T Matrix3T::getScale() const {
    return SVD(0);
}

TEMPLATE
void Matrix3T::add(T scalar) {
    m00 += scalar; m01 += scalar; m02 += scalar;
    m10 += scalar; m11 += scalar; m12 += scalar;
    m20 += scalar; m21 += scalar; m22 += scalar;
}

TEMPLATE
void Matrix3T::sub(T scalar) {
    add(-scalar);
}

TEMPLATE
void Matrix3T::add(T scalar, const Matrix3& m1) {
    set(m1);
    add(scalar);
}


TEMPLATE
void Matrix3T::add(const Matrix3& m1, const Matrix3& m2) {
    // note this is alias safe.
    set(
        m1.m00 + m2.m00,
        m1.m01 + m2.m01,
        m1.m02 + m2.m02,
        m1.m10 + m2.m10,
        m1.m11 + m2.m11,
        m1.m12 + m2.m12,
        m1.m20 + m2.m20,
        m1.m21 + m2.m21,
        m1.m22 + m2.m22
        );
}


TEMPLATE
void Matrix3T::add(const Matrix3& m1) {
    m00 += m1.m00; m01 += m1.m01; m02 += m1.m02;
    m10 += m1.m10; m11 += m1.m11; m12 += m1.m12;
    m20 += m1.m20; m21 += m1.m21; m22 += m1.m22;
}


TEMPLATE
void Matrix3T::sub(const Matrix3& m1, const Matrix3& m2) {
    // note this is alias safe.
    set(
        m1.m00 - m2.m00,
        m1.m01 - m2.m01,
        m1.m02 - m2.m02,
        m1.m10 - m2.m10,
        m1.m11 - m2.m11,
        m1.m12 - m2.m12,
        m1.m20 - m2.m20,
        m1.m21 - m2.m21,
        m1.m22 - m2.m22
        );
}

TEMPLATE
void Matrix3T::sub(const Matrix3& m1) {
    m00 -= m1.m00; m01 -= m1.m01; m02 -= m1.m02;
    m10 -= m1.m10; m11 -= m1.m11; m12 -= m1.m12;
    m20 -= m1.m20; m21 -= m1.m21; m22 -= m1.m22;
}


TEMPLATE
void Matrix3T::transpose() {
    T tmp = m01;
    m01 = m10;
    m10 = tmp;

    tmp = m02;
    m02 = m20;
    m20 = tmp;

    tmp = m12;
    m12 = m21;
    m21 = tmp;
}


TEMPLATE
void Matrix3T::transpose(const Matrix3& m1) {
    // alias-safe
    set(m1);
    transpose();
}


TEMPLATE
void Matrix3T::invert(const Matrix3& m1)  {
    // alias-safe way.
    set(m1);
    invert();
}


TEMPLATE
void Matrix3T::invert() {
    T s = determinant();
    // zero div may happen
    s = 1/s;
    // alias-safe way.
    set(
        m11*m22 - m12*m21, m02*m21 - m01*m22, m01*m12 - m02*m11,
        m12*m20 - m10*m22, m00*m22 - m02*m20, m02*m10 - m00*m12,
        m10*m21 - m11*m20, m01*m20 - m00*m21, m00*m11 - m01*m10
        );
    mul(s);
}


TEMPLATE
T Matrix3T::determinant() const {
    // less *,+,- calculation than expanded expression.
    return m00*(m11*m22 - m21*m12)
        - m01*(m10*m22 - m20*m12)
        + m02*(m10*m21 - m20*m11);
}


TEMPLATE
void Matrix3T::set(T scale) {
    m00 = scale; m01 = 0.0;   m02 = 0.0;
    m10 = 0.0;   m11 = scale; m12 = 0.0;
    m20 = 0.0;   m21 = 0.0;   m22 = scale;
}

TEMPLATE
void Matrix3T::rotX(T angle) {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
    m00 = 1.0; m01 = 0.0; m02 = 0.0;
    m10 = 0.0; m11 = c;   m12 = -s;
    m20 = 0.0; m21 = s;   m22 = c;
}

TEMPLATE
void Matrix3T::rotY(T angle) {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
    m00 = c;   m01 = 0.0; m02 = s;
    m10 = 0.0; m11 = 1.0; m12 = 0.0;
    m20 = -s;  m21 = 0.0; m22 = c;
}

TEMPLATE
void Matrix3T::rotZ(T angle) {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
    m00 = c;   m01 = -s;  m02 = 0.0;
    m10 = s;   m11 = c;   m12 = 0.0;
    m20 = 0.0; m21 = 0.0; m22 = 1.0;
}

TEMPLATE
void Matrix3T::mul(T scalar) {
    m00 *= scalar; m01 *= scalar;  m02 *= scalar;
    m10 *= scalar; m11 *= scalar;  m12 *= scalar;
    m20 *= scalar; m21 *= scalar;  m22 *= scalar;
}

TEMPLATE
void Matrix3T::mul(T scalar, const Matrix3& m1) {
    set(m1);
    mul(scalar);
}

TEMPLATE
void Matrix3T::mul(const Matrix3& m1) {
    mul(*this, m1);
}


TEMPLATE
void Matrix3T::mul(const Matrix3& m1, const Matrix3& m2) {
    // alias-safe way.
    set(
        m1.m00*m2.m00 + m1.m01*m2.m10 + m1.m02*m2.m20,
        m1.m00*m2.m01 + m1.m01*m2.m11 + m1.m02*m2.m21,
        m1.m00*m2.m02 + m1.m01*m2.m12 + m1.m02*m2.m22,

        m1.m10*m2.m00 + m1.m11*m2.m10 + m1.m12*m2.m20,
        m1.m10*m2.m01 + m1.m11*m2.m11 + m1.m12*m2.m21,
        m1.m10*m2.m02 + m1.m11*m2.m12 + m1.m12*m2.m22,

        m1.m20*m2.m00 + m1.m21*m2.m10 + m1.m22*m2.m20,
        m1.m20*m2.m01 + m1.m21*m2.m11 + m1.m22*m2.m21,
        m1.m20*m2.m02 + m1.m21*m2.m12 + m1.m22*m2.m22
        );
}

TEMPLATE
void Matrix3T::mulTransposeRight(const Matrix3& m1, const Matrix3& m2) {
    // alias-safe way.
    set(
        m1.m00*m2.m00 + m1.m01*m2.m01 + m1.m02*m2.m02,
        m1.m00*m2.m10 + m1.m01*m2.m11 + m1.m02*m2.m12,
        m1.m00*m2.m20 + m1.m01*m2.m21 + m1.m02*m2.m22,

        m1.m10*m2.m00 + m1.m11*m2.m01 + m1.m12*m2.m02,
        m1.m10*m2.m10 + m1.m11*m2.m11 + m1.m12*m2.m12,
        m1.m10*m2.m20 + m1.m11*m2.m21 + m1.m12*m2.m22,

        m1.m20*m2.m00 + m1.m21*m2.m01 + m1.m22*m2.m02,
        m1.m20*m2.m10 + m1.m21*m2.m11 + m1.m22*m2.m12,
        m1.m20*m2.m20 + m1.m21*m2.m21 + m1.m22*m2.m22
        );
}

TEMPLATE
void Matrix3T::mulTransposeLeft(const Matrix3& m1, const Matrix3& m2) {
    // alias-safe way.
    set(
        m1.m00*m2.m00 + m1.m10*m2.m10 + m1.m20*m2.m20,
        m1.m00*m2.m01 + m1.m10*m2.m11 + m1.m20*m2.m21,
        m1.m00*m2.m02 + m1.m10*m2.m12 + m1.m20*m2.m22,

        m1.m01*m2.m00 + m1.m11*m2.m10 + m1.m21*m2.m20,
        m1.m01*m2.m01 + m1.m11*m2.m11 + m1.m21*m2.m21,
        m1.m01*m2.m02 + m1.m11*m2.m12 + m1.m21*m2.m22,

        m1.m02*m2.m00 + m1.m12*m2.m10 + m1.m22*m2.m20,
        m1.m02*m2.m01 + m1.m12*m2.m11 + m1.m22*m2.m21,
        m1.m02*m2.m02 + m1.m12*m2.m12 + m1.m22*m2.m22
        );
}


TEMPLATE
bool Matrix3T::equals(const Matrix3& m1) const {
    return  m00 == m1.m00
        && m01 == m1.m01
        && m02 == m1.m02 
        && m10 == m1.m10
        && m11 == m1.m11
        && m12 == m1.m12
        && m20 == m1.m20
        && m21 == m1.m21
        && m22 == m1.m22;
}

TEMPLATE
bool Matrix3T::epsilonEquals(const Matrix3& m1, T epsilon) const {
    return  abs(m00 - m1.m00) <= epsilon
        && abs(m01 - m1.m01) <= epsilon
        && abs(m02 - m1.m02 ) <= epsilon

        && abs(m10 - m1.m10) <= epsilon
        && abs(m11 - m1.m11) <= epsilon
        && abs(m12 - m1.m12) <= epsilon

        && abs(m20 - m1.m20) <= epsilon
        && abs(m21 - m1.m21) <= epsilon
        && abs(m22 - m1.m22) <= epsilon;
}


TEMPLATE
void Matrix3T::setZero() {
    m00 = 0.0; m01 = 0.0; m02 = 0.0;
    m10 = 0.0; m11 = 0.0; m12 = 0.0;
    m20 = 0.0; m21 = 0.0; m22 = 0.0;
}

TEMPLATE
void Matrix3T::negate() {
    m00 = -m00; m01 = -m01; m02 = -m02;
    m10 = -m10; m11 = -m11; m12 = -m12;
    m20 = -m20; m21 = -m21; m22 = -m22;
}


TEMPLATE
void Matrix3T::transform(const Tuple3T& t, Tuple3T* result) const {
    // alias-safe
    result->set(
                m00*t.x + m01*t.y + m02*t.z,
                m10*t.x + m11*t.y + m12*t.z,
                m20*t.x + m21*t.y + m22*t.z
                );
}


TEMPLATE
T Matrix3T::SVD(Matrix3* rot) const {
    // this is a simple svd.
    // Not complete but fast and reasonable.

        /*
         * SVD scale factors(squared) are the 3 roots of
         * 
         *     | xI - M*MT | = 0.
         * 
         * This will be expanded as follows
         * 
         * x^3 - A x^2 + B x - C = 0
         * 
         * where A, B, C can be denoted by 3 roots x0, x1, x2.
         *
         * A = (x0+x1+x2), B = (x0x1+x1x2+x2x0), C = x0x1x2.
         *
         * An avarage of x0,x1,x2 is needed here. C^(1/3) is a cross product
         * normalization factor.
         * So here, I use A/3. Note that x should be sqrt'ed for the
         * actual factor.
         */

    T s = UtilT::sqrt((
                   m00*m00 + m10*m10 + m20*m20 + 
                   m01*m01 + m11*m11 + m21*m21 +
                   m02*m02 + m12*m12 + m22*m22
                   )/3.0
                  );

    if (rot) {
        // zero-div may occur.
        double n = 1/UtilT::sqrt(m00*m00 + m10*m10 + m20*m20);
        rot->m00 = m00*n;
        rot->m10 = m10*n;
        rot->m20 = m20*n;

        n = 1/UtilT::sqrt(m01*m01 + m11*m11 + m21*m21);
        rot->m01 = m01*n;
        rot->m11 = m11*n;
        rot->m21 = m21*n;

        n = 1/UtilT::sqrt(m02*m02 + m12*m12 + m22*m22);
        rot->m02 = m02*n;
        rot->m12 = m12*n;
        rot->m22 = m22*n;
    }

    return s;
}


TEMPLATE
void Matrix3T::setFromQuat(T x, T y, T z, T w) {
    T n = x*x + y*y + z*z + w*w;
    T s = (n > 0.0) ? (2.0/n) : 0.0;

    T xs = x*s,  ys = y*s,  zs = z*s;
    T wx = w*xs, wy = w*ys, wz = w*zs;
    T xx = x*xs, xy = x*ys, xz = x*zs;
    T yy = y*ys, yz = y*zs, zz = z*zs;

    m00 = 1.0 - (yy + zz); m01 = xy - wz;         m02 = xz + wy;
    m10 = xy + wz;         m11 = 1.0 - (xx + zz); m12 = yz - wx;
    m20 = xz - wy;         m21 = yz + wx;         m22 = 1.0 - (xx + yy);
}

TEMPLATE
void Matrix3T::setFromAxisAngle(T x, T y, T z, T angle) {
    // Taken from Rick's which is taken from Wertz. pg. 412
    // Bug Fixed and changed into right-handed by hiranabe
    T n = UtilT::sqrt(x*x + y*y + z*z);
    // zero-div may occur
    n = 1/n;
    x *= n;
    y *= n;
    z *= n;
    T c = UtilT::cos(angle);
    T s = UtilT::sin(angle);
    T omc = 1.0 - c;
    m00 = c + x*x*omc;
    m11 = c + y*y*omc;
    m22 = c + z*z*omc;

    T tmp1 = x*y*omc;
    T tmp2 = z*s;
    m01 = tmp1 - tmp2;
    m10 = tmp1 + tmp2;

    tmp1 = x*z*omc;
    tmp2 = y*s;
    m02 = tmp1 + tmp2;
    m20 = tmp1 - tmp2;

    tmp1 = y*z*omc;
    tmp2 = x*s;
    m12 = tmp1 - tmp2;
    m21 = tmp1 + tmp2;
}

#ifdef USE_TOSTRING
TEMPLATE
STD::string Matrix3T::toString() const {
    VM_TOSTRING
}
#endif /* USE_TOSTRING */

END_NAMESPACE

#ifdef USE_IO
TEMPLATE
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Matrix3T& t1) {
    return  o << 
        "[ ["<<t1.m00<<","<<t1.m01<<","<<t1.m02<<"]" << STD::endl <<
        "  ["<<t1.m10<<","<<t1.m11<<","<<t1.m12<<"]" << STD::endl <<
        "  ["<<t1.m20<<","<<t1.m21<<","<<t1.m22<<"] ]";
}
#endif /* USE_IO */

BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Matrix3<double> Matrix3d;
typedef Matrix3<float> Matrix3f;
#else
typedef Matrix3 Matrix3d;
typedef Matrix3 Matrix3f;
#endif


END_NAMESPACE

#endif /* MATRIX3__H */
