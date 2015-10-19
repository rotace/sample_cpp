/**
 * @file CUI.cpp
 * @brief CUI操作プログラム
 *
 * @author Shibata
 * @date 2014-8-1
 *
 */
#include "CUI.hpp"
#include <iostream>
#include <iomanip>


CUI::CUI()
{
  TheAM.setData(&TheData);
  TheAB.setAM(&TheAM);
  TheHR.setData(&TheData);
  TheHR.setAM(&TheAM);
  TheHR.setAB(&TheAB);
  TheHR.setBE(&TheBE);
  calc();
}
CUI::~CUI(){}

int CUI::DoCommand(){

  int theRet = 0;
  char theCommand[255];
  cout << "command?>";
  cin >> theCommand;
  if (strcmp(theCommand, "quit") == 0){
    theRet = -1;
  }else if(strcmp(theCommand, "help") == 0){
    Help();
  }else if(strcmp(theCommand, "set") == 0){
    Set();
  }else if(strcmp(theCommand, "setall") == 0){
    Setall();
  }else if(strcmp(theCommand, "setRr") == 0){
    setRratio();
  }else if(strcmp(theCommand, "setR") == 0){
    setR();
  }else if(strcmp(theCommand, "setIAngle") == 0){
    setIAngle();
  }else if(strcmp(theCommand, "setmass") == 0){
    setmass();
  }else if(strcmp(theCommand, "setfw") == 0){
    setfw();
  }else if(strcmp(theCommand, "result") == 0){
    calc();
    resultwindow();
  }else if(strcmp(theCommand, "plotvel") == 0){
    plotvel();
  }else if(strcmp(theCommand, "plotqw") == 0){
    plotqw();
  }else if(strcmp(theCommand, "plotbe") == 0){
    plotbe();
  }
  return theRet;
}

void CUI::Set(){
  setRratio();
  setR();
  setIAngle();
  setmass();
  setfw();
  calc();
  resultwindow();  
}

void CUI::Setall(){
  setRratio();
  setR();
  setIAngle();
  setmass();
  setZ();
  setfw();
  setrhog();
  setv0();
  calc();
  resultwindow();  
}

void CUI::setRratio(){
  double value;
  cout << "ratio R/r (1~2) ?>";
  cin >> value;
  TheData.setRratio(1/value);
}
void CUI::setR(){
  double value;
  cout << "R (0.2~0.4) [m] ?>";
  cin >> value;
  TheData.setR(value);
}
void CUI::setIAngle(){
  double value;
  cout << "Inclination Angle [degree] ?>";
  cin >> value;
  TheData.setThetaInit(value);
}
void CUI::setmass(){
  double value;
  cout << "mass (20~30) [kg] ?>";
  cin >> value;
  TheData.setMass(value);
}
void CUI::setZ(){
  double value;
  cout << "Z (default:1.2e-4) [m-1] ?>";
  cin >> value;
  TheData.setZ(value);
}
void CUI::setfw(){
  double value;
  cout << "fw (=f0) (fw=0:wall, fw<0:suction)?>";
  cin >> value;
  TheBE.setf0(value);
  TheBE.Calc();
}
void CUI::setrhog(){
  double value;
  cout << "rho at ground (default:1.2) [kg/m3] ?>";
  cin >> value;
  TheAM.setrhog(value);
}
void CUI::setv0(){
  double value;
  cout << "velocity at rentry (default:1.108e4) [m/s] ?>";
  cin >> value;
  TheAM.setv0(value);
}
void CUI::calc(){
  TheData.Calc();
  TheAM.Calc();
  TheAB.Calc();
  TheBE.Calc();
  TheHR.Calc();
}
void CUI::plotvel(){
  TheAM.Plotvinf();
  cout << "-- altitude / velocity / accel --" << endl;
}
void CUI::plotqw(){
  TheHR.Plotqw();
  cout << "-- altitude / qw --" << endl;
}
void CUI::plotbe(){
  TheBE.PlotBE();
  cout << "-- eta / f / f' /f'' / g / g' --" << endl;
}

void CUI::resultwindow(){
  double value;
  cout << "=========================================" << endl;
  cout << "                 result                  " << endl;
  cout << "=========================================" << endl;
  cout << " ### BoundaryEquation ###" << endl;
  cout << "      g'(0)        : " << TheBE.getgd0() << endl;
  cout << " ###      AirModel    ###" << endl;
  value = TheAM.altOfmaxAccel();
  cout << "   altitude [m]    : " << value << endl;
  value = TheAM.dvel(value);
  cout << "  max_accel [m/s2] : " << value << endl;
  cout << " ###  max heat rate   ###" << endl;
  cout << "   altitude [m]    : " << TheHR.altOfMaxqw() << endl;
  cout << "     max_qw [MW/m2]: " << TheHR.getqw()/1.0e6 << endl;
}


void CUI::Help(){
  cout << "No. 281465153 : Shibaya Yasunori" << endl;
  cout << "------------  ------------  -----------  -------------" <<endl;
  cout << setw(10) << right << "quit:" << "   " << "you can quit." << endl;
  cout << setw(10) << right << "help:" << "   " << "you can see helpfile." << endl;
  cout << setw(10) << right << "set:" << "   " << "you can set some main variables." << endl;
  cout << setw(10) << right << "setall:" << "   " << "you can set all variables." << endl;
  cout << setw(10) << right << "setRr:" << "   " << "set R/r." << endl;
  cout << setw(10) << right << "setR:" << "   " << "set R." << endl;
  cout << setw(10) << right << "setIAngle:" << "   " << "set Inclination Angle." << endl;
  cout << setw(10) << right << "setmass:" << "   " << "set mass." << endl;
  cout << setw(10) << right << "setfw:" << "   " << "set fw" << endl;
  cout << setw(10) << right << "result:" << "   " << "you can see the result." << endl;
  cout << setw(10) << right << "plotvel:" << "   " << "output alt-vel into csv." << endl;
  cout << setw(10) << right << "plotqw:" << "   " << "output alt-qw into csv." << endl;
  cout << setw(10) << right << "plotbe:" << "   " << "output boundaryEquation graph into csv." << endl;

}
