// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapRegistrationBase.h"
//#include "mapRegistrationDescriptor.h"
#include "mapCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{

		//class RegistrationTestObject: public core::RegistrationBase
		//{
		//public:
		//  typedef RegistrationTestObject Self;
		//  typedef core::RegistrationBase Superclass;
		//  typedef itk::SmartPointer<Self> Pointer;
		//  typedef itk::SmartPointer<const Self> ConstPointer;

		//  itkTypeMacro(RegistrationTestObject,RegistrationBase);

		//  static Pointer New()
		//  {
		//    Pointer smartPtr = new Self();
		//    smartPtr->UnRegister();
		//    return smartPtr;
		//  }

		//   virtual unsigned int getMovingDimensions() const
		//  {
		//    //never used in the test; stub function
		//    return 0;
		//  }

		//  virtual unsigned int getTargetDimensions() const
		//  {
		//    //never used in the test; stub function
		//    return 0;
		//  }
		//
		//protected:
		//  RegistrationTestObject() {};
		//  virtual ~RegistrationTestObject() {};

		//private:
		//  //No copy constructor allowed
		//  RegistrationTestObject(const Self & source);
		//  void operator=(const Self&); //purposely not implemented
		//};



		int mapRegistrationDescriptorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			//RegistrationTestObject::Pointer spReg = RegistrationTestObject::New();
			//bool limitedMoving = true;
			//bool limitedTarget = true;
			//core::RegistrationDescriptor::TagMapType tags;
			//std::string tag = "param1";
			//std::string value = "value1";
			//std::pair<std::string,std::string> taggedValue(tag,value);
			//tags.insert(taggedValue);

			//core::RegistrationDescriptor::Pointer spDescriptor;
			//
			//CHECK_NO_THROW(spDescriptor = core::RegistrationDescriptor::New(spReg,tags,limitedMoving,limitedTarget));

			//CHECK_EQUAL(spReg,spDescriptor->getRegistration());
			//CHECK_EQUAL(limitedMoving,spDescriptor->hasLimitedMovingRepresentation());
			//CHECK_EQUAL(limitedTarget,spDescriptor->hasLimitedTargetRepresentation());

			//std::string foundValue = "";
			//CHECK_NO_THROW(spDescriptor->getTagValue(tag,foundValue));
			//CHECK_EQUAL(value,foundValue);

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
