//----------------------------------------------------------------------
/**
   @file mybool.hpp
   @brief マイブールクラス
   
   @author Shibata
   @date 2014-12-23(火) 12:34:42
   
***********************************************************************/

#ifndef _MYBOOL_H_
#define _MYBOOL_H_


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class MyBool
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  bool entity_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const MyBool& mybool); // prohibited
  
public:
  // ---- Copy Operator
  MyBool& operator=(const MyBool& mybool)
  {
    this->entity_ = mybool.entity_;
    return *this;
  }
  
  // ---- Copy Constructor
  MyBool(const MyBool& mybool)
    :entity_(mybool.entity_)
  {}
  
  // ##### Constructors
  MyBool()
    :entity_(false)
  {}

  MyBool(bool e)
    :entity_(e)
  {}
  
  // ##### Destructor
  virtual ~MyBool()
  {}
  
  // ##### Member Functions
  // ---- Getter
  // ---- Setter
  
  // ##### Member Operators
  operator bool&() {return entity_;}
  operator const bool&() const {return entity_;}
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MYBOOL_H_ */
