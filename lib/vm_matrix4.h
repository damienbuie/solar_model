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
 
#ifndef MATRIX4__H
#define MATRIX4__H

#include <vm_configure.h>
#include <vm_utility.h>

#include <vm_matrix3.h>
#include <vm_vector4.h>
#include <vm_point4.h>

BEGIN_NAMESPACE

TEMPLATE
class Matrix4 {
protected:
    static T abs(T t) { return UtilT::abs(t); }

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
    enum { DIMENSION = 4 };
    /**
     * the type for tuple
     */
    typedef Tuple4T tuple_type;
    /**
     * the type for vector
     */
    typedef Vector4T vector_type;
    /**
     * the type for point
     */
    typedef Point4T point_type;

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
      * The fourth element of the first row.
      */
    T m03;

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
      * The fourth element of the second row.
      */
    T m13;

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
      * The fourth element of the third row.
      */
    T m23;

    /**
      * The first element of the fourth row.
      */
    T m30;

    /**
      * The second element of the fourth row.
      */
    T m31;

    /**
      * The third element of the fourth row.
      */
    T m32;

    /**
      * The fourth element of the fourth row.
      */
    T m33;

    /**
      * Constructs and initializes a Matrix4 from the specified 16 values.
      * @param m00 the [0][0] element
      * @param m01 the [0][1] element
      * @param m02 the [0][2] element
      * @param m03 the [0][3] element
      * @param m10 the [1][0] element
      * @param m11 the [1][1] element
      * @param m12 the [1][2] element
      * @param m13 the [1][3] element
      * @param m20 the [2][0] element
      * @param m21 the [2][1] element
      * @param m22 the [2][2] element
      * @param m23 the [2][3] element
      * @param m30 the [3][0] element
      * @param m31 the [3][1] element
      * @param m32 the [3][2] element
      * @param m33 the [3][3] element
      */
    Matrix4(T m00, T m01, T m02, T m03, 
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33);

    /**
      * Constructs and initializes a Matrix4 from the specified 16
      * element array.  this.m00 =v[0], this.m01=v[1], etc.
      * @param  v the array of length 16 containing in order
      */
    Matrix4(const T v[]);

    /**
      * Constructs and initializes a Matrix4 from the specified 4x4
      * element array.  this.m00 =m[0][0], this.m01=m[0][1], etc.
      * @param  m the array of 4 x 4 containing in order
      */
    Matrix4(const T m[][4]);

    /**
      * Constructs and initializes a Matrix4 from the quaternion,
      * translation, and scale values; the scale is applied only to the
      * rotational components of the matrix (upper 3x3) and not to the
      * translational components.
      * @param q1  The quaternion value representing the rotational component
      * @param t1  The translational component of the matrix
      * @param s  The scale value applied to the rotational components
      */
    Matrix4(const Quat4T& q1, const Vector3T& t1, T s);

#if 0
    /**
      * Constructs and initializes a Matrix4 from the quaternion,
      * translation, and scale values; the scale is applied only to the
      * rotational components of the matrix (upper 3x3) and not to the
      * translational components.
      * @param q1  The quaternion value representing the rotational component
      * @param t1  The translational component of the matrix
      * @param s  The scale value applied to the rotational components
      */
    Matrix4(Quat4f q1, Vector3d t1, T s) {
	set(q1, t1, s);
    }

    /**
      * Constructs a new matrix with the same values as the Matrix4f parameter.
      * @param m1 The source matrix.
      */
    Matrix4(Matrix4f m1) {
	set(m1);
    }

    /**
      * Constructs and initializes a Matrix4 from the rotation matrix,
      * translation, and scale values; the scale is applied only to the
      * rotational components of the matrix (upper 3x3) and not to the
      * translational components.
      * @param m1  The rotation matrix representing the rotational components
      * @param t1  The translational components of the matrix
      * @param s  The scale value applied to the rotational components
      */
    Matrix4(Matrix3f m1, Vector3d t1, T s) {
	// why no set(Matrix3f, Vector3d, T) ?
	// set(Matrix3f, Vector3f, float) is there.
	// feel inconsistent.
	set(m1);
	mulRotationScale(s);
	setTranslation(t1);
	m33 = 1.0;
    }
#endif

    /**
      * Constructs and initializes a Matrix4 from the rotation matrix,
      * translation, and scale values; the scale is applied only to the
      * rotational components of the matrix (upper 3x3) and not to the
      * translational components.
      * @param m1  The rotation matrix representing the rotational components
      * @param t1  The translational components of the matrix
      * @param s  The scale value applied to the rotational components
      */
    Matrix4(const Matrix3T& m1, const Vector3T& t1, T s);

    /**
      * Constructs and initializes a Matrix4 to all zeros.
      */
    Matrix4();

    /**
      * Sets 16 values	
      * @param m00 the [0][0] element
      * @param m01 the [0][1] element
      * @param m02 the [0][2] element
      * @param m03 the [0][3] element
      * @param m10 the [1][0] element
      * @param m11 the [1][1] element
      * @param m12 the [1][2] element
      * @param m13 the [1][3] element
      * @param m20 the [2][0] element
      * @param m21 the [2][1] element
      * @param m22 the [2][2] element
      * @param m23 the [2][3] element
      * @param m30 the [3][0] element
      * @param m31 the [3][1] element
      * @param m32 the [3][2] element
      * @param m33 the [3][3] element
      */
    void set(T m00, T m01, T m02, T m03, 
             T m10, T m11, T m12, T m13,
             T m20, T m21, T m22, T m23,
             T m30, T m31, T m32, T m33);

    /**
      * Sets the values in this Matrix4 equal to the row-major array parameter
      * (ie, the first four elements of the array will be copied into the first
      * row of this matrix, etc.).
      */
    void set(const T m[]);

    /**
      * Sets the values in this Matrix4 equal to the row-major array parameter
      * (ie, the first four elements of the array will be copied into the first
      * row of this matrix, etc.).
      */
    void set(const T m[][4]);

    /**
      * Sets the value of this matrix to a copy of the
      * passed matrix m1.
      * @param m1 the matrix to be copied
      */
    void set(const Matrix4T& m1);

    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * values in the T precision Matrix3d argument; the other elements of
      * this matrix are initialized as if this were an identity matrix
      * (ie, affine matrix with no translational component).
      * @param m1 the 3x3 matrix
      */
    void set(const Matrix3T& m1);

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * (T precision) quaternion argument. 
      * @param q1 the quaternion to be converted 
      */
    void set(const Quat4T& q1);

    /**
      * Sets the value of this matrix to the matrix conversion of the
      * T precision axis and angle argument. 
      * @param a1 the axis and angle to be converted 
      */
    void set(const AxisAngle4T& a1);

    /**
     * Sets this Matrix4 to identity.
     */
    void setIdentity();

    /**
     * Sets the specified element of this matrix4d to the value provided.
     * @param row  the row number to be modified (zero indexed)
     * @param column  the column number to be modified (zero indexed)
     * @param value the new value
     */
    void setElement(size_t row, size_t column, T value) _THROW_ERROR;

    /**
     * Retrieves the value at the specified row and column of this matrix.
     * @param row  the row number to be retrieved (zero indexed)
     * @param column  the column number to be retrieved (zero indexed)
     * @return the value at the indexed element
     */
    T getElement(size_t row, size_t column) const _THROW_ERROR;

    /**
     * Retrieves the lvalue at the specified row and column of this matrix.
     * @param row  the row number to be retrieved (zero indexed)
     * @param column  the column number to be retrieved (zero indexed)
     * @return the lvalue at the indexed element
     */
    T& getElementReference(size_type row, size_type column) _THROW_ERROR;

    /**
      * Performs an SVD normalization of this matrix in order to acquire the
      * normalized rotational component; the values are placed into the Matrix3d parameter.
      * @param m1 matrix into which the rotational component is placed
      */
    void get(Matrix3T* m1) const;

#if 0
    /**
      * Performs an SVD normalization of this matrix in order to acquire the
      * normalized rotational component; the values are placed into the Matrix3f parameter.
      * @param m1 matrix into which the rotational component is placed
      */
    void get(Matrix3f m1) const{
	SVD(m1);
    }
#endif

    /**
      * Performs an SVD normalization of this matrix to calculate the rotation
      * as a 3x3 matrix, the translation, and the scale. None of the matrix values are modified.
      * @param m1 The normalized matrix representing the rotation
      * @param t1 The translation component
      * @return The scale component of this transform
      */
    T get(Matrix3T* m1, Vector3T* t1) const;

    /**
      * Performs an SVD normalization of this matrix in order to acquire the
      * normalized rotational component; the values are placed into
      * the Quat4f parameter.
      * @param q1 quaternion into which the rotation component is placed
      */
    void get(Quat4T* q1) const;

#if 0
    /**
      * Performs an SVD normalization of this matrix to calculate the rotation
      * as a 3x3 matrix, the translation, and the scale. None of the matrix values are modified.
      * @param m1 The normalized matrix representing the rotation
      * @param t1 The translation component
      * @return The scale component of this transform
      */
    T get(Matrix3f m1, Vector3d t1) {
	get(t1);
	return SVD(m1);
    }

    /**
      * Performs an SVD normalization of this matrix in order to acquire the
      * normalized rotational component; the values are placed into
      * the Quat4f parameter.
      * @param q1 quaternion into which the rotation component is placed
      */
    void get(Quat4f q1) {
	q1.set(this);
	q1.normalize();
    }


