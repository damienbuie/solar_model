/*
*
* Package For Solar Modelling 
*
* Damien Buie
* Solar Energy Group, 
* University of Sydney
*
*
* This software was developed at the University of Sydney
* by Damien Buie and is not subject to copyright protection
* and is in the public domain. The University of Sydney and
* or Damien Buie assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
*
*/


#ifndef PSM_STACK_K
#define PSM_STACK_K

#include <psm.h>

/* 
 * The s component - transverse electric
 * The p component - transverse magnetic 
 */

namespace PSM {

template<class T>
class Stack{

public:
  Stack(const unsigned int a): noLayers(a), S(1), P(0)
  {
    n         = new std::complex<T>[noLayers];
    theta     = new std::complex<T>[noLayers];
    thickness = new T[noLayers];
  }

  ~Stack(void){
    delete []n;
    delete []theta;
    delete []thickness;
  }

  void layer(const unsigned int a, const T b, std::complex<T> c){
    thickness[a] = b;
    n[a] = c;
  }

  void layer(const unsigned int a, const T b, T c, T d = 0){
    thickness[a] = b;
    n[a] = std::complex<T>(c,d);
  }

  void getReflect(T& a){
    a = alloc(reflect);
  }

  void getTransmit(T& a){
    a = alloc(transmit);
  }

  void getAbsorb(T& a){
    a = alloc(absorb);
  }
  
  T alloc(std::complex<T>* comp){
    std::complex<T> tempa;

    tempa = std::sqrt( comp[S] * conj( comp[S] ) );
    tempa += std::sqrt( comp[P] * conj( comp[P] ) );

    return (tempa.real()/2);
  }
  
  void generate(const T wavelength, const T angle){
    std::complex<T> cangle(angle,0);

    determineATR(wavelength,cangle);
  }

  void generate(const T wavelength, const modelling::Vector4<T> solarVector,
	     const modelling::Vector4<T> surfaceNormal){

    T angle = acos( solarVector.dot(surfaceNormal));
    std::complex<T> cangle(angle,0);

    determineATR(wavelength,cangle);

  }


private:
  
  void determineATR(const T  , std::complex<T> );
  
public:
  const unsigned int noLayers;
  
  std::complex<T>* theta; // radians
  std::complex<T>* n; 
  T* thickness; // in meters

  std::complex<T> reflect[2];
  std::complex<T> transmit[2];
  std::complex<T> absorb[2];

	const int S;
	const int P;

};

template <class T>
void Stack<T>::determineATR(const T wavelength , std::complex<T> b){
  /* Stack::determineATR calculates the reflection, transmittion and
   * absorption of a thin film stack into a substrate for a given
   * incident beam of radiation with a specific wavelength, and
   * complex angle on incidence onto the initial layer.
   */

  theta[0] = b;

  const std::complex<T> im_i( 0, 1 );
  const T pi    = 3.14159265358979;
  const T mu0   = 4 * pi * 1E-7;
  const T eps0  = 8.85418782E-12;

  /* asin wasn't present in the <complex> library */
  for ( unsigned int i = 1; i < noLayers; i++ ){
    std::complex<T> sinangle = n[i-1] * sin(theta[i-1]) / n[i];
    theta[i] = conj(im_i) *
    std::log( im_i *  sinangle + std::sqrt( std::complex<T>(1,0) - sinangle * sinangle ) );
  }
  
  for (unsigned int sORp = 0; sORp < 2; sORp++){

		
    std::complex<T>* delta = new std::complex<T>[noLayers];
    std::complex<T>* Y = new std::complex<T>[noLayers];

    for (unsigned int i = 0; i < noLayers; i++){
      if (sORp) Y[i] = ( std::sqrt( eps0 / mu0 ) * std::cos( theta[i] ) ) * n[i];
      else      Y[i] = ( std::sqrt( eps0 / mu0 ) / std::cos( theta[i] ) ) * n[i];
      
      delta[i]= 2 * pi * thickness[i] * std::cos( theta[i] ) / wavelength * n[i] ;
    }

    std::complex<T> U[4];

    std::complex<T> M[4];
    M[0] = std::complex<T>(1,0);
    M[3] = std::complex<T>(1,0);
    
    for ( unsigned int j = 1; j < noLayers-1;j++){
    
      for ( unsigned int i = 0; i < 4; i++) U[i] = M[i];

      std::complex<T> Temp[4];

      Temp[0] = std::cos( delta[j] );
      Temp[1] = im_i * std::sin( delta[j] ) / Y[j];
      Temp[2] = im_i * std::sin( delta[j] ) * Y[j];
      Temp[3] = std::cos(delta[j]);

      M[0]=U[0]*Temp[0]+U[1]*Temp[2];
      M[1]=U[0]*Temp[1]+U[1]*Temp[3];
      M[2]=U[2]*Temp[0]+U[3]*Temp[2];
      M[3]=U[2]*Temp[1]+U[3]*Temp[3];

//      std::complex<T> determinent=M[0]*M[3]-M[1]*M[2];
//      std::cout<<determinent<<std::endl;
    }

    std::complex<T> B = M[0] + M[1] * Y[noLayers-1];
    std::complex<T> C = M[2] + M[3] * Y[noLayers-1];
    std::complex<T> D = Y[0] * B + C;

    std::complex<T> temp = ( Y[0] * B - C ) / D;
    reflect[sORp] = temp * conj( temp );

    transmit[sORp]= T(4.0) * Y[0] * Y[noLayers-1].real() / (D * conj( D ) );

    temp = B * conj( C ) - Y[noLayers-1];
    absorb[sORp]= 	T(4.0) * Y[0] * temp.real() / ( D * conj( D ) );

		delete []delta;
		delete []Y;

  }

}

}

#endif
