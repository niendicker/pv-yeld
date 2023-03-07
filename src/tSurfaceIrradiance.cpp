
// ## Global irradiance on the tilted PV module ##

/*
We can compute the amount of global irradiance incident on the tilted PV module
using the Hay & Davies model:
 - Duffie JA, Beckman WA (2013) Solar engineering of thermal processes. Wiley, Toronto.
The meterological data usually includes the global irradiance on a horizontal surface.
This is the sum of direct and the diffuse irradiance. 
The idea is to convert the global irradiance on the horizontal surface into 
tilted irradiance values based on the tilt of the PV panel. We present the irradiance
model for an isotropic and an anisotropic sky. 
The isotropic sky model assumes a uniform distribution of diffuse irradiance from the sky. 
For an isotropic sky model, global irradiance on the tilted surface is defined by the equation below:
 g represents global, 
 d represents direct, 
 df represents diffuse, 
 r represents reflected, 
 t represents tilted, 
 gr represents ground.

 https://link.springer.com/article/10.1007/s40565-018-0393-5#Sec11
*/

#include <cmath>

#include "tSurfaceIrradiance.h"

//Global irradiance for isotropic sky and tilted surface
double tiltedIsotropicG(double Gdt, /*Tilted Direct Irradiance*/
                        double Gdft, /*Tilted Diffuse Irradiance*/ 
                        double Grt /*Tilted Reflected Irradiance*/){
  return(Gdt + Gdft + Grt);
};

//Global irradiance for anisotropic sky and tilted surface
double tiltedAnisotropicG(double Gdt, /*Tilted Direct Irradiance*/ 
                          double GdtAniso, /*Tilted Diffuse Irradiance Anisotropic sky*/ 
                          double Grt /*Tilted Reflected Irradiance*/){
  return(Gdt + GdtAniso + Grt);
};

//Direct(d) Irradiance(g) on Tilted(t) surface
//CALCULATING SOLAR RADIATION FOR INCLINED SURFACES: PRACTICAL APPROACHES John E Hay (1) and (2)
double gdt(double sunZenith, double sunAzimuth, double surfaceTilt, double surfaceAzimuth, double gDirect){
  //Math functions need angle in radians
  sunZenith = degreeToRad(sunZenith); 
  sunAzimuth = degreeToRad(sunAzimuth);
  surfaceTilt = degreeToRad(surfaceTilt);
  surfaceAzimuth = degreeToRad(surfaceAzimuth);

  //double cosIA = cos(sunZenith)*cos(surfaceTilt) + 
  //               sin(sunZenith)*sin(surfaceTilt) + 
  //               cos(sunAzimuth-surfaceAzimuth);
  double cosIA = cos(sunZenith) * cos(surfaceTilt) + 
                 sin(sunZenith) * sin(surfaceTilt) * cos(sunAzimuth-surfaceAzimuth);

  //double Rd = cosIA / cos(sunZenith); //Geometric factor between incidence angle and sun zenith angle
  
  return(cosIA * gDirect);
};

//Diffuse(df) Irradiance(g) on Tilted(t) surface for Isotropic Sky
double gdftIso(double surfaceTilt, double gDiffuseHorizontal ){
  surfaceTilt = degreeToRad(surfaceTilt); //cos() function need radians
  double Rd = 0.5 * (1+cos(surfaceTilt)); //Geometric Factor(R) for diffuse(d) Irradiance
  return(Rd * gDiffuseHorizontal);
};

//Reflected Irradiance from the Ground(gr)
double ggrt(double surfaceTilt, double albedoCoeff, double gGlobalHorizontal){
  surfaceTilt = degreeToRad(surfaceTilt); // cos() function need radians
  double Rgr = 0.5 * (1-cos(surfaceTilt)); //Geometric factor(R) for Reflected Irradiance from the Ground(gr)
  return( Rgr*albedoCoeff*gGlobalHorizontal );
};


//## Interface
//double directIrradiance(){
//  //Zenith = 90 - sunElevation
//  double g = gdt( (90-25.31), -25.43, 33, 0, 821);
//  return(g);  
//};
//
//double diffuseIrradiance(){
//  double g = gdftIso(33, 88);
//  return(g);
//};
//
//double reflectedIrradiance(){
//  double g = ggrt(33, 0.33, 438) ;
//  return(g);
//};

////Geometric factor for anisotropic sky
//double rdfAniso(double anisoIndex,
//                double geometricFactor, /*Rd*/
//                double surfaceTilt){
//  return( 0.5 * (1-anisoIndex) * (1+cos(surfaceTilt)) + anisoIndex*geometricFactor );
//};
//
////Anisotropic(a) Index(i) is a function of transmittance of the atmosphere for the beam radiation
//double ai(double gDirectHorizontal,
//          double sunZenith,
//          double gExt /*??*/){
//  return( gDirectHorizontal / (gExt*cos(sunZenith)) );
//};
