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


#ifndef __LAZY_FIELD_POLICY_H
#define __LAZY_FIELD_POLICY_H

#include "mapRegistrationTopology.h"
#include "mapTransformGenerationFunctor.h"

#include "itkSimpleFastMutexLock.h"

namespace map
{
	namespace core
	{

		/*! @class LazyTransformPolicy
		    @brief class for LazyTransformPolicy.

		    This class is the class for the LazyTransformPolicy.
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class LazyTransformPolicy
		{
		public:
			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectTransformType
			TransformType;
      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
          MappingVectorType;

			typedef functors::TransformGenerationFunctor<VInputDimensions, VOutputDimensions>
			TransformGenerationFunctorType;
			typedef typename TransformGenerationFunctorType::ConstPointer TransformGenerationFunctorConstPointer;

			/*! sets the field's functor
			  @eguarantee no fail
			  @param functor Reference to the functor that is responsible for generating the field
			*/
			virtual void setTransformFunctor(const TransformGenerationFunctorType& functor);

			/*! gets the field's functor
			  @eguarantee no fail
			  @return Pointer to the field functor that is used to generate the field on demand.
			*/
			virtual const TransformGenerationFunctorType*  getTransformFunctor() const;


			/*! Returns if the transform was already created or if the generation still is pending / wasn't necessary.
			    @eguarantee strong
			*/
			bool transformExists() const;

      void setNullVector(const MappingVectorType& nullVector);

      void setNullVectorUsage(bool use);


		protected:
			LazyTransformPolicy();
			~LazyTransformPolicy();

			typedef typename TransformType::Pointer TransformPointer;
			//is mutable because it is a cache for the functor result, thus it may be changed by checkAndPrepareTransform()
			mutable TransformPointer _spTransform;

			TransformGenerationFunctorConstPointer _spGenerationFunctor;

      MappingVectorType _nullVector;
      bool _useNullVector;

			/*! checks the field that has been set for correctness and prepares it
			  @eguarantee strong
			  @return the success of the operation
			*/
			bool checkAndPrepareTransform() const;

			/*! generates the field
			  @eguarantee strong
			*/
			void generateTransform() const;


      const MappingVectorType& doGetNullVector() const;

      bool doUsesNullVector() const;

			typedef FieldRepresentationDescriptor<VInputDimensions> RepresentationDescriptorType;
			typedef typename RepresentationDescriptorType::ConstPointer  RepresentationDescriptorConstPointer;

			RepresentationDescriptorConstPointer getRepresentationDescriptor() const;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			typedef ::itk::SimpleFastMutexLock MutexType;
			/*!Mutex to make the checks of the policy thread safe*/
			mutable MutexType _checkMutex;
			/*!Mutex to make the generation of the fields thread safe and to avoid paralel
			 * generation of fields because of a racing condition of two checkAndPrepare calls*/
			mutable MutexType _generateMutex;

			//No copy constructor allowed
			LazyTransformPolicy(const LazyTransformPolicy&);
			void operator=(const LazyTransformPolicy&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapLazyTransformPolicy.tpp"
#endif

#endif
