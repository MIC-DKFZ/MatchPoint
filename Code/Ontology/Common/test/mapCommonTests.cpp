// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------


// this file defines the mapCommonTests for the test driver
// and all it expects is that you have a function called RegisterTests
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "litMultiTestsMain.h" 
#include <iostream>

namespace iro
{
  namespace testing
  {
    void registerTests()
    {
      LIT_REGISTER_TEST(mapOntologyResultTest);
    }
  }
}

  int main(int argc, char* argv[])
  {
    int result = 0;

    iro::testing::registerTests();

    try
    {
      result = lit::multiTestsMain(argc,argv);
    }
    catch(...)
    {
      std::cerr << "MatchPoint test driver caught an unknown exception!!!\n";
      result = -1;
    }

    return result;
  }
