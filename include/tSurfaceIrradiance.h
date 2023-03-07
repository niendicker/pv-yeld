#ifndef T_SURFACE_IRRADIANCE
#define T_SURFACE_IRRADIANCE

// ## Global irradiance on the tilted PV module ##

/*
We can compute the amount of global irradiance incident on the tilted PV module
using the Hay & Davies model:
 
## Duffie JA, Beckman WA (2013) Solar engineering of thermal processes. Wiley, Toronto.

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

typedef struct{
  double gGlobalH; /*Global Horizontal Irradiance*/
  double gDiffuseH; /*Diffuse Horizontal Irradiance*/
  double albedoCoeff; /*Ground albedo coefficient*/
} simuData;

typedef struct{
  double sunZenith, sunAzimuth;
} geoData; //Geospatial data

typedef struct{
  double surfaceTilt, surfaceAzimuth;
  double latitude, longitude;
  double surfaceArea;
  double efficiency;
  double glassThickness /*2mm*/, glassRi; /*Refraction angle for the PV module cover*/
} moduleData;

typedef struct{
  int year, month, day, hour, minute;
  simuData sData;
  geoData gData;
  moduleData mData;
} pointSimuData;

//Global irradiance for isotropic sky and tilted surface
double tiltedIsotropicG(double Gdt, /*Tilted Direct Irradiance*/
                        double Gdft, /*Tilted Diffuse Irradiance*/ 
                        double Grt /*Tilted Reflected Irradiance*/);

//Global irradiance for anisotropic sky and tilted surface
double tiltedAnisotropicG(double Gdt, /*Tilted Direct Irradiance*/ 
                          double GdtAniso, /*Tilted Diffuse Irradiance Anisotropic sky*/ 
                          double Grt /*Tilted Reflected Irradiance*/);

//Direct(d) Irradiance(g) on Tilted(t) surface
double gdt(double sunZenith, double sunAzimuth, double surfaceTilt, double surfaceAzimuth, double gDirect);

//Diffuse(df) Irradiance(g) on Tilted(t) surface
double gdftIso(double surfaceTilt, double gDiffuseHorizontal);

//Reflected Irradiance from the Ground(gr)
double ggrt(double surfaceTilt, double albedoCoeff, double gGlobalHorizontal);


//Interface
inline double degreeToRad(double d){ return(d*M_PI/180.0); };

//double directIrradiance();
//double diffuseIrradiance();
//double reflectedIrradiance();

#endif