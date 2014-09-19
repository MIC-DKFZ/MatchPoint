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

#ifndef __DIRECT_FIELD_POLICY_TPP
#define __DIRECT_FIELD_POLICY_TPP

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		setField(FieldType& field)
		{
			_spField = &field;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		PreCachedFieldPolicy() : _spField(NULL)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		~PreCachedFieldPolicy()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		checkAndPrepareField() const
		{
			return _spField.IsNotNull();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		getRepresentationDescriptor() const
		{
			assert(_spField.IsNotNull());
      if(_spField.IsNull())
      {
        mapDefaultExceptionStaticMacro(<<"Error. Cannot get representation descriptor in PreCachedFieldPolicy. Field is not set");
      }

			RepresentationDescriptorConstPointer spRepresentation = createFieldRepresentation(
						*_spField).GetPointer();
			return spRepresentation;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		PreCachedFieldPolicy<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			if (_spField.IsNotNull())
			{
				os << indent << "Field : " << std::endl << _spField << std::endl;
			}
			else
			{
				os << indent << "Field : NULL" << std::endl;
			}
		};

	} // end namespace core
} // end namespace map

#endif
