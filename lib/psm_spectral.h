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

#ifndef SPECTRAL_H
#define SPECTRAL_H

/* The algorithm Spectral can be used without using
* the vecmath library. Simply uncomment the following
* line or edit solar_conf.h
*/
//#undef USE_VECMATH

namespace PSM {

template <class T>
class Spectral{

public:

  int outputUnits; /* Spectral2 output units */
  
  T tau500;        /* Aerosol optical depth at 0.5 microns, base e */
  T watvap; 	   /* Precipitable water vapor (cm) */
  T alpha ; 	   /* Power on Angstrom turbidity */
  T assym ; 	   /* Aerosol assymetry factor */
  T ozone ; 	   /* Atmospheric ozone (cm) */
  T airpressure;
  T tilt;          /* Tilt angle of the receiver surface */
  T aspect;        /* Aspect of the surface */
  T airmass;       /* Optical airmass */
  T airmassPC;     /* Optical airmass pressure corrected */

  T zenithAngle;
  T azimuthAngle;
  int dayNumber;   /* Day of the year */

	size_t blocksize;

  /* Spectral arrays */
  T* extraTSpectrum;
  T* diffuseSpectrum;
  T* directSpectrum;
  T* globalSpectrum;
  T* wavelength;

  /* Local insolations values (W/m^2) */
  T diffuseRadiation;
  T directRadiation;
  T globalRadiation;

public:

  /* Constructor */
  Spectral(int a = 1, T b = 0.084, T c = 1.4164, T d= 1.14, T e = 0.65, T f = 0.3438,
	     T g = 1013.25, T h = 0.0, T i = 0.0  ): outputUnits(a), tau500(b), 
       watvap(c), alpha(d), assym(e), ozone(f), airpressure(g), tilt(h), aspect(i), blocksize(122) {

      directSpectrum  = new T[blocksize];
      diffuseSpectrum = new T[blocksize];
      globalSpectrum  = new T[blocksize];
      extraTSpectrum  = new T[blocksize];
      wavelength      = new T[blocksize];

	}
  
  virtual ~Spectral() {
	    delete []directSpectrum;
			delete []diffuseSpectrum;
			delete []globalSpectrum;
			delete []extraTSpectrum;
			delete []wavelength;
	}

  /* Input parameters specifically */
  void putUnits       (int x){ outputUnits = x; }
  void putAirPressure (T x)  { airpressure = x; }
  void putTau500      (T x)  { tau500 = x; }
  void putWaterVapour (T x)  { watvap = x; }
  void putAlpha       (T x)  { alpha  = x; }
  void putAssym       (T x)  { assym  = x; }
  void putOzone       (T x)  { ozone  = x; }
  void putTilt        (T x)  { tilt   = x; }

  // Return Function
  const size_t size(void) const {return blocksize;}   // Size of spectral arrays
  void  size(  size_t &ret) const { ret = blocksize;}  // Size of spectral arrays

  void getDifSpectrum  (T* ret) const {alloc(ret, diffuseSpectrum);} // Diffuse spectrum
  void getDirSpectrum  (T* ret) {alloc(ret, directSpectrum);}  // Direct spectrum
  void getExtTSpectrum (T* ret) const {alloc(ret, extraTSpectrum);}  // Extraterrestrial spectrum
  void getGloSpectrum  (T* ret) const {alloc(ret, globalSpectrum);}  // globalRadiation_ spectrum
  void getWavelength   (T* ret) const {alloc(ret, wavelength);}      // X-value  of spectrum

  void alloc(T* ret, T* p) const { for (size_t i=blocksize; i--; ) ret[i] = p[i];}

  void getDifSpectrum  (T& ret,size_t i) const {ret =  diffuseSpectrum[i];} // Diffuse spectrum
  void getDirSpectrum  (T& ret,size_t i) const {ret =  directSpectrum[i];}  // Direct spectrum
  void getExtTSpectrum (T& ret,size_t i) const {ret =  extraTSpectrum[i];}  // Extraterrestrial spectrum
  void getGloSpectrum  (T& ret,size_t i) const {ret =  globalSpectrum[i];}  // globalRadiation_ spectrum
  void getWavelength   (T& ret,size_t i) const {ret =  wavelength[i];}      // X-value  of spectrum

