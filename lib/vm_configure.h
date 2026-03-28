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
 
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *******************************************

// use parallel processing MPI
//#define USE_MPI

// use template 
#define USE_TEMPLATE

// can do cout<<vector<<endl;
#define USE_IO

// places all files within a namespace
#define USE_NAMESPACE

// use exception handling requires stl & iostream
#define USE_EXCEPTION

// can do 'mat(i,j); v[i];'
#define USE_SUBSCRIPTION_OPERATOR

// can do vec.toString();
//#define USE_TOSTRING

// can do 'double a[3][3]; mat.set(a);'
//#define USE_CONVERSION_FROM_2DARRAY

// use cmath, cstddef, ... cXXXX type headers
#define STD_C_HEADERS

// use vecmath package
#define USE_VECMATH

// *******************************************

#ifdef USE_NAMESPACE
# define NAMESPACE  modelling
# define USING_NAMESPACE using namespace modelling;
# define BEGIN_NAMESPACE namespace modelling {
# define END_NAMESPACE }
# define STD std
#else
# define NAMESPACE
# define USING_NAMESPACE 
# define BEGIN_NAMESPACE
# define END_NAMESPACE
# define STD
#endif

#ifdef USE_TOSTRING
#  ifndef USE_IO
#    define USE_IO
#  endif
#endif

#ifdef STD_C_HEADERS
# include <cstddef>
# include <cstdlib>
# include <cassert>
# include <cmath>
# include <complex>
# include <vector>
# ifdef USE_TOSTRING
#  include <string>
#  include <sstream>
#   define VM_TOSTRING STD::stringstream s; s << *this; return s.str();
# endif
# ifdef USE_EXCEPTION
#  include <stdexcept>
#  include <string>
# endif
# ifdef USE_IO
#  include <iostream>
#  include <fstream>
# endif
#else
# include <stddef.h>
# include <stdlib.h>
# include <assert.h>
# include <math.h>
# include <complex.h>
# include <vector.h>
# ifdef USE_TOSTRING
#  include <string.h>
#  include <strstream.h>
#  define VM_TOSTRING STD::strstream s; s << *this << ends; STD::string str = s.str(); s.freeze(0); return str;
# endif
# ifdef USE_IO
#  include <iostream.h>
#  include <fstream.h>
# endif
#endif

#ifdef USE_MPI
#include <mpi.h>
#include <mpicxx.h>
#endif


#ifdef USE_EXCEPTION
/* C++17 removed dynamic exception specifications; use noexcept instead. */
# define _NO_THROW        noexcept
# define _THROW_ERROR     noexcept(false)
# define REPORT_ERROR(ErrormMsg)  throw std::logic_error( ErrormMsg);
# define OUT_OF_RANGE throw std::out_of_range("Error: OUT OF RANGE");
# define OPEN_ERROR throw std::logic_error("Error: Couldn't open file");
# define NO_ALLOCATION throw std::logic_error("Error: No allocation");
# define DIVIDE_BY_ZERO throw std::logic_error("Error: Divide by zero");
# define EXCEPTION_BEGIN try {
# define EXCEPTION_END } catch (std::exception& e){ std::cout<<e.what()<<std::endl; } catch (...) {std::cout<<"I have no idea what went wrong"<<std::endl;}

#else 
# define _NO_THROW        
# define _THROW_ERROR    
# define REPORT_ERROR(ErrormMsg) {}
# define OUT_OF_RANGE {}
# define OPEN_ERROR {}
# define NO_ALLOCATION {}
# define DIVIDE_BY_ZERO {}
# define EXCEPTION_BEGIN 
# define EXCEPTION_END 
#endif

#ifdef USE_TEMPLATE

#define TEMPLATE template <class T>
#define AxisAngle4T AxisAngle4<T>
#define Color3T Color<T>
#define Color4T Color4<T>
#define Matrix3T Matrix3<T>
#define Matrix4T Matrix4<T>
#define Point2T Point2<T>
#define Point3T Point3<T>
#define Point4T Point4<T>
#define Quat4T Quat4<T>
#define TexCoord2T TexCoord2<T>
#define Tuple2T Tuple2<T>
#define Tuple3T Tuple3<T>
#define Tuple4T Tuple4<T>
#define UtilT Util<T>
#define Vector2T Vector2<T>
#define Vector3T Vector3<T>
#define Vector4T Vector4<T>
#define complexT complex<T>

#else

#define TEMPLATE
#define AxisAngle4T AxisAngle4
#define Color3T Color
#define Color4T Color4
#define Matrix3T Matrix3
#define Matrix4T Matrix4
#define Point2T Point2
#define Point3T Point3
#define Point4T Point4
#define Quat4T Quat4
#define TexCoord2T TexCoord2
#define Tuple2T Tuple2
#define Tuple3T Tuple3
#define Tuple4T Tuple4
#define UtilT Util
#define Vector2T Vector2
#define Vector3T Vector3
#define Vector4T Vector4
#define complexT complex

#define T double
#endif



#endif

