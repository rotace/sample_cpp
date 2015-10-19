/**
 * @file Calc.hpp
 * @brief ニュートン・ラプソン法計算クラスヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef CALC_HPP
#define CALC_HPP

class Calc
{
private:
  double InitX;
  double InitY;
  double Initeps;
  bool askInit;
  
public:
  Calc();
  virtual ~Calc();

  virtual void Function(double in,double *out) = 0;
  void DFunction(double in,double *out);
  virtual void DoubleFunction(double in1,double in2,double *out1,double *out2) = 0;
  void DDoubleFunction(double in1,double in2,double *out1,double *out2,double *out3,double *out4);
  void Newton(double *x);
  void DoubleNewton(double *x,double *y);
  void setInitX(double x){InitX = x;};
  void setInitY(double y){InitY = y;};
  void seteps(double eps){Initeps =eps;};
  void setAskOn(){askInit = true;};
  void setAskOff(){askInit = false;};
  double getInitX(){return InitX;};
  double getInitY(){return InitY;};
  double geteps(){return Initeps;};
  
};

#endif
