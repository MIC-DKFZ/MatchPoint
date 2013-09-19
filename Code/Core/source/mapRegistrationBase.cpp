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

#include "mapRegistrationBase.h"

#include "gdcmUIDGenerator.h"

/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
	namespace core
	{

		// **** protected methods ****
		// ***************************
		RegistrationBase::
		RegistrationBase()
		{
			_tags.clear();
			ensureRegistrationUID();
		}

		RegistrationBase::
		~RegistrationBase()
		{
		}

		void
		RegistrationBase::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "MovingDimensions: " << this->getMovingDimensions() << std::endl;
			os << indent << "TargetDimensions: " << this->getTargetDimensions() << std::endl;
			// tags
			os << indent << "Registration tags: " << std::endl;
			TagMapType::const_iterator iter;
			iter = _tags.begin();
			itk::Indent indent2 = indent.GetNextIndent();

			while (iter != _tags.end())
			{
				os << indent2 << iter -> first << ": " << iter -> second << std::endl;
				++iter;
			}

			os << std::endl;
		}

		const RegistrationBase::TagMapType&
		RegistrationBase::
		getTags() const
		{
			return _tags;
		}

		bool
		RegistrationBase::
		getTagValue(const TagType& tag, ValueType& value) const
		{
			bool retval = false;
			TagMapType::const_iterator iter;
			iter = _tags.find(tag);

			if (iter != _tags.end())  // found one element
			{
				value = iter -> second;
				retval = true;
			}

			return retval;
		}

		void
		RegistrationBase::
		setTagValues(const RegistrationBase::TagMapType& tags)
		{
			TagMapType tempTags = tags;

			ValueType uid = getRegistrationUID();

			TagMapType::const_iterator iter;
			iter = tempTags.find(map::tags::RegistrationUID);

			if (iter == tempTags.end()) //found nothing
			{
				tempTags.insert(std::make_pair(map::tags::RegistrationUID, uid));
			}

			_tags = tempTags;
			this->Modified();
		};

		RegistrationBase::TagMapType&
		RegistrationBase::
		getTagValues()
		{
			return _tags;
		};

		RegistrationBase::ValueType
		RegistrationBase::
		getRegistrationUID() const
		{
			ValueType result;
			bool valid = getTagValue(tags::RegistrationUID, result);
			assert(valid);
			return result;
		};

		void
		RegistrationBase::
		ensureRegistrationUID()
		{
			String uid;

			if (!getTagValue(tags::RegistrationUID, uid))
			{
				gdcm::UIDGenerator uidGenerator;
				uid = uidGenerator.Generate();

				/*@TODO check how a prefix is defined, what the prefix for DKFZ would be to define a MatchPoint default prefix*/
				//String prefix = String(MatchPoint_REGISTRATION_UID_PREFIX);
				_tags.insert(std::make_pair(tags::RegistrationUID, uid));
			}
		};

	}
}
