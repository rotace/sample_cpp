/**
 * @file HeatRatio.cpp
 * @brief よどみ点加熱率クラス
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "HeatRatio.hpp"

HeatRatio::HeatRatio()
  :alts(1),
   alte(120e3)
{}
HeatRatio::~HeatRatio(){}

void HeatRatio::Function(double in, double *out){
  double alt,dalt,qw1,qw2;
  dalt = 1.0;
  alt = in;
  TheData->setAltitude(alt);
  Calcall();
  qw1 = qw;

  alt = in + dalt;
  TheData->setAltitude(alt);
  Calcall();
  qw2 = qw;
  
  *out = (qw2 -qw1)/dalt;
}

void HeatRatio::Calc(){
  double Pr,he,rhoe,mue,pe,pinf,R,gd0;
  Pr = 0.7;
  he   = TheABS->gethe(); 
  rhoe = TheABS->getrhoe();
  mue  = TheABS->getmue();
  pe   = TheABS->getpe();
  pinf = TheAM->getpinf();
  R    = TheData->getR();
  gd0  = TheBE->getgd0();
  qw = he/Pr*sqrt(rhoe*mue/R)*pow(2*(pe-pinf)/rhoe,0.25)*gd0 ;
}
void HeatRatio::Calcall(){
  TheData->Calc();
  TheAM->Calc();
  TheABS->Calc();
  Calc();
}

void HeatRatio::Plotqw(){

  double alt=0.0, dalt=1000;
  Output TheOut;
  TheOut.setSkipItrNum(1);
  TheOut.setFileName("HR.csv");
  TheOut.startData();
  
  while( alt <= 120000.0 ){
    TheData->setAltitude(alt);
    Calcall();
    TheOut.printData(alt,qw);
    TheOut.writeData(alt,qw);
    alt += dalt;
  }

  TheOut.endData();
}

double HeatRatio::altOfMaxqw(){
  // bisection method
  double dqw1,dqw2,dqwm,alt1,alt2,altm;
  alts = TheAM->alt(1.0);
  alt1 = alts;
  alt2 = alte;

  Function(alt1,&dqw1);
  Function(alt2,&dqw2);
  assert(dqw1*dqw2<0);

  int itr=0;
  while ( fabs(dqw1-dqw2) > 1.0e-4){
    Function(alt1,&dqw1);
    Function(alt2,&dqw2);
    altm = 0.5*(alt1+alt2);
    Function(altm,&dqwm);
    if (dqw1*dqwm > 0){
      alt1 = altm;
    }else{
      alt2 = altm;
    }
    itr++;
  }
  
  return alt1;
}


