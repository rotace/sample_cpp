//----------------------------------------------------------------------
/**
   @file object.hpp
   @brief オブジェクトクラス
   
   @author Shibata
   @date 2014-12-21(日) 20:37:16
   
***********************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Object
{
public:
  // ##### enum
  
  /// Position Definition of Data
  enum DataType
    {
    NODE,
    FACE,
    CELL,
    };

  /// TYPE
  enum ValueType
    {
    INT,
    DOUBLE,
    XYZ,
    BOOL,
    };

  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  std::string name_;
  DataType datatype_;
  ValueType valuetype_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  
public:  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const Object& object);
  
  // ---- Copy Operator
  Object& operator=(const Object& object);
  
  // ---- Copy Constructor
  Object(const Object& object);
  
  // ##### Constructors
  Object();
  Object(const std::string name,
	 const DataType datatype,
	 const ValueType valuetype);
  
  // ##### Destructor
  virtual ~Object();
  
  // ##### Member Functions
  // ---- Getter
  const std::string name() const;
  const DataType datatype() const;
  const ValueType valuetype() const;
  
  // ---- Setter
  void SetName(const std::string name);
  void SetDataType(const DataType datatype);
  void SetValueType(const ValueType valuetype);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _OBJECT_H_ */
