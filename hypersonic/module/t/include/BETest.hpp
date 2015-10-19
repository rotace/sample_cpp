/**
 * @file BETest.hpp
 * @brief BoundaryEquationクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef _BETEST_H_
#define _BETEST_H_


#include "CppUTest/CommandLineTestRunner.h"

#include "Calc.hpp"
#include "BoundaryEquation.hpp"

#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;



// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(BETestGroup) {
  BoundaryEquation TheBE;
  const static double eps = 10e-7;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(BETestGroup, BETest) {

  cout << "###BETestGroup BETest ###" << endl;

  double initx,inity,initeps;
  // double ansx, ansy;
  initx=1.0;
  inity=1.0;
  initeps=1.0e-7;
  TheBE.setInitX(initx);
  TheBE.setInitY(inity);
  TheBE.seteps(initeps);
  // ThetestCalc.setAskOn();

  // // DoubleFunction Test
  // double out1,out2;
  // TheBE.DoubleFunction(0.927,0.376397,&out1,&out2);
  // cout << out1 << endl
  //      << out2 << endl;
  
  // DoubleNewton Test
  // TheBE.Calc::DoubleNewton(&ansx, &ansy);
  // cout << ansx << endl
  //      << ansy << endl;
  
  TheBE.Calc();
  // cout << TheBE.getfdd0() << endl;
  // cout << TheBE.getgd0() << endl;
  DOUBLES_EQUAL(TheBE.getfdd0(), 0.927661, eps);
  DOUBLES_EQUAL(TheBE.getgd0(), 0.37638, eps);

  // TheBE.PlotBE();
}


#endif /* _BETEST_H_ */
