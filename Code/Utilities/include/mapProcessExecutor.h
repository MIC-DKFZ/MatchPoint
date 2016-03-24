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


#ifndef __MAP_PROCESS_EXECUTOR_H
#define __MAP_PROCESS_EXECUTOR_H


#include <vector>

#include "itkObject.h"

#include "mapString.h"
#include "mapMacros.h"
#include "mapEvents.h"
#include "mapClassMacros.h"
#include "mapMAPUtilitiesExports.h"

namespace map
{
	namespace events
	{
		/*!@class TaskBatchEvent
		 * @brief Base event indicating an output of an external process (e.g. by ProcessExecutor). The output is stored in the comment.
		 * @ingroup Events
		 */
		mapEventMacro(ExternalProcessOutputEvent, AnyMatchPointEvent, MAPUtilities_EXPORT);

		/*!@class TaskBatchEvent
		 * @brief Event indicating an standard output (STDOUT) of an external process (e.g. by ProcessExecutor). The output is stored in the comment.
		 * @ingroup Events
		 */
		mapEventMacro(ExternalProcessStdOutEvent, ExternalProcessOutputEvent, MAPUtilities_EXPORT);
		/*!@class TaskBatchEvent
		* @brief Event indicating an error output of an external process (e.g. by ProcessExecutor). The output is stored in the comment.
		* @ingroup Events
		*/
		mapEventMacro(ExternalProcessStdErrEvent, ExternalProcessOutputEvent, MAPUtilities_EXPORT);
	}

	namespace utilities
	{

		/*! Helper class that allows to execute an application with arguments.
		 * You may register an observer for an ExternalProcessOutputEvent, ExternalProcessStdOutEvent or ExternalProcessStdErrEvent
		 * in order to get notified of any output.
		 * @remark The events will only be invoked if the pipes are NOT(!) shared. By default the pipes are not shared.
		 */
		class MAPUtilities_EXPORT ProcessExecutor : public itk::Object
		{
		public:
			typedef ProcessExecutor Self;
			typedef ::itk::Object  Superclass;
			typedef ::itk::SmartPointer<Self>                                     Pointer;
			typedef ::itk::SmartPointer<const Self>                               ConstPointer;

			itkTypeMacro(ProcessExecutor, ::itk::Object);
			itkFactorylessNewMacro(Self);

			mapSetMacro(SharedOutputPipes, bool);
			mapGetConstMacro(SharedOutputPipes, bool);

			typedef std::vector<::map::core::String> ArgumentListType;

			bool execute(const core::String& executionPath, const core::String& executableName,
						 ArgumentListType argumentList);

			/**Executes the process. This version assumes that the executable name is the first argument in the argument list
			* and has already been converted to its OS dependent name via the static convert function of this class.*/
			bool execute(const core::String& executionPath, const ArgumentListType& argumentList);

			int getExitValue();

			static core::String getOSDependendExecutableName(const core::String& name);

		protected:
			ProcessExecutor();
			virtual ~ProcessExecutor();

			int _exitValue;

			/*! specifies if the child process should share the output pipes (true) or not (false).
			 * If pipes are not shared the output will be passed by invoking ExternalProcessOutputEvents
			 * @remark The events will only be invoked if the pipes are NOT(!) shared.*/
			bool _SharedOutputPipes;
		private:
			ProcessExecutor(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}
#endif