  T getDifSpectrum  (const size_t i) const {return  diffuseSpectrum[i];} // Diffuse spectrum
  T getDirSpectrum  (const size_t i) const {return  directSpectrum[i];}  // Direct spectrum
  T getExtTSpectrum (const size_t i) const {return  extraTSpectrum[i];}  // Extraterrestrial spectrum
  T getGloSpectrum  (const size_t i) const {return  globalSpectrum[i];}  // globalRadiation_ spectrum
  T getWavelength   (const size_t i) const {return  wavelength[i];}      // X-value  of spectrum

  /** Returns the Diffuse radiation W/m^2
    * Returns the Direct radiation W/m^2
    * Returns the Global radiation W/m^2
    */
  void getDifRadiation(T& ret) const { ret = diffuseRadiation;}
  void getDirRadiation(T& ret) const { ret = directRadiation;}
  void getGloRadiation(T& ret) const { ret = globalRadiation;}

  void getAirmass(T& a) const { a = airmass;}
  void getAirmassPC(T& a) const { a = airmassPC;}

	void getOutputUnit(int& i){ i = outputUnits; }

  /* generate the solar spectrum + insolation values using the zenith, azimuth
   * and day number as input arguments */
  void generate(const T ze, const T az, const int dn, const int onlyif = 1){
    zenithAngle = ze;
    azimuthAngle = az;
    dayNumber = dn;
    calcAirmass();
    calcSpectrum();
    if ( onlyif ) calcInsolation();
  }

#ifdef SUNPOS_H
  /* generate the solar spectrum + insolation values using the
   * variables contained with the Sunpos::sunpos */
  void generate(const Sunpos<T>& sunpos, const int onlyif = 1){
    zenithAngle = sunpos.zenithAngle;
    azimuthAngle = sunpos.azimuthAngle;
    dayNumber = sunpos.dayNumber;
    calcAirmass();
    calcSpectrum();
    if ( onlyif ) calcInsolation();
  }
#endif

#ifdef USE_VECMATH
  /* Generates the solar spectrum + insolation for a given solar vector and daynumber */
  void generate( NAMESPACE::Vector4T solarVector, const int DN = 1, const int onlyif = 1){
    if (solarVector.length() != 1) solarVector.normalize();

    zenithAngle = std::acos(solarVector.z);

    if (zenithAngle == 0) azimuthAngle = 0.0;
    else azimuthAngle = std::acos(solarVector.y / sin(zenithAngle));

    dayNumber = DN;
    
    calcAirmass();
    calcSpectrum();
    if ( onlyif ) calcInsolation();
  }
#endif

  /** Kasten, F. and Young, A.  1989.  Revised optical air mass
    * tables and approximation formula.  Applied Optics 28 (22),
    * pp. 4735-4738 */  
  void calcAirmass( void ) {

    const T RAD = 0.01745329252;
    
    if ( zenithAngle / RAD > 93.0 ) {
      airmass   = -1.0;
      airmassPC = -1.0;
    }
    else {
      airmass = 1.0 / ( std::cos(zenithAngle) + 0.50572 *
			   std::pow( (96.07995 - zenithAngle / RAD) , -1.6364) );
      airmassPC = airmass * airpressure / 1013.25;
    }
  }

  /**
    * Calculate the solar insolation values
   * using the trapazoidal method. This is
   * probably the most appropriate
   * method as the wavelengths were chosen at
   * absorption lines. The equation includes
   * a correction for the corresponding units.
   */
  void calcInsolation(void);

  /**
    * Calculate the energy for a given wavelengh
   * using the trapazoidal method. This is
   * probably the most appropriate
   * method as the wavelengths were chosen at
   * absorption lines. The equation includes
   * a correction for the corresponding units.
   */
  T getDirectEnergy(const T&) const;
  T getDirectEnergy(const size_t&) const;

