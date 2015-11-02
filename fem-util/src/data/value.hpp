//----------------------------------------------------------------------
/**
   @file value.hpp
   @brief バリュークラス
   
   @author Shibata
   @date 2014-12-21(日) 19:06:59
   
***********************************************************************/

#ifndef _VALUE_H_
#define _VALUE_H_

#include <vector>

#include "object.hpp"


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
template <typename T>
class ValueArray :public Object
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  std::vector<T> values_;
  std::vector<bool> flag_;
  
  // ##### Private Member Functions
  // ---- getter
  const std::vector<T>& values() const; // used for copy

  // ---- Init & Release
  
public:
  // ##### Copy
  // ---- Copy Function
  bool Copy(const ValueArray<T>& value);
  
  // ---- Copy Operator
  ValueArray<T>& operator=(const ValueArray<T>& value);
  
  // ---- Copy Constructor
  ValueArray(const ValueArray<T>& value);
  
  // ##### Constructors
  ValueArray();
  
  ValueArray(const int num_values,
	     const T value,
	     const Object object = Object(),
	     const bool flag=true);
  
  // ##### Destructor
  virtual ~ValueArray();
  
  // ##### Member Functions
  // ---- Getter
  const size_t size()const;
  const bool flag( const int index )const;
  
  // ---- Setter
  void SetValue(const int index, const T value);
  void SetFlag(const int index, const bool flag);
  
  // ##### Member Operators
  // reference member
  T& operator[](unsigned int index);
  T& operator[](int index);
  T operator[](unsigned int index)const;
  T operator[](int index)const;
  
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef
typedef ValueArray<int> IntValueArray;
typedef ValueArray<double> DoubleValueArray;
#include "xyz.hpp"
typedef ValueArray<XYZ> XYZValueArray;
#include "mybool.hpp"
typedef ValueArray<MyBool> BoolValueArray;


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //
// #include "value_inl.hpp"


#endif /* _VALUE_H_ */
