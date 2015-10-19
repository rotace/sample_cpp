/**
 * @file AirBehindShock.cpp
 * @brief 衝撃波背後流れクラス
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "AirBehindShock.hpp"

molecule::molecule()
  :mol(N)
{
  setMolecule();
}
molecule::molecule(int themol)
{
  if(themol == 0){
    mol = N;
  }else if(themol == 1){
    mol = N2;
  }
  setMolecule();
}
molecule::~molecule(){}
void molecule::setMolecule(){
  switch(mol){
  case N:
    MM = 14;
    dHf = 470.820e3;		// // [J/mol]
    break;
  case N2:
    MM = 28;
    THETArot = 2.88;
    THETAvib = 3371.0;
    dHf = 0;
    break;
  }
}
double molecule::Qtrv(double T){
  double Qtrv;
  Qtrv = pow(M_C*MM*T,1.5);
  return Qtrv;
}
double molecule::Qrot(double T){
  double Qrot;
  switch(mol){
  case N:
    Qrot = 1.0;
    break;
  case N2:
    Qrot = 0.5*T / THETArot;
    break;
  }
  return Qrot;
}
double molecule::Qvib(double T){
  double Qvib;
  switch(mol){
  case N:
    Qvib = 1.0;
    break;
  case N2:
    Qvib = 1.0 / (1 - exp( -THETAvib/T));
    break;
  }
  return Qvib;
}
double molecule::H(double T){
  double H;
  switch(mol){
  case N:
    H = 2.5*M_Ru*T + dHf;
    break;
  case N2:
    H = (3.5 + THETAvib/T / exp(THETAvib/T) )*M_Ru*T + dHf;
    break;
  }
  return H;
}






AirBehindShock::AirBehindShock()
  :N(0),
   N2(1)
{}
AirBehindShock::~AirBehindShock(){}


double AirBehindShock::hs(double T, double p){
  // statistic
  double THETAdisN2=113000.0;
  fs = M_k*T/p * N.Qtrv(T)*N.Qtrv(T)/N2.Qtrv(T)/N2.Qrot(T)/N2.Qvib(T)*exp(-THETAdisN2/T);
  alphas = sqrt(fs/(4+fs));
  h2s = alphas * N.H(T) / N.M() *1000 + (1.0-alphas) * N2.H(T) / N.M() *1000;
  return h2s;
}

double AirBehindShock::Ts(double h, double p){
  // bisection method
  double f1,f2,T1,T2,Tm,fm;
  T1 = 0.1;
  T2 = 100000;
  
  f1 = hs(T1,p) - h;
  f2 = hs(T2,p) - h;
  assert(f1*f2 < 0);

  int itr=0;
  while ( fabs(f1-f2) > 1.0e-4){
    f1 = hs(T1,p) -h ;
    f2 = hs(T2,p) -h ;
    Tm = 0.5*(T1+T2);
    fm = hs(Tm,p) -h ;
    if (f1*fm > 0){
      T1 = Tm;
    }else{
      T2 = Tm;
    }
    itr++;
  }
  return T1;
}


void AirBehindShock::Function(double in, double *out){
  double rho1,u1,p1,T1,h1;
  double rho2,   p2,T2,h2;
  rho1 = TheAM->getrhoinf();
  u1 = TheAM->getvinf();
  p1 = TheAM->getpinf();
  T1 = TheAM->getTinf();
  h1 = TheAM->gethinf();

  h2 = h1 + 0.5*u1*u1*(1-in*in);
  p2 = rho1*u1*u1*(1 - in)+ p1;
  // cout << "p2=" << p2 << endl;
  // cout << "h2=" << h2 << endl;
  T2 = Ts(h2,p2);
  rho2 = p2/M_Ru/T2;
  
  *out = rho1/rho2 - in;
}


void AirBehindShock::Calc(){
  // double ratio,T2;
  // Calc::DoubleNewton(&ratio, &T2);
  double ratio;
  Calc::Newton(&ratio);

  double rho1,u1,p1,T1,h1;
  rho1 = TheAM->getrhoinf();
  u1 = TheAM->getvinf();
  p1 = TheAM->getpinf();
  T1 = TheAM->getTinf();
  h1 = TheAM->gethinf();

  rhoe = rho1 / ratio;
  ve = ratio * u1;
  // Te = T2;
  pe = rho1*u1*u1*(1 - ratio)+ p1;
  he = h1 + 0.5*u1*u1*(1-ratio*ratio);
  Te = Ts(he,pe);
  mue = 1.7e-5* pow(Te/300, 0.75);
}


