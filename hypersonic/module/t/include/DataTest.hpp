/**
 * @file DataTest.hpp
 * @brief Dataクラスのテストモジュール
 *
 * @author Shibata
 * @date 2014-8-4
 *
 */

#ifndef DATATEST_H
#define DATATEST_H

#include "CppUTest/CommandLineTestRunner.h"

#include "AirModel.hpp"
#include "math.h"


#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;


// テストグループの定義 TEST_GROUP(group)
// フィクスチャの準備
TEST_GROUP(DATATestGroup) {
  Data TheData;
  const static double eps = 10e-4;
 
  TEST_SETUP() {
    // 各テストケース実行前に呼ばれる、ここではなにもしない
  }
 
  TEST_TEARDOWN() {
    // 各テストケース実行後に呼ばれる、ここではなにもしない
  }
};
 
// テストケース TEST(group, name)
TEST(DATATestGroup, DATATest) {
  
  cout << "###DATATestGroup DATATest ###" << endl;
  TheData.setAltitude(1.0);
  TheData.setRratio(1.0);
  TheData.setR(1.0);
  TheData.setThetaInit(90.0);
  TheData.setMass(1.0);
  TheData.setgd0();
  
  DOUBLES_EQUAL(TheData.getAltitude(),1.0 , eps);
  DOUBLES_EQUAL(TheData.getR(),1.0 , eps);
  DOUBLES_EQUAL(TheData.getCd(),1.25 , eps);
  DOUBLES_EQUAL(TheData.getS0(),M_PI , eps);
  DOUBLES_EQUAL(TheData.getZ(),1.207e-4 , eps);
  DOUBLES_EQUAL(TheData.getK(),32535.13519 , eps);
  DOUBLES_EQUAL(TheData.getgd0(),0.37638 , eps);

}



#endif
