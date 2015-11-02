//----------------------------------------------------------------------
/**
   @file iodatavtk.cpp
   @brief VTK入出力
   
   @author Shibata
   @date 2014-12-20(土) 17:33:25
   
***********************************************************************/

#include "iodata.hpp"

#include <string.h>		// strstr
#include <sstream>		// stringstream
#include <iostream>		// string
#include <iomanip>		// setw, uppercase, etc.
#include <fstream>		// fstream
#include <map>			// map
#include <boost/format.hpp>	// format


#include "tool.hpp"		// trim





/*--------------------------------------------------------------------*
  Import Section
 *--------------------------------------------------------------------*/
void IOData::ImportVtk(const std::string filename)
  throw(tool::IOError)
{
  std::cout << std::endl << std::endl;
  std::cout << "## IOData::ImportVtk ##" << std::endl;

  // read and check
  std::ifstream ifs( filename.c_str() );
  if(ifs.fail()){
    BOOST_THROW_EXCEPTION( tool::IOError("Cannot Open File!") );
  }
  
  // initialize mesh
  InitMeshVtk( ifs );
  // read mesh
  ReadMeshVtk( ifs );
  // read value
  ReadValueVtk( ifs );

  // information
  Info();
  // register import format type
  default_fmt_ = VTK;
}






// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::InitMeshVtk(std::ifstream &ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  int num_nodes=0;
  int num_faces=0;
  int num_cells=0;
  MeshInfo::CellType max_celltype = MeshInfo::TRIA3;
  
  // ### Count Mesh Elements ###
  // define
  bool read_nodes=false;
  bool read_cells=false;
  bool read_types=false;

  // eof flag clear and rewind
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;

    // Check Dataset
    if( strstr( head.c_str() , "DATASET") ){
      if( !strstr( buffer.c_str() , "UNSTRUCTURED_GRID") ){
	BOOST_THROW_EXCEPTION
	  ( tool::IOError("File Format is not UNSTRUCTURED_GRID !") );
      }

      
      // Count Nodes
    }else if( strstr( head.c_str() , "POINTS")){
      headline >> num_nodes;
      // read flag
      read_nodes=true;

      
      // Count Cells
    }else if( strstr( head.c_str() , "CELLS")){
      headline >> num_cells;
      // read flag
      read_cells=true;

      
      // Count Faces and Check max_celltype
    }else if(strstr( head.c_str() , "CELL_TYPES")){

      int tmp_i;
      MeshInfo::CellType tmp_celltype;
      for(int icell=0; icell<num_cells; icell++){
	ifs >> tmp_i;
	
	if      ( tmp_i == 5  ){ // TRIA3
	  tmp_celltype = MeshInfo::TRIA3;
	}else if( tmp_i == 9  ){ // QUAD4
	  tmp_celltype = MeshInfo::QUAD4;
	}else if( tmp_i == 10 ){ // TETRA4
	  tmp_celltype = MeshInfo::TETRA4;
	}else if( tmp_i == 12 ){ // HEXA8
	  tmp_celltype = MeshInfo::HEXA8;
	}else{
	  std::stringstream error;
	  error << "Cannot Recognize CellType No."
		<< tmp_i;
	  BOOST_THROW_EXCEPTION( tool::IOError(error.str()) );
	}
	  
	// check celltype
	if ( max_celltype < tmp_celltype )
	  max_celltype = tmp_celltype;
	// count num_faces
	num_faces += MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLFACES);
      }
      // read flag
      read_types=true;
      
    } // endif
  } // endwhile

  
  // error information
  if( !read_nodes )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_nodes!") );
  if( !read_cells )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_cells!") );
  if( !read_types )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_celltypes!") );

  // ### Init ###
  Init(num_nodes, num_faces, num_cells, max_celltype);
    
// #ifndef NDEBUG
//     // information
//     std::cout << "NUM_NODES    : " << num_nodes << std::endl;
//     std::cout << "NUM_FACES    : " << num_faces << std::endl;
//     std::cout << "NUM_CELLS    : " << num_cells << std::endl;
//     std::cout << "MAX_CELLTYPE : " << max_celltype << std::endl;
// #endif
}






// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ReadMeshVtk(std::ifstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();
  
  
  // ### Read Mesh Elements ###
  // define
  bool read_nodes=false;
  bool read_cells=false;
  bool read_types=false;

  
  // ## READ NODES ------
  ifs.clear();
  ifs.seekg(0, std::ios::beg);

  while(getline(ifs, buffer)){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;
    
    if( strstr( head.c_str() , "POINTS") ){
      std::cout << "POINTS     ...reading";

      for(int inode=0; inode<num_nodes; inode++){
	XYZ tmp_grid;
      	ifs >> tmp_grid.x;
	ifs >> tmp_grid.y;
	ifs >> tmp_grid.z;
	mesh.nodes(inode).SetGrid(tmp_grid);
	mesh.nodes(inode).SetID(inode);
      }
      read_nodes=true;
      std::cout << "  ...finished" << std::endl;
    }
  }
  
  // ## READ CELLS -------
  ifs.clear();
  ifs.seekg(0, std::ios::beg);

  while(getline(ifs, buffer)){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;
      
    if( strstr( head.c_str() , "CELLS") ){
      std::cout << "CELLS      ...reading";

      int num_cellnodes;
      for(int icell=0; icell<num_cells; icell++){
	ifs >> num_cellnodes;
	// fitting
	mesh.cells(icell).SetSizeOfNodes(num_cellnodes);
	// set id
	mesh.cells(icell).SetID(icell);

	int inode;
	for(int jnode=0; jnode<num_cellnodes; jnode++){
	  ifs >> inode;

	  if(inode >= num_nodes)
	  BOOST_THROW_EXCEPTION( tool::IOError("num_nodes Over Size!") );
	  
	  // linking
	  mesh.cells(icell).SetNodePtr(jnode, &(mesh.nodes(inode)) );
	}
      }
      read_cells=true;
      std::cout << "  ...finished" << std::endl;
    }
  }

  // ## READ CELLTYPES -------
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while(getline(ifs, buffer)){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;
      
    if( strstr( head.c_str() , "CELL_TYPES") ){
      std::cout << "CELL_TYPES ...reading";

      int tmp_i;
      MeshInfo::CellType tmp_celltype;
      for(int icell=0; icell<num_cells; icell++){
	ifs >> tmp_i;

	if      ( tmp_i == 5  ){ // TRIA3
	  tmp_celltype = MeshInfo::TRIA3;
	}else if( tmp_i == 9  ){ // QUAD4
	  tmp_celltype = MeshInfo::QUAD4;
	}else if( tmp_i == 10 ){ // TETRA4
	  tmp_celltype = MeshInfo::TETRA4;
	}else if( tmp_i == 12 ){ // HEXA8
	  tmp_celltype = MeshInfo::HEXA8;
	}else{
	  std::stringstream error;
	  error << "Cannot Recognize CellType No."
		<< tmp_i;
	  BOOST_THROW_EXCEPTION( tool::IOError(error.str()) );
	}
	// set celltype
	mesh.cells(icell).SetCellType(tmp_celltype);
      }
      read_types=true;
      std::cout << "  ...finished" << std::endl;
    }
  }

  // error information
  if( !read_nodes )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_nodes!") );
  if( !read_cells )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_cells!") );
  if( !read_types )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_celltypes!") );

  // linking
  mesh.Link();
}






// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ReadValueVtk(std::ifstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();


  // ### Read Data ###
  // define
  bool read_scalars = false;
  bool read_vectors = false;
  
  
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while(getline(ifs, buffer)){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;
    
    std::string name;
    std::string waste;
    int num_values;
    Object tmp_obj;
    
    if      ( strstr( head.c_str() , "POINT_DATA" ) ){
      // num_values check
      headline >> num_values;
      if ( num_values != num_nodes ){
	BOOST_THROW_EXCEPTION
	  ( tool::IOError("NUM_POINT_DATA != NUM_POINTS") );
      }
      // set value info
      tmp_obj.SetDataType( Object::NODE );
      
    }else if( strstr( head.c_str() , "CELL_DATA") ){
      // num_values check
      headline >> num_values;
      if ( num_values != num_cells ){
	BOOST_THROW_EXCEPTION
	  ( tool::IOError("NUM_CELL_DATA != NUM_CELLS") );
      }
      // set value info
      tmp_obj.SetDataType( Object::CELL );
      
    }else if( strstr( head.c_str() , "SCALARS") ){
      read_scalars = true;
      read_vectors = false;
      headline >> name;		// get name
      headline >> waste;	// waste float/double
      getline(ifs, buffer);	// waste LOOKUP_TABLE

      // set value info
      tmp_obj.SetName( name );
      tmp_obj.SetValueType( Object::DOUBLE );
      
    }else if( strstr( head.c_str() , "VECTORS") ){
      read_scalars = false;
      read_vectors = true;
      headline >> name;		// get name
      headline >> waste;	// waste float/double

      // set value info
      tmp_obj.SetName( name );
      tmp_obj.SetValueType( Object::XYZ );
    }

    
    if      ( read_scalars ){	// ## READ SCALARS -------
      std::cout << "SCALARS    ...reading";
      
      DoubleValueArray tmp_values( num_values, 0.0, tmp_obj);

      double scalar;
      for(int ivalue=0; ivalue<num_values; ivalue++){
	ifs >> scalar;
	tmp_values.SetValue(ivalue, scalar);
      }
      // set to object dictionary
      SetValues( tmp_values );

      // end processing
      std::cout << "  ...finished" << std::endl;
      read_scalars = false;


      
    }else if( read_vectors ){	// ## READ VECTORS -------
      std::cout << "VECTORS    ...reading";

      XYZValueArray tmp_values(num_values, XYZ(0,0,0), tmp_obj);

      XYZ vector;
      for(int ivalue=0; ivalue<num_values; ivalue++){
	ifs >> vector.x;
	ifs >> vector.y;
	ifs >> vector.z;
	tmp_values.SetValue(ivalue, vector);
      }
      
      // set to object dictionary
      SetValues( tmp_values );

      // end processing
      std::cout << "  ...finished" << std::endl;
      read_vectors = false;
    }
  }
    
}






