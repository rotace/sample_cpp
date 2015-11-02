//----------------------------------------------------------------------
/**
   @file iodata.cpp
   @brief 入出力クラス
   
   @author Shibata
   @date 2014-12-20(土) 15:01:34
   
***********************************************************************/

#include "iodata.hpp"

#include "tool.hpp"


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
void IOData::Init(const int num_nodes,
		  const int num_faces,
		  const int num_cells,
		  const MeshInfo::CellType max_celltype)
{
  // reset mesh pointer
  mesh_ptr_.reset(new Mesh(num_nodes,
			   num_faces,
			   num_cells,
			   max_celltype));
  // clear object dictionary
  obj_dict_.clear();
  // clear material dictionary
  mate_dict_.clear();
}

// ---- Init & Release

// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
IOData::IOData()
  :default_fmt_(VTK)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
IOData::~IOData()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
void IOData::Import(const std::string filename, IOData::Fmt fmt)
  throw(tool::IOError)
{
  switch(fmt){
  case VTK:
    ImportVtk(filename);
    return;
  case FEA:
    ImportFea(filename);
    return;
  case BDF_SMALL:
  case BDF_LARGE:
  case BDF_FREE:
    ImportBdf(filename, fmt);
    return;
  case AUTO:
    break;
  }
  // automatically distinguish format
  std::string ext = tool::GetExtension(filename);
  if      ( ext == "vtk"){
    ImportVtk(filename);
  }else if( ext == "fea"){
    ImportFea(filename);
  }else if( ext == "bdf"){
    std::cout << "ERROR: bdf import is not implimented!" << std::endl;
    assert(false);
  }else{
    std::cout << "invalid file extension: " + ext  << std::endl;
    assert(false);
  }
}

void IOData::Export(const std::string filename, Fmt fmt)
  throw(tool::IOError)
{
  switch(fmt){
  case VTK:
    ExportVtk(filename);
    break;
  case FEA:
    ExportFea(filename);
    break;
  case BDF_SMALL:
  case BDF_LARGE:
  case BDF_FREE:
    ExportBdf(filename);
    break;
  case AUTO:
    if( default_fmt_ == AUTO ){	// prohibit roop
      default_fmt_ = VTK;
    }
    Export(filename, default_fmt_);
    break;
  }
}

// ---- Information
void IOData::Info()
{
  Mesh& mesh = *mesh_ptr_;
  std::cout << "NUM_NODES    : " << mesh.nodes().size() << std::endl;
  std::cout << "NUM_FACES    : " << mesh.faces().size() << std::endl;
  std::cout << "NUM_CELLS    : " << mesh.cells().size() << std::endl;
  if( obj_dict_.size() == 0 ){
    std::cout << "NUM_VALUESET : " << "NOVALUE" << std::endl;
  }else{
    std::cout << "NUM_VALUESET : " << obj_dict_.size() << std::endl;

    int i=0;
    for(ObjectDict::iterator itl = obj_dict_.begin();
	itl != obj_dict_.end();
	++itl){
      ObjectPtr object = (*itl).second;
      std::cout << "SET"
		<< i
		<<"_NAME    : "
		<< object->name() << std::endl;
      i++;
    }
  }
  
}

// ---- Getter
Mesh& IOData::mesh(){
  return *mesh_ptr_;
}

const Mesh& IOData::mesh()const{
  return *mesh_ptr_;
}

template <typename T>
ValueArray<T> IOData::values(const std::string name)
  throw(tool::RuntimeError)
{
  NameDict::iterator itl = name_dict_.find(name);

  if ( itl == name_dict_.end() )
    BOOST_THROW_EXCEPTION( tool::RuntimeError("Not Found in Dictionary !") );
  
  ObjectPtr obj_ptr = itl->second;
  return *(ValueArray<T>*)obj_ptr.get();
}

// ---- Setter
template <typename T>
void IOData::SetValues(const ValueArray<T> values)
{
  // generate
  ValueArray<T>* value_ptr = new ValueArray<T>(values);
  // shared_ptr initialize
  ObjectPtr obj_ptr( dynamic_cast<Object*>(value_ptr) );
  // register
  obj_dict_.push_back(std::make_pair(0, obj_ptr ));
  name_dict_.insert(std::make_pair(obj_ptr->name() ,obj_ptr ));
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //


// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
template void IOData::SetValues(const IntValueArray values);
template void IOData::SetValues(const DoubleValueArray values);
template void IOData::SetValues(const XYZValueArray values);
// template void IOData::SetValues(const ValueArray<bool> value);
#include "mybool.hpp"
template void IOData::SetValues(const BoolValueArray values);


template IntValueArray IOData::values(const std::string name);
template DoubleValueArray IOData::values(const std::string name);
template XYZValueArray IOData::values(const std::string name);

