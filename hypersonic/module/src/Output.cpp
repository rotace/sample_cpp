/**
 * @file Output.cpp
 * @brief プロット出力プログラム
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "Output.hpp"


Output::Output()
  :ItrNum(0),
   ItrNumWrite(0),
   skipItrNum(1),
   FileName( "default.csv" )
{}
Output::~Output(){}

void Output::writeData(double x,double y){
  if ( ItrNumWrite % skipItrNum == 0 )
    {
      fprintf(File,"%.5f,%.5f\n",x,y);
    }
  ItrNumWrite++;
}

void Output::printData(double x,double y)
{
  if ( ItrNum % skipItrNum == 0 )
    {
      cout << x  << " , "
	   << y  << endl;

    }
}

void Output::writeData(double x,double y1,double y2)
{
  if ( ItrNumWrite % skipItrNum == 0 )
    {
      fprintf(File,"%.5f,%.5f,%.5f\n",x,y1,y2);
    }
  ItrNumWrite++;
}



  void Output::printData(double x,double y1, double y2)
  {
    if ( ItrNum % skipItrNum == 0 )
      {
	cout << x  << " , "
	     << y1 << " , "
	     << y2 << endl;
      }
  }

void Output::writeData(double x,double y1,double y2,double y3,double y4, double y5)
{
  if ( ItrNumWrite % skipItrNum == 0 )
    {
      fprintf(File,"%.5f,%.5f,%.5f,%.5f,%.5f,%.5f\n",x,y1,y2,y3,y4,y5);
    }
  ItrNumWrite++;
}

void Output::printData(double x,double y1,double y2,double y3,double y4, double y5)
{
  if ( ItrNum % skipItrNum == 0 )
    {
      cout << x  << " , "
	   << y1 << " , "
	   << y2 << " , "
	   << y3 << " , "
	   << y4 << " , "
	   << y5 << endl;

    }
  
  ItrNum++;
}
void Output::setSkipItrNum(int TheSkipItrNum)
{
  assert(TheSkipItrNum > 0);
  skipItrNum = TheSkipItrNum;
};

void Output::startData()
{
  if ((File = fopen( FileName.c_str() ,"w")) == NULL)
    {
      cout << "file open error!!" << endl;
      abort();
    }
  
}
void Output::endData()
{
  fclose(File);
}