    /**
      * Gets the upper 3x3 values of this matrix and places them into the matrix m1.
      * @param m1 The matrix that will hold the values
      */
    void getRotationScale(Matrix3f m1) {
	m1.m00 = (float)m00; m1.m01 = (float)m01; m1.m02 = (float)m02;
	m1.m10 = (float)m10; m1.m11 = (float)m11; m1.m12 = (float)m12;
	m1.m20 = (float)m20; m1.m21 = (float)m21; m1.m22 = (float)m22;
    }
#endif

    /**
      * Retrieves the translational components of this matrix.
      * @param trans the vector that will receive the translational component
      */
    void get(Vector3T* trans) const {
        assert(trans != 0);
        trans->x = m03;
        trans->y = m13;
        trans->z = m23;
    }


    /**
      * Gets the upper 3x3 values of this matrix and places them into the matrix m1.
      * @param m1 The matrix that will hold the values
      */
    void getRotationScale(Matrix3T* m1) const;

    /**
      * Performs an SVD normalization of this matrix to calculate and return the
      * uniform scale factor. This matrix is not modified.
      * @return the scale factor of this matrix
      */
    T getScale() const;

    /**
      * Replaces the upper 3x3 matrix values of this matrix with the values in the matrix m1.
      * @param m1 The matrix that will be the new upper 3x3
      */
    void setRotationScale(const Matrix3T& m1);

#if 0
    /**
      * Replaces the upper 3x3 matrix values of this matrix with the values in the matrix m1.
      * @param m1 The matrix that will be the new upper 3x3
      */
    void setRotationScale(Matrix3f m1) {
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02;
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22;
    }
#endif

    /**
      * Sets the scale component of the current matrix by factoring out the
      * current scale (by doing an SVD) from the rotational component and
      * multiplying by the new scale.
      * note: this method doesn't change m44.
      * @param scale the new scale amount
      */
    void setScale(T scale);

    /**
     * Sets the specified row of this matrix4d to the four values provided.
     * @param row  the row number to be modified (zero indexed)
     * @param x the first column element
     * @param y the second column element
     * @param z the third column element
     * @param w the fourth column element
     */
    void setRow(size_t row, T x, T y, T z, T w);

    /**
     * Sets the specified row of this matrix4d to the Vector provided.
     * @param row the row number to be modified (zero indexed)
     * @param v the replacement row
     */
    void setRow(size_t row, const Vector4T& v);

    /**
      * Sets the specified row of this matrix4d to the four values provided.
      * @param row the row number to be modified (zero indexed)
      * @param v the replacement row
      */
    void setRow(size_t row, const T v[]);

    /**
     * Copies the matrix values in the specified row into the
     * vector parameter.
     * @param row the matrix row
     * @param v The vector into which the matrix row values will be copied
     */
    void getRow(size_t row, Vector4T* v) const;

    /**
      * Copies the matrix values in the specified row into the
      * array parameter.
      * @param row the matrix row
      * @param v The array into which the matrix row values will be copied
      */
    void getRow(size_t row, T v[]) const;

    /**
      * Sets the specified column of this matrix4d to the four values provided.
      * @param  column the column number to be modified (zero indexed)
      * @param x the first row element
      * @param y the second row element
      * @param z the third row element
      * @param w the fourth row element
      */
    void setColumn(size_t column, T x, T y, T z, T w);

    /**
      * Sets the specified column of this matrix4d to the vector provided.
      * @param column the column number to be modified (zero indexed)
      * @param v the replacement column
      */
    void setColumn(size_t column, const Vector4T& v);

    /**
      * Sets the specified column of this matrix4d to the four values provided. 
      * @param column  the column number to be modified (zero indexed) 
      * @param v       the replacement column 
      */
    void setColumn(size_t column,  const T v[]);

    /**
     * Copies the matrix values in the specified column into the
     * vector parameter.
     * @param column the matrix column
     * @param v The vector into which the matrix column values will be copied
     */
    void getColumn(size_t column, Vector4T* v) const;

    /**
      * Copies the matrix values in the specified column into the
      * array parameter.
      * @param column the matrix column
      * @param v The array into which the matrix column values will be copied
      */
    void getColumn(size_t column, T v[]) const;

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
      * @param scalar The scalar adder.
      * @parm m1 The original matrix values.
      */
    void add(T scalar, const Matrix4& m1) {
        set(m1);
        add(scalar);
    }

    /**
     * Sets the value of this matrix to the matrix sum of matrices m1 and m2. 
     * @param m1 the first matrix 
     * @param m2 the second matrix 
     */
    void add(const Matrix4& m1, const Matrix4& m2);

    /**
     * Sets the value of this matrix to sum of itself and matrix m1. 
     * @param m1 the other matrix 
     */
    void add(const Matrix4& m1);

    /**
      * Sets the value of this matrix to the matrix difference
      * of matrices m1 and m2. 
      * @param m1 the first matrix 
      * @param m2 the second matrix 
      */
    void sub(const Matrix4& m1, const Matrix4& m2);

    /**
     * Sets the value of this matrix to the matrix difference of itself
     * and matrix m1 (this = this - m1). 
     * @param m1 the other matrix 
     */
    void sub(const Matrix4& m1);

    /**
      * Sets the value of this matrix to its transpose. 
      */
    void transpose();

    /**
     * Sets the value of this matrix to the transpose of the argument matrix
     * @param m1 the matrix to be transposed 
     */
    void transpose(const Matrix4& m1) {
        // alias-safe
        set(m1);
        transpose();
    }

#if 0
    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * values in the single precision Matrix3f argument; the other elements of
      * this matrix are initialized as if this were an identity matrix
      * (ie, affine matrix with no translational component).
      * @param m1 the 3x3 matrix
      */
    void set(Matrix3f m1)  {
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; m03 = 0.0;
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12; m13 = 0.0;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; m23 = 0.0;
	m30 =    0.0; m31 =    0.0; m32 =    0.0; m33 = 1.0;
    }

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
#endif

  /**
    * Sets the value of this matrix from the rotation expressed by the
    * quaternion q1, the translation t1, and the scale s.
    * @param q1  the rotation expressed as a quaternion
    * @param t1  the translation
    * @param s  the scale value
    */
    void set(const Quat4T& q1, const Vector3T& t1, T s);

#if 0
  /**
    * Sets the value of this matrix from the rotation expressed by the
    * quaternion q1, the translation t1, and the scale s.
    * @param q1  the rotation expressed as a quaternion
    * @param t1  the translation
    * @param s  the scale value
    */
    void set(Quat4f q1, Vector3d t1, T s) {
        set(q1);
        mulRotationScale(s);
        m03 = t1.x;
        m13 = t1.y;
        m23 = t1.z;
    }

  /**
    * Sets the value of this matrix from the rotation expressed by the
    * quaternion q1, the translation t1, and the scale s.
    * @param q1  the rotation expressed as a quaternion
    * @param t1  the translation
    * @param s  the scale value
    */
    void set(Quat4f q1, Vector3f t1, float s) {
	set(q1);
	mulRotationScale(s);
	m03 = t1.x;
	m13 = t1.y;
	m23 = t1.z;
    }

    /**
      * Sets the value of this matrix to the T value of the
      * passed matrix4f.
      * @param m1 the matrix4f
      */
    void set(Matrix4f m1) {
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; m03 = m1.m03;
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12; m13 = m1.m13;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; m23 = m1.m23;
	m30 = m1.m30; m31 = m1.m31; m32 = m1.m32; m33 = m1.m33;
    }
#endif

    /**
     * Sets the value of this matrix to the matrix inverse
     * of the passed matrix m1. 
     * @param m1 the matrix to be inverted 
     */
    void invert(const Matrix4T& m1);

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
      * Modifies the translational components of this matrix to the values of
      * the Vector3d argument; the other values of this matrix are not modified.
      * @param trans the translational component
      */
    void setTranslation(const Vector3T& trans) {
        m03 = trans.x;
        m13 = trans.y;  
        m23 = trans.z;
    }

    /**
     * Sets the value of this matrix to a translate matrix by the
     * passed translation value.
     * @param v1 the translation amount
     */
    void set(const Vector3T& v1) {
        setIdentity();
        setTranslation(v1);
    }

    /**
     * Sets the value of this matrix to a scale and translation matrix;
     * scale is not applied to the translation and all of the matrix
     * values are modified.
     * @param scale the scale factor for the matrix
     * @param v1 the translation amount
     */
    void set(T scale, const Vector3T& v1) {
        set(scale);
        setTranslation(v1);
    }

    /**
     * Sets the value of this matrix to a scale and translation matrix;
     * the translation is scaled by the scale factor and all of the
     * matrix values are modified.
     * @param v1 the translation amount
     * @param scale the scale factor for the matrix
     */
    void set(const Vector3T& v1, T scale);

#if 0
    /**
      * Sets the value of this matrix from the rotation expressed by the
      * rotation matrix m1, the translation t1, and the scale s. The translation
      * is not modified by the scale.
      * @param m1 The rotation component
      * @param t1 The translation component
      * @param scale The scale component
      */
    void set(Matrix3f m1, Vector3f t1, float scale) {
	setRotationScale(m1);
	mulRotationScale(scale);
	setTranslation(t1);
	m33 = 1.0;
    }
#endif

