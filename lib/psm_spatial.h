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

#ifndef SPATIAL_H
#define SPATIAL_H

/*--------------------------------------------------
* 
*
* Variable name       | description
* ______________________________________________________________________________
*
* cirSolarLimit         Limit of the solar disk (rad) 
* cirSolarRatio         Circumsolar ratio
* standDevGaussian    	Standard Deviation of surface normals
* noRadialPoints        Number of radial points
* int noSpurs           Number of radial spurs
* int blockSize    Size of the solar array
* baseArray             Array of vectors about znormal
* array                 Array of vectors about the solar vector
* weight                Energy each vector represents (sum = 1)
* phi;                  Spatial energy distribution of the sun 
* theta;                Angular displacement of each vector from the solar vector
* thetaLim;             Angular limit of each vector (for no. steradians
*
* Variable name        | type          | default value/size
* ________________________________________________________________________________
*
* cirSolarLimit          T				 0.04365 rad
* cirSolarRatio          T				 0.05 (dimensionless)
* standDevGaussian     	 T				 0.0035 rad
* noRadialPoints         size_t	         50
* noSpurs            	 size_t	         100
* blockSize     	 size_t	         4901
* baseArray              Vector4T*	 blockSize
* array                  Vector4T*	 blockSize
* weight                 T*	             blockSize
* phi;                   T*	             noRadialPoints
* theta;                 T*	             noRadialPoints
* thetaLim;              T*	             noRadialPoints
*
*
* Function name        | return | description
* ____________________________________________________________________________
*
* putSigma(T)            void    input the standard deviation of combined errors
* putCirSolarLimit(T)    void    input the circumsolar limit
* putCSR(T)              void    input the circumsolar ratio
* putArrayDim(int,int)   void    redefine the solar array dimensions
* generate()             void    generates the baseArray + weight
* generate(Vector4)      void    generates the baseArray + weight + solarArray about Vector4
* generate(T*,T*,T*,int) void    generates the baseArray + weight with external theta, thetalim (radial symmetric)
*
*/

// This program requires the vecmath package

#include <vecmath.h>

namespace PSM {

template <class T>
class Spatial
{

  typedef NAMESPACE::Vector4<T> vec4;
  typedef NAMESPACE::Matrix4<T> mat4;
  
public:

  // Angular size of the virtual solar array
  // from the solar vector (radians)
  // default value of 0.0436 rad
  T cirSolarLimit;

  // Cirumsolar ratio, defined as the ratio
  // of the amount of energy contained within the
  // solar disk, to the total amount of energy 
  // contained within the solar disk and circumsolar
  // region (out to cirSolarLimit).
  // default value of 0.05 
  T cirSolarRatio;

  // The value of the combined Gaussian error associated with 
  // the non-specula reflection, surface normal deviations and
  // tracking errors etc. (Radians). 
  // Default value of 0.0035 rad 
  T standDevGaussian;

  // The virual solar array consists of a number of 
  // spurs propagating about the solar vector (noSpurs),
  // with a noRadialPoints in each spur. Leaving the 
  // total number of points in the solar vector as
  // blockSize. 
  size_t noRadialPoints;
  size_t noSpurs;
  size_t blockSize;

  // The solar array is contained as a series of vectors
  // centered about the znormal array and generated using
  // create (baseArray). The array can also be rotated to be about 
  // the solar vector (array) 
  vec4 *baseArray;   
  vec4 *array; 

  // Each of the vectors in the solar array has a 
  // corresponding weight defined by the spatial
  // energy distribution of the sun (phi). 
  // Discretely this distribution is defined at each
  // point theta some radial displacement from the 
  // solar vector. Each of the regions are defined 
  // by the solar displacment thetaLim
  T *weight;
  T *phi;
  T *theta;
  T *thetaLim;

public:
  // The constructor builds a solar distribution with 100 radial limbs with 50 points
  // along each limb about the znormal vector. The spatial extent of the solar
  // distribution goes out to 43.65 mrad. The distribution has a cirsumsolar
  // ratio of 0.05, and the whole distribion has been simulated after the reflection
  // off a mirrored surface with a standard deviation of errors of 3.5 milliradians.

  Spatial( T b = 0.04365, T c = 0.05, T d = 0.0035, size_t e = 50, size_t f = 100):
     cirSolarLimit(b), cirSolarRatio(c), standDevGaussian(d), noRadialPoints(e),
    noSpurs(f) {
		array = 0; baseArray = 0; weight = 0; theta = 0; thetaLim = 0; phi = 0;
		// Generate the array with those parameters
		generate();
	};

