//----------------------------------------------------------------------
/**
   @file mateuser1.cpp
   @brief Materialサブクラス　USER1
   
   @author Shibata
   @date 2015-10-08(木) 19:20:05
   
***********************************************************************/

#include "mateuser1.hpp"


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
MateUser1::MateUser1(){}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
MateUser1::~MateUser1(){}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const double MateUser1::rho() const{return rho_;}
const double MateUser1::c() const{return c_;}

// ---- Setter
void MateUser1::SetRho(double rho){ rho_ = rho;}
void MateUser1::SetC(double c){ c_ = c;}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