    /**
      * Sets the value of this matrix from the rotation expressed by the
      * rotation matrix m1, the translation t1, and the scale s. The translation
      * is not modified by the scale.
      * @param m1 The rotation component
      * @param t1 The translation component
      * @param scale The scale component
      */
    void set(const Matrix3T& m1, const Vector3T& t1, T scale);

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
     void mul(T scalar, const Matrix4& m1) {
         set(m1);
         mul(scalar);
     }

    /**
     * Sets the value of this matrix to the result of multiplying itself
     * with matrix m1. 
     * @param m1 the other matrix 
     */
    void mul(const Matrix4& m1) {
        mul(*this, m1);
    }

    /**
     * Sets the value of this matrix to the result of multiplying
     * the two argument matrices together. 
     * @param m1 the first matrix 
     * @param m2 the second matrix 
     */
    void mul(const Matrix4& m1, const Matrix4& m2);

    /**
      * Multiplies the transpose of matrix m1 times the transpose of matrix m2,
      * and places the result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeBoth(const Matrix4& m1, const Matrix4& m2) {
        mul(m2, m1);
        transpose();
    }

    /**
      * Multiplies matrix m1 times the transpose of matrix m2, and places the
      * result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeRight(const Matrix4& m1, const Matrix4& m2);
    
    /**
      * Multiplies the transpose of matrix m1 times matrix m2, and places the
      * result into this.
      * @param m1 The matrix on the left hand side of the multiplication
      * @param m2 The matrix on the right hand side of the multiplication
      */
    void mulTransposeLeft(const Matrix4& m1, const Matrix4& m2);

    /**
     * Returns true if all of the data members of Matrix4 m1 are
     * equal to the corresponding data members in this Matrix4. 
     * @param m1 The matrix with which the comparison is made. 
     * @return true or false 
     */
    bool equals(const Matrix4& m1) const;

    /**
      * Returns true if the L-infinite distance between this matrix and matrix
      * m1 is less than or equal to the epsilon parameter, otherwise returns
      * false. The L-infinite distance is equal to MAX[i=0,1,2,3 ; j=0,1,2,3 ;
      * abs(this.m(i,j) - m1.m(i,j)]
      * @param m1 The matrix to be compared to this matrix
      * @param epsilon the threshold value
      */
    bool epsilonEquals(const Matrix4& m1, T epsilon) const;

    /**
     * Returns a hash number based on the data values in this
     * object.  Two different Matrix4 objects with identical data values
     * (ie, returns true for equals(Matrix4) ) will return the same hash
     * number.  Two objects with different data members may return the
     * same hash value, although this is not likely.
     * @return the integer hash value 
     */
    size_t hashCode() const {
        return UtilT::hashCode(sizeof *this, this);
    }

    /**
     * Transform the vector vec using this Matrix4 and place the
     * result into vecOut.
     * @param vec the T precision vector to be transformed
     * @param vecOut the vector into which the transformed values are placed
     */
    void transform(const Tuple4T& vec, Tuple4T* vecOut) const;

    /**
     * Transform the vector vec using this Matrix4 and place the
     * result back into vec.
     * @param vec the T precision vector to be transformed
     */
    void transform(Tuple4T* vec) const {
        transform(*vec, vec);
    }

#if 0
    /**
     * Transform the vector vec using this Matrix4 and place the
     * result into vecOut.
     * @param vec the single precision vector to be transformed
     * @param vecOut the vector into which the transformed values are placed
     */
    void transform(Tuple4f vec, Tuple4f vecOut) {
	// alias-safe
	vecOut.set(
	    (float)(m00*vec.x + m01*vec.y + m02*vec.z + m03*vec.w),
	    (float)(m10*vec.x + m11*vec.y + m12*vec.z + m13*vec.w),
	    (float)(m20*vec.x + m21*vec.y + m22*vec.z + m23*vec.w),
	    (float)(m30*vec.x + m31*vec.y + m32*vec.z + m33*vec.w)
	    );
    }


    /**
     * Transform the vector vec using this Matrix4 and place the
     * result back into vec.
     * @param vec the single precision vector to be transformed
     */
    void transform(Tuple4f vec)  {
	transform(vec, vec);
    }
#endif

    /**
      * Transforms the point parameter with this Matrix4 and places the result
      * into pointOut. The fourth element of the point input paramter is assumed
      * to be one.
      * @param point the input point to be transformed.
      * @param pointOut the transformed point
      */
    void transform(const Point3T& point, Point3T* pointOut) const;


    /**
     * Transforms the point parameter with this Matrix4 and
     * places the result back into point.  The fourth element of the
     * point input paramter is assumed to be one.
     * @param point the input point to be transformed.
     */
    void transform(Point3T* point) const {
        assert(point != 0);
        transform(*point, point);
    }

#if 0
    /**
      * Transforms the point parameter with this Matrix4 and places the result
      * into pointOut. The fourth element of the point input paramter is assumed
      * to be one.
      * @param point the input point to be transformed.
      * @param pointOut the transformed point
      */
    void transform(Point3f point, Point3f pointOut) {
	pointOut.set(
	    (float)(m00*point.x + m01*point.y + m02*point.z + m03),
	    (float)(m10*point.x + m11*point.y + m12*point.z + m13),
	    (float)(m20*point.x + m21*point.y + m22*point.z + m23)
	    );
    }

    /**
     * Transforms the point parameter with this Matrix4 and
     * places the result back into point.  The fourth element of the
     * point input paramter is assumed to be one.
     * @param point the input point to be transformed.
     */
    void transform(Point3f point) {
	transform(point, point);
    }
#endif

    /**
     * Transforms the normal parameter by this Matrix4 and places the value
     * into normalOut.  The fourth element of the normal is assumed to be zero.
     * @param normal the input normal to be transformed.
     * @param normalOut the transformed normal
     */
    void transform(const Vector3T& normal, Vector3T* normalOut) const;

    /**
     * Transforms the normal parameter by this transform and places the value
     * back into normal.  The fourth element of the normal is assumed to be zero.
     * @param normal the input normal to be transformed.
     */
    void transform(Vector3T* normal) const {
        assert(normal != 0);
        transform(*normal, normal);
    }

#if 0
    /**
     * Transforms the normal parameter by this Matrix4 and places the value
     * into normalOut.  The fourth element of the normal is assumed to be zero.
     * @param normal the input normal to be transformed.
     * @param normalOut the transformed normal
     */
    void transform(Vector3f normal, Vector3f normalOut) {
	normalOut.set(
	    (float)(m00 * normal.x + m01 * normal.y + m02 * normal.z),
	    (float)(m10 * normal.x + m11 * normal.y + m12 * normal.z),
	    (float)(m20 * normal.x + m21 * normal.y + m22 * normal.z)
	    );
    }

    /**
     * Transforms the normal parameter by this transform and places the value
     * back into normal.  The fourth element of the normal is assumed to be zero.
     * @param normal the input normal to be transformed.
     */
    void transform(Vector3f normal) {
	transform(normal, normal);
    }
#endif

    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * values in the T precision Matrix3d argument; the other elements of
      * this matrix are unchanged; a singular value decomposition is performed
      * on this object's upper 3x3 matrix to factor out the scale, then this
      * object's upper 3x3 matrix components are replaced by the passed rotation
      * components, and then the scale is reapplied to the rotational
      * components.
      * @param m1 T precision 3x3 matrix
      */
    void setRotation(const Matrix3T& m1);

#if 0
    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * values in the single precision Matrix3f argument; the other elements of
      * this matrix are unchanged; a singular value decomposition is performed
      * on this object's upper 3x3 matrix to factor out the scale, then this
      * object's upper 3x3 matrix components are replaced by the passed rotation
      * components, and then the scale is reapplied to the rotational
      * components.
      * @param m1 single precision 3x3 matrix
      */
    void setRotation(Matrix3f m1) {
        T scale = SVD(null, null);
        setRotationScale(m1);
        mulRotationScale(scale);
    }

    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * equivalent values of the quaternion argument; the other elements of this
      * matrix are unchanged; a singular value decomposition is performed on
      * this object's upper 3x3 matrix to factor out the scale, then this
      * object's upper 3x3 matrix components are replaced by the matrix
      * equivalent of the quaternion, and then the scale is reapplied to the
      * rotational components.
      * @param q1 the quaternion that specifies the rotation
      */
    void setRotation(Quat4f q1) {
	T scale = SVD(null, null);

	// save other values
	T tx = m03; 
	T ty = m13; 
	T tz = m23; 
	T w0 = m30;                  
	T w1 = m31;
	T w2 = m32;
	T w3 = m33;

	set(q1);
	mulRotationScale(scale);

	// set back
	m03 = tx;
	m13 = ty;
	m23 = tz;
	m30 = w0;
	m31 = w1;
	m32 = w2;
	m33 = w3;
    }
#endif

    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * equivalent values of the quaternion argument; the other elements of this
      * matrix are unchanged; a singular value decomposition is performed on
      * this object's upper 3x3 matrix to factor out the scale, then this
      * object's upper 3x3 matrix components are replaced by the matrix
      * equivalent of the quaternion, and then the scale is reapplied to the
      * rotational components.
      * @param q1 the quaternion that specifies the rotation
      */
    void setRotation(const Quat4T& q1);

