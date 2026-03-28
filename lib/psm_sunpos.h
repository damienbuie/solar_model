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



#ifndef SUNPOS_H
#define SUNPOS_H

/* The algorithm Sunpos can be used without calculating
 * the solar position as a vector (that is without using
 * the vecmath library). Simply uncomment the following 
 * line or edit solar_conf.h
 */
//#undef USE_VECMATH

#include <iostream>

namespace PSM {

template <class T>
class Sunpos
{

#ifdef USE_VECMATH
typedef NAMESPACE::Vector4T vec4;
#endif

public:
  /* Both longitude and Latitude are
   * represented as floating point
   * numbers. Local time can be a floating 
   * point number.
   */
  T longitude; 
  T latitude;  
  T localTime;
  
  /* Day of the month, month of the year
   * (0-12) and year (1995 - 2005)
   */
  int day;
  int month;
  int year;

  /** Local time at the given location
    * hours minutes and seconds can be
    * given as floating point number
    */
  T hours;
  T minutes;
  T seconds;

  /** decimalHours and elapsedJulianDays
    * are both required to determine the
    * day of the year
    */
  T decimalHours;
  T elapsedJulianDays;  
  int dayNumber;

  /** Both the zenith angle and the
    * azimuth angle are now represented
    * in radians
    */
  T zenithAngle;  
  T azimuthAngle;

#ifdef USE_VECMATH
  /** Solar vector represented as a four vector
    */
  vec4 solarVector;
  
#endif

public:

  /** The default constructor is for the locations of Sydney, Australia,
    * at 1:06 pm 1/1/2000 ESDT (Eastern Standard Daylightsavings Time) */
  Sunpos(T a = 151.2,T b = -33.867,T c = 11.0,int d = 1,int e = 1,
		  int f = 2000,T g = 13.0,T h = 6.0 ,T i = 0.0 ):
	     longitude(a),latitude(b),localTime(c), day(d),
	     month(e), year(f), hours(g - c), minutes(h), seconds(i) 
		 {
		 	calcSolarVector();
		 }

  /** Containing the dependent variables in an array */
  Sunpos( const T a[] ):
    longitude(a[0]), latitude(a[1]), localTime(a[2]), day(int(a[3])),
    month(int(a[4])), year(int(a[5])), hours(a[6] - a[2]), 
    minutes(a[7]), seconds(a[8]) 
	{
		calcSolarVector();
	}
  
#ifdef USE_VECMATH
  /** Directly imput the solar vector on initialtion */
  Sunpos( vec4& vec, const int dn = 1): 
     dayNumber(dn), solarVector(vec) {}

  /** Input the solar vector directly */
   void putSolarVector(const vec4& vec, const int dn = 1){
    	solarVector = vec;
    	dayNumber   = dn;
  }

  /** return the terrestrial solar vector */
   void get(vec4& vec){ vec = solarVector; }

#endif  

  ~Sunpos(){};

  /** Input the Zenith and Azimuth values directly (radians) */
  void putZenithAzimuth(const T zen, const T azi){
    zenithAngle = zen;
    azimuthAngle = azi;
    sphericalToVector();
    calculateDayOfTheYear();
  }
  
  /** Input longatude latitude and localtime. For information on
    * local time zones and regions see:
    * http://aa.usno.navy.mil/faq/docs/world_tzones.html */
   void putLongLatLoc(const T lon, const T lat, const T loc){
    longitude = lon;
    latitude  = lat;
    localTime = loc;
   }

  void putUniversalTime(const T loc){
  	localTime = loc;
  }

  /** Input the day, month and year */
  void putDMY(const int d, const int m, const int y){
    day   =d;
    month =m;
    year  =y;
  }

  /** Input the local time (floating point number of hours) */
   void putHour(const T h){
    hours   = h - localTime;
    minutes = 0.0;
    seconds = 0.0;    
  }

  /** Input the local time (hours, minutes, seconds) */
   void putHMS(const T h,const T m,const T s = 0.0){
    hours   = h - localTime;
    minutes = m;
    seconds = s;    
  }

  /** return the azimuth, zenith and daynum */
   void getAzimuth(T& azi)    {azi = azimuthAngle;}
   void getZenith(T& zen)     {zen = zenithAngle;}
   void getDayNum(int& dn)    {dn = dayNumber;}

  /** Calculates the solar vector in both spherical and vector coordinates
    * written by Blanco Muriel et. al. from the PSA. The azimuth and zenith
    * angles are now stored as radians */
   void generate(void){
     calcSolarVector();
   }
   
private:

  /* The original PSA algorithm */
  void calcSolarVector(void);

