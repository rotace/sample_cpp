//----------------------------------------------------------------------
/**
   @file material.hpp
   @brief 物質情報のデータ
   
   @author Shibata
   @date 2015-10-08(木) 11:58:34
   
***********************************************************************/

#ifndef _MATERIAL_H_
#define _MATERIAL_H_


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Material
{
public:
  // ##### enum
  enum MateType
  {
	  BLANK,  /// Initialize Type
	  SOLID,  /// elastic FEM
	  USER1,  /// acoustic FEM
	  USER2,  /// polo-elastic FEM
  };

  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  int id_;	       // material ID
  MateType type_; // material type
  
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const Material& material);	// prohibited
  
  // ---- Copy Operator
  Material& operator=(const Material& material); // prohibited
  
  // ---- Copy Constructor
  Material(const Material& material); // prohibited
  
public:
  // ##### Constructors
  Material();
  
  // ##### Destructor
  virtual ~Material();
  
  // ##### Member Functions
  // ---- Getter
  const int id()const;
  const MateType type()const;

  virtual const double rho()const{return 0.0;};
  virtual const double c()const{return 0.0;};
  virtual const double E()const{return 0.0;};
  virtual const double nu()const{return 0.0;};

  // ---- Setter
  void SetId(const int id);
  void SetType(const MateType type);
  
  virtual void SetRho(const double rho){};
  virtual void SetC(const double c){};
  virtual void SetE(const double E){};
  virtual void SetNu(const double nu){};

  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MATERIAL_H_ */
