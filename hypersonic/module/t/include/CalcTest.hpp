/**
 * @file CalcTest.hpp
 * @brief Calcクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef CALCTEST_H
#define CALCTEST_H

#include "CppUTest/CommandLineTestRunner.h"

#include "Calc.hpp"


#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;


class testCalc : public Calc
{
public:
  testCalc(){}
  virtual ~testCalc(){}
  void Function(double x, double *out)
  {
    *out = x*x + 4*x + 4;
  };
  void DoubleFunction(double x,double y,double *out1,double *out2)
  {
    *out1 = x*x+y*y-1;
    *out2 = x*x*x-y;
  };
};


// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(calcTestGroup) {
  testCalc ThetestCalc;
  const static double eps = 10e-7;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(calcTestGroup, NewtonTest) {

  cout << "###calcTestGroup NewtonTest ###" << endl;

  double initx,inity,initeps;
  double ansx, ansy;
  initx=1.0;
  inity=1.0;
  initeps=1.0e-7;
  ThetestCalc.setInitX(initx);
  ThetestCalc.setInitY(inity);
  ThetestCalc.seteps(initeps);
  // ThetestCalc.setAskOn();

  // DFunction Test
  // df = 2x + 4
  double df;
  ThetestCalc.Calc::DFunction(1.0,&df);
  DOUBLES_EQUAL(df, 6.0, eps);

  // Newton Test
  ThetestCalc.Calc::Newton(&ansx);
  DOUBLES_EQUAL(ansx, -2.0, eps);

  // DDoubleFunction Test
  // df1x = 2x
  // df1y = 2y
  // df2x = 3*x*x
  // df2y = -1
  double df1x,df1y,df2x,df2y;
  ThetestCalc.Calc::DDoubleFunction(1.0,2.0,&df1x,&df1y,&df2x,&df2y);
  DOUBLES_EQUAL(df1x,  2.0, eps);
  DOUBLES_EQUAL(df1y,  4.0, eps);
  DOUBLES_EQUAL(df2x,  3.0, eps);
  DOUBLES_EQUAL(df2y, -1.0, eps);

  // DoubleNewton Test
  ThetestCalc.Calc::DoubleNewton(&ansx, &ansy);
  DOUBLES_EQUAL(ansx, 0.826031358, eps);
  DOUBLES_EQUAL(ansy, 0.563624162, eps);
}



#endif
