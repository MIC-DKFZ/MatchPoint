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

#ifndef __PRE_CACHED_TRANSFORM_POLICY_H
#define __PRE_CACHED_TRANSFORM_POLICY_H

#include "mapRegistrationTopology.h"

namespace map
{
	namespace core
	{

		/*! @class PreCachedTransformPolicy
		    @brief class for PreCachedTransformPolicy.

		    This class is the class for the PreCachedTransformPolicy.
		    @ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class PreCachedTransformPolicy
		{
		public:
      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectTransformType TransformType;

      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
          MappingVectorType;


			/*! sets the transform
			  @eguarantee no fail
			  @param transform the transform that shall be set
			*/
      void setTransform(TransformType* transform);

      void setNullVector(const MappingVectorType& nullVector);

      void setNullVectorUsage(bool use);

		protected:
			PreCachedTransformPolicy();
			~PreCachedTransformPolicy();

      typedef typename TransformType::Pointer TransformPointer;
      TransformPointer _spTransform;

      MappingVectorType _nullVector;
      bool _useNullVector;

			/*! checks the transform that has been set for correctness and prepares(?) it
			  @eguarantee strong
			  @return the success of the operation
			*/
			bool checkAndPrepareTransform() const;

      const MappingVectorType& doGetNullVector() const;

      bool doUsesNullVector() const;

			typedef FieldRepresentationDescriptor<VInputDimensions> RepresentationDescriptorType;
			typedef typename RepresentationDescriptorType::ConstPointer  RepresentationDescriptorConstPointer;
			/* Generates the representation descriptor according to the _spTransform.
			 @pre _spTransform must not be null
			 @return Smart pointer to the representation descriptor
			*/
			RepresentationDescriptorConstPointer getRepresentationDescriptor() const;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			//No copy constructor allowed
			PreCachedTransformPolicy(const PreCachedTransformPolicy&);
			void operator=(const PreCachedTransformPolicy&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapPreCachedTransformPolicy.tpp"
#endif

#endif
