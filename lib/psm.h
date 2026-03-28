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

#ifndef PACKAGE_FOR_SOLAR_MODELLING_H
#define PACKAGE_FOR_SOLAR_MODELLING_H

#ifndef PSM
# define PSM modelling
#endif

#define USE_VECMATH

#ifdef USE_VECMATH
# include <vecmath.h>
#endif

#include <psm_sunpos.h>
#include <psm_spectral.h>
#ifdef USE_VECMATH
# include <psm_spatial.h>
#endif
#include <psm_stack.h>

#endif /* SOLAR_H */
