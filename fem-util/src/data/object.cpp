//----------------------------------------------------------------------
/**
   @file object.cpp
   @brief オブジェクトクラス
   
   @author Shibata
   @date 2014-12-21(日) 20:53:05
   
***********************************************************************/

#include "object.hpp"

#include <iostream>


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
bool Object::Copy(const Object& object)
{
  if( this == &object)
    return true;
  // Release();

  // copy members
  this->name_      = object.name_;
  this->datatype_  = object.datatype_;
  this->valuetype_ = object.valuetype_;
  
  return true;
}
  
// ---- Copy Operator
Object& Object::operator=(const Object& object)
{
  Object::Copy(object);
  return *this;
}

// ---- Copy Constructor
Object::Object(const Object& object)
  :name_(object.name()),
   datatype_(object.datatype()),
   valuetype_(object.valuetype())
{
  // Init();
  // Copy(object);
}

// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Object::Object()
  :name_(std::string("default_name")),
   datatype_(NODE),
   valuetype_(INT)
{}

Object::Object(const std::string name,
	       const DataType datatype,
	       const ValueType valuetype)
  :name_(name),
   datatype_(datatype),
   valuetype_(valuetype)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Object::~Object()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const std::string Object::name() const{return name_;}
const Object::DataType Object::datatype() const{return datatype_;}
const Object::ValueType Object::valuetype() const{return valuetype_;}

// ---- Setter
void Object::SetName(const std::string name){ name_=name;}
void Object::SetDataType(const DataType datatype){ datatype_=datatype;}
void Object::SetValueType(const ValueType valuetype){ valuetype_=valuetype;}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

