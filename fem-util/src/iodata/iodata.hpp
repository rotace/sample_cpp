//----------------------------------------------------------------------
/**
   @file iodata.hpp
   @brief 入出力クラス
   
   @author Shibata
   @date 2014-12-20(土) 14:59:54
   
***********************************************************************/

#ifndef _IODATA_H_
#define _IODATA_H_

#include <iostream>
#include <utility>		// pair
#include <list>			// list
#include <map>			// map
#include <boost/scoped_ptr.hpp>	// scoped_ptr
#include <boost/shared_ptr.hpp>	// shared_ptr

#include "mesh.hpp"
#include "object.hpp"
#include "value.hpp"
#include "myexception.hpp"
#include "material.hpp"

typedef boost::shared_ptr<Material> MatePtr;
typedef std::map< int, MatePtr > MateDict;
typedef boost::scoped_ptr<Mesh> MeshPtr;
typedef boost::shared_ptr<Object> ObjectPtr;
typedef std::list< std::pair<int, ObjectPtr> > ObjectDict;
typedef std::map< std::string, ObjectPtr> NameDict;

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class IOData
{
public:
  // ##### enum
  enum Fmt
    {
      VTK,
      FEA,
      BDF_SMALL,
      BDF_LARGE,
      BDF_FREE,
      AUTO,
    };

  enum BdfCard
    {
      BLANK,
      GRID,
      CTRIA3,
      CQUAD4,
      CTETRA,
      CHEXA,
      PSHELL,
      MAT1,
    };
  
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  MateDict mate_dict_;   /// Material
  MeshPtr mesh_ptr_;		/// MeshPtr
  ObjectDict obj_dict_;		/// ObjectPtr Dictionary list
  NameDict name_dict_;		/// ObjectPtr Dictionary map
  Fmt default_fmt_;		/// Default File Format

  
  // ##### Private Member Functions
  // ---- Init & Release
  void Init(const int num_nodes,
	    const int num_faces,
	    const int num_cells,
	    const MeshInfo::CellType max_celltype);
    
  // ##### Copy
  // ---- Copy Function
  bool Copy(const IOData& iodata); // prohibited
  // ---- Copy Operator
  IOData& operator=(const IOData& iodata); // prohibited
  // ---- Copy Constructor
  IOData(const IOData& iodata);	// prohibited
  
public:
  // ##### Constructors
  IOData();
  
  // ##### Destructor
  virtual ~IOData();
  
  // ##### Member Functions
  void Import(const std::string filename, Fmt fmt=AUTO) throw(tool::IOError);
  void Export(const std::string filename, Fmt fmt=AUTO) throw(tool::IOError);
  // VTK
  void InitMeshVtk(std::ifstream& ifs) throw(tool::IOError);
  void ReadMeshVtk(std::ifstream& ifs) throw(tool::IOError);
  void ReadValueVtk(std::ifstream& ifs) throw(tool::IOError);
  void ImportVtk(const std::string filename) throw(tool::IOError);
  void ExportVtk(const std::string filename) throw(tool::IOError);
  // FEAP
  void InitMeshFea(std::stringstream& ifs) throw(tool::IOError);
  void ReadMeshFea(std::stringstream& ifs) throw(tool::IOError);
  void ReadBoundaryFea(std::stringstream& ifs) throw(tool::IOError); 
  void ReadPropertyFea(std::stringstream& ifs) throw(tool::IOError); // TODO: should be implimented
  void ImportFea(const std::string filename) throw(tool::IOError);
  void ExportFea(const std::string filename) throw(tool::IOError);
  // NASTRAN
  BdfCard GetBdfCard(const std::string& buf);
  double ConvertNumBdf(const std::string& buf);
  void ConvertFmtBdf(std::ifstream& ifs, const Fmt fmt, std::stringstream& ss);
  void InitMeshBdf(std::stringstream& ifs) throw(tool::IOError);
  void ReadMeshBdf(std::stringstream& ifs) throw(tool::IOError);
  void ReadPropertyBdf(std::ifstream& ifs) throw(tool::IOError); // TODO: should be implimented
  void ReadBoundaryBdf(std::ifstream& ifs) throw(tool::IOError); // TODO: should be implimented
  void ImportBdf(const std::string filename, const Fmt fmt) throw(tool::IOError);
  void ExportBdf(const std::string filename) throw(tool::IOError);
  /// Write Bulk Data Section by Small Field Format
  void WriteSmallBdf(std::ofstream& ofs) throw(tool::IOError); // TODO: should be implimented
  /// Write Bulk Data Section by Large Field Format
  void WriteLargeBdf(std::ofstream& ofs) throw(tool::IOError); // TODO: should be implimented
  /// Write Bulk Data Section by Free Field Format
  void WriteFreeBdf(std::ofstream& ofs) throw(tool::IOError);

  
  // ---- Information
  void Info();	// Notice Mesh and Value Information
  
  // ---- Getter
  Mesh& mesh();
  const Mesh& mesh()const;
  
  template <typename T>
  ValueArray<T> values(const std::string name) throw(tool::RuntimeError);
  
  // ---- Setter
  template <typename T>
  void SetValues(const ValueArray<T> values);
  

  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef



// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //



#endif /* _IODATA_H_ */
