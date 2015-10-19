/**
 * @file HeatRatio.hpp
 * @brief よどみ点加熱率クラスヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef HEATRATIO_HPP
#define HEATRATIO_HPP

#include "Calc.hpp"
#include "Data.hpp"
#include "AirModel.hpp"
#include "AirBehindShock.hpp"
#include "BoundaryEquation.hpp"
#include "Output.hpp"

class Calc;
class Data;
class AirModel;
class AirBehindShock;

class HeatRatio : public Calc
{
private:
  double qw;
  double alts;			// bisection range
  double alte;			// bisection range
  Data *TheData;
  AirModel *TheAM;
  AirBehindShock *TheABS;
  BoundaryEquation *TheBE;
  
public:
  HeatRatio();
  virtual ~HeatRatio();

  void setData(Data *inData){TheData = inData;};
  void setAM(AirModel *inAM){TheAM = inAM;};
  void setAB(AirBehindShock *inABS){TheABS = inABS;};
  void setBE(BoundaryEquation *inBE){TheBE = inBE;};

  void Function(double in, double *out);
  void DoubleFunction(double in1, double in2,double *out1 ,double *out2){};
  double getqw(){return qw;};
  void Calc();
  void Calcall();
  void Plotqw();
  double altOfMaxqw();

};

#endif