    /**
      * Sets the rotational component (upper 3x3) of this matrix to the matrix
      * equivalent values of the axis-angle argument; the other elements of this
      * matrix are unchanged; a singular value decomposition is performed on
      * this object's upper 3x3 matrix to factor out the scale, then this
      * object's upper 3x3 matrix components are replaced by the matrix
      * equivalent of the axis-angle, and then the scale is reapplied to the
      * rotational components.
      * @param a1 the axis-angle to be converted (x, y, z, angle)
      */
    void setRotation(const AxisAngle4T& a1);

    /**
      * Sets this matrix to all zeros.
      */
    void setZero();

    /**
      * Negates the value of this matrix: this = -this.
      */
    void negate();

    /**
      * Sets the value of this matrix equal to the negation of of the Matrix4
      * parameter.
      * @param m1 The source matrix
      */
    void negate(const Matrix4& m1) {
        set(m1);
        negate();
    }

    /**
     * Returns a string that contains the values of this Matrix4.
     * @return the String representation
     */
#ifdef USE_TOSTRING
STD::string toString() const;
#endif

protected:
    /**
      * Performs SVD on this matrix and gets scale and rotation.
      * Rotation is placed into rot3, and rot4.
      * @param rot3 the rotation factor(Matrix3d). if null, ignored
      * @param rot4 the rotation factor(Matrix4) only upper 3x3 elements are changed. if null, ignored
      * @return scale factor
      */
    T SVD(Matrix3T* rot3, Matrix4* rot4) const;

#if 0
    /**
      * Performs SVD on this matrix and gets the scale and the pure rotation.
      * The pure rotation is placed into rot.
      * @param rot the rotation factor.
      * @return scale factor
      */
    private float SVD(Matrix3f rot) {
	// this is a simple svd.
	// Not complete but fast and reasonable.
	// See comment in Matrix3d.

	T s = Math.sqrt(
	    (
	     m00*m00 + m10*m10 + m20*m20 + 
	     m01*m01 + m11*m11 + m21*m21 +
	     m02*m02 + m12*m12 + m22*m22
	    )/3.0
	    );

	// zero-div may occur.
	T t = (s == 0.0 ? 0.0 : 1.0/s);

	if (rot != null) {
	    this.getRotationScale(rot);
	    rot.mul((float)t);
	}

	return (float)s;
    }
#endif

    /**
      * Multiplies 3x3 upper elements of this matrix by a scalar.
      * The other elements are unchanged.
      */
    void mulRotationScale(T scale);

    /**
      * Sets only 3x3 upper elements of this matrix to that of m1.
      * The other elements are unchanged.
      */
    void setRotationScale(const Matrix4& m1);

    /**
     * Sets this matrix from the 4 values of quaternion.
     * @param x q.x
     * @param y q.y
     * @param z q.z
     * @param w q.w
     */
    void setFromQuat(T x, T y, T z, T w);

    /**
     * Sets this matrix from the 4 values of axisAngle.
     * @param x a.x
     * @param y a.y
     * @param z a.z
     * @param angle a.angle
     */
    void setFromAxisAngle(T x, T y, T z, T angle);

#if 0
    /**
      * Modifies the translational components of this matrix to the values of
      * the Vector3f argument; the other values of this matrix are not modified.
      * @param trans the translational component
      */
    private void setTranslation(Vector3f trans) {
        m03 = trans.x;
        m13 = trans.y;  
        m23 = trans.z;
    }
#endif

public:
    // copy constructor and operator = is made by complier