  // Destructor
  ~Spatial(){
    delete []array;
    delete []baseArray;
    delete []weight;
    delete []theta;
    delete []thetaLim;
    delete []phi;
  }

  // Input the standard deviation of errors 
  void putSigma(const T sigma){
    standDevGaussian = sigma;
  }

  // Input the limit of the spatial energy distribution
  void putCirSolarLimit(const T csl){
    cirSolarLimit = csl;
  }

  // Input the circumsolar ratio
  void putCSR(const T csr){
    cirSolarRatio = csr;
  }

  // Define the number of point that make up the solar array
  void putArrayDim(const  size_t nrp, const  size_t ns){
    noRadialPoints = nrp;
    noSpurs        = ns;
    blockSize = nrp * ns;
  }  

  // Generate the solar energy distribution
  void generate(void){

    delete []array;
    delete []baseArray;
    delete []weight;
    delete []theta;
    delete []thetaLim;
    delete []phi;

    allocateDimensions();
    allocateProfile();
    generateSolarArray();
    if (standDevGaussian > 0.0) broadenDist();
    allocateWeight();
  }
  
  /* Generate the solar energy distribution 
   * calculating the spatial distribution at each
   * of these angular displacement from the solar
   * vector and boundary regions */
  void generate(const T externTheta[], const T externThetaLim[], const  int n){

    delete []array;
    delete []baseArray;
    delete []weight;
    delete []theta;
    delete []thetaLim;
    delete []phi;

    allocateDimensions();
    noRadialPoints = n;
    theta    = new T[noRadialPoints];
    thetaLim = new T[noRadialPoints];
    
    for ( size_t i = 0; i < noRadialPoints; i++){
      theta[i] = externTheta[i];
      thetaLim[i] = externThetaLim[i];
    }

    allocateProfile();
    generateSolarArray();
    if (standDevGaussian > 0.0) broadenDist();
    allocateWeight();
  }

  /* Generate the solar energy distribution
   * using this spatial energy profile */  
  void generate(const T externTheta[], const T externThetaLim[], 
	const T externPhi[], const size_t n){

    delete []array;
    delete []baseArray;
    delete []weight;
    delete []theta;
    delete []thetaLim;
    delete []phi;

    allocateDimensions();

    noRadialPoints = n;
    theta    = new T[noRadialPoints];
    thetaLim = new T[noRadialPoints];
    phi      = new T[noRadialPoints];

    for ( size_t i = 0; i < noRadialPoints; i++){
      theta[i]     = externTheta[i];
      thetaLim[i]  = externThetaLim[i];
      phi[i]       = externPhi[i];
    }

    generateSolarArray();
    if (standDevGaussian > 0.0) broadenDist();
    allocateWeight();
  }

  /* Rotate the solar array to be about the solar vector */
  void rotate(vec4 solarVector)  {

    if (solarVector.length() != 1.0 ) solarVector.normalize();  
    
	// Determine the half vector
    vec4 axis(solarVector);  
		if (axis.equals( vec4(0,0,-1,0) ) ){
			axis.set(0,1,0,0);
		} else {
    	axis += vec4(0,0,1,0);
    	axis.normalize();
		}

	// Determine the angle of rotation
    const T cosAngle = axis.dot(solarVector);

	// create the axis of rotation and angle
    axis.cross( axis , solarVector );
    axis.w = cosAngle;

	// Set the rotational matrix
    mat4 mat;
    mat.set(axis);

	// Allocate the array
    for ( size_t i = 0; i < blockSize; i++)
	 	array[i] = mat * baseArray[i];
  }

#ifdef SUNPOS_H
  void rotate(const Sunpos<T>& solarpos){
     rotate(solarpos.solarVector);
  }
#endif

  /* Allocate the size of the solar array */
  void size( size_t& i) {
    i = blockSize;
  }

  /* Return the size of the solar array */
   size_t size(void) const {
    return blockSize;
  }

  /* Return the solar array about the znormal vector */
  void getNormalArray(vec4* ar, T* we) const {
    for ( size_t i = 0; i < blockSize; i++){
	    ar[i] = baseArray[i];
	    we[i] = weight[i];
    }
  }

  /* Return the solar array about the solar vector */
  void get(vec4* ar, T* we) const {
    for ( size_t i = 0; i < blockSize; i++){
	    ar[i] = array[i];
	    we[i] = weight[i];
    }
  }