	size_t getIndexValue(const T& wave) const {

		assert(wave < 4);

		size_t i;
		for ( i = blocksize; i--;  ) {
			if (wave >= wavelength[i])
				break;
		}
	
		return i;
	}

	T getDirectAverage(const T& wave1, const T& wave2) const {
		const int i = getIndexValue(wave1);
		const int j = getIndexValue(wave2);

		T tmp = 0;

		assert(i <= j);

		if ( i == j) {
			return getDirSpectrum(i);
		} else {
			for (int k = i; k < j; k++)
				tmp += getDirSpectrum(k);
		}

		return tmp/(j-i);

	}


  /**
    * Spectral2 C++ implementation using the day number and position
   * as imput arguments.
   */
  void calcSpectrum( void );

}; // End of class Spectral2;

template <class T>
T Spectral<T>::getDirectEnergy(const T& tmp_wavelength) const {
	
	size_t i;
	for ( i = 0; i < blocksize; i++ ) {
		if (tmp_wavelength < wavelength[i])
			break;
	}
	
	return getDirectEnergy(i);

}

template <class T>
T Spectral<T>::getDirectEnergy(const size_t& i) const {
	assert( i < blocksize );
	
	if (i == blocksize - 1)
		return 0;
	
	T tDir  = ( directSpectrum[i]  + directSpectrum[i+1] );
	T tStep = ( wavelength[i+1] - wavelength[i] );
	T var;

	switch (outputUnits){
	 case 1:
	   tDir /= 2.0 * tStep;
	   break;

	 case 2:
	   var = tStep / ( wavelength[i+1] + wavelength[i] ) * 2.9979244e8 * 6.6261762e-24;
	   tDir *= var;
	   break;

	 case 3:
	   var = ( wavelength[i+1] + wavelength[i] ) / 4.0 * tStep  * 1.6021891e-15;
	   tDir *= -var;
	   break;
    }

	return tDir;

}


template <class T>
void Spectral<T>::calcInsolation(void){
  /**
    * Calculate the solar insolation values
    * using the trapazoidal method. This is
    * probably the most appropriate
    * method as the wavelengths were chosen at
    * absorption lines. The equation includes
    * a correction for the corresponding units.
    */

    diffuseRadiation = directRadiation  = globalRadiation  = 0.0;
    
    for(size_t i=0; i<blocksize - 1; i++) {

      T tStep = ( wavelength[i+1] - wavelength[i] );
      T tDif  = ( diffuseSpectrum[i] + diffuseSpectrum[i+1] );
      T tDir  = ( directSpectrum[i]  + directSpectrum[i+1] );
      T tGlo  = ( globalSpectrum[i]  + globalSpectrum[i+1] );
      T var;

      switch (outputUnits){
	 case 1:
	   diffuseRadiation += tDif / 2.0 * tStep;
	   directRadiation  += tDir / 2.0 * tStep;
	   globalRadiation  += tGlo / 2.0 * tStep;
	   break;

	 case 2:
	   var = tStep / ( wavelength[i+1] + wavelength[i] ) * 2.9979244e8 * 6.6261762e-24;
	   diffuseRadiation += tDif * var;
	   directRadiation  += tDir * var;
	   globalRadiation  += tGlo * var;
	   break;

	 case 3:
	   var = ( wavelength[i+1] + wavelength[i] ) / 4.0 * tStep  * 1.6021891e-15;
	   diffuseRadiation -= tDif * var;
	   directRadiation  -= tDir * var;
	   globalRadiation  -= tGlo * var;
	   break;
    }
  }
}

template <class T>
void Spectral<T>::calcSpectrum(void) {
 /* Spectral.h ::  Developed from the anscii c code
  * S_spectral2 (National Renewable Energy Laboratories's
  * simple spectral model), initially written by Martin Rymes
  * from the National Renewable Energy Laboratory (NREL) on
  * 21 April 1998. Spectral2 is based on the SERI (now NREL)
  * technical report SERI/TR-215-2436, "Simple Solar Spectral
  * Model for Direct and Diffuse Irradiance on Horizontal and
  * Tilted Planes at the Earth's Surface for Cloudless
  * Atmospheres", by R. Bird & C. Riordan
  */
  
  
  /* wavelegths points */
  const float tempWavelength[122] = {
    0.3, 0.305, 0.31, 0.315, 0.32, 0.325, 0.33, 0.335, 0.34,
    0.345, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47,
    0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.57, 0.593, 0.61, 0.63, 0.656,
    0.6676, 0.69, 0.71, 0.718, 0.7244, 0.74, 0.7525, 0.7575, 0.7625, 0.7675, 0.78, 0.8,
    0.816, 0.8237, 0.8315, 0.84, 0.86, 0.88, 0.905, 0.915, 0.925, 0.93, 0.937, 0.948,
    0.965, 0.98, 0.9935, 1.04, 1.07, 1.1, 1.12, 1.13, 1.145, 1.161, 1.17, 1.2, 1.24,
    1.27, 1.29, 1.32, 1.35, 1.395, 1.4425, 1.4625, 1.477, 1.497, 1.52, 1.539, 1.558,
    1.578, 1.592, 1.61, 1.63, 1.646, 1.678, 1.74, 1.8, 1.86, 1.92, 1.96, 1.985, 2.005,
    2.035, 2.065, 2.1, 2.148, 2.198, 2.27, 2.36, 2.45, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0,
    3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0};
  /* extraterrestrial spectrum (W/sq m/micron) */
  const float horizExtraSpectrum[122] = {
    535.9, 558.3, 622.0, 692.7, 715.1, 832.9, 961.9, 931.9, 900.6, 911.3, 975.5,
    975.9, 1119.9, 1103.8, 1033.8, 1479.1, 1701.3, 1740.4, 1587.2, 1837.0, 2005.0,
    2043.0, 1987.0, 2027.0, 1896.0, 1909.0, 1927.0, 1831.0, 1891.0, 1898.0, 1892.0,
    1840.0, 1768.0, 1728.0, 1658.0, 1524.0, 1531.0, 1420.0, 1399.0, 1374.0, 1373.0,
    1298.0, 1269.0, 1245.0, 1223.0, 1205.0, 1183.0, 1148.0, 1091.0, 1062.0, 1038.0,
    1022.0, 998.7, 947.2, 893.2, 868.2, 829.7, 830.3, 814.0, 786.9, 768.3, 767.0, 757.6,
    688.1, 640.7, 606.2, 585.9, 570.2, 564.1, 544.2, 533.4, 501.6, 477.5, 442.7, 440.0,
    416.8, 391.4, 358.9, 327.5, 317.5, 307.3, 300.4, 292.8, 275.5, 272.1, 259.3, 246.9,
    244.0, 243.5, 234.8, 220.5, 190.8, 171.1, 144.5, 135.7, 123.0, 123.8, 113.0, 108.5,
    97.5, 92.4, 82.4, 74.6, 68.3, 63.8, 49.5, 48.5, 38.6, 36.6, 32.0, 28.1, 24.8, 22.1,
    19.6, 17.5, 15.7, 14.1, 12.7, 11.5, 10.4, 9.5, 8.6};
  /* Water vapor absorption coefficient */
  const float waterVapourAdj[122] = {
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.075, 0.0, 0.0, 0.0, 0.0, 0.016, 0.0125, 1.8, 2.5, 0.061, 0.0008, 0.0001, 0.00001,
    0.00001, 0.0006, 0.036, 1.6, 2.5, 0.5, 0.155, 0.00001, 0.0026, 7.0, 5.0, 5.0, 27.0,
    55.0, 45.0, 4.0, 1.48, 0.1, 0.00001, 0.001, 3.2, 115.0, 70.0, 75.0, 10.0, 5.0, 2.0,
    0.002, 0.002, 0.1, 4.0, 200.0, 1000.0, 185.0, 80.0, 80.0, 12.0, 0.16, 0.002, 0.0005,
    0.0001, 0.00001, 0.0001, 0.001, 0.01, 0.036, 1.1, 130.0, 1000.0, 500.0, 100.0, 4.0,
    2.9, 1.0, 0.4, 0.22, 0.25, 0.33, 0.5, 4.0, 80.0, 310.0, 15000.0, 22000.0, 8000.0,
    650.0, 240.0, 230.0, 100.0, 120.0, 19.5, 3.6, 3.1, 2.5, 1.4, 0.17, 0.0045 };
  /* Ozone absorption coefficient */
  const float ozoneAdj[122] = {
    10.0, 4.8, 2.7, 1.35, 0.8, 0.38, 0.16, 0.075, 0.04, 0.019, 0.007, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.003, 0.006, 0.009, 0.01400, 0.021, 0.03, 0.04,
    0.048, 0.063, 0.075, 0.085, 0.12, 0.119, 0.12, 0.09, 0.065, 0.051, 0.028, 0.018,
    0.015, 0.012, 0.01, 0.008, 0.007, 0.006, 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 };
  /* Uniformly mixed gas "absorption coefficient" */
  const float uniMixedGasAdj[122] = {
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.15, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.0, 0.35, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.05, 0.3, 0.02, 0.0002, 0.00011, 0.00001, 0.05,
    0.011, 0.005, 0.0006, 0.0, 0.005, 0.13, 0.04, 0.06, 0.13, 0.001, 0.0014, 0.0001,
    0.00001, 0.00001, 0.0001, 0.001, 4.3, 0.2, 21.0, 0.13, 1.0, 0.08, 0.001, 0.00038,
    0.001, 0.0005, 0.00015, 0.00014, 0.00066, 100.0, 150.0, 0.13, 0.0095, 0.001, 0.8,
    1.9, 1.3, 0.075, 0.01, 0.00195, 0.004, 0.29, 0.025 };

  const T c      =  2.9979244e14;  // Used to calculate photon flux
  const T cons   =  5.0340365e14;  // Used to calculate photon flux
  const T evolt  =  1.6021891e-19; // Joules per electron-volt
  const T h      =  6.6261762e-34; // Used to calculate photon flux
  const T OMEG   =  0.945;         // Single scattering albedo, 0.4 microns
  const T OMEGP  =  0.095;         // Wavelength variation factor
  const T e      =  h * c / evolt; // energy in electron volts
  const T PI     = 3.1415926535;
  const T RAD    = 0.01745329252;
  
  /* Cosine of the angle between the sun and a tipped flat surface,
    useful for calculating solar energy on tilted surfaces. */
  T ci  = std::cos(zenithAngle) * std::cos ( tilt ) + std::sin ( zenithAngle )
    * std::sin ( tilt ) * ( std::cos ( azimuthAngle ) * std::cos ( aspect )
			  * + std::sin( azimuthAngle ) * std::sin( aspect ));

  /* If the tilt angle is greater than PI assuming tracking */
  if (fabs(tilt) > PI){
    tilt = zenithAngle;
    ci   = 1.0;
  }

  /* Precalculate the cosines */
  T ct = std::cos( tilt );
  T cz = std::cos( zenithAngle );

  /* Ground Reflection have been hardwired -
    * these are for solar energy calculations*/
  T wv[6] = {0.3, 0.7, 0.8, 1.3, 2.5, 4.0};
  T rf[6] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2};

