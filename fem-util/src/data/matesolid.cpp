//----------------------------------------------------------------------
/**
   @file matesolid.cpp
   @brief Materialサブクラス SOLID
   
   @author Shibata
   @date 2015-10-08(木) 19:20:41
   
***********************************************************************/

#include "matesolid.hpp"



// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
MateSolid::MateSolid(){}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
MateSolid::~MateSolid(){}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const double MateSolid::rho() const{return rho_;}
const double MateSolid::E()const{return E_;};
const double MateSolid::nu()const{return nu_;};
// ---- Setter
void MateSolid::SetRho(double rho){ rho_ = rho;}
void MateSolid::SetE(const double E){ E_ = E;};
void MateSolid::SetNu(const double nu){ nu_ = nu;};

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