  /* Return the solar array about the solar vector */
  void get(vec4& ar, T& we, size_t i) const {
	    ar = array[i];
	    we = weight[i];
  }

  
private:

  T calcIntensity(const double tempAngle) const {
    /** Sunshape distribution defined by Buie et al.
      * "Sunshape distribution for terrestrial solar simulations"
      * Solar Energy 74(2):111-120 
	  */

    // Solar Disk limit
    const T solarDiskLimit = 0.00465;
    // Output variable
    T intensity;
    // Algorithm is for milliradians
    const T tempAngleMrad = tempAngle * 1000.0;
    // circumsolar region variables
    const T kappa = 0.9 * std::log( 13.5 * cirSolarRatio ) * 
	    std::pow( cirSolarRatio , -0.3 );
    const T gamma = 2.2 * std::log( 0.52 * cirSolarRatio ) * 
	    std::pow( cirSolarRatio , 0.43 ) - 0.1;
    // Calculating the intensity
    if ( tempAngle <= solarDiskLimit )
      intensity = std::cos( tempAngleMrad * 0.326 ) / std::cos( 0.308 * tempAngleMrad);
    else intensity = std::exp( kappa ) * std::pow( tempAngleMrad , gamma );
    // Returning the value of the normalised intensity per steradian
    return intensity;
  }
  