  /* Equation 3-14 */
  T alg = std::log( 1.0 - assym );

  /* Equation 3-12 */
  T afs = alg*( 1.459 + alg * ( 0.1595 + alg * 0.4129));

  /* Equation 3-13 */
  T bfs = alg*( 0.0783 + alg * ( -0.3824 - alg * 0.5874));

  /* Equation 3-15 */
  T fsp = 1.0 - 0.5 * std::exp( ( afs + bfs / 1.8 ) / 1.8);

  /* Equation 3-11 */
  T fs  = 1.0 - 0.5 * std::exp ( ( afs + bfs * cz ) * cz);

  /* Ozone mass */
  T ozoneMass = 1.003454 / std::sqrt( cz * cz + 0.006908 );

  /* Current wavelength range */
  int nr = 1;

  /** ERV calculation, Day angle
    * Iqbal, M.  (1983)  An Introduction to
    * Solar Radiation. Academic Press, NY., page 3 */
  T dayang = RAD * 360.0 * ( dayNumber - 1.0 ) / 365.0;

  /** Earth radius Vector * solar constant = solar energy
    * Spencer, J. W.  1971.  Fourier series representation of the
    * position of the sun.  Search 2 (5), page 172 */
  T erv = 1.000110 + 0.034221 * std::cos( dayang ) + 0.001280 * std::sin( dayang )
    + 0.000719 * std::cos( dayang * 2 ) + 0.000077 * std::sin( dayang * 2 );

