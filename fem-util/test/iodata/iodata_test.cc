//----------------------------------------------------------------------
/**
   @file iodata_test.cc
   @brief Iodata Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 15:10:54
   
***********************************************************************/

#include "iodata.hpp"
#include "gtest/gtest.h"

TEST(IOData, DefaultConstructor){
  IOData iodata;
}

// VTK Test
TEST(IODataVtk, IOTest){
  IOData iodata;

  try{
  // first import
  iodata.ImportVtk("import.vtk");
  // second import
  iodata.ImportVtk("import.vtk");
  // export
  iodata.ExportVtk("export.vtk");

  EXPECT_TRUE(true);
  
  }catch(const tool::MyException& e){
    std::cerr << e.what() << std::endl;
    EXPECT_TRUE(false);
  }
  
}


// FEAP Test
TEST(IODataFea, IOTest){
  IOData iodata;

  try{
  // first import
  iodata.ImportFea("import.fea");
  // second import
  iodata.ImportFea("import.fea");
  // export
  iodata.ExportFea("export.fea");

  EXPECT_TRUE(true);
  
  }catch(const tool::MyException& e){
    std::cerr << e.what() << std::endl;
    EXPECT_TRUE(false);
  }
  
}


// BDF Test
TEST(IODataBdf, IOTest){
  IOData iodata;

  try{
    // first import
    iodata.ImportBdf("import.bdf", IOData::BDF_FREE);
    // second import
    iodata.ImportBdf("import.bdf", IOData::BDF_FREE);
    // small field fmt import
    iodata.ImportBdf("smallfmt.bdf", IOData::BDF_SMALL);
    // export
    iodata.ExportBdf("export.bdf");
    
    EXPECT_TRUE(true);
  
  }catch(const tool::MyException& e){
    std::cerr << e.what() << std::endl;
    EXPECT_TRUE(false);
  }
  
}