  void allocateDimensions(void);
  void allocateProfile(void);
  void generateSolarArray(void);
  void allocateWeight(void);
  void broadenDist(void);
  void gaussianWeight(const vec4*,T*, const  size_t);
  void gaussianDist(vec4 *, size_t*,const T);
  void convolution(const vec4*,const T*,const  size_t );  
  

}; // end class Spatial


template <class T>
void Spatial<T>::allocateDimensions(void) {

  // step size 
  const T ang = cirSolarLimit / (noRadialPoints-1);

  // Angular displacement of each vector 
  theta     = new T[noRadialPoints];
  for ( size_t i = 0; i <noRadialPoints; i++) theta[i] = i * ang;

  // Angular displacement of each vector boundary 
  thetaLim  = new T[noRadialPoints];

  for (  size_t i = 0; i < noRadialPoints - 1; i++)
    thetaLim[i] = ( theta[i] + theta[i+1] ) / 2.0;

  thetaLim[noRadialPoints - 1] = 2 * theta[noRadialPoints - 1] 
	  - thetaLim[noRadialPoints - 2];
}

template <class T>
void Spatial<T>::allocateProfile(void) {
  phi = new T[noRadialPoints];
  for ( size_t i = 0; i < noRadialPoints; i++) phi[i] = calcIntensity(theta[i]);
}

template <class T>
void Spatial<T>::generateSolarArray(void) {
  // Define the maximum size of the solar array 
  blockSize = noRadialPoints * noSpurs;

  // Dynamically allocate two arrays 
  baseArray   = new vec4[blockSize];
  array       = new vec4[blockSize];

  // Initiate auxiliary variables 
  const T ang = 6.28318530717956 / noSpurs;
  size_t counter = 0;

  // Generate the solar array 
  baseArray[counter++].set(0.0,0.0,1.0,0);

  for( size_t j = 1; j < noRadialPoints; j++){
    const T sinang = std::sin(theta[j]);
    const T cosang = std::cos(theta[j]);
    for( size_t i = 0; i < noSpurs; i++)
      baseArray[counter++].set( sinang* std::cos(ang * i ),
	    sinang * std::sin(ang * i ), cosang,0);
  }

  // Redefine the size of the solar array 
  blockSize = counter;

}

template <class T>
void Spatial<T>::allocateWeight(void) {

  // weight of each vector and the number
  // of steradians each vector represents 
  weight     = new T[blockSize];
  T *noSter  = new T[noRadialPoints];

  const T TWOPI = 6.28318530717956;

  for( size_t i=0; i<noRadialPoints; i++) noSter[i] = TWOPI * (1.0 - cos(thetaLim[i]) );
  for( size_t i=1; i<noRadialPoints; i++) noSter[i] -= TWOPI * (1.0 - cos(thetaLim[i - 1]) );

  size_t counter = 0;
  T normalisingConstant = 0;

  weight[counter++] = noSter[0] * phi[0];
  normalisingConstant = noSter[0] * phi[0];

  for ( size_t j = 1; j < noRadialPoints; j++){
	const T tempvar = noSter[j] * phi[j] / noSpurs;
    for ( size_t k = 0; k < noSpurs; k++){
      weight[counter++]    = tempvar;
      normalisingConstant += tempvar;
    }
  }

  for ( size_t i = 0; i < blockSize; i++)
    weight[i] /= normalisingConstant;

  delete []noSter;
}

template <class T>
void Spatial<T>::broadenDist(){
// This performs the convolution of the of the solar energy
// distribution and a gaussian distribution represnting 
// the standard deviation of the surface normal deviations 
 
  size_t size = noRadialPoints;

  vec4 *gaussian = new vec4[size*size];
  gaussianDist(gaussian,&size, 3.0 * standDevGaussian);

  T *gaussWeight = new T[size];
  gaussianWeight(gaussian,gaussWeight,size);

  convolution(gaussian,gaussWeight,size);

  delete []gaussian;
  delete []gaussWeight;
}

template <class T>
void Spatial<T>::gaussianDist(vec4 gaussian[], size_t *n,const T extent){
// creates the gaussian distribution represnting the spatial variation
// in the surface normal distribution 
 
  size_t counter = 0;
  const T unit = 2 * extent / (*n-1);
  const T angleExt = std::cos(extent);

  for( size_t i=0; i < *n; i++) {
    for( size_t j = 0; j < *n; j++) {
      gaussian[counter].set(-extent + i*unit, -extent + j * unit , 1, 0);
      gaussian[counter].normalize();
	  // Ensure that the gaussian distribution is circular 
      if (gaussian[counter++].z < angleExt ) counter--;
    }
  }

  // reallocate the dimensions of size 
  *n = counter;
}

template <class T>
void Spatial<T>::gaussianWeight(const vec4 gaussian[],T gaussWeight[], const  size_t n){
// Calculates the weight of each of the solar vectors 

  const T precalc =  2.0 * standDevGaussian * standDevGaussian; // precalculate

	T all = 0;

  for(  size_t i = 0; i < n; i++) {
    const T angle = std::acos( gaussian[i].z );
    gaussWeight[i] =  exp( -angle * angle / precalc );
	all += gaussWeight[i];
  }

  for (size_t i = 0; i < n; i++)
  	gaussWeight[i] /= all;
  
}

template <class T>
void Spatial<T>::convolution(const vec4 locarray[],const T locweight[],const  size_t n){

  T *tempPhi    = new T[noRadialPoints];
  T *energy     = new T[noRadialPoints];
  T *noSter     = new T[noRadialPoints];

  const T TWOPI = 6.28318530717956;

  for(  size_t i=0; i < noRadialPoints; i++ )
  {

    tempPhi[i] = 0.0;
    noSter[i]  = TWOPI * ( 1.0 - std::cos( thetaLim[i] )  );
    if ( i != 0 ) noSter[i] -= TWOPI * ( 1.0 - std::cos( thetaLim[i-1] )  );
    energy[i]  = noSter[i]*phi[i];

  }

  for( size_t i=0; i<noRadialPoints; i++)
  {

    mat4 rotMat;
    rotMat.rotY(theta[i]);

    for ( size_t j=0; j<n; j++){
      const vec4 tempVec = rotMat * locarray[j];
      const T angle = std::acos(tempVec.z);
//       size_t k = 0;
		
	  for (size_t k = 0; k < noRadialPoints; ++k)
		if (angle < thetaLim[k])
		{
			tempPhi[k]+= energy[i] * locweight[j];
			break;
		}
    }
  }

  for( size_t i=0; i<noRadialPoints; i++) phi[i] = tempPhi[i] / noSter[i];

  delete []tempPhi;
  delete []energy;
  delete []noSter;
}

} // End of namespace


template <class T>
std::ostream& operator<<(std::ostream& o, const PSM::Spatial<T>& s1) {
  return o
  <<"Circumsolar Limit                    > "<<s1.cirSolarLimit<<" Radians"<< std::endl
  <<"Circumsolar Ratio                    > "<<s1.cirSolarRatio<<" "<< std::endl
  <<"Standard Deviation of errors         > "<<s1.standDevGaussian<<" Radians"<< std::endl
  <<"Number of Radial Points              > "<<s1.noRadialPoints<<" "<< std::endl
  <<"Number of Spurs                      > "<<s1.noSpurs << std::endl
  <<"Total Number of solar vectors        > "<<s1.blockSize<< std::endl;
}


#endif  // SUNPOS_H