/*--------------------------------------------------------------------*
  Export Section
 *--------------------------------------------------------------------*/
void IOData::ExportVtk(const std::string filename)
  throw(tool::IOError)
{
  std::cout << std::endl << std::endl;
  std::cout << "## IOData::ExportVtk ##" << std::endl;

  // define
  const Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();

  // mesh CHECK
  mesh.Check();
  // information
  Info();
  
  // OPEN
  std::ofstream ofs( filename.c_str() );

  
  // ## WRITE HEADER --------
  ofs << "# vtk DataFile Version 3.0" << std::endl;
  ofs << "output vtk" << std::endl;
  ofs << "ASCII" << std::endl;
  ofs << "DATASET UNSTRUCTURED_GRID" << std::endl;
  
  
  // ## WRITE NODES --------
  std::cout << "POINTS     ...writing";
  // set format
  boost::format fmt_node("%14E  %14E  %14E\n");
  // header
  ofs << "POINTS        "
      << num_nodes
      << " float" << std::endl;
  // write node
  for(int inode=0; inode<num_nodes; inode++){
    const XYZ tmp_grid = mesh.nodes(inode).grid();
    
    fmt_node % (float)tmp_grid.x % (float)tmp_grid.y % (float)tmp_grid.z;
    ofs << fmt_node;
    // ofs << std::fixed << std::scientific << std::uppercase
    // 	<< std::setw(15) << std::right
    // 	<< (float)tmp_grid.x << "  "
    // 	<< (float)tmp_grid.y << "  "
    // 	<< (float)tmp_grid.z << std::endl;
  }
  std::cout << "  ...finished" << std::endl;


  
  // ## WRITE CELLS --------
  std::cout << "CELLS      ...writing";
  // count num_cellsdata
  int num_cellsdata=0;
  for(int icell=0; icell<num_cells; icell++){
    num_cellsdata = num_cellsdata + 1; // header
    num_cellsdata = num_cellsdata + mesh.cells(icell).node_ptrs().size();
  }
  // write cell pointer
  ofs << "CELLS         "
      << num_cells << "     "
      << num_cellsdata << std::endl;
  for(int icell=0; icell<num_cells; icell++){
    int num_cellnodes = mesh.cells(icell).node_ptrs().size();
    ofs << "  " << num_cellnodes;
    for(int jnode=0; jnode<num_cellnodes; jnode++){
      int inode = mesh.cells(icell).nodes(jnode).index();
      ofs << "  " << inode;
    }
    ofs << std::endl;
  }
  std::cout << "  ...finished" << std::endl;


  
  // ## WRITE CELL_TYPES ------
  std::cout << "CELL_TYPES ...writing";
  ofs << "CELL_TYPES       "
      << num_cells << std::endl;
  for(int icell=0; icell<num_cells; icell++){
    ofs << "  " << mesh.cells(icell).celltype() << std::endl;
  }
  std::cout << "  ...finished" << std::endl;


  // if NO VALUE
  if ( obj_dict_.size() == 0 )
    return;

  // ## SORT VALUES   -------- 
  // define
  typedef std::multimap< int, ObjectPtr > SortDict;
  SortDict sort_dict;
  enum SortType{
    POINT_SCALARS = 1,
    POINT_VECTORS = 2,
    CELL_SCALARS  = 3,
    CELL_VECTORS  = 4,
  };
  // sorting
  for(ObjectDict::iterator itl = obj_dict_.begin();
      itl != obj_dict_.end();
      ++itl){
    
    const ObjectPtr obj_ptr            = (*itl).second;
    const Object::DataType datatype   = (*obj_ptr).datatype();
    const Object::ValueType valuetype = (*obj_ptr).valuetype();

    bool writable=true;
    bool is_point=false;
    bool is_scalars=false;
    SortType sort_type;

    switch(datatype){
    case Object::NODE:
      is_point=true;
      break;
    case Object::CELL:
      is_point=false;
      break;
    default:
      writable=false;
    }
    
    switch(valuetype){
    case Object::INT:
    case Object::DOUBLE:
    case Object::BOOL:
      is_scalars=true;
      break;
    case Object::XYZ:
      is_scalars=false;
      break;
    default:
      writable=false;
    }
    
    if      ( is_point && is_scalars   ){
      sort_type = POINT_SCALARS;
    }else if( is_point && !is_scalars  ){
      sort_type = POINT_VECTORS;
    }else if( !is_point && is_scalars  ){
      sort_type = CELL_SCALARS;
    }else if( !is_point && !is_scalars ){
      sort_type = CELL_VECTORS;
    }

    if( writable )
      sort_dict.insert( std::make_pair( (int)sort_type, obj_ptr ));
  }


  
  // ## WRITE VALUES  --------
  // define
  bool point_writing = false;
  bool cell_writing  = false;
  int num_values=0;
  // write
  for(SortDict::iterator itl = sort_dict.begin();
      itl != sort_dict.end();
      ++itl){
    ObjectPtr obj_ptr = (*itl).second;
    std::cout << obj_ptr->name() << " ...writing";

    // writing header
    if      ( !point_writing &&
	      obj_ptr->datatype() == Object::NODE ){
      ofs << "POINT_DATA   " << num_nodes << std::endl;
      num_values=num_nodes;
      point_writing = true;
    }else if( !cell_writing &&
	      obj_ptr->datatype() == Object::CELL ){
      ofs << "CELL_DATA   " << num_cells << std::endl;
      num_values=num_nodes;
      cell_writing = true;
    }

    // writing values
    if      ( obj_ptr->valuetype() == Object::INT ){
      ofs << "SCALARS  " << obj_ptr->name() << "  float" << std::endl;
      ofs << "LOOKUP_TABLE default" << std::endl;
      IntValueArray values = *dynamic_cast<IntValueArray*>(obj_ptr.get());
      if( num_values != (int)values.size() ){
	BOOST_THROW_EXCEPTION( tool::IOError("Data Mismatch!") );
      }

      for(int ival=0; ival<num_values; ival++){
	double value = values[ival];
	ofs << "  " << value << std::endl;
      }
      
    }else if( obj_ptr->valuetype() == Object::DOUBLE ){
      ofs << "SCALARS  " << obj_ptr->name() << "  float" << std::endl;
      ofs << "LOOKUP_TABLE default" << std::endl;
      DoubleValueArray values = *dynamic_cast<DoubleValueArray*>(obj_ptr.get());
      if( num_values != (int)values.size() ){
	BOOST_THROW_EXCEPTION( tool::IOError("Data Mismatch!") );
      }

      for(int ival=0; ival<num_values; ival++){
	double value = values[ival];
	ofs << "  " << value << std::endl;
      }
      
    }else if( obj_ptr->valuetype() == Object::BOOL ){
      ofs << "SCALARS  " << obj_ptr->name() << "  float" << std::endl;
      ofs << "LOOKUP_TABLE default" << std::endl;
      BoolValueArray values = *dynamic_cast<BoolValueArray*>(obj_ptr.get());
      if( num_values != (int)values.size() ){
	BOOST_THROW_EXCEPTION( tool::IOError("Data Mismatch!") );
      }

      for(int ival=0; ival<num_values; ival++){
	double value = values[ival];
	ofs << "  " << value << std::endl;
      }
      
    }else if( obj_ptr->valuetype() == Object::XYZ ){
      ofs << "VECTORS  " << obj_ptr->name() << "  float" << std::endl;
      XYZValueArray values = *dynamic_cast<XYZValueArray*>(obj_ptr.get());
      if( num_values != (int)values.size() ){
	BOOST_THROW_EXCEPTION( tool::IOError("Data Mismatch!") );
      }

      for(int ival=0; ival<num_values; ival++){
	XYZ value = values[ival];
	ofs << "  "
	    << value.x << "  "
	    << value.y << "  "
	    << value.z << std::endl;
      }
      
    }
    std::cout << "  ...finished" << std::endl;
  }
}
