/**
 * @file Output.hpp
 * @brief プロット出力プログラムヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <assert.h>		// assert
#include <iostream>		// cout,cin,endl
#include <string.h>		// string
#include <stdio.h>		// fopen,fclose
#include <stdlib.h>		// abort
using namespace std;


class Output
{
private:
  int ItrNum;
  int ItrNumWrite;
  int skipItrNum;
  string FileName;
  FILE *File;
public:
  Output();
  virtual ~Output();

  void writeData(double x,double y);
  void printData(double x,double y);
  void writeData(double x,double y1,double y2);
  void printData(double x,double y1,double y2);

  void writeData(double x,double y1,double y2,double y3,double y4, double y5);
  void printData(double x,double y1,double y2,double y3,double y4, double y5);
  void setFileName(string TheFileName){FileName = TheFileName;};
  void setSkipItrNum(int TheSkipItrNum);
  void startData();
  void endData();
  
};


#endif
