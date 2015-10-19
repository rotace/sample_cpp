/**
 * @file Calc.cpp
 * @brief ニュートン・ラプソン法計算クラス
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "Calc.hpp"
#include <math.h>
#include <assert.h>

#include <iostream>
#include <stdio.h>
using namespace std;
 

Calc::Calc()
  :InitX(1.0),
   InitY(1.0),
   Initeps(1.0e-7),
   askInit(false)
{}

Calc::~Calc(){}

/** 1元1変数評価関数の一階微分
 * @param x 入力値ｘ
 * @param df 関数ｆの微分値
 */
void Calc::DFunction(double x,double *df)
{
  double f0,f1;
  double x0,x1;
  x0 = x;
  x1 = x + Initeps;
  
  Function( x0, &f0);
  Function( x1, &f1);
  *df = (f1 - f0) / Initeps;
}

/** 2元2変数評価関数の1階微分
 * @param x 入力値ｘ
 * @param y 入力値ｙ
 * @param df1dx 関数ｆ１のｘ方向微分値
 * @param df1dy 関数ｆ１のｙ方向微分値
 * @param df2dx 関数ｆ２のｘ方向微分値
 * @param df2dy 関数ｆ２のｙ方向微分値
 */
void Calc::DDoubleFunction(double x,double y,double *df1dx,double *df1dy, double *df2dx, double *df2dy)
{
  double f10,f20,f11dx,f21dx,f11dy,f21dy;
  double x0,x1,y0,y1;
  x0 = x, x1 = x + Initeps;
  y0 = y, y1 = y + Initeps;

  DoubleFunction( x0, y0, &f10, &f20);
  DoubleFunction( x1, y0, &f11dx, &f21dx);
  DoubleFunction( x0, y1, &f11dy, &f21dy);
  *df1dx = (f11dx - f10) / Initeps; 
  *df1dy = (f11dy - f10) / Initeps; 
  *df2dx = (f21dx - f20) / Initeps; 
  *df2dy = (f21dy - f20) / Initeps; 
  
}

/** １元１変数評価関数を０に収束させるニュートン法
 * @param *x 解
 */
void Calc::Newton(double *x)
{
  double x0,x1;
  double f,df;

  // set Initial X
  if (askInit)
    {
      cout << "Input value Init X = ? " << endl;
      cin  >> x1;
    }else{
    x1 = InitX;
  }

  // Newton
  int itr=0;
  x0 = x1 -1.0;
  while( fabs(x1-x0) > Initeps ){
    x0 = x1;
    Function( x0, &f  );
    DFunction( x0, &df );
    assert( fabs(df) > Initeps);
    x1 = x0 - f/df;
    itr++;
    assert( itr < 30);
  }
  *x = x1;
}

/** ２元２変数評価関数を０に収束させるニュートン法
 * @param *x ｘの解
 * @param *y ｙの解
 */
void Calc::DoubleNewton(double *x,double *y)
{
  double x0,x1,y0,y1;
  double f1,f2,df1x,df1y,df2x,df2y;
  double det;

  // set Initial X and Y
  if (askInit)
    {
      cout << "Input value Init X = ? " << endl;
      cin  >> x1;
      cout << "Input value Init Y = ? " << endl;
      cin  >> y1;
    }else{
    x1 = InitX;
    y1 = InitY;
  }

  // Newton
  int itr=0;
  x0 = x1 -1.0 ,y0 = y1 -1.0;
  while( fabs(x1-x0)+fabs(y1-y0) > Initeps ){
    x0 = x1;
    y0 = y1;
    DoubleFunction(x0,y0,&f1,&f2);
    DDoubleFunction(x0,y0,&df1x,&df1y,&df2x,&df2y);
    det = df1x*df2y - df1y*df2x;
    assert( fabs(det) > Initeps);
    x1 = x0 - ( df2y*f1 - df1y*f2)/det;
    y1 = y0 - (-df1y*f1 + df1x*f2)/det;
    itr++;
    assert(itr < 30);
  }
  *x = x1;
  *y = y1;
}


