/**
 * @file mainTest.cpp
 * @brief テスト実行メインプログラム
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */


#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"

#include <CalcTest.hpp>
#include <DataTest.hpp>
#include <BETest.hpp>
#include <AMTest.hpp>
#include <ABTest.hpp>
#include <HRTest.hpp>
 
 
int main(int argc, char** argv) {
  // テストランナー
  return RUN_ALL_TESTS(argc, argv);
}
