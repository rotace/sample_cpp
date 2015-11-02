//----------------------------------------------------------------------
/**
   @file xyz.cpp
   @brief ベクトルクラス
   
   @author Shibata
   @date 2014-12-20(土) 11:45:13
   
***********************************************************************/

#include "xyz.hpp"

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
XYZ::XYZ():x(0),y(0),z(0)
{
}
XYZ::XYZ(double in_x, double in_y, double in_z):x(in_x),y(in_y),z(in_z)
{
}
// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
XYZ::~XYZ()
{
}
// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
// ---- Setter
void XYZ::Set(const double in_x, const double in_y, const double in_z)
{
  x = in_x;
  y = in_y;
  z = in_z;
}
// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //


//   =
XYZ& XYZ::operator=(const XYZ& v){
  this->x=v.x; this->y=v.y; this->z=v.z; return *this;
}
//   +=
XYZ& XYZ::operator+=(const XYZ& v){
  this->x+=v.x; this->y+=v.y; this->z+=v.z; return *this;
}
//   -=
XYZ& XYZ::operator-=(const XYZ& v){
  this->x-=v.x; this->y-=v.y; this->z-=v.z; return *this;
}
//   *=
XYZ& XYZ::operator*=(const XYZ& v){
  this->x*=v.x; this->y*=v.y; this->z*=v.z; return *this;
}
//   /=
XYZ& XYZ::operator/=(const XYZ& v){
  this->x/=v.x; this->y/=v.y; this->z/=v.z; return *this;
}
//   +
XYZ XYZ::operator+(){
  return *this;
}
//   -
XYZ XYZ::operator-(){
  return XYZ(-x,-y,-z);
}




//    vector + vector
XYZ operator+(const XYZ& u,const XYZ& v){
  XYZ w;
  w.x = u.x + v.x;
  w.y = u.y + v.y;
  w.z = u.z + v.z;
  return w;
}
//   vector - vector
XYZ operator-(const XYZ& u,const XYZ& v){
  XYZ w;
  w.x = u.x - v.x;
  w.y = u.y - v.y;
  w.z = u.z - v.z;
  return w;
}
//  vector * vector (inner product)
double operator*(const XYZ& u,const XYZ& v){
  return u.x*v.x + u.y*v.y + u.z*v.z;
}
//  vector % vector (outer product)
XYZ operator%(const XYZ& u,const XYZ& v){
  XYZ w;
  w.x = u.y*v.z - u.z*v.y;
  w.y = u.z*v.x - u.x*v.z;
  w.z = u.x*v.y - u.y*v.x;
  return w;
}
//   scalar * vector
XYZ operator*(const double& a,const XYZ& v){
  XYZ w;
  w.x = a * v.x;
  w.y = a * v.y;
  w.z = a * v.z;
  return w;
}
//   vector * scalar
XYZ operator*(const XYZ& u,const double& b){
  XYZ w;
  w.x = u.x * b;
  w.y = u.y * b;
  w.z = u.z * b;
  return w;
}
//   vector / scalar
XYZ operator/(const XYZ& u,const double& b){
  XYZ w;
  w.x = u.x / b;
  w.y = u.y / b;
  w.z = u.z / b;
  return w;
}
// ==
bool operator==(const XYZ& u, const XYZ& v){
  return u.x == v.x && u.y == v.y && u.z == v.z;
}


// output
std::ostream& operator<<(std::ostream& s, const XYZ& v){
  return s << '('<< v.x << "," << v.y << "," << v.z << ')';
}


// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

