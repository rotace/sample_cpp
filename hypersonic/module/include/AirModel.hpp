/**
 * @file AirModel.hpp
 * @brief 大気落下速度分布モデル・大気モデルクラスヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef AIRMODEL_HPP
#define AIRMODEL_HPP

#include <math.h>		// exp,pow
#include <iostream>		// cout...
#include <stdlib.h>		// abort();


#include "Data.hpp"
#include "Output.hpp"

class AirModel
{
private:
  double rhoinf;
  double vinf;
  double Tinf;
  double pinf;
  double hinf;
  double rhog;
  double v0;
  Data *TheData;
  
public:
  AirModel();
  virtual ~AirModel();

  void setData(Data *inData){TheData = inData;};
  void setrhog(double x){rhog = x;};
  void setv0(double x){v0 = x;};
  void Calc();
  void Plotvinf();

  double vel(double alt);
  double dvel(double alt);
  double ddvel(double alt);
  double alt(double vel);
  double altOfmaxAccel();
    
  double getrhoinf(){return rhoinf ;};
  double getvinf(){return vinf ;};
  double getTinf(){return Tinf ;};
  double getpinf(){return pinf ;};
  double gethinf(){return hinf ;};

  
};

#endif
