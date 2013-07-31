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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapPreCachedFieldPolicy.h $
*/

#ifndef __DIRECT_FIELD_POLICY_H
#define __DIRECT_FIELD_POLICY_H

#include "mapRegistrationTopology.h"

namespace map
{
	namespace core
	{

		/*! @class PreCachedFieldPolicy
		    @brief class for PreCachedFieldPolicy.

		    This class is the class for the PreCachedFieldPolicy.
		    @ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class PreCachedFieldPolicy
		{
		public:
			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType FieldType;


			/*! sets a field
			  @eguarantee no fail
			  @param field the field that shall be set
			*/
			void setField(FieldType &field);

		protected:
			PreCachedFieldPolicy();
			~PreCachedFieldPolicy();

			typedef typename FieldType::Pointer FieldPointer;
			FieldPointer _spField;

			/*! checks the field that has been set for correctness and prepares(?) it
			  @eguarantee strong
			  @return the success of the operation
			*/
			bool checkAndPrepareField() const;

			typedef FieldRepresentationDescriptor<VInputDimensions> RepresentationDescriptorType;
			typedef typename RepresentationDescriptorType::ConstPointer  RepresentationDescriptorConstPointer;
			/* Generates the representation descriptor according to the _spField.
			 @pre _spField must not be null
			 @return Smart pointer to the representation descriptor
			*/
			RepresentationDescriptorConstPointer getRepresentationDescriptor() const;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

		private:
			//No copy constructor allowed
			PreCachedFieldPolicy(const PreCachedFieldPolicy &);
			void operator=(const PreCachedFieldPolicy &); //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapPreCachedFieldPolicy.tpp"
#endif

#endif
