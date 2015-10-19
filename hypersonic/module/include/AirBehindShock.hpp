/**
 * @file AirBehindShock.hpp
 * @brief 衝撃波背後流れクラスヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef AIRBEHINDSHOCK_HPP
#define AIRBEHINDSHOCK_HPP

#include <string.h>		// string
#include <math.h>		// pow

#include "Calc.hpp"
#include "AirModel.hpp"

#define M_Ru 8.314
#define M_C 3.2865972e20
#define M_k 1.386488e-23


class Calc;
class AirModel;

// definition of molecule enum
enum molnum { N,N2};

class molecule
{
private:
  molnum mol;
  double MM;			// [g/mol]
  double THETArot;
  double THETAvib;
  double dHf;			// [J/mol]
public:
  molecule();
  molecule(int themol);
  virtual ~molecule();
  void setMolecule();
  double Qtrv(double T);
  double Qrot(double T);
  double Qvib(double T);
  double H(double T);
  double M(){return MM;};
};


class AirBehindShock : public Calc
{
private:
  double rhoe;
  double ve;
  double Te;
  double pe;
  double he;
  double mue;
  AirModel *TheAM;
  molecule N;
  molecule N2;
  double fs;
  double alphas;
  double h2s;
  
public:
  AirBehindShock();
  virtual ~AirBehindShock();

  void setAM(AirModel *inAM){TheAM = inAM;};
  double hs(double T, double p);
  double Ts(double h, double p);
  void Function(double in, double *out);
  
  void DoubleFunction(double in1, double in2,double *out1,double *out2){};
  double getrhoe(){return rhoe ;};
  double getve(){return ve ;};
  double getTe(){return Te ;};
  double getpe(){return pe ;};
  double gethe(){return he ;};
  double getmue(){return mue ;};
  double getfs(){return fs ;};
  double getalphas(){return alphas ;};
  double geth2s(){return h2s ;};
  
  void Calc();
  
};

#endif
