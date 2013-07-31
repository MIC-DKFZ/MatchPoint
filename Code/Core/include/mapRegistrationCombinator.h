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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapRegistrationCombinator.h $
*/


#ifndef __MAP_REGISTRATION_COMBINATOR_H
#define __MAP_REGISTRATION_COMBINATOR_H

#include "mapStaticServiceStack.h"
#include "mapRegistrationKernelCombinatorBase.h"
#include "mapRegistration.h"
#include "mapKernelCombinatorLoadPolicy.h"

#include "itkObject.h"

namespace map
{

	namespace core
	{
		/*! @class RegistrationCombinator
		* @brief Class combines two given registrations to a now one.
		*
		* This class is used to combine two registrations assuming that the target space of the first
		* given reigstration equals the moving space of the second registration. The resulting registration
		* maps from the movingspace of the first registration in the target space of the second registration.\n
		* by registration algorithms to establish the inverse counterpart
		* of the registration kernel determined by the algorithm, thus to establish a fully
		* functional Registration instance.\n
		* To combine the registrations the class uses a static service stack populated with
		* RegistrationKernelCombinators for the direct and the inverse mapping direction.
		* You can change the stack content by the static class methods of the member typedef KernelCombinatorStackType.
		* If the combination of kernels cannot be expressed analyticaly (by transformation models) a LazyFieldKernel
		* will be used.\n
		* Depending on the registrations and there field representations in these cases it could be possible, that a mapping of points
		* across both kernels is not possible, how the combinator (more exactly its functor) should behave can be
		* controlled by the padding value properties of this class.\n
		* Its also possible to choose which mapping direction should be directly initialized by the combinator, no lazy field generation will
		* be used for the specific mapping directions.
		*
		* @ingroup RegOperation
		* @ingroup Registration
		* @tparam TPreRegistration the first registration or pre registration, that should be combined.
		* @tparam TRegistration the second registration or main registration, that should be combined.
		* @tparam TLoadPolicy the load policy that should be used for the provider stack of the recombinator.
		*/
		template <class TPreRegistration, class TRegistration, template <typename> class TLoadPolicy = KernelCombinatorLoadPolicy >
		class RegistrationCombinator: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			typedef RegistrationCombinator<TPreRegistration, TRegistration, TLoadPolicy>  Self;
			typedef itk::Object                    Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(RegistrationCombinator, itk::Object);
			itkNewMacro(Self);

			typedef TPreRegistration PreRegistrationType;
			typedef TRegistration    RegistrationType;

			itkStaticConstMacro(MovingDimensions, unsigned int, PreRegistrationType::MovingDimensions);
			itkStaticConstMacro(InterimDimensions, unsigned int, PreRegistrationType::TargetDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, RegistrationType::TargetDimensions);

			typedef RegistrationKernelCombinatorBase < itkGetStaticConstMacro(MovingDimensions),
			        itkGetStaticConstMacro(InterimDimensions),
			        itkGetStaticConstMacro(TargetDimensions) > DirectKernelCombinatorBaseType;
			typedef RegistrationKernelCombinatorBase < itkGetStaticConstMacro(TargetDimensions),
			        itkGetStaticConstMacro(InterimDimensions),
			        itkGetStaticConstMacro(MovingDimensions) > InverseKernelCombinatorBaseType;

			typedef Registration < itkGetStaticConstMacro(MovingDimensions),
			        itkGetStaticConstMacro(TargetDimensions) >  CombinedRegistrationType;
			typedef typename CombinedRegistrationType::Pointer						  CombinedRegistrationPointer;

			typedef typename RegistrationTopology < itkGetStaticConstMacro(MovingDimensions),
			        itkGetStaticConstMacro(TargetDimensions) >::DirectMappingVectorType DirectMappingVectorType;
			typedef typename RegistrationTopology < itkGetStaticConstMacro(MovingDimensions),
			        itkGetStaticConstMacro(TargetDimensions) >::InverseMappingVectorType InverseMappingVectorType;

			typedef typename CombinedRegistrationType::DirectFieldRepresentationType	CombinedDirectFieldRepresentationType;
			typedef typename CombinedRegistrationType::InverseFieldRepresentationType	CombinedInverseFieldRepresentationType;


