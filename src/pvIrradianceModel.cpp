

// ## GLOBAL IRRADIANCE ABSORBED BY THE TILTED PV MODULE ##
/*
The output power of the photovoltaic system depends directly on the amount of tilted global
irradiance absorbed by the surface which is a function of the incident tilted global irradiance,
air mass and angle of incidence.

 De Soto W, Klein S, Beckman W (2006) Improvement and validation of a model for photovoltaic array performance. 
 Sol Energy 80(1):78–88

We can approximate the amount of the irradiance absorbed by the photovoltaic module by (as shown in [20]):
*/

#include <cmath>
#include "tSurfaceIrradiance.h"

//Amount of irradiance absorbed by the PV module
double gAbsorbed(double gDirectTilted, 
                 double gDiffuseTilted,
                 double gGlobalTilted,
                 double alfa /*Transmittance absorption product*/){
  return( gDirectTilted*alfa + gDiffuseTilted*alfa + gGlobalTilted*alfa ); //TODO: check if it is correct
};

//The transmittance-absorption product(ta) is based on Snell’s law, Fresnel’s law and Boughers’s law
//K = glazingExtinctionCoeff = 0.25m, L = glazingThickness = 2mm
double ta(double glazingExtinctionCoeff,
          double glazingThickness,
          double refractionAngle,
          double incidenceAngle){
  double e = 2.7182; //Euler constant
  double firstTerm = pow(e, -( glazingExtinctionCoeff*glazingThickness / cos(refractionAngle) ));
  double secondTerm = ( 
    1 - ( 0.5 * (( pow(sin(refractionAngle-incidenceAngle), 2) / 
                   pow(sin(refractionAngle+incidenceAngle), 2) ) +
                 ( pow(tan(refractionAngle-incidenceAngle), 2) /
                   pow(tan(refractionAngle+incidenceAngle), 2) )) )
  );
  return( firstTerm*secondTerm );
};

//The Incidence Angle is computed for direct, diffuse and reflected radiation
//Direct Irradiance incidence angle
double gdia(double tagd, /*Transmittance(t) absorption(a) Direct(d) Irradiance(g) */
            double sunAzimuth,
            double surfaceAzimuth,
            double tiltAngle){
  return( acos( cos(tagd)*cos(sunAzimuth-surfaceAzimuth)*sin(tiltAngle) +
                sin(tagd)*cos(tiltAngle) ) );
};

//Diffuse Irradiance Incidence Angle (Isotropic Sky)
double gdfia(double tiltAngle){
  return( 59.7 - 0.1388*tiltAngle + 0.001497*pow(tiltAngle, 2) );
};

//Reflected Irradiance Incidence Angle (Isotropic Sky)
double gria(double tiltAngle){
  return( 90 - 0.5788*tiltAngle + 0.002693*pow(tiltAngle, 2) );
};

//Refraction Angle for Direct, Diffuse and Reflected Irradiance
double ra(double airRefractiveIndex, /*n1*/
          double glassRefractiveIndex, /*n2*/ 
          double reflectionAngle){
  return( asin( glassRefractiveIndex*sin(reflectionAngle) / airRefractiveIndex ) );
};


// ## PHOTOVOLTAIC TEMPERATURE MODEL ##
/*
Photovoltaic module efficiency and performance depends, besides other effects, on the temperature of the module/cell. 
The photovoltaic cell temperature changes during operation either due to changes in the ambient temperature (Tamb)
or due to the radiation absorbed by the PV module.

  Nordmann T, Clavadetscher L (2003) Understanding temperature effects on PV system performance. 
  In: Proceedings of 3rd world conference on photovoltaic energy conversion, vol 3, Osaka, Japan, 11–18 May 2003, pp 2243–2246
  
  Pearsall N (2017) Introduction to photovoltaic system performance. 
  In: The performance of photovoltaic systems modelling, measurement and assessment. Elesvier, London, pp 6–15

The PV module temperature (TModule) can be calculated by using the ambient temperature for any type of PV array mounting:
  
  Skoplaki E, Playvos GA (2008) 
  A simple correlation for the operating temperature of the photovoltaic modules of arbitrary mounting.
  Sol Energy Mater Sol Cells 92(11):1393–1402
*/

double tModule(double tAmb,
               double irradiance, /*Gt*/
               double windSpeed){
  double mountingCoeff = 1; //Free standing
  return( tAmb + mountingCoeff * ( 0.32*irradiance / (8.91 + 2 * ( windSpeed/0.67 )) ) );
};
