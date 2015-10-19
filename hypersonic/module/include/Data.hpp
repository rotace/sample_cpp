/**
 * @file Data.hpp
 * @brief カプセル形状諸元データヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef DATA_HPP
#define DATA_HPP

#include <math.h>
#include <iostream>
using namespace std;


class Data
{
private:
  double Rratio;
  double R;
  double thetaInit;
  double mass;			// [kg]
  double Cd;
  double S0;
  double Z;
  double K;
  double altitude;
  double gd0;
  
public:
  Data();
  virtual ~Data();

  void setAltitude(double x);
  void setRratio(double x);
  void setR(double x);
  void setThetaInit(double x);
  void setMass(double x);
  void setZ(double x);
  void setgd0();
  void Calc();
  
  double getAltitude(){return altitude;};
  double getR(){return R;};
  double getMass(){return mass;};
  double getCd(){return Cd;};
  double getS0(){return S0;};
  double getZ(){return Z;};
  double getK(){return K;};
  double getgd0(){return gd0;};
  
};

#endif