			struct InitialisationStyle
			{
				enum Type
				{
				    None = 0,
				    DirectMapping = 1,
				    InverseMapping = 2,
				    CompleteRegistration = 3,
				};
			};
			typedef typename InitialisationStyle::Type InitialisationStyleType;

#ifdef ITK_USE_CONCEPT_CHECKING
			/** Begin concept checking */
			itkConceptMacro(CombinableRegistrationsCheck,
			                (itk::Concept::SameDimension<PreRegistrationType::TargetDimensions, RegistrationType::MovingDimensions>));
			/** End concept checking */
#endif

		protected:
			typedef services::ServiceStack<DirectKernelCombinatorBaseType, TLoadPolicy<DirectKernelCombinatorBaseType> > ConcreteDirectCombinatorStackType;
			typedef services::ServiceStack<InverseKernelCombinatorBaseType, TLoadPolicy<InverseKernelCombinatorBaseType> > ConcreteInverseCombinatorStackType;
		public:
			typedef services::StaticServiceStack<ConcreteDirectCombinatorStackType>			 DirectKernelCombinatorStackType;
			typedef services::StaticServiceStack<ConcreteInverseCombinatorStackType>			 InverseKernelCombinatorStackType;

			/*! Generates a combined registration using the both passed registrations.
			 * @eguarantee strong
			 * @param [in] preRegistration Referenz to the first registration.
			 * @param [in] registration Referenz to the second registration.
			 * @param [in] initStyle Defines the which mapping direction should be initialized directly by the combinator and therefor are not in "lazy mode".
			 * @return Smart pointer to the registration combining the two given registrations.
			 */
			CombinedRegistrationPointer process(const PreRegistrationType &preRegistration, const RegistrationType &registration,
			                                    InitialisationStyleType initStyle = InitialisationStyle::None) const;

			CombinedRegistrationPointer process(const PreRegistrationType &preRegistration, const RegistrationType &registration,
			                                    const CombinedDirectFieldRepresentationType *pDirectRepresentation,
			                                    const CombinedInverseFieldRepresentationType *pInverseRepresentation,
			                                    InitialisationStyleType initStyle = InitialisationStyle::None) const;

			/*! gets _useDirectPadding */
			bool getUseDirectPadding() const;
			/*! Sets _useDirectPadding . */
			void setUseDirectPadding(bool directPadding);

			/*! gets _useInversePadding */
			bool getUseInversePadding() const;
			/*! Sets _useInversePadding */
			void setUseInversePadding(bool inversePadding);


			/*! Gets _directPaddingVector
			 * @return vector The _directPaddingVector*/
			const DirectMappingVectorType &getDirectPaddingVector() const;

			/*! Sets _directPaddingVector by vector and _useDirectPadding to true.
			 * @param [in] vector The new value for _directPaddingVector*/
			void setDirectPaddingVector(const DirectMappingVectorType &vector);

			/*! Gets _inversePaddingVector
			 * @return vector The _directPaddingVector*/
			const InverseMappingVectorType &getInversePaddingVector() const;

			/*! Sets _inversePaddingVector by vector and _useInversePadding to true.
			 * @param [in] vector The new value for _inversePaddingVector*/
			void setInversePaddingVector(const InverseMappingVectorType &vector);

		protected:
			RegistrationCombinator();
			virtual ~RegistrationCombinator();

			DirectMappingVectorType _directPaddingVector;
			InverseMappingVectorType _inversePaddingVector;

			/*! Indicicates how the recombinator and its functor should handle points that cannot be mapped through both kernels in direct direction
			 * (e.g. a point that is mapped by the first kernel outside of the supported region of the second registration
			 * kernel). If the _useDirectPadding is true, _directPaddingVector will be used as padding value in each of the mentioned cases.
			 * If _useDirectPadding value is false, the vector of the pre registration kernel will be used.
			 * By default _useDirectPadding is false.
			 */
			bool _useDirectPadding;
			/*! Indicicates how the recombinator and its functor should handle points that cannot be mapped through both kernels in inverse direction
			 * (e.g. a point that is mapped by the first kernel outside of the supported region of the second registration
			 * kernel). If the _useInversePadding is true, _inversePaddingVector will be used as padding value in each of the mentioned cases.
			 * If _useInversePadding value is false, the vector of the pre registration kernel will be used.
			 * By default _useInversePadding is false.
			 */
			bool _useInversePadding;

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream &os, itk::Indent indent) const;

		private:
			RegistrationCombinator(const Self &); //purposely not implemented
			void operator=(const Self &); //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapRegistrationCombinator.tpp"
#endif

#endif
