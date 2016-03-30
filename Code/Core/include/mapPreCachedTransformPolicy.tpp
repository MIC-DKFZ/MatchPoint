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
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
		setTransform(TransformType* transform)
		{
        _spTransform = transform;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
        PreCachedTransformPolicy() : _spTransform(NULL), _nullVector(
        ::itk::NumericTraits< typename MappingVectorType::ValueType >::NonpositiveMin()),
        _useNullVector(false)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
		~PreCachedTransformPolicy()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
		checkAndPrepareTransform() const
		{
			return _spTransform.IsNotNull();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
		getRepresentationDescriptor() const
		{
			assert(_spTransform.IsNotNull());

			if (_spTransform.IsNull())
			{
				mapDefaultExceptionStaticMacro( <<
												"Error. Cannot get representation descriptor in PreCachedTransformPolicy. Transform is not set");
			}

			RepresentationDescriptorConstPointer spRepresentation = createTransformRepresentation(
						*_spTransform).GetPointer();
			return spRepresentation;
		};

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    const typename PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::MappingVectorType&
        PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
        doGetNullVector() const
    {
        return _nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    bool
        PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
        doUsesNullVector() const
    {
        return _useNullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
        setNullVector(const MappingVectorType& nullVector)
    {
        _nullVector = nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
        setNullVectorUsage(bool use)
    {
        _useNullVector = use;
    };

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		PreCachedTransformPolicy<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			if (_spTransform.IsNotNull())
			{
				os << indent << "Transform : " << std::endl << _spTransform << std::endl;
			}
			else
			{
				os << indent << "Transform : NULL" << std::endl;
			}

      os << indent << "Use null vector: " << _useNullVector << std::endl;
      os << indent << "Null vector: " << this->_nullVector << std::endl;
		};

	} // end namespace core
} // end namespace map

#endif
