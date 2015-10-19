/**
 * @file BoundaryEquation.cpp
 * @brief 境界層方程式を解くプログラム
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "BoundaryEquation.hpp"

#include "math.h"
#include <iostream>
using namespace std;


BoundaryEquation::BoundaryEquation()
  :fdd0(0.0),
   gd0(0.0),
   f0(0.0),
   plot(false)
{}
BoundaryEquation::~BoundaryEquation(){}

void  BoundaryEquation::DoubleFunction(double in1,double in2,double *out1,double *out2)
{
  Output TheOut;
  // pre-process-writing
  if ( plot )
    {
      TheOut.setSkipItrNum(1000);
      TheOut.setFileName( "BE.csv" );
      TheOut.startData();
    }
  
  // BoundaryCondition
  double fd0,fdinf;
  fd0   = 0.0;
  fdinf = 1.0;

  double g0,ginf,Pr;
  g0    = 0.2;
  ginf = 1.0;
  Pr    = 0.7;

  // Runge-Kutta
  double e,de;
  e  = 0;
  de = 1.0e-4;
  
  double f,fd,fdd;
  double d1fdd,d1fd,d1f;
  double d2fdd,d2fd,d2f;
  double d3fdd,d3fd,d3f;
  double d4fdd,d4fd,d4f;
  f   = f0;
  fd  = fd0;
  fdd = in1;

  double g,gd;
  double d1gd,d1g;
  double d2gd,d2g;
  double d3gd,d3g;
  double d4gd,d4g;
  g   = g0;
  gd  = in2;

  while (e < 6){

    if ( plot )
      {
	TheOut.printData(e,f,fd,fdd,g,gd);
	TheOut.writeData(e,f,fd,fdd,g,gd);
      }
    
    // Step1
    d1fdd = de * -(f*fdd +0.5*(1-fd*fd));
    d1fd  = de * fdd;
    d1f   = de * fd;
    d1gd  = de * (-Pr*f*gd);
    d1g   = de * gd;

    // Step2
    d2fdd = de * -((f+0.5*d1f)*(fdd+0.5*d1fdd) +0.5*(1-(fd+0.5*d1fd)*(fd+0.5*d1fd)));
    d2fd  = de * (fdd + 0.5*d1fdd);
    d2f   = de * (fd  + 0.5*d1fdd);
    d2gd  = de * (-Pr*(f+0.5*d1f)*(gd+0.5*d1gd));
    d2g   = de * (gd+0.5*d1gd);
    
    // Step3
    d3fdd = de * -((f+0.5*d2f)*(fdd+0.5*d2fdd) +0.5*(1-(fd+0.5*d2fd)*(fd+0.5*d2fd)));
    d3fd  = de * (fdd + 0.5*d2fdd);
    d3f   = de * (fd  + 0.5*d2fdd);
    d3gd  = de * (-Pr*(f+0.5*d2f)*(gd+0.5*d2gd));
    d3g   = de * (gd+0.5*d2gd);

    // Step4
    d4fdd = de * -((f + d3f)*(fdd + d3fdd) +0.5*(1-(fd + d3fd)*(fd + d3fd)));
    d4fd  = de * (fdd + d3fdd);
    d4f   = de * (fd  + d3fdd);
    d4gd  = de * (-Pr*(f + d3f)*(gd + d3gd));
    d4g   = de * (gd + d3gd);

    // Sum
    fdd  += ( d1fdd + 2*d2fdd + 2*d3fdd + d4fdd )/6.0;
    fd   += ( d1fd  + 2*d2fd  + 2*d3fd  + d4fd  )/6.0;
    f    += ( d1f   + 2*d2f   + 2*d3f   + d4f   )/6.0;
    gd   += ( d1gd  + 2*d2gd  + 2*d3gd  + d4gd  )/6.0;
    g    += ( d1g   + 2*d2g   + 2*d3g   + d4g   )/6.0;
    e    += de;

  }

  // post-process-writing
  if ( plot )
    {
      TheOut.endData();
    }

  *out1 = fd - fdinf;
  *out2 = g - ginf;
  
}
void  BoundaryEquation::Calc()
{
  DoubleNewton(&fdd0,&gd0);
}
void  BoundaryEquation::PlotBE()
{
  double dummy1,dummy2;
  plot = true;
  DoubleFunction(fdd0,gd0,&dummy1,&dummy2);
  plot = false;
}
