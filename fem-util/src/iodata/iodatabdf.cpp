//----------------------------------------------------------------------
/**
   @file iodatabdf.cpp
   @brief BDF入出力
   
   @author Shibata
   @date 2015-02-12(木) 12:16:24
   
***********************************************************************/

#include "iodata.hpp"

#include <fstream>		// fstream
#include <boost/format.hpp>	// format

#include "tool.hpp"		// split


using std::cout;
using std::endl;

/*--------------------------------------------------------------------*
  Import Section
 *--------------------------------------------------------------------*/
void IOData::ImportBdf(const std::string filename, const Fmt fmt)
  throw(tool::IOError)
{
  cout << endl << endl;
  cout << "## IOData::ImportBdf ##" << endl;

  // read and check
  std::ifstream ifs( filename.c_str() );
  if(ifs.fail()){
    BOOST_THROW_EXCEPTION( tool::IOError("Cannot Open File!") );
  }

  std::stringstream ss;
  ConvertFmtBdf(ifs, fmt, ss);
  
  
  // initialize mesh
  InitMeshBdf( ss );
  // read mesh
  ReadMeshBdf( ss );

  // information
  Info();
  // register import format type
  default_fmt_ = fmt;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
IOData::BdfCard IOData::GetBdfCard(const std::string& buf)
{
  if( strstr(buf.c_str(), "GRID") ) return IOData::GRID;
  if( strstr(buf.c_str(), "CTRIA3") ) return IOData::CTRIA3;
  if( strstr(buf.c_str(), "CQUAD4") ) return IOData::CQUAD4;
  if( strstr(buf.c_str(), "CTETRA") ) return IOData::CTETRA;
  if( strstr(buf.c_str(), "CHEXA") ) return IOData::CHEXA;
  if( strstr(buf.c_str(), "PSHELL") ) return IOData::PSHELL;
  if( strstr(buf.c_str(), "MAT1") ) return IOData::MAT1;
  return IOData::BLANK;		// default
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
double IOData::ConvertNumBdf(const std::string& buf)
{
  std::string buf_co(buf);
  if     ( buf_co.at(0) == '.' ){
    // buf_co.insert(0, "0");
  }
  else if( buf_co.substr(0,2) == "-." ) {
    // buf_co.insert(1, "0");
  }
  
  if( buf_co.find("E") == std::string::npos ){
    int min_char = 100;
    int end =buf_co.size();
    min_char = ( buf_co.rfind("+", end) != std::string::npos
    		 ? std::min( min_char, static_cast<int>(buf_co.rfind("+", end)) )
    		 : min_char );
    min_char = ( buf_co.rfind("-", end) != std::string::npos
    		 ? std::min( min_char, static_cast<int>(buf_co.rfind("-", end)) )
    		 : min_char );

    if( min_char != 100 && min_char != 0){
      if (std::isdigit ( buf_co.at(min_char-1) )) buf_co.insert(min_char,"E");
    }
  }
  return atof( buf_co.c_str());
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ConvertFmtBdf(std::ifstream& ifs,
			   const Fmt fmt,
			   std::stringstream& ss)
{
  while( !ifs.eof() ){
    std::string buf;
    getline( ifs, buf );
    // remove commentout
    std::string buf_co = buf.substr(0, buf.find( "$", 0) );
    // chenge format and write
    int num = 0;
    switch(fmt){
    case IOData::BDF_SMALL:		// Small Field Format
      switch( GetBdfCard(buf_co) ){
	
      case GRID:
	num = 5;
	break;

      case CTRIA3:
	num = 5;
	break;
	
      case CQUAD4:
	num = 6;
	break;
	
      case CTETRA:
	num = 6;
	break;
	
      case CHEXA:
	buf_co = buf_co.substr(0,72);
	getline(ifs, buf);
	buf_co.insert(72 , buf.substr(8,16) );
	num = 10;
	break;
	
      case PSHELL:
      case MAT1:
      case BLANK:
	buf_co = std::string("");	// empty
	break;
      }
      break;
    
    case IOData::BDF_LARGE:		// Large Field Format
      std::cerr << "ERROR: LARGE is not implimented!" << endl;
      assert(false);
      break;
    
    case IOData::BDF_FREE:		// Free Field Format
      num = 0;
      break;
    default:
      std::cerr << "ERROR: other format is selected!" << std::endl;
      assert(false);
    }
  
    // insert delimiter ","
    for(int i=num*8; i>7; i -= 8){
      buf_co.insert(i, ",");
    }
    // write
    ss << buf_co << endl;
  }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::InitMeshBdf(std::stringstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  int num_nodes=0;
  int num_faces=0;
  int num_cells=0;
  MeshInfo::CellType max_celltype = MeshInfo::TRIA3;

  // ### Count Mesh Elements ###

  // eof flag clear and rewind
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;

    MeshInfo::CellType tmp_celltype = MeshInfo::TRIA3;
    switch( GetBdfCard(head) ){
    case BLANK:
      break;
    case GRID:
      num_nodes += 1;
      break;

    case CTRIA3:
      num_cells += 1;
      tmp_celltype = MeshInfo::TRIA3;
      num_faces += MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLFACES);
      break;
    case CQUAD4:
      num_cells += 1;
      tmp_celltype = MeshInfo::QUAD4;
      num_faces += MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLFACES);
      break;
    case CTETRA:
      num_cells += 1;
      tmp_celltype = MeshInfo::TETRA4;
      num_faces += MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLFACES);
      break;
    case CHEXA:
      num_cells += 1;
      tmp_celltype = MeshInfo::HEXA8;
      num_faces += MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLFACES);
      break;
      
    case PSHELL:
    case MAT1:
      break;
    }

    // check celltype
    if ( max_celltype < tmp_celltype )
      max_celltype = tmp_celltype;
    
  } // end while

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
void IOData::ReadMeshBdf(std::stringstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();

  int inode=0;
  int icell=0;
  // map<node_id,node_index>
  std::map<int,int> id_link;

  // ## READ NODES ------
  ifs.clear();
  ifs.seekg(0, std::ios::beg);

  std::cout << "NODE AND CELL      ...reading";
  while(getline(ifs, buffer)){
    std::string head = buffer.substr(0.2);

    if      ( strstr( head.c_str() , "G") ){
      std::vector<std::string> vs = tool::split(buffer,',');
      
      if(inode >= num_nodes)
	BOOST_THROW_EXCEPTION( tool::IOError("num_nodes Over Size!") );
      if(vs.size() != 6)
	BOOST_THROW_EXCEPTION( tool::IOError("GRID field incorrect!") );
      
      int node_id;
      XYZ tmp_XYZ;
      node_id   = atoi(vs.at(1).c_str()); // field 2
      tmp_XYZ.x = ConvertNumBdf( vs.at(3) ); // field 4
      tmp_XYZ.y = ConvertNumBdf( vs.at(4) ); // field 5
      tmp_XYZ.z = ConvertNumBdf( vs.at(5) ); // field 6

      id_link[node_id] = inode;
      mesh.nodes(inode).SetGrid(tmp_XYZ);
      mesh.nodes(inode).SetID(node_id);
      inode++;
    } // end if G
    
    else if( strstr( head.c_str() , "C") ){
      if(icell >= num_cells)
	BOOST_THROW_EXCEPTION( tool::IOError("num_cells Over Size!") );

      int num_cellnodes;
      MeshInfo::CellType tmp_celltype = MeshInfo::TRIA3;
      switch( GetBdfCard(head) ){
      case CTRIA3:
	tmp_celltype = MeshInfo::TRIA3;
	break;
      case CQUAD4:
	tmp_celltype = MeshInfo::QUAD4;
	break;
      case CTETRA:
	tmp_celltype = MeshInfo::TETRA4;
	break;
      case CHEXA:
	tmp_celltype = MeshInfo::HEXA8;
	break;
      case GRID:
      case BLANK:
      case PSHELL:
      case MAT1:
	std::stringstream error;
	error << "Cannot Recognize CellType No."
	      << (int)tmp_celltype;
	BOOST_THROW_EXCEPTION( tool::IOError(error.str()) );
      }
      num_cellnodes = MeshInfo::GetNumOf(tmp_celltype,MeshInfo::CELLNODES);

      
      std::vector<std::string> vs = tool::split(buffer,',');
      int cell_id = atoi(vs.at(1).c_str()); // field 2

      
      // fitting
      mesh.cells(icell).SetSizeOfNodes(num_cellnodes);
      // set celltype
      mesh.cells(icell).SetCellType(tmp_celltype);
      // set id
      mesh.cells(icell).SetID( cell_id );

      if(vs.size() != (size_t)(3+num_cellnodes))
	BOOST_THROW_EXCEPTION( tool::IOError("ERROR: field incorrect!") );

      int inode=-1;
      int node_id=-1;
      for(int jnode=0; jnode<num_cellnodes; jnode++){
	node_id = atoi(vs.at(jnode+3).c_str());
	inode = id_link[node_id];
	
	// linking
	mesh.cells(icell).SetNodePtr(jnode, &(mesh.nodes(inode)) );
      }
      icell++;
    } // end if C
    
  } // end while
  std::cout << "  ...finished" << std::endl;

  // linking
  mesh.Link();
}