  for(size_t i=0; i<blocksize; ++i) {
    /* MAIN LOOP:  step through the wavelengths */

    /* Input variables */
    T lambda         = tempWavelength[i];
    T H0             = horizExtraSpectrum[i] * erv;
    T WatVap         = waterVapourAdj[i] * watvap;
    T Ozone          = ozoneAdj[i] * ozone;
    T UniMixAdj      = uniMixedGasAdj[i];


    /* Equation 3-16 */
    T omegl = OMEG * std::exp(-OMEGP * std::pow(std::log(lambda/0.4), 2));

    /* Equation 2-7 */
    T c1 = tau500 * std::pow(lambda * 2.0, -alpha);

    /* Advance to the next wavelength range for ground reflectivity */
    if (lambda>wv[nr]) ++nr;

    /* Equation 2-4 */
    T Tr = std::exp( -airmassPC /
	     ( std::pow( lambda, 4 ) * ( 115.6406 - 1.3366 / std::pow( lambda, 2 ))) );

    /* Equation 2-9 */
    T To = std::exp( -Ozone * ozoneMass );

    /* Equation 2-8 */
    T Tw = std::exp( -0.2385 * WatVap  * airmass /
		  std::pow (( 1.0 + 20.07 * WatVap * airmass ), 0.45 ));

    /* Equation 2-11 */
    T Tu = std::exp( -1.41 * UniMixAdj * airmassPC /
		  std::pow(( 1.0 + 118.3 * UniMixAdj * airmassPC), 0.45 ) );

    /* Equation 3-9 */
    T Tas = std::exp( -omegl * c1 * airmass);

    /* Equation 3-10 */
    T Taa = std::exp(( omegl - 1.0 ) * c1 * airmass );

    /* Equation 2-6, sort of */
    T Ta = std::exp( -c1 * airmass );

    /* Equation 2-4; primed */
    T Trp = std::exp( -1.8 /
	 ( std::pow( lambda, 4 ) * ( 115.6406 - 1.3366 / std::pow( lambda, 2 ))) );

    /* Equation 2-8; primed */
    T Twp = std::exp( -0.4293 * WatVap / std::pow( 1.0 + 36.126 * WatVap, 0.45) );

    /*Equation2-11;primedairmassM = 1.8 */
    T Tup = std::exp( -2.538 * UniMixAdj / std::pow( 1.0+212.94 * UniMixAdj, 0.45) );

    /* Equation 3-9; primed airmass M = 1.8 (Section 3.1) */
    T Tasp = std::exp( -omegl * c1 * 1.8 );

    /* Equation 3-10; primed airmass M = 1.8 (Section 3.1) */
    T Taap = std::exp( ( omegl - 1.0 ) * c1 * 1.8 );

    /* Direct energy */
    T c2 = H0 * To * Tw * Tu;

    /* Equation 2-1 */
    T dir = c2 * Tr * Ta;

    /* Diffuse energy */
    c2  *= cz * Taa;
    T c3 = (rf[nr]-rf[nr-1])/(wv[nr]-wv[nr-1]);

    /* Equation 3-17; c4 = Cs */
    T c4 = 1.0;

    if ( lambda <= 0.45 ) c4 = std::pow((lambda+0.55),1.8);

    /* Equation 3-8 */
    T rhoa = Tup*Twp*Taap*( 0.5*(1.0-Trp) + (1.0-fsp)*Trp*(1.0-Tasp) );

    /* Interpolated ground reflectivity */
    T rho = c3 * ( lambda - wv[nr-1] ) + rf[nr-1];

    /* Equation 3-5 */
    T dray = c2*(1.0-std::pow(Tr,0.95))/2.0;

    /* Equation 3-6 */
    T daer = c2* std::pow(Tr,1.5)*(1.0-Tas)*fs;

    /* Equation 3-7 */
    T drgd = (dir*cz+dray+daer)*rho*rhoa/(1.0-rho*rhoa);

    /* Equation 3-1 */
    T dif = (dray+daer+drgd)*c4;

    /* globalRadiation (total) energy */
    T dtot = dir*cz+dif;

    /* Tilt energy, if applicable */
    if ( tilt > 1.0e-4 ) {

      /* Equation 3-18 without the first (direct radiation - beam) term */
      c1 = dtot*rho*(1.0-ct)/2.0;
      c2 = dir/H0;
      c3 = dif*c2*ci/cz;
      c4 = dif*(1.0-c2)*(1.0+ct)/2.0;
      dif = c1+c3+c4;
      dtot = dir*ci+dif;
    }

    /* Adjust the output according to the units requested */
    switch (outputUnits) {
      case 1:
	 c1 = 1;
	 wavelength[i] = lambda;
	 break;
      case 2:
	 wavelength[i] = lambda;
	 c1  = lambda * cons;
	 break;
      case 3:
	 wavelength[i] = e/lambda;
	 c1 = lambda * lambda * lambda *cons / e;
	 break;
    }

    globalSpectrum[i]  = dtot * c1;
    directSpectrum[i]  = dir  * c1;
    diffuseSpectrum[i] = dif  * c1;
    extraTSpectrum[i]  = H0   * c1;
  }
}

} // End namespace

