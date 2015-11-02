//----------------------------------------------------------------------
/**
   @file value.cpp
   @brief バリュークラス
   
   @author Shibata
   @date 2014-12-23(火) 11:20:19
   
***********************************************************************/

#include "value.hpp"

#include <assert.h>
#include <iostream>
#include <algorithm>		// std::copy
#include <iterator>		// std::back_iserter


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release

// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
template <typename T>
bool ValueArray<T>::Copy(const ValueArray<T>& value)
{
  if( this == &value)
    return true;
  // Release();

  // copy members
  this->values_ = value.values_;
  this->flag_   = value.flag_;
  
  return true;
}
  
// ---- Copy Operator
template <typename T>
ValueArray<T>& ValueArray<T>::operator=(const ValueArray<T>& value)
{
  Object::Copy( (Object)value ); // base class copy
  ValueArray<T>::Copy(value);	 // derived class copy
  return *this;
}

// ---- Copy Constructor
template <typename T>
ValueArray<T>::ValueArray(const ValueArray<T>& value)
  :Object(value),		// base class copy constructor
   values_(value.values())	// derived class member copy
{
  this->flag_ = value.flag_;
  // Init();
  // Copy(value);
}

// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
template <typename T>
ValueArray<T>::ValueArray()
  :Object(Object()),
   values_(1),
   flag_(true)
{
  std::cerr << "Error: Default constructor is prohibited ! " << std::endl;
  assert(false);
}

template <typename T>
ValueArray<T>::ValueArray(const int num_values,
			  const T value,
			  const Object object,
			  const bool flag)
  :Object(object),
   values_(num_values, value),
   flag_(num_values, flag)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
template <typename T>
ValueArray<T>::~ValueArray()
{
  // Release();
}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
template <typename T>
const std::vector<T>& ValueArray<T>::values() const{ return values_;}

template <typename T>
const size_t ValueArray<T>::size() const{ return values_.size();}

template <typename T>
const bool ValueArray<T>::flag(const int index) const
{
  return flag_.at( (size_t)index );
}

// ---- Setter
template <typename T>
void ValueArray<T>::SetValue(const int index, const T value)
{
  values_.at(index) = value;
}

template <typename T>
void ValueArray<T>::SetFlag(const int index, const bool flag)
{
  flag_.at(index) = flag;
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
template <typename T>
T& ValueArray<T>::operator[](unsigned int index)
{
  return values_.at((size_t)index);
}

template <typename T>
T& ValueArray<T>::operator[](int index)
{
  return (*this)[(unsigned int)index];
}

template <typename T>
T ValueArray<T>::operator[](unsigned int index)const
{
  return values_.at((size_t)index);
}

template <typename T>
T ValueArray<T>::operator[](int index)const
{
  return (*this)[(unsigned int)index];
}


// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
template class ValueArray<int>;
template class ValueArray<double>;
#include "xyz.hpp"
template class ValueArray<XYZ>;
// template class ValueArray<bool>; Bit_reference problem
#include "mybool.hpp"
template class ValueArray<MyBool>;
