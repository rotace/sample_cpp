//----------------------------------------------------------------------
/**
   @file material.cpp
   @brief 物質情報のデータ
   
   @author Shibata
   @date 2015-10-08(木) 12:00:15
   
***********************************************************************/

#include "material.hpp"


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Material::Material()
  :id_(0),
   type_(BLANK)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Material::~Material()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const int Material::id() const{return id_;}
const Material::MateType Material::type() const{return type_;}

// ---- Setter
void Material::SetId(int id)
{
	id_ = id;
}

void Material::SetType(Material::MateType type)
{
	type_ = type;
}


// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