/*--------------------------------------------------------------------*
  Export Section
 *--------------------------------------------------------------------*/
void IOData::ExportBdf(const std::string filename)
  throw(tool::IOError)
{
  cout << endl << endl;
  cout << "## IOData::ExportBdf ##" << endl;
  const Mesh& mesh = *mesh_ptr_;

  // mesh CHECK
  mesh.Check();
  // infomation
  Info();

  // OPEN
  std::ofstream ofs( filename.c_str() );

  // ## FREE FORMAT TYPE
  WriteFreeBdf( ofs );
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::WriteFreeBdf(std::ofstream& ofs)
  throw(tool::IOError)
{
  // define
  const Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();

  // ## WRITE HEADER --------
  ofs << "$ written by fem_utility" << endl;
  
  // ## WRITE NODES -------
  cout << "POINTS     ...writing";
  // set format
  boost::format fmt_node("%s,%10d,%6d,%14f,%14f,%14f\n");
  // write header
  ofs << "$" << endl;
  ofs << "$ MODEL" << endl;
  ofs << "$" << endl;
  // write data
  for(int inode=0; inode<num_nodes; inode++){
    const XYZ tmp_grid = mesh.nodes(inode).grid();
    fmt_node % "GRID" % (inode+1); // [0~n-1] -> [1~n]
    fmt_node % 0;
    fmt_node % (float)tmp_grid.x % (float)tmp_grid.y % (float)tmp_grid.z;
    ofs << fmt_node;
  }
  cout << "  ...finished" << endl;

  // ## WRITE CELLS -------
  cout << "CELLS      ...writing";
  // set format
  boost::format fmt_cell_head("%s,%10d,%6d");
  boost::format fmt_cell_foot(",  %3.1f,  %3.1f,  %3.1f\n");
  // write
  for(int icell=0; icell<num_cells; icell++){
    int num_cellnodes = mesh.cells(icell).node_ptrs().size();
    MeshInfo::CellType celltype = mesh.cells(icell).celltype();

    fmt_cell_head % MeshInfo::GetBdfCellName( celltype );
    fmt_cell_head % (icell+1);	// [0~n-1] -> [1~n]
    fmt_cell_head % 1000;
    ofs << fmt_cell_head;
    
    for(int jnode=0; jnode<num_cellnodes; jnode++){
      int inode = mesh.cells(icell).nodes(jnode).index();
      ofs << ",  " << (inode+1); // [0~n-1] -> [1~n]
    }
    
    fmt_cell_foot % 0.0 % 1.0 % 0.0;
    ofs << fmt_cell_foot;
  }
  cout << "  ...finished" << endl;

  ofs << "$" << endl;
  ofs << "ENDDATA" << endl;
}
