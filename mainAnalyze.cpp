#include "analyze.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  Analyze a;
  string location = "";
  if(argc == 2)
  {
    location = argv[1];
  }
  a.readFile(location);
  a.outputError();
  return 0;
}
