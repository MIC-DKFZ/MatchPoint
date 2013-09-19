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
#include "mapFieldGenerationFunctor.h"

#include "itkSimpleFastMutexLock.h"

namespace map
{
	namespace core
	{

		/*! @class LazyFieldPolicy
		    @brief class for LazyFieldPolicy.

		    This class is the class for the LazyFieldPolicy.
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class LazyFieldPolicy
		{
		public:
			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType
			FieldType;
			typedef functors::FieldGenerationFunctor<VInputDimensions, VOutputDimensions>
			FieldGenerationFunctorType;
			typedef typename FieldGenerationFunctorType::ConstPointer FieldGenerationFunctorConstPointer;

			/*! sets the field's functor
			  @eguarantee no fail
			  @param functor Reference to the functor that is responsible for generating the field
			*/
			virtual void setFieldFunctor(const FieldGenerationFunctorType& functor);

			/*! gets the field's functor
			  @eguarantee no fail
			  @return Pointer to the field functor that is used to generate the field on demand.
			*/
			virtual const FieldGenerationFunctorType*  getFieldFunctor() const;


			/*! Returns if the field was already created or if the generation still is pending / wasn't necessary.
			    @eguarantee strong
			*/
			bool fieldExists() const;

		protected:
			LazyFieldPolicy();
			~LazyFieldPolicy();

			typedef typename FieldType::Pointer FieldPointer;
			//is mutable because it is a cache for the functor result, thus it may be changed by checkAndPrepareField()
			mutable FieldPointer _spField;

			FieldGenerationFunctorConstPointer _spGenerationFunctor;

			/*! checks the field that has been set for correctness and prepares it
			  @eguarantee strong
			  @return the success of the operation
			*/
			bool checkAndPrepareField() const;

			/*! generates the field
			  @eguarantee strong
			*/
			void generateField() const;

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
			LazyFieldPolicy(const LazyFieldPolicy&);
			void operator=(const LazyFieldPolicy&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapLazyFieldPolicy.tpp"
#endif

#endif