template <class T>
std::ostream& operator<<(std::ostream& o, const PSM::Spectral<T>& s1) {
  return o
  <<"Aerosol optical depth at 0.5 microns > "<<s1.tau500<<" base e"<<std::endl
  <<"Precipitable water vapor             > "<<s1.watvap <<" cm"<<std::endl
  <<"Power on Angstrom turbidity          > "<<s1.alpha<<"  "<<std::endl
  <<"Aerosol assymetry factor             > "<<s1.assym<<std::endl
  <<"Atmospheric ozone                    > "<<s1.ozone<<" cm" <<std::endl
  <<"Air Pressure                         > "<<s1.airpressure<<" E02 pa"<<std::endl
  <<"Tilt on surface                      > "<<s1.tilt<<" Radians"<<std::endl
  <<"Aspect of surface                    > "<<s1.aspect <<" Radians" <<std::endl
  <<"Optical Airmass                      > "<<s1.airmass <<std::endl
  <<"Optical Airmass Pressure corrected   > "<<s1.airmassPC <<std::endl
  <<std::endl
  <<"Zenith Angle                         > "<<s1.zenithAngle<<std::endl
  <<"Azimuth Angle                        > "<<s1.azimuthAngle<<std::endl
  <<"Day Number                           > "<<s1.dayNumber<<std::endl
  <<std::endl
  <<"Diffuse Insolation                   > "<<s1.diffuseRadiation<<" W/m^2"<<std::endl
  <<"Direct Insolation                    > "<<s1.directRadiation<<" W/m^2"<<std::endl
  <<"Global Insolation                    > "<<s1.globalRadiation<<" W/m^2"<<std::endl;
}

#endif // SPECTRAL_H