  /** Calculate both the difference in days between the current Julian Day
    * and JD 2451545.0, which is noon 1 January 2000 Universal Time
    * written by Blanco et al. and the day of year added by Buie et al. */
  void calculateDayOfTheYear(void){

    T dJulianDate; 
    long int liAux1; 
    long int liAux2;
    decimalHours = hours + (minutes + seconds / 60.0 ) / 60.0;
    liAux1 =(month-14)/12;
    liAux2=( 1461 * ( year + 4800 + liAux1 )) / 4 +
      (367 * ( month - 2 - 12 * liAux1 ) ) / 12 -
      ( 3 * (( year + 4900 + liAux1 ) / 100 ) ) / 4 + day -32075;
    dJulianDate = T(liAux2) - 0.5 + decimalHours / 24.0;
    elapsedJulianDays = dJulianDate - 2451545.0;

    dayNumber = liAux2 - (( 1461 * ( year + 4799 )) / 4 + 336
				 - (3 * (( year + 4899 ) / 100 )) / 4 - 32075 );
  }

#ifdef VECMATH_H
  /**Converts spherical azimuth, zenith solar coordinates to a local vector */
  void sphericalToVector(void){
    solarVector.set(
		      std::sin( azimuthAngle ) * std::sin( zenithAngle ),
		      std::cos( azimuthAngle ) * std::sin( zenithAngle ),
		      std::cos( zenithAngle ),
		      0.0
		    );
  }
#endif

}; // End of class sunpos

template <class T>
void Sunpos<T>::calcSolarVector(void) {
 /*
  * The PSA algorithm :: This Code was initially written by
  * Blanco Muriel et. al. from the PSA. The original
  * ansii c code can be downloaded from http://www.psa.es/sdg/sunpos.htm
  * The code is called the PSA algorithm for solar positioning
  * B. Muriel et al.,"Computing the solar vector "
  * Solar Energy, 2001.
  */
  
  // Defining const variables
  const T dEarthMeanRadius   = 6371.01;	 // In km
  const T dAstronomicalUnit  = 149597890;	 // In km
  const T twopi              = 6.28318530717956;
  const T rad                = 0.01745329252;

  // Main variables
  T dEclipticLongitude;
  T dEclipticObliquity;
  T dRightAscension;
  T dDeclination;

  // Auxiliary variables
  T dY;
  T dX;

  // Calculate difference in days between the current Julian Day
  // and JD 2451545.0, which is noon 1 January 2000 Universal Time

  calculateDayOfTheYear();

  // Calculate ecliptic coordinates (ecliptic longitude and obliquity of the
  // ecliptic in radians but without limiting the angle to be less than 2*Pi
  // (i.e., the result may be greater than 2*Pi)
  {
    T dMeanLongitude;
    T dMeanAnomaly;
    T dOmega;
    dOmega=2.1429-0.0010394594*elapsedJulianDays;
    dMeanLongitude = 4.8950630 + 0.017202791698 * elapsedJulianDays ; // Radians
    dMeanAnomaly = 6.2400600 + 0.0172019699 * elapsedJulianDays;
    dEclipticLongitude = dMeanLongitude + 0.03341607 * std::sin( dMeanAnomaly )
      + 0.00034894 * std::sin( 2 * dMeanAnomaly ) - 0.0001134 - 0.0000203 * std::sin(dOmega);
    dEclipticObliquity = 0.4090928 - 6.2140e-9 * elapsedJulianDays + 0.0000396 *
    std::cos( dOmega );
  }

  // Calculate celestial coordinates ( right ascension and declination ) in radians
  // but without limiting the angle to be less than 2*Pi (i.e., the result may be
  // greater than 2*Pi)
  {
    T dSin_EclipticLongitude;
    dSin_EclipticLongitude= std::sin( dEclipticLongitude );
    dY = std::cos( dEclipticObliquity ) * dSin_EclipticLongitude;
    dX = std::cos( dEclipticLongitude );
    dRightAscension = std::atan2( dY,dX );
    if( dRightAscension < 0.0 ) dRightAscension = dRightAscension + twopi;
    dDeclination = std::asin( std::sin( dEclipticObliquity ) * dSin_EclipticLongitude );
  }

  // Calculate local coordinates ( azimuth and zenith angle ) in degrees
  {
    T dGreenwichMeanSiderealTime;
    T dLocalMeanSiderealTime;
    T latitude_InRadians;
    T dHourAngle;
    T dCos_Latitude;
    T dSin_Latitude;
    T dCos_HourAngle;
    T dParallax;
    dGreenwichMeanSiderealTime = 6.6974243242 + 0.0657098283 * elapsedJulianDays + decimalHours;
    dLocalMeanSiderealTime = ( dGreenwichMeanSiderealTime * 15 + longitude ) * rad;
    dHourAngle = dLocalMeanSiderealTime - dRightAscension;
    latitude_InRadians = latitude * rad;
    dCos_Latitude = std::cos( latitude_InRadians );
    dSin_Latitude = std::sin( latitude_InRadians );
    dCos_HourAngle= std::cos( dHourAngle );
    zenithAngle = std::acos( dCos_Latitude * dCos_HourAngle * std::cos( dDeclination )
				  + std::sin( dDeclination ) * dSin_Latitude ) ;
    dY = - std::sin( dHourAngle );
    dX = std::tan( dDeclination ) * dCos_Latitude - dSin_Latitude * dCos_HourAngle ;
    azimuthAngle = std::atan2( dY, dX );
    if ( azimuthAngle < 0.0 )  azimuthAngle = azimuthAngle + twopi;
    // Parallax Correction
    dParallax = ( dEarthMeanRadius / dAstronomicalUnit ) * std::sin( zenithAngle );
    zenithAngle = zenithAngle  + dParallax;
  }

#ifdef USE_VECMATH
  // Convert to vector coordinates
  sphericalToVector();
#endif
}

} // End of namespace


template <class T>
std::ostream& operator<<(std::ostream& o, const PSM::Sunpos<T>& s1) {
  return o
  <<"Longitude                            > "<<s1.longitude<<" Degrees"<<std::endl
  <<"Latitude                             > "<<s1.latitude <<" Degrees"<<std::endl
  <<"Timezone                             > "<<s1.localTime<<" hours"<<std::endl
  <<"Day                                  > "<<s1.day<<std::endl
  <<"Month                                > "<<s1.month <<std::endl
  <<"Year                                 > "<<s1.year<<std::endl
  <<std::endl
  <<"Local Time                           > "<<s1.hours + s1.localTime<<":"
  <<s1.minutes<<":"<<s1.seconds <<std::endl
  <<"Zenith Angle                         > "<<s1.zenithAngle/M_PI*180<<" Degrees"<<std::endl
  <<"Azimuth Angle                        > "<<s1.azimuthAngle/M_PI*180<<" Degrees"<<std::endl;
}


#endif  // SUNPOS_H

