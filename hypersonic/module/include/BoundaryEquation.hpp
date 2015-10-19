/**
 * @file BoundaryEquation.hpp
 * @brief 境界層方程式を解くプログラムヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef BOUNDARYEQUATION_HPP
#define BOUNDARYEQUATION_HPP

#include "Calc.hpp"
#include "Output.hpp"


class BoundaryEquation :public Calc
{
private:
  double fdd0;
  double gd0;
  double f0;
  bool plot;
  
public:
  BoundaryEquation();
  virtual ~BoundaryEquation();

  void Function(double in, double *out){};
  void DoubleFunction(double in1,double in2,double *out1,double *out2);
  double getgd0(){return gd0;};
  double getfdd0(){return fdd0;};
  void Calc();
  void PlotBE();
  void setf0(double inf0){f0 = inf0;};
  
};

#endif