    bool operator==(const Matrix4& m1) const {
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
    Matrix4& operator+=(const Matrix4& m1) {
        add(m1);
        return *this;
    }
    Matrix4& operator-=(const Matrix4& m1) {
        sub(m1);
        return *this;
    }
    Matrix4& operator*=(const Matrix4& m1) {
        mul(m1);
        return *this;
    }
    Matrix4& operator*=(T s) {
        mul(s);
        return *this;
    }
    Matrix4 operator+(const Matrix4& m1) const {
        return (Matrix4(*this)).operator+=(m1);
    }
    Matrix4 operator-(const Matrix4& m1) const {
        return (Matrix4(*this)).operator-=(m1);
    }
    Matrix4 operator*(const Matrix4& m1) const {
        return (Matrix4(*this)).operator*=(m1);
    }
    Matrix4 operator*(T s) const {
        return (Matrix4(*this)).operator*=(s);
    }

};

TEMPLATE
inline
Matrix4T operator*(T s, const Matrix4T& m) {
    return (Matrix4T(m)).operator*=(s);
}

TEMPLATE
inline
Matrix4T operator*(const Matrix4T& m1, const Matrix4T& m2) {
    return (Matrix4T(m1)).operator*=(m2);
}

TEMPLATE
inline
Tuple4T operator*(const Matrix4T& m, const Tuple4T& t) {
    Tuple4T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE
inline
Vector4T operator*(const Matrix4T& m, const Vector4T& t) {
    //return operator*(m, (const Tuple3T&)t);
    Tuple4T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE
inline
Point4T operator*(const Matrix4T& m, const Point4T& t) {
    //return operator*(m, (const Tuple3T&)t);
    Tuple4T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE
inline
Vector3T operator*(const Matrix4T& m, const Vector3T& t) {
    Vector3T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE inline
Point3T operator*(const Matrix4T& m, const Point3T& t) {
    Point3T out;
    m.transform(t,&out); 
    return out;
}

TEMPLATE
Matrix4T::Matrix4(T n00, T n01, T n02, T n03, 
                    T n10, T n11, T n12, T n13,
                    T n20, T n21, T n22, T n23,
                    T n30, T n31, T n32, T n33):
    m00(n00), m01(n01), m02(n02), m03(n03),
    m10(n10), m11(n11), m12(n12), m13(n13),
    m20(n20), m21(n21), m22(n22), m23(n23),
    m30(n30), m31(n31), m32(n32), m33(n33) { }

TEMPLATE
Matrix4T::Matrix4(const T v[]):
    m00(v[ 0]), m01(v[ 1]), m02(v[ 2]), m03(v[ 3]),
    m10(v[ 4]), m11(v[ 5]), m12(v[ 6]), m13(v[ 7]),
    m20(v[ 8]), m21(v[ 9]), m22(v[10]), m23(v[11]),
    m30(v[12]), m31(v[13]), m32(v[14]), m33(v[15]) { }

#ifdef USE_CONVERSION_FROM_2DARRAY
TEMPLATE
Matrix4T::Matrix4(const T v[][4]):
    m00(v[0][0]), m01(v[0][1]), m02(v[0][2]), m03(v[0][3]),
    m10(v[1][0]), m11(v[1][1]), m12(v[1][2]), m13(v[1][3]),
    m20(v[2][0]), m21(v[2][1]), m22(v[2][2]), m23(v[2][3]),
    m30(v[3][0]), m31(v[3][1]), m32(v[3][2]), m33(v[3][3]) { }
#endif


TEMPLATE
Matrix4T::Matrix4():
    m00(0), m01(0), m02(0), m03(0),
    m10(0), m11(0), m12(0), m13(0),
    m20(0), m21(0), m22(0), m23(0),
    m30(0), m31(0), m32(0), m33(0) { }


TEMPLATE
void Matrix4T::set(T n00, T n01, T n02, T n03, 
                T n10, T n11, T n12, T n13,
                T n20, T n21, T n22, T n23,
                T n30, T n31, T n32, T n33) {
    m00 = n00; m01 = n01; m02 = n02; m03 = n03;
    m10 = n10; m11 = n11; m12 = n12; m13 = n13;
    m20 = n20; m21 = n21; m22 = n22; m23 = n23;
    m30 = n30; m31 = n31; m32 = n32; m33 = n33;
}

TEMPLATE
void Matrix4T::set(const Matrix4& m1) {
    m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; m03 = m1.m03;
    m10 = m1.m10; m11 = m1.m11; m12 = m1.m12; m13 = m1.m13;
    m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; m23 = m1.m23;
    m30 = m1.m30; m31 = m1.m31; m32 = m1.m32; m33 = m1.m33;
}

TEMPLATE
void Matrix4T::set(const T m[]) {
    assert(m != 0);
    m00 = m[ 0]; m01 = m[ 1]; m02 = m[ 2]; m03 = m[ 3];
    m10 = m[ 4]; m11 = m[ 5]; m12 = m[ 6]; m13 = m[ 7];
    m20 = m[ 8]; m21 = m[ 9]; m22 = m[10]; m23 = m[11];
    m30 = m[12]; m31 = m[13]; m32 = m[14]; m33 = m[15];
}

#ifdef USE_CONVERSION_FROM_2DARRAY
TEMPLATE
void Matrix4T::set(const T m[][4]) {
    assert(m != 0);
    m00 = m[0][0]; m01 = m[0][1]; m02 = m[0][2]; m03 = m[0][3];
    m10 = m[1][0]; m11 = m[1][1]; m12 = m[1][2]; m13 = m[1][3];
    m20 = m[2][0]; m21 = m[2][1]; m22 = m[2][2]; m23 = m[2][3];
    m30 = m[3][0]; m31 = m[3][1]; m32 = m[3][2]; m33 = m[3][3];
}
#endif

TEMPLATE
void Matrix4T::set(const Matrix3T& m1)  {
    m00 = m1.m00; m01 = m1.m01; m02 = m1.m02; m03 = 0.0;
    m10 = m1.m10; m11 = m1.m11; m12 = m1.m12; m13 = 0.0;
    m20 = m1.m20; m21 = m1.m21; m22 = m1.m22; m23 = 0.0;
    m30 =    0.0; m31 =    0.0; m32 =    0.0; m33 = 1.0;
}


TEMPLATE
void Matrix4T::set(const Quat4T& q1) {
    setFromQuat(q1.x, q1.y, q1.z, q1.w);
}


TEMPLATE
void Matrix4T::set(const AxisAngle4T& a1) {
    setFromAxisAngle(a1.x, a1.y, a1.z, a1.angle);
}

TEMPLATE
void Matrix4T::setIdentity() {
    m00 = 1.0; m01 = 0.0; m02 = 0.0; m03 = 0.0;
    m10 = 0.0; m11 = 1.0; m12 = 0.0; m13 = 0.0;
    m20 = 0.0; m21 = 0.0; m22 = 1.0; m23 = 0.0;
    m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0;
}

TEMPLATE
Matrix4T::Matrix4(const Quat4T& q1, const Vector3T& t1, T s) {
    set(q1, t1, s);
}

TEMPLATE
Matrix4T::Matrix4(const Matrix3T& m1, const Vector3T& t1, T s) {
    set(m1, t1, s);
}

TEMPLATE
void Matrix4T::setElement(size_t row, size_t column, T value) _THROW_ERROR {
	if (row > 3 || column > 3 )
		REPORT_ERROR("Error: Index exceed matrix dimensions");
	const size_t index (column + row * 4);
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
			m03 = value;
			break;
		case 4:
			m10 = value;
			break;
		case 5:
			m11 = value;
			break;
		case 6:
			m12 = value;
			break;
		case 7:
			m13 = value;
			break;
		case 8:
			m20 = value;
			break;
		case 9:
			m21 = value;
			break;
		case 10:
			m22 = value;
			break;
		case 11:
			m23 = value;
			break;
		case 12:
			m30 = value;
			break;
		case 13:
			m31 = value;
			break;
		case 14:
			m32 = value;
			break;
		case 15:
			m33 = value;
			break;
	}
}

TEMPLATE
T Matrix4T::getElement(size_t row, size_t column) const _THROW_ERROR{
	if (row > 3 || column > 3 )
		REPORT_ERROR("Error: Index exceed matrix dimensions");
	const size_t index (column + row * 4);
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
			value = m03;
			break;
		case 4:
			value = m10;
			break;
		case 5:
			value = m11;
			break;
		case 6:
			value = m12;
			break;
		case 7:
			value = m13;
			break;
		case 8:
			value = m20;
			break;
		case 9:
			value = m21;
			break;
		case 10:
			value = m22;
			break;
		case 11:
			value = m23;
			break;
		case 12:
			value = m30;
			break;
		case 13:
			value = m31;
			break;
		case 14:
			value = m32;
			break;
		case 15:
			value = m33;
			break;
	}

    return value;
}

TEMPLATE
T& Matrix4T::getElementReference(size_t row, size_t column) _THROW_ERROR {
	if (row > 3 || column > 3 )
		REPORT_ERROR("Error: Index exceed matrix dimensions");
	const size_t index (column + row * 4);
	static T value;
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
			return m03;
			break;
		case 4:
			return m10;
			break;
		case 5:
			return m11;
			break;
		case 6:
			return m12;
			break;
		case 7:
			return m13;
			break;
		case 8:
			return m20;
			break;
		case 9:
			return m21;
			break;
		case 10:
			return m22;
			break;
		case 11:
			return m23;
			break;
		case 12:
			return m30;
			break;
		case 13:
			return m31;
			break;
		case 14:
			return m32;
			break;
		case 15:
			return m33;
			break;
	}

	return value;
}



TEMPLATE
void Matrix4T::get(Matrix3T* m1) const {
    assert(m1 != 0);
    SVD(m1, 0);
}


TEMPLATE
T Matrix4T::get(Matrix3T* m1, Vector3T* t1) const {
    assert(m1 != 0);
    assert(t1 != 0);
	get(t1);
	return SVD(m1, 0);
}

TEMPLATE
void Matrix4T::get(Quat4T* q1) const {
    assert(q1 !=  0);

    q1->set(*this);
    q1->normalize();
}

TEMPLATE
void Matrix4T::getRotationScale(Matrix3T* m1) const {
    assert(m1 != 0);
    m1->m00 = m00; m1->m01 = m01; m1->m02 = m02;
    m1->m10 = m10; m1->m11 = m11; m1->m12 = m12;
    m1->m20 = m20; m1->m21 = m21; m1->m22 = m22;
}

TEMPLATE
T Matrix4T::getScale() const {
    return SVD(0, 0);
}

TEMPLATE
void Matrix4T::setRotationScale(const Matrix3T& m1) {
    m00 = m1.m00; m01 = m1.m01; m02 = m1.m02;
    m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
    m20 = m1.m20; m21 = m1.m21; m22 = m1.m22;
}

TEMPLATE
void Matrix4T::setScale(T scale) {
    // note: this don't change m44.
    SVD(0, this);
    mulRotationScale(scale);
}

TEMPLATE
void Matrix4T::setRow(size_t row, T x, T y, T z, T w) {
    assert(row < 4);
	if (row == 0) {
	    m00 = x;
	    m01 = y;
	    m02 = z;
	    m03 = w;
	} else if (row == 1) {
	    m10 = x;
	    m11 = y;
	    m12 = z;
	    m13 = w;
	} else if (row == 2) {
	    m20 = x;
	    m21 = y;
	    m22 = z;
	    m23 = w;
	} else if (row == 3) {
	    m30 = x;
	    m31 = y;
	    m32 = z;
	    m33 = w;
	} else {
	}
}

TEMPLATE
void Matrix4T::setRow(size_t row, const Vector4T& v) {
    assert(row < 4);
	if (row == 0) {
	    m00 = v.x;
	    m01 = v.y;
	    m02 = v.z;
	    m03 = v.w;
	} else if (row == 1) {
	    m10 = v.x;
	    m11 = v.y;
	    m12 = v.z;
	    m13 = v.w;
	} else if (row == 2) {
	    m20 = v.x;
	    m21 = v.y;
	    m22 = v.z;
	    m23 = v.w;
	} else if (row == 3) {
	    m30 = v.x;
	    m31 = v.y;
	    m32 = v.z;
	    m33 = v.w;
	} else {
	}
}

TEMPLATE
void Matrix4T::setRow(size_t row, const T v[]) {
	if (row == 0) {
	    m00 = v[0];
	    m01 = v[1];
	    m02 = v[2];
	    m03 = v[3];
	} else if (row == 1) {
	    m10 = v[0];
	    m11 = v[1];
	    m12 = v[2];
	    m13 = v[3];
	} else if (row == 2) {
	    m20 = v[0];
	    m21 = v[1];
	    m22 = v[2];
	    m23 = v[3];
	} else if (row == 3) {
	    m30 = v[0];
	    m31 = v[1];
	    m32 = v[2];
	    m33 = v[3];
	} else {
	}
}

TEMPLATE
void Matrix4T::getRow(size_t row, Vector4T* v) const {
    assert(row < 4);
    assert(v != 0);
	if (row == 0) {
	    v->x = m00;
	    v->y = m01;
	    v->z = m02;
	    v->w = m03;
	} else if (row == 1) {
	    v->x = m10;
	    v->y = m11;
	    v->z = m12;
	    v->w = m13;
	} else if (row == 2) {
	    v->x = m20;
	    v->y = m21;
	    v->z = m22;
	    v->w = m23;
	} else if (row == 3) {
	    v->x = m30;
	    v->y = m31;
	    v->z = m32;
	    v->w = m33;
	} else {
	}
}

TEMPLATE
void Matrix4T::getRow(size_t row, T v[]) const {
    assert(row < 4);
	if (row == 0) {
	    v[0] = m00;
	    v[1] = m01;
	    v[2] = m02;
	    v[3] = m03;
	} else if (row == 1) {
	    v[0] = m10;
	    v[1] = m11;
	    v[2] = m12;
	    v[3] = m13;
	} else if (row == 2) {
	    v[0] = m20;
	    v[1] = m21;
	    v[2] = m22;
	    v[3] = m23;
	} else if (row == 3) {
	    v[0] = m30;
	    v[1] = m31;
	    v[2] = m32;
	    v[3] = m33;
	} else {
	}
}

TEMPLATE
void Matrix4T::setColumn(size_t column, T x, T y, T z, T w) {
    assert(column < 4);
	if (column == 0) {
	    m00 = x;
	    m10 = y;
	    m20 = z;
	    m30 = w;
	}  else if (column == 1) {
	    m01 = x;
	    m11 = y;
	    m21 = z;
	    m31 = w;
	} else if (column == 2) {
	    m02 = x;
	    m12 = y;
	    m22 = z;
	    m32 = w;
	} else if (column == 3) {
	    m03 = x;
	    m13 = y;
	    m23 = z;
	    m33 = w;
	} else {
	}
}

TEMPLATE
void Matrix4T::setColumn(size_t column, const Vector4T& v) {
	if (column == 0) {
	    m00 = v.x;
	    m10 = v.y;
	    m20 = v.z;
	    m30 = v.w;
	} else if (column == 1) {
	    m01 = v.x;
	    m11 = v.y;
	    m21 = v.z;
	    m31 = v.w;
	} else if (column == 2) {
	    m02 = v.x;
	    m12 = v.y;
	    m22 = v.z;
	    m32 = v.w;
	} else if (column == 3) {
	    m03 = v.x;
	    m13 = v.y;
	    m23 = v.z;
	    m33 = v.w;
	} else {
	}
}

TEMPLATE
void Matrix4T::setColumn(size_t column,  const T v[]) {
	if (column == 0) {
	    m00 = v[0];
	    m10 = v[1];
	    m20 = v[2];
	    m30 = v[3];
	} else if (column == 1) {
	    m01 = v[0];
	    m11 = v[1];
	    m21 = v[2];
	    m31 = v[3];
	} else if (column == 2) {
	    m02 = v[0];
	    m12 = v[1];
	    m22 = v[2];
	    m32 = v[3];
	} else if (column == 3) {
	    m03 = v[0];
	    m13 = v[1];
	    m23 = v[2];
	    m33 = v[3];
	} else {
	}
}

TEMPLATE
void Matrix4T::getColumn(size_t column, Vector4T* v) const {
    assert(column < 4);
    assert(v != 0);
	if (column == 0) {
	    v->x = m00;
	    v->y = m10;
	    v->z = m20;
	    v->w = m30;
	} else if (column == 1) {
	    v->x = m01;
	    v->y = m11;
	    v->z = m21;
	    v->w = m31;
	} else if (column == 2) {
	    v->x = m02;
	    v->y = m12;
	    v->z = m22;
	    v->w = m32;
	} else if (column == 3) {
	    v->x = m03;
	    v->y = m13;
	    v->z = m23;
	    v->w = m33;
	} else {
	}
}

TEMPLATE
void Matrix4T::getColumn(size_t column, T v[]) const {
    assert(column < 4);
    assert(v != 0);
	if (column == 0) {
	    v[0] = m00;
	    v[1] = m10;
	    v[2] = m20;
	    v[3] = m30;
	} else if (column == 1) {
	    v[0] = m01;
	    v[1] = m11;
	    v[2] = m21;
	    v[3] = m31;
	} else if (column == 2) {
	    v[0] = m02;
	    v[1] = m12;
	    v[2] = m22;
	    v[3] = m32;
	} else if (column == 3) {
	    v[0] = m03;
	    v[1] = m13;
	    v[2] = m23;
	    v[3] = m33;
	} else {
	}
}

TEMPLATE
void Matrix4T::add(T scalar) {
    m00 += scalar; m01 += scalar; m02 += scalar; m03 += scalar;
    m10 += scalar; m11 += scalar; m12 += scalar; m13 += scalar;
    m20 += scalar; m21 += scalar; m22 += scalar; m23 += scalar;
    m30 += scalar; m31 += scalar; m32 += scalar; m33 += scalar;
}

TEMPLATE
void Matrix4T::sub(T scalar) {
    add(-scalar);
}

TEMPLATE
void Matrix4T::add(const Matrix4& m1, const Matrix4& m2) {
	// note this is alias safe.
	set(
	    m1.m00 + m2.m00,
	    m1.m01 + m2.m01,
	    m1.m02 + m2.m02,
	    m1.m03 + m2.m03,
	    m1.m10 + m2.m10,
	    m1.m11 + m2.m11,
	    m1.m12 + m2.m12,
	    m1.m13 + m2.m13,
	    m1.m20 + m2.m20,
	    m1.m21 + m2.m21,
	    m1.m22 + m2.m22,
	    m1.m23 + m2.m23,
	    m1.m30 + m2.m30,
	    m1.m31 + m2.m31,
	    m1.m32 + m2.m32,
	    m1.m33 + m2.m33
	    );
}

TEMPLATE
void Matrix4T::add(const Matrix4& m1) {
    m00 += m1.m00; m01 += m1.m01; m02 += m1.m02; m03 += m1.m03;
    m10 += m1.m10; m11 += m1.m11; m12 += m1.m12; m13 += m1.m13;
    m20 += m1.m20; m21 += m1.m21; m22 += m1.m22; m23 += m1.m23;
    m30 += m1.m30; m31 += m1.m31; m32 += m1.m32; m33 += m1.m33;
}


TEMPLATE
void Matrix4T::sub(const Matrix4& m1, const Matrix4& m2) {
	// note this is alias safe.
	set(
	    m1.m00 - m2.m00,
	    m1.m01 - m2.m01,
	    m1.m02 - m2.m02,
	    m1.m03 - m2.m03,
	    m1.m10 - m2.m10,
	    m1.m11 - m2.m11,
	    m1.m12 - m2.m12,
	    m1.m13 - m2.m13,
	    m1.m20 - m2.m20,
	    m1.m21 - m2.m21,
	    m1.m22 - m2.m22,
	    m1.m23 - m2.m23,
	    m1.m30 - m2.m30,
	    m1.m31 - m2.m31,
	    m1.m32 - m2.m32,
	    m1.m33 - m2.m33
	    );
    }

TEMPLATE
void Matrix4T::sub(const Matrix4& m1) {
    m00 -= m1.m00; m01 -= m1.m01; m02 -= m1.m02; m03 -= m1.m03;
    m10 -= m1.m10; m11 -= m1.m11; m12 -= m1.m12; m13 -= m1.m13;
    m20 -= m1.m20; m21 -= m1.m21; m22 -= m1.m22; m23 -= m1.m23;
    m30 -= m1.m30; m31 -= m1.m31; m32 -= m1.m32; m33 -= m1.m33;
}

TEMPLATE
void Matrix4T::transpose() {
    T tmp = m01; m01 = m10; m10 = tmp;
    tmp = m02;	m02 = m20;	m20 = tmp;
    tmp = m03;	m03 = m30;	m30 = tmp;
    tmp = m12;	m12 = m21;	m21 = tmp;
    tmp = m13;	m13 = m31;	m31 = tmp;
    tmp = m23;	m23 = m32;	m32 = tmp;
}


TEMPLATE
void Matrix4T::set(const Quat4T& q1, const Vector3T& t1, T s) {
    set(q1);
    mulRotationScale(s);
    m03 = t1.x;
    m13 = t1.y;
    m23 = t1.z;
}


TEMPLATE
void Matrix4T::invert(const Matrix4T& m1) {
    set(m1);
    invert();
}


TEMPLATE
void Matrix4T::invert() {
	T s = determinant();
	if (s == 0.0)
	    return;
	s = 1/s;
	// alias-safe way.
	// less *,+,- calculation than expanded expression.
	set(
	    m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33) + m13*(m21*m32 - m22*m31),
	    m21*(m02*m33 - m03*m32) + m22*(m03*m31 - m01*m33) + m23*(m01*m32 - m02*m31),
	    m31*(m02*m13 - m03*m12) + m32*(m03*m11 - m01*m13) + m33*(m01*m12 - m02*m11),
	    m01*(m13*m22 - m12*m23) + m02*(m11*m23 - m13*m21) + m03*(m12*m21 - m11*m22),

	    m12*(m20*m33 - m23*m30) + m13*(m22*m30 - m20*m32) + m10*(m23*m32 - m22*m33),
	    m22*(m00*m33 - m03*m30) + m23*(m02*m30 - m00*m32) + m20*(m03*m32 - m02*m33),
	    m32*(m00*m13 - m03*m10) + m33*(m02*m10 - m00*m12) + m30*(m03*m12 - m02*m13),
	    m02*(m13*m20 - m10*m23) + m03*(m10*m22 - m12*m20) + m00*(m12*m23 - m13*m22),

	    m13*(m20*m31 - m21*m30) + m10*(m21*m33 - m23*m31) + m11*(m23*m30 - m20*m33),
	    m23*(m00*m31 - m01*m30) + m20*(m01*m33 - m03*m31) + m21*(m03*m30 - m00*m33),
	    m33*(m00*m11 - m01*m10) + m30*(m01*m13 - m03*m11) + m31*(m03*m10 - m00*m13),
	    m03*(m11*m20 - m10*m21) + m00*(m13*m21 - m11*m23) + m01*(m10*m23 - m13*m20),

	    m10*(m22*m31 - m21*m32) + m11*(m20*m32 - m22*m30) + m12*(m21*m30 - m20*m31),
	    m20*(m02*m31 - m01*m32) + m21*(m00*m32 - m02*m30) + m22*(m01*m30 - m00*m31),
	    m30*(m02*m11 - m01*m12) + m31*(m00*m12 - m02*m10) + m32*(m01*m10 - m00*m11),
	    m00*(m11*m22 - m12*m21) + m01*(m12*m20 - m10*m22) + m02*(m10*m21 - m11*m20)
	    );

	mul(s);
}

TEMPLATE
T Matrix4T::determinant() const {
	// less *,+,- calculation than expanded expression.
	return
	    (m00*m11 - m01*m10)*(m22*m33 - m23*m32)
	   -(m00*m12 - m02*m10)*(m21*m33 - m23*m31)
	   +(m00*m13 - m03*m10)*(m21*m32 - m22*m31)
	   +(m01*m12 - m02*m11)*(m20*m33 - m23*m30)
	   -(m01*m13 - m03*m11)*(m20*m32 - m22*m30)
	   +(m02*m13 - m03*m12)*(m20*m31 - m21*m30);
}

TEMPLATE
void Matrix4T::set(T scale) {
    m00 = scale; m01 = 0.0;   m02 = 0.0;   m03 = 0.0;
    m10 = 0.0;   m11 = scale; m12 = 0.0;   m13 = 0.0;
    m20 = 0.0;   m21 = 0.0;   m22 = scale; m23 = 0.0;
    m30 = 0.0;   m31 = 0.0;   m32 = 0.0;   m33 = 1.0;
}

TEMPLATE
void Matrix4T::set(const Vector3T& v1, T scale) {
	m00 = scale; m01 = 0.0;   m02 = 0.0;   m03 = scale*v1.x;
	m10 = 0.0;   m11 = scale; m12 = 0.0;   m13 = scale*v1.y;
	m20 = 0.0;   m21 = 0.0;   m22 = scale; m23 = scale*v1.z;
	m30 = 0.0;   m31 = 0.0;   m32 = 0.0;   m33 = 1.0;
}

TEMPLATE
void Matrix4T::set(const Matrix3T& m1, const Vector3T& t1, T scale) {
	setRotationScale(m1);
	mulRotationScale(scale);
	setTranslation(t1);
	m33 = 1.0;
}

TEMPLATE
void Matrix4T::rotX(T angle)  {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
	m00 = 1.0; m01 = 0.0; m02 = 0.0; m03 = 0.0;
	m10 = 0.0; m11 = c;   m12 = -s;  m13 = 0.0;
	m20 = 0.0; m21 = s;   m22 = c;   m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}


TEMPLATE
void Matrix4T::rotY(T angle)  {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
	m00 = c;   m01 = 0.0; m02 = s;   m03 = 0.0;
	m10 = 0.0; m11 = 1.0; m12 = 0.0; m13 = 0.0;
	m20 = -s;  m21 = 0.0; m22 = c;   m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}


TEMPLATE
void Matrix4T::rotZ(T angle)  {
	T c = UtilT::cos(angle);
	T s = UtilT::sin(angle);
	m00 = c;   m01 = -s;  m02 = 0.0; m03 = 0.0;
	m10 = s;   m11 = c;   m12 = 0.0; m13 = 0.0;
	m20 = 0.0; m21 = 0.0; m22 = 1.0; m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0; 
}


TEMPLATE
void Matrix4T::mul(T scalar) {
	m00 *= scalar; m01 *= scalar;  m02 *= scalar; m03 *= scalar;
	m10 *= scalar; m11 *= scalar;  m12 *= scalar; m13 *= scalar;
	m20 *= scalar; m21 *= scalar;  m22 *= scalar; m23 *= scalar;
	m30 *= scalar; m31 *= scalar;  m32 *= scalar; m33 *= scalar;
}


TEMPLATE
void Matrix4T::mul(const Matrix4& m1, const Matrix4& m2) {
	// alias-safe way
	set(
	    m1.m00*m2.m00 + m1.m01*m2.m10 + m1.m02*m2.m20 + m1.m03*m2.m30,
	    m1.m00*m2.m01 + m1.m01*m2.m11 + m1.m02*m2.m21 + m1.m03*m2.m31,
	    m1.m00*m2.m02 + m1.m01*m2.m12 + m1.m02*m2.m22 + m1.m03*m2.m32,
	    m1.m00*m2.m03 + m1.m01*m2.m13 + m1.m02*m2.m23 + m1.m03*m2.m33,

	    m1.m10*m2.m00 + m1.m11*m2.m10 + m1.m12*m2.m20 + m1.m13*m2.m30,
	    m1.m10*m2.m01 + m1.m11*m2.m11 + m1.m12*m2.m21 + m1.m13*m2.m31,
	    m1.m10*m2.m02 + m1.m11*m2.m12 + m1.m12*m2.m22 + m1.m13*m2.m32,
	    m1.m10*m2.m03 + m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13*m2.m33,

	    m1.m20*m2.m00 + m1.m21*m2.m10 + m1.m22*m2.m20 + m1.m23*m2.m30,
	    m1.m20*m2.m01 + m1.m21*m2.m11 + m1.m22*m2.m21 + m1.m23*m2.m31,
	    m1.m20*m2.m02 + m1.m21*m2.m12 + m1.m22*m2.m22 + m1.m23*m2.m32,
	    m1.m20*m2.m03 + m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23*m2.m33,

	    m1.m30*m2.m00 + m1.m31*m2.m10 + m1.m32*m2.m20 + m1.m33*m2.m30,
	    m1.m30*m2.m01 + m1.m31*m2.m11 + m1.m32*m2.m21 + m1.m33*m2.m31,
	    m1.m30*m2.m02 + m1.m31*m2.m12 + m1.m32*m2.m22 + m1.m33*m2.m32,
	    m1.m30*m2.m03 + m1.m31*m2.m13 + m1.m32*m2.m23 + m1.m33*m2.m33
	    );
}

TEMPLATE
void Matrix4T::mulTransposeRight(const Matrix4& m1, const Matrix4& m2) {
	// alias-safe way.
	set(
	    m1.m00*m2.m00 + m1.m01*m2.m01 + m1.m02*m2.m02 + m1.m03*m2.m03,
	    m1.m00*m2.m10 + m1.m01*m2.m11 + m1.m02*m2.m12 + m1.m03*m2.m13,
	    m1.m00*m2.m20 + m1.m01*m2.m21 + m1.m02*m2.m22 + m1.m03*m2.m23,
	    m1.m00*m2.m30 + m1.m01*m2.m31 + m1.m02*m2.m32 + m1.m03*m2.m33,

	    m1.m10*m2.m00 + m1.m11*m2.m01 + m1.m12*m2.m02 + m1.m13*m2.m03,
	    m1.m10*m2.m10 + m1.m11*m2.m11 + m1.m12*m2.m12 + m1.m13*m2.m13,
	    m1.m10*m2.m20 + m1.m11*m2.m21 + m1.m12*m2.m22 + m1.m13*m2.m23,
	    m1.m10*m2.m30 + m1.m11*m2.m31 + m1.m12*m2.m32 + m1.m13*m2.m33,

	    m1.m20*m2.m00 + m1.m21*m2.m01 + m1.m22*m2.m02 + m1.m23*m2.m03,
	    m1.m20*m2.m10 + m1.m21*m2.m11 + m1.m22*m2.m12 + m1.m23*m2.m13,
	    m1.m20*m2.m20 + m1.m21*m2.m21 + m1.m22*m2.m22 + m1.m23*m2.m23,
	    m1.m20*m2.m30 + m1.m21*m2.m31 + m1.m22*m2.m32 + m1.m23*m2.m33,
	    
	    m1.m30*m2.m00 + m1.m31*m2.m01 + m1.m32*m2.m02 + m1.m33*m2.m03,
	    m1.m30*m2.m10 + m1.m31*m2.m11 + m1.m32*m2.m12 + m1.m33*m2.m13,
	    m1.m30*m2.m20 + m1.m31*m2.m21 + m1.m32*m2.m22 + m1.m33*m2.m23,
	    m1.m30*m2.m30 + m1.m31*m2.m31 + m1.m32*m2.m32 + m1.m33*m2.m33
	    );
}


TEMPLATE
void Matrix4T::mulTransposeLeft(const Matrix4& m1, const Matrix4& m2) {
	// alias-safe way.
	set(
	    m1.m00*m2.m00 + m1.m10*m2.m10 + m1.m20*m2.m20 + m1.m30*m2.m30,
	    m1.m00*m2.m01 + m1.m10*m2.m11 + m1.m20*m2.m21 + m1.m30*m2.m31,
	    m1.m00*m2.m02 + m1.m10*m2.m12 + m1.m20*m2.m22 + m1.m30*m2.m32,
	    m1.m00*m2.m03 + m1.m10*m2.m13 + m1.m20*m2.m23 + m1.m30*m2.m33,

	    m1.m01*m2.m00 + m1.m11*m2.m10 + m1.m21*m2.m20 + m1.m31*m2.m30,
	    m1.m01*m2.m01 + m1.m11*m2.m11 + m1.m21*m2.m21 + m1.m31*m2.m31,
	    m1.m01*m2.m02 + m1.m11*m2.m12 + m1.m21*m2.m22 + m1.m31*m2.m32,
	    m1.m01*m2.m03 + m1.m11*m2.m13 + m1.m21*m2.m23 + m1.m31*m2.m33,

	    m1.m02*m2.m00 + m1.m12*m2.m10 + m1.m22*m2.m20 + m1.m32*m2.m30,
	    m1.m02*m2.m01 + m1.m12*m2.m11 + m1.m22*m2.m21 + m1.m32*m2.m31,
	    m1.m02*m2.m02 + m1.m12*m2.m12 + m1.m22*m2.m22 + m1.m32*m2.m32,
	    m1.m02*m2.m03 + m1.m12*m2.m13 + m1.m22*m2.m23 + m1.m32*m2.m33,

	    m1.m03*m2.m00 + m1.m13*m2.m10 + m1.m23*m2.m20 + m1.m33*m2.m30,
	    m1.m03*m2.m01 + m1.m13*m2.m11 + m1.m23*m2.m21 + m1.m33*m2.m31,
	    m1.m03*m2.m02 + m1.m13*m2.m12 + m1.m23*m2.m22 + m1.m33*m2.m32,
	    m1.m03*m2.m03 + m1.m13*m2.m13 + m1.m23*m2.m23 + m1.m33*m2.m33
	    );
}

TEMPLATE
bool Matrix4T::equals(const Matrix4T& m1) const {
	return  m00 == m1.m00
		&& m01 == m1.m01
		&& m02 == m1.m02 
		&& m03 == m1.m03
		&& m10 == m1.m10
		&& m11 == m1.m11
		&& m12 == m1.m12
		&& m13 == m1.m13
		&& m20 == m1.m20
		&& m21 == m1.m21
		&& m22 == m1.m22
		&& m23 == m1.m23
		&& m30 == m1.m30
		&& m31 == m1.m31
		&& m32 == m1.m32
		&& m33 == m1.m33;
}

TEMPLATE
bool Matrix4T::epsilonEquals(const Matrix4T& m1, T epsilon) const {
	  return  abs(m00 - m1.m00) <= epsilon
		&& abs(m01 - m1.m01) <= epsilon
		&& abs(m02 - m1.m02 ) <= epsilon
		&& abs(m03 - m1.m03) <= epsilon

		&& abs(m10 - m1.m10) <= epsilon
		&& abs(m11 - m1.m11) <= epsilon
		&& abs(m12 - m1.m12) <= epsilon
		&& abs(m13 - m1.m13) <= epsilon

		&& abs(m20 - m1.m20) <= epsilon
		&& abs(m21 - m1.m21) <= epsilon
		&& abs(m22 - m1.m22) <= epsilon
		&& abs(m23 - m1.m23) <= epsilon

		&& abs(m30 - m1.m30) <= epsilon
		&& abs(m31 - m1.m31) <= epsilon
		&& abs(m32 - m1.m32) <= epsilon
        && abs(m33 - m1.m33) <= epsilon;
}



TEMPLATE
void Matrix4T::transform(const Tuple4T& vec, Tuple4T* vecOut) const {
	// alias-safe
    assert(vecOut != 0);
	vecOut->set(
	    m00*vec.x + m01*vec.y + m02*vec.z + m03*vec.w,
	    m10*vec.x + m11*vec.y + m12*vec.z + m13*vec.w,
	    m20*vec.x + m21*vec.y + m22*vec.z + m23*vec.w,
	    m30*vec.x + m31*vec.y + m32*vec.z + m33*vec.w
	    );
}


TEMPLATE
void Matrix4T::transform(const Point3T& point, Point3T* pointOut) const {
    assert(pointOut != 0);
	pointOut->set(
	    m00*point.x + m01*point.y + m02*point.z + m03,
	    m10*point.x + m11*point.y + m12*point.z + m13,
	    m20*point.x + m21*point.y + m22*point.z + m23
	    );
}


TEMPLATE
void Matrix4T::transform(const Vector3T& normal, Vector3T* normalOut) const {
	normalOut->set(
	    m00 * normal.x + m01 * normal.y + m02 * normal.z,
	    m10 * normal.x + m11 * normal.y + m12 * normal.z,
	    m20 * normal.x + m21 * normal.y + m22 * normal.z
	    );
}


TEMPLATE
void Matrix4T::setRotation(const Matrix3T& m1) {
	T scale = SVD(0, 0);
	setRotationScale(m1);
	mulRotationScale(scale);
}


TEMPLATE
void Matrix4T::setRotation(const Quat4T& q1) {
	T scale = SVD(0, 0);
	// save other values
	T tx = m03; 
	T ty = m13; 
	T tz = m23; 
	T w0 = m30;                  
	T w1 = m31;
	T w2 = m32;
	T w3 = m33;

	set(q1);
	mulRotationScale(scale);

	// set back
	m03 = tx;
	m13 = ty;
	m23 = tz;
	m30 = w0;
	m31 = w1;
	m32 = w2;
	m33 = w3;
}


TEMPLATE
void Matrix4T::setRotation(const AxisAngle4T& a1) {
	T scale = SVD(0, 0);
	// save other values
	T tx = m03; 
	T ty = m13; 
	T tz = m23; 
	T w0 = m30;                  
	T w1 = m31;
	T w2 = m32;
	T w3 = m33;

	set(a1);
	mulRotationScale(scale);

	// set back
	m03 = tx;
	m13 = ty;
	m23 = tz;
	m30 = w0;
	m31 = w1;
	m32 = w2;
	m33 = w3;
}


TEMPLATE
void Matrix4T::setZero() {
    m00 = 0.0; m01 = 0.0; m02 = 0.0; m03 = 0.0;
    m10 = 0.0; m11 = 0.0; m12 = 0.0; m13 = 0.0;
    m20 = 0.0; m21 = 0.0; m22 = 0.0; m23 = 0.0;
    m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 0.0;
}


TEMPLATE
void Matrix4T::negate() {
    m00 = -m00; m01 = -m01; m02 = -m02; m03 = -m03;
    m10 = -m10; m11 = -m11; m12 = -m12; m13 = -m13;
    m20 = -m20; m21 = -m21; m22 = -m22; m23 = -m23;
    m30 = -m30; m31 = -m31; m32 = -m32; m33 = -m33;
}


TEMPLATE
T Matrix4T::SVD(Matrix3T* rot3, Matrix4* rot4) const {
	// this is a simple svd.
	// Not complete but fast and reasonable.
	// See comment in Matrix3d.

	T s = UtilT::sqrt(
	    (
	     m00*m00 + m10*m10 + m20*m20 + 
	     m01*m01 + m11*m11 + m21*m21 +
	     m02*m02 + m12*m12 + m22*m22
	    )/3.0
	    );

	if (rot3) {
	    this->getRotationScale(rot3);
        // zero-div may occur.
        double n = 1/UtilT::sqrt(m00*m00 + m10*m10 + m20*m20);
        rot3->m00 *= n;
        rot3->m10 *= n;
        rot3->m20 *= n;

        n = 1/UtilT::sqrt(m01*m01 + m11*m11 + m21*m21);
        rot3->m01 *= n;
        rot3->m11 *= n;
        rot3->m21 *= n;

        n = 1/UtilT::sqrt(m02*m02 + m12*m12 + m22*m22);
        rot3->m02 *= n;
        rot3->m12 *= n;
        rot3->m22 *= n;
	}

	if (rot4) {
	    if (rot4 != this)
            rot4->setRotationScale(*this);  // private method

        // zero-div may occur.
        double n = 1/UtilT::sqrt(m00*m00 + m10*m10 + m20*m20);
        rot4->m00 *= n;
        rot4->m10 *= n;
        rot4->m20 *= n;

        n = 1/UtilT::sqrt(m01*m01 + m11*m11 + m21*m21);
        rot4->m01 *= n;
        rot4->m11 *= n;
        rot4->m21 *= n;

        n = 1/UtilT::sqrt(m02*m02 + m12*m12 + m22*m22);
        rot4->m02 *= n;
        rot4->m12 *= n;
        rot4->m22 *= n;
	}

	return s;
}


TEMPLATE
void Matrix4T::mulRotationScale(T scale) {
	m00 *= scale; m01 *= scale; m02 *= scale;
	m10 *= scale; m11 *= scale; m12 *= scale;
	m20 *= scale; m21 *= scale; m22 *= scale;
}


TEMPLATE
void Matrix4T::setRotationScale(const Matrix4& m1) {
	m00 = m1.m00; m01 = m1.m01; m02 = m1.m02;
	m10 = m1.m10; m11 = m1.m11; m12 = m1.m12;
	m20 = m1.m20; m21 = m1.m21; m22 = m1.m22;
}


TEMPLATE
void Matrix4T::setFromQuat(T x, T y, T z, T w) {
	T n = x*x + y*y + z*z + w*w;
	T s = (n > 0.0) ? (2.0/n) : 0.0;

	T xs = x*s,  ys = y*s,  zs = z*s;
	T wx = w*xs, wy = w*ys, wz = w*zs;
	T xx = x*xs, xy = x*ys, xz = x*zs;
	T yy = y*ys, yz = y*zs, zz = z*zs;

	setIdentity();
	m00 = 1.0 - (yy + zz);	m01 = xy - wz;         m02 = xz + wy;
	m10 = xy + wz;          m11 = 1.0 - (xx + zz); m12 = yz - wx;
	m20 = xz - wy;          m21 = yz + wx;         m22 = 1.0 - (xx + yy);
}


TEMPLATE
void Matrix4T::setFromAxisAngle(T x, T y, T z, T angle) {
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
STD::string Matrix4T::toString() const {
    VM_TOSTRING
}
#endif /* USE_TOSTRING */

END_NAMESPACE

#ifdef USE_IO
TEMPLATE
STD::ostream& operator<<(STD::ostream& o, const NAMESPACE::Matrix4T& t1) {
    return  o << 
    "[ ["<<t1.m00<<","<<t1.m01<<","<<t1.m02<<","<<t1.m03<<"]" << STD::endl <<
    "  ["<<t1.m10<<","<<t1.m11<<","<<t1.m12<<","<<t1.m13<<"]" << STD::endl <<
    "  ["<<t1.m20<<","<<t1.m21<<","<<t1.m22<<","<<t1.m23<<"]" << STD::endl <<
    "  ["<<t1.m30<<","<<t1.m31<<","<<t1.m32<<","<<t1.m33<<"]""] ]";
}
#endif


BEGIN_NAMESPACE

#ifdef USE_TEMPLATE
typedef Matrix4<double> Matrix4d;
typedef Matrix4<float> Matrix4f;
#else
typedef Matrix4 Matrix4d;
typedef Matrix4 Matrix4f;
#endif

END_NAMESPACE


#endif /* MATRIX4__H */
