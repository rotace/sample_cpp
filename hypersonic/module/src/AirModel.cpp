/**
 * @file AirModel.cpp
 * @brief 大気落下速度分布モデル・大気モデルクラス
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "AirModel.hpp"

AirModel::AirModel()
  :rhog(1.2),
   v0(1.108e4)
{}
AirModel::~AirModel(){}


void AirModel::Calc(){

  // altitude
  double alt;
  alt = TheData->getAltitude();

  // rho
  double Z;
  Z = TheData->getZ();
  rhoinf = rhog * exp(-Z*alt);

  // v
  double K;
  K = TheData->getK();
  vinf = v0 * exp(-0.5*K*rhoinf);

  // T,p
  if (alt > 25000){
    Tinf = -131.21 + 0.00299*alt + 273.1;
    pinf = 2.488e3 * pow( Tinf/216.6 , -11.388 );
      
  }else if(alt <= 25000 && alt > 11000){
    Tinf = -56.46 + 273.1;
    pinf = 22.65e3 * exp( 1.73 - 0.000157*alt );

  }else if(alt <= 11000){
    Tinf = 15.04 - 0.00649*alt + 273.1;
    pinf = 101.29e3 * pow( Tinf/288.08 , 5.256 );

  }else{
    cout << "out of range (altitude)" << endl;
    abort();
  }
  
  // h
  double Ru;
  Ru = 8.314;			// [J/mol/K]
  hinf = 3.5 * Ru * Tinf;	// [J/mol]
  
}

void AirModel::Plotvinf(){

  double alt=0.0, dalt=1000;
  Output TheOut;
  TheOut.setSkipItrNum(1);
  TheOut.setFileName("AM.csv");
  TheOut.startData();
  
  double velp,dvelp;
  while( alt <= 120000.0 ){
    velp  = vel(alt);
    dvelp = dvel(alt);
    TheOut.printData(alt,velp,dvelp);
    TheOut.writeData(alt,velp,dvelp);
    alt += dalt;
  }

  TheOut.endData();
}


double AirModel::vel(double alt){
  TheData->setAltitude(alt);
  TheData->Calc();
  Calc();
  return vinf;
}

double AirModel::alt(double invel){
  // bisection method
  double alt1,alt2,altm,vel1,vel2,velm;
  alt1 = 0.1;
  alt2 = 120e3;

  vel1 = vel(alt1) - invel;
  vel2 = vel(alt2) - invel;
  assert(vel1*vel2 < 0);

  int itr=0;
  while ( fabs(vel1-vel2) > 1.0e-4 ){
    vel1 = vel(alt1) - invel;
    vel2 = vel(alt2) - invel;
    altm = 0.5*(alt1+alt2);
    velm = vel(altm) - invel;
    if (vel1*velm > 0){
      alt1 = altm;
    }else{
      alt2 = altm;
    }
    itr++;
  }
  return alt1;
 
}

double AirModel::dvel(double inalt){
  double alt,dalt,velat,cd,rho,S,mass,accel;
  dalt =1.0;
  alt = inalt;
  velat =vel(alt);
  cd = TheData->getCd();
  rho = getrhoinf();
  mass = TheData->getMass();
  S = TheData->getS0();
  
  accel = cd * 0.5*rho*velat*velat * S/ mass ;
  
  return accel;
}

double AirModel::ddvel(double inalt){
  double alt,dalt,dvel1,dvel2;
  dalt =1.0;
  alt = inalt;
  dvel1 =dvel(alt);
  
  alt = inalt + dalt;
  dvel2 =dvel(alt);

  return (dvel2-dvel1)/dalt;
}

double AirModel::altOfmaxAccel(){
  // bisection method
  double ddvel1,ddvel2,ddvelm,alt1,alt2,altm;
  alt1 = alt(20.0);
  alt2 = 120e3;

  ddvel1 = ddvel(alt1);
  ddvel2 = ddvel(alt2);
  assert(ddvel1*ddvel2 <0);

  int itr=0;
  while ( fabs(ddvel1-ddvel2) > 1.0e-4 ){
    ddvel1 = ddvel(alt1);
    ddvel2 = ddvel(alt2);
    altm  = 0.5*(alt1+alt2);
    ddvelm = ddvel(altm);
    if (ddvel1*ddvelm > 0){
      alt1 = altm;
    }else{
      alt2 = altm;
    }
    itr++;
  }
  return alt1;
}

