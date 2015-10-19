/**
 * @file ABTest.hpp
 * @brief AirBehindShockクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef ABTEST_H
#define ABTEST_H

#include "CppUTest/CommandLineTestRunner.h"

#include "Data.hpp"
#include "AirModel.hpp"
#include "AirBehindShock.hpp"
#include "Output.hpp"



#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;


// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(ABTestGroup){
  Data TheABData;
  AirModel TheABAM;
  AirBehindShock TheAB;

  const static double eps = 10e-4;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(ABTestGroup, ABTest) {

  cout << "###ABTestGroup ABTest ###" << endl;
  TheABAM.setData(&TheABData);
  TheAB.setAM(&TheABAM);
  TheABAM.Calc();

  // funcs test
  TheAB.hs(5000,40000);
  DOUBLES_EQUAL(TheAB.getfs(),5.84827 , eps);
  DOUBLES_EQUAL(TheAB.getalphas(),0.77 , eps);
  DOUBLES_EQUAL(TheAB.geth2s(),3.425390549177e7 , eps);

  // Ts bisection method test
  DOUBLES_EQUAL(TheAB.Ts(4e7,40000) ,5397.10570 , eps);

  
  // cout  << "Ts="
  // 	<< fixed
  // 	<< setprecision(5)
  // 	<< TheAB.Ts(4e7,40000) << endl;

  
  // // Plot 単調増加を確認
  // double T=0.0, dT=100;
  // Output TheOut;
  // TheOut.setSkipItrNum(1);
  // TheOut.setFileName("ABTest.csv");
  // TheOut.startData();
  //
  // while( T <= 12000.0 ){
  //   TheAB.hs(T,101401);
  //   TheOut.printData(T,TheAB.geth2s());
  //   TheOut.writeData(T,TheAB.geth2s());
  //   T += dT;
  // }
  // TheOut.endData();


  // // function テスト
  // double diff;
  // TheAB.Function(0.001,&diff);
  // cout << "diff=" << diff << endl;
  // TheAB.Function(0.01,&diff);
  // cout << "diff=" << diff << endl;
  // TheAB.Function(0.1,&diff);
  // cout << "diff=" << diff << endl;

  
  // // Newton法　テスト
  // double ratio;
  // TheAB.Calc::Newton(&ratio);
  // cout << "ratio=" << ratio << endl;


  TheABData.setRratio(2.0);
  TheABData.setR(0.5);
  TheABData.setThetaInit(30);
  TheABData.setMass(3000);
  TheABData.setgd0();

  // // Plot 全高度で収束を確認
  // double alt=0.0, dalt=10000;
  // Output TheOut;
  // TheOut.setSkipItrNum(1);
  // TheOut.setFileName("ABTest.csv");
  // TheOut.startData();
  
  // while( alt <= 120e3 ){
  //   TheABData.setAltitude(alt);
  //   TheABData.Calc();
  //   TheABAM.Calc();
  //   TheAB.Calc();
  //   TheOut.printData(alt,TheAB.getpe()-TheABAM.getpinf());
  //   TheOut.writeData(alt,TheAB.getpe()-TheABAM.getpinf());
  //   alt += dalt;
  // }
  // TheOut.endData();


  
}



#endif
