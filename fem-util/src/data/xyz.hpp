//----------------------------------------------------------------------
/**
   @file xyz.hpp
   @brief ベクトルクラス
   
   @author Shibata
   @date 2014-12-20(土) 11:39:26
   
***********************************************************************/

#ifndef _XYZ_H_
#define _XYZ_H_


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class XYZ
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy ( default copy constructor )
  // // ---- Copy Function
  // bool Copy(const XYZ& xyz);
  // // ---- Copy Operator 
  // XYZ& operator=(const XYZ& xyz);
  // // ---- Copy Constructor
  // XYZ(const XYZ& xyz);
  
public:
  // ##### Public Data Members
  double x,y,z;
  
  // ##### Constructors
  XYZ();
  XYZ(double in_x, double in_y, double in_z);
  
  // ##### Destructor
  virtual ~XYZ();
  
  // ##### Member Functions
  // ---- Getter
  // ---- Setter
  void Set(const double in_x, const double in_y, const double in_z);
  
  // ##### Member Operators
  XYZ& operator=(const XYZ& v);
  XYZ& operator+=(const XYZ& v);
  XYZ& operator-=(const XYZ& v);
  XYZ& operator*=(const XYZ& v);
  XYZ& operator/=(const XYZ& v);
  XYZ operator+();
  XYZ operator-();
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// 二項演算子(global)
XYZ operator+(const XYZ& u,const XYZ& v);
XYZ operator-(const XYZ& u,const XYZ& v);
double operator*(const XYZ& u,const XYZ& v);
XYZ operator%(const XYZ& u,const XYZ& v);
XYZ operator*(const double& a,const XYZ& v);
XYZ operator*(const XYZ& u,const double& b);
XYZ operator/(const XYZ& u,const double& b);
bool operator==(const XYZ& u, const XYZ& v);

// 画面出力
#include <iostream>
std::ostream& operator<<(std::ostream& s, const XYZ& v);

// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _XYZ_H_ */
