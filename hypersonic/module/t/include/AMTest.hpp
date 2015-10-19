/**
 * @file AMTest.hpp
 * @brief AirModelクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef AMTEST_H
#define AMTEST_H

#include "CppUTest/CommandLineTestRunner.h"

#include "AirModel.hpp"
#include "Data.hpp"
#include "Output.hpp"


#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;


// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(AMTestGroup) {
  AirModel TheAM;
  Data TheAMData;
  const static double eps = 10e-4;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(AMTestGroup, AMTest) {

  cout << "###AMTestGroup AMTest ###" << endl;
  TheAM.setData(&TheAMData);
  TheAM.Calc();
  
  DOUBLES_EQUAL(TheAM.getrhoinf(),1.205 , eps);
  DOUBLES_EQUAL(TheAM.getvinf(),0.0 , eps);
  DOUBLES_EQUAL(TheAM.getTinf(),288.14 , eps);
  DOUBLES_EQUAL(TheAM.getpinf(),101400.9309 , eps);
  DOUBLES_EQUAL(TheAM.gethinf(),8384.58586 , eps);

 
  // TheAMData.setZ(1.2e-4);
  // TheAMData.setMass(3665);
  // TheAMData.setRratio(0.0);
  // TheAMData.setR(0.5);
  // TheAMData.setThetaInit(30);
  // TheAM.setrhog(1.2);
  // TheAM.setv0(1.2e4);
  // TheAM.Calc();
  // TheAM.Plotvinf();

  
  // TheAMData.setThetaInit(60);
  // TheAMData.Calc();
  // TheAM.Calc();

  // TheAM.Plotvinf();

  
  // // Plot alt ,vinf ,dv/dt
  // double alt=0.0, dalt=1000,vel,dvel;
  // Output TheOut;
  // TheOut.setSkipItrNum(1);
  // TheOut.setFileName("AMTest.csv");
  // TheOut.startData();
  
  // while( alt <= 120000.0 ){
  //   TheAMData.setAltitude(alt);
  //   TheAMData.Calc();
  //   TheAM.Calc();
  //   vel = TheAM.getvinf();
  //   dvel = TheAM.dvel(alt);
  //   TheOut.printData(alt,vel,dvel);
  //   TheOut.writeData(alt,vel,dvel);
  //   alt += dalt;
  // }
  // TheOut.endData();

  // alt = TheAM.altOfmaxAccel();
  // dvel = TheAM.dvel(alt);
  // cout << "alt= " << alt << endl
  //      << "acel= " << dvel << endl;

 

}



#endif
