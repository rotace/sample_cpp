/**
 * @file Data.cpp
 * @brief カプセル形状諸元データ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "Data.hpp"

Data::Data()
  :Rratio(1.0),
   R(1.0),
   thetaInit(M_PI/2.0),
   mass(1.0),
   Cd(1.0),
   S0(1.0),
   Z(1.2e-4),
   K(1.0),
   altitude(0.0),
   gd0(1.0){
  Calc();
}
Data::~Data(){}

void Data::setAltitude(double x){
  altitude = x;
  Calc();
}
void Data::setRratio(double x){
  Rratio = x;
  Calc();
}
void Data::setR(double x){
  R = x;
  Calc();
}
void Data::setThetaInit(double x){
  thetaInit = x/180.0*M_PI;
  Calc();
}
void Data::setMass(double x){
  mass = x;
  Calc();
}
void Data::setZ(double x){
  Z = x;
  Calc();
}
void Data::setgd0(){
  gd0 = 0.37638;
  Calc();
}
void Data::Calc(){
  Cd = 1 + 0.25*Rratio*Rratio;
  S0 = M_PI * R*R;
  K  = Cd*S0/mass/Z/sin(thetaInit);
}
