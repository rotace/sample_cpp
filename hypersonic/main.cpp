
#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

#include <CUI.hpp>


int main(int argc, char *argv[])
{
  
  CUI theCUI;

  cout << "If you want to know how to use it, please type [help]" << endl;

  while(theCUI.DoCommand() != -1);
  
  return 0;
}
