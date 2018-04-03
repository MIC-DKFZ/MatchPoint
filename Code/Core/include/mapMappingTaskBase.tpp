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


#ifndef __MAP_MAPPING_TASK_BASE_TPP
#define __MAP_MAPPING_TASK_BASE_TPP

#include "mapMappingTaskBase.h"
#include <assert.h>

namespace map
{
	namespace core
	{

		template <class TRegistration>
		bool
		MappingTaskBase<TRegistration>::
		execute(void) const
		{
			assert(_spRegistration.IsNotNull());

			if (_spRegistration.IsNull())
			{
				mapDefaultExceptionMacro( <<
										  "Cannot execute registration task. Registration is undefined. Pleas set registration.");
			}

			mapLogInfoMacro( << "Start registration task execution");
			clearException();

			bool success = false;

			try
			{
				doExecution();
				success = true;
				this->Modified();
			}
			catch (ExceptionObject& ex)
			{
				_pException = ex.clone();

				if (_isExceptionNeutral)
				{
					throw;
				}
			}
			catch (itk::ExceptionObject& ex)
			{
				_pException = new ExceptionObject(__FILE__, __LINE__, ex.what(), MAP_FUNCTION_SIGNATURE);

				if (_isExceptionNeutral)
				{
					throw;
				}
			}
			catch (...)
			{
				_pException = new ExceptionObject(__FILE__, __LINE__,
												  "Unknown exception while prosessing registration task.", MAP_FUNCTION_SIGNATURE);

				if (_isExceptionNeutral)
				{
					throw;
				}
			}

			return success;
		}

		template <class TRegistration>
		void
		MappingTaskBase<TRegistration>::
		setRegistration(const RegistrationType* pRegistration)
		{
			if (pRegistration != _spRegistration.GetPointer())
			{
				_spRegistration = pRegistration;
				clearResults();
				this->Modified();
			}
		}

		template <class TRegistration>
		const typename MappingTaskBase<TRegistration>::RegistrationType*
		MappingTaskBase<TRegistration>::
		getRegistration(void) const
		{
			return _spRegistration;
		}

		template <class TRegistration>
		const ExceptionObject*
		MappingTaskBase<TRegistration>::
		getRegistrationException(void) const
		{
			return _pException;
		}

		template <class TRegistration>
		void
		MappingTaskBase<TRegistration>::
		clearException(void) const
		{
			delete _pException;
			_pException = NULL;
		};

		template <class TRegistration>
		void
		MappingTaskBase<TRegistration>::
		reset(void)
		{
			clearException();
			this->clearInputs();
			this->clearResults();
			this->Modified();
		}

		template <class TRegistration>
		MappingTaskBase<TRegistration>::
		MappingTaskBase(): _isExceptionNeutral(true), _pException(NULL)
		{
		}

		template <class TRegistration>
		MappingTaskBase<TRegistration>::
		~MappingTaskBase()
		{
			clearException();
		}

		template <class TRegistration>
		void
		MappingTaskBase<TRegistration>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "Registration: " << _spRegistration.GetPointer() << std::endl;
			os << indent << "IsExceptionNeutral: " << _isExceptionNeutral << std::endl;
			os << indent << "Cached Exception: " << _pException << std::endl;
		}

		template <class TRegistration>
		void
		MappingTaskBase<TRegistration>::
		setIsExceptionNeutral(bool neutral)
		{
			_isExceptionNeutral = neutral;
			this->Modified();
		};

		template <class TRegistration>
		bool
		MappingTaskBase<TRegistration>::
		getIsExceptionNeutral(void) const
		{
			return _isExceptionNeutral;
		};

	} // end namespace core
} // end namespace map

#endif
