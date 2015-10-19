/**
 * @file HRTest.hpp
 * @brief HeatRatioクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef HRTEST_H
#define HRTEST_H

#include "CppUTest/CommandLineTestRunner.h"

#include "Data.hpp"
#include "AirModel.hpp"
#include "AirBehindShock.hpp"
#include "HeatRatio.hpp"
#include "BoundaryEquation.hpp"
#include "Output.hpp"

#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;


// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(HRTestGroup) {
  Data TheHRData;
  AirModel TheHRAM;
  AirBehindShock TheHRAB;
  BoundaryEquation TheHRBE;
  HeatRatio TheHR;

  const static double eps = 10e-4;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(HRTestGroup, HRTest) {

  TheHRAM.setData(&TheHRData);
  TheHRAB.setAM(&TheHRAM);
  TheHR.setData(&TheHRData);
  TheHR.setAM(&TheHRAM);
  TheHR.setAB(&TheHRAB);
  TheHR.setBE(&TheHRBE);
  cout << "###HRTestGroup HRTest ###" << endl;

  TheHRData.setRratio(2.0);
  TheHRData.setR(0.5);
  TheHRData.setThetaInit(30);
  TheHRData.setMass(3000);
  TheHRBE.setf0(-0.2);

  TheHRData.setAltitude(10000);
  TheHRAB.Calc::setInitX(0.1);
  TheHRData.Calc();
  TheHRAM.Calc();
  TheHRAB.Calc();
  TheHRBE.Calc();
  TheHR.Calc();
  // cout << "qw=" <<  TheHR.getqw() << endl;
  DOUBLES_EQUAL(TheHR.getqw(),1921170.38685 , eps);

  // altitude at max of qw
  // cout << TheHR.altOfMaxqw() << endl;

  
  // // Plot
  // double alt=0.0, dalt=1000;
  // Output TheOut;
  // TheOut.setSkipItrNum(1);
  // TheOut.setFileName("HRTest.csv");
  // TheOut.startData();
  // double rho1,u1,p1,T1,h1;
  
  // while( alt <= 120000.0 ){
  //   TheHRData.setAltitude(alt);
  //   TheHRData.Calc();
  //   TheHRAM.Calc();
  //   rho1 = TheHRAM.getrhoinf();
  //   u1 = TheHRAM.getvinf();
  //   p1 = TheHRAM.getpinf();
  //   T1 = TheHRAM.getTinf();
  //   h1 = TheHRAM.gethinf();
  //   TheOut.printData(alt,rho1,u1,p1,T1,h1);
  //   TheOut.writeData(alt,rho1,u1,p1,T1,h1);
  //   alt += dalt;
  // }
  // TheOut.endData();

  
  
  TheHR.Plotqw();
  
  // TheHR.setData(&TheHRData);
  // TheHR.Calc();
  
  // DOUBLES_EQUAL(TheHR.getrhoinf(),1.205 , eps);
  // DOUBLES_EQUAL(TheHR.getvinf(),0.0 , eps);
  // DOUBLES_EQUAL(TheHR.getTinf(),288.14 , eps);
  // DOUBLES_EQUAL(TheHR.getpinf(),101.4009349 , eps);
  // DOUBLES_EQUAL(TheHR.gethinf(),8384.58586 , eps);

 
  // TheHRData.setZ(1.2e-4);
  // TheHRData.setMass(3665);
  // TheHRData.setRratio(0.0);
  // TheHRData.setR(0.5);
  // TheHRData.setThetaInit(30);
  // TheHR.setrhog(1.2);
  // TheHR.setv0(1.2e4);
  // TheHR.Calc();
  // TheHR.Plotvinf();

}



#endif
