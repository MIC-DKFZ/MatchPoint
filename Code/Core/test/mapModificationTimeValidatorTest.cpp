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

#include "mapModificationTimeValidator.h"
#include "litCheckMacros.h"

#include <stdlib.h>

namespace map
{
	namespace testing
	{
		/** Helper class that mimics an object with a different modification time context*/
		class OffContextObject : public ::itk::Object
		{
		public:
			typedef OffContextObject Self;
			typedef ::itk::Object  Superclass;
			typedef ::itk::SmartPointer<Self>        Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;
			itkTypeMacro(OffContextObject, ::itk::Object);
			itkFactorylessNewMacro(Self);

			virtual unsigned long GetMTime() const
			{
				return _offContextMTime;
			};

			virtual void Modified() const
			{
				_offContextMTime++;
			};

			OffContextObject()
			{
				_offContextMTime = 0;
			};

			~OffContextObject() {};

			mutable unsigned long _offContextMTime;
		};

		int mapModificationTimeValidatorTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			::itk::TimeStamp contextRefTS;

			::itk::Object::Pointer spInContextObj = ::itk::Object::New();
			OffContextObject::Pointer spOffContextObj = OffContextObject::New();
			::itk::Object::Pointer spInContextObj2 = ::itk::Object::New();
			OffContextObject::Pointer spOffContextObj2 = OffContextObject::New();

			//check constructors
			core::ModificationTimeValidator mtv;
			CHECK_EQUAL(contextRefTS.GetMTime(), mtv.getMTime());

			core::ModificationTimeValidator mtv2(NULL);
			CHECK_EQUAL(contextRefTS.GetMTime(), mtv2.getMTime());

			core::ModificationTimeValidator mtv3(spInContextObj);
			unsigned long lastTS_MTV3 = mtv3.getMTime();
			CHECK(contextRefTS.GetMTime() < lastTS_MTV3);

			//check setter (NULL before);
			mtv.setWatchedObject(spInContextObj);
			unsigned long lastTS_MTV = mtv.getMTime();
			CHECK(contextRefTS.GetMTime() < lastTS_MTV);

			////////////////////////////////////////
			// Check in context handling (using same time stamp)

			//check setter when using same obj
			mtv3.setWatchedObject(spInContextObj);
			CHECK_EQUAL(lastTS_MTV3, mtv3.getMTime());

			//check setter when using same obj
			mtv3.setWatchedObject(spInContextObj);
			CHECK_EQUAL(lastTS_MTV3, mtv3.getMTime());

			//check setter when using different obj
			mtv3.setWatchedObject(spInContextObj2);
			CHECK(lastTS_MTV3 < mtv3.getMTime());
			lastTS_MTV3 = mtv3.getMTime();

			//check getter when object is modified
			spInContextObj2->Modified();
			CHECK(lastTS_MTV3 < mtv3.getMTime());


			////////////////////////////////////////
			// Check "off context handling" (external time stamp is higher)

			spOffContextObj->_offContextMTime = 2000;
			spOffContextObj2->_offContextMTime = 2020;
			contextRefTS.Modified();

			//check setter when using same obj
			mtv.setWatchedObject(spOffContextObj);
			lastTS_MTV = mtv.getMTime();
			CHECK(contextRefTS < lastTS_MTV);

			//check setter when using same obj
			mtv.setWatchedObject(spOffContextObj);
			CHECK_EQUAL(lastTS_MTV, mtv.getMTime());

			//check setter when using different obj
			mtv.setWatchedObject(spOffContextObj2);
			CHECK(lastTS_MTV < mtv.getMTime());
			lastTS_MTV = mtv.getMTime();

			//check getter when object is modified
			spOffContextObj2->Modified();
			CHECK(lastTS_MTV < mtv.getMTime());

			////////////////////////////////////////
			// Check "off context handling" (external time stamp is lower)

			spOffContextObj->_offContextMTime = 0;
			spOffContextObj2->_offContextMTime = 1;
			contextRefTS.Modified();

			//check setter when using same obj
			mtv.setWatchedObject(spOffContextObj);
			lastTS_MTV = mtv.getMTime();
			CHECK(contextRefTS < lastTS_MTV);

			//check setter when using same obj
			mtv.setWatchedObject(spOffContextObj);
			CHECK_EQUAL(lastTS_MTV, mtv.getMTime());

			//check setter when using different obj
			mtv.setWatchedObject(spOffContextObj2);
			CHECK(lastTS_MTV < mtv.getMTime());
			lastTS_MTV = mtv.getMTime();

			//check getter when object is modified
			spOffContextObj2->Modified();
			CHECK(lastTS_MTV < mtv.getMTime());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
