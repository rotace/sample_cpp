/**
 * @file CUI.hpp
 * @brief CUI操作プログラムヘッダ
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */

#ifndef CUI_HPP
#define CUI_HPP

#include "Data.hpp"
#include "AirModel.hpp"
#include "AirBehindShock.hpp"
#include "BoundaryEquation.hpp"
#include "HeatRatio.hpp"

class CUI
{
private:
  Data TheData;
  AirModel TheAM;
  AirBehindShock TheAB;
  BoundaryEquation TheBE;
  HeatRatio TheHR;
  
public:
  CUI();
  virtual ~CUI();

  int DoCommand();
  void Set();
  void Setall();
  
  void setRratio();
  void setR();
  void setIAngle();
  void setmass();
  void setZ();
  void setfw();
  void setrhog();
  void setv0();
  void plotvel();
  void plotqw();
  void plotbe();
  void calc();
  void resultwindow();
  
  void Help();

  
  
};

#endif
