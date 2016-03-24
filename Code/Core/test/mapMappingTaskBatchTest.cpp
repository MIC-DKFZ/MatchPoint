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

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "mapMappingTaskBatch.h"
#include "mapMappingTaskBase.h"
#include "mapTestMappingTask.h"
#include "litTestCommand.h"

#include "mapRegistration.h"
#include "mapServiceException.h"
#include "litCheckMacros.h"

#include  <algorithm>

namespace map
{
	namespace testing
	{

		namespace
		{
			class BatchTestCommand : public lit::TestCommand
			{
			public:
				/** Standard class typedefs. */
				typedef BatchTestCommand   Self;
				typedef itk::SmartPointer<Self>    Pointer;

				/** Run-time type information (and related methods). */
				itkTypeMacro(BatchTestCommand, TestCommand);

				/** Method for creation through the object factory. */
				itkNewMacro(Self);

			protected:
				virtual void checkEvent(const ::itk::Object* caller, const ::itk::EventObject& e)
				{
					const events::AnyMatchPointThreadEvent* pThreadEvent =
						dynamic_cast<const events::AnyMatchPointThreadEvent*>(&e);

					if (pThreadEvent)
					{
						std::cout << std::endl << pThreadEvent->GetEventName() << " (@" << caller << "; Thread # " <<
								  pThreadEvent->getThreadID() << "): " << pThreadEvent->getComment() << std::endl;
					}
					else
					{
						const events::AnyMatchPointEvent* pEvent = dynamic_cast<const events::AnyMatchPointEvent*>(&e);

						if (pEvent)
						{
							std::cout << std::endl << pEvent->GetEventName() << " (@" << caller << "): " << pEvent->getComment()
									  << std::endl;
						}
						else
						{
							std::cout << std::endl << e.GetEventName() << " (@" << caller << ")" << std::endl;
						}
					}
				};

				BatchTestCommand() {};
				virtual ~BatchTestCommand() {};

			private:
				BatchTestCommand(const Self&);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};
		}

		int mapMappingTaskBatchTest(int, char* [])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			typedef core::Registration<2, 2> RegistrationType;
			typedef TestMappingTask<RegistrationType> MappingTaskType;
			typedef core::MappingTaskBatch<RegistrationType> MappingTaskBatchType;

			MappingTaskBatchType::Pointer spBatch = MappingTaskBatchType::New();

			BatchTestCommand::Pointer spTestCommand = BatchTestCommand::New();
			spBatch->AddObserver(::map::events::AnyMatchPointEvent(), spTestCommand);

			lit::TestCommand::Pointer spNextCommand = lit::TestCommand::New();
			lit::TestCommand::Pointer spSuccesCommand = lit::TestCommand::New();
			lit::TestCommand::Pointer spFailedCommand = lit::TestCommand::New();
			spBatch->AddObserver(::map::events::NextTaskThreadEvent(::map::events::NextTaskThreadEvent::anyThreadID),
								 spNextCommand);
			spBatch->AddObserver(::map::events::ProcessedTaskThreadEvent(::map::events::NextTaskThreadEvent::anyThreadID),
								 spSuccesCommand);
			spBatch->AddObserver(::map::events::FailedTaskThreadEvent(::map::events::NextTaskThreadEvent::anyThreadID),
								 spFailedCommand);

			MappingTaskType::Pointer spTask1 = MappingTaskType::New();
			MappingTaskType::Pointer spTask2 = MappingTaskType::New();
			MappingTaskType::Pointer spTask3 = MappingTaskType::New();
			MappingTaskType::Pointer spTask4 = MappingTaskType::New();

			RegistrationType::Pointer spRegistration = RegistrationType::New();
			RegistrationType::Pointer spRegistration2 = RegistrationType::New();

			CHECK_EQUAL(true, spBatch->getOneThreadPerTask());
			spBatch->setMaxThreadCount(5);
			CHECK_EQUAL(false, spBatch->getOneThreadPerTask());
			CHECK_EQUAL(5, spBatch->getMaxThreadCount());
			spBatch->activateOneThreadPerTask();
			CHECK_EQUAL(true, spBatch->getOneThreadPerTask());
			CHECK_EQUAL(0, spBatch->getMaxThreadCount());
			spBatch->setMaxThreadCount(1);
			CHECK_EQUAL(false, spBatch->getOneThreadPerTask());
			CHECK_EQUAL(1, spBatch->getMaxThreadCount());

			spBatch->activateOneThreadPerTask();

			spTask1->setIsExceptionNeutral(false);
			spTask2->setIsExceptionNeutral(false);
			spTask3->setIsExceptionNeutral(false);
			spTask4->setIsExceptionNeutral(false);

			CHECK_THROW_EXPLICIT(spBatch->addTask(NULL), core::ServiceException);

			CHECK_NO_THROW(spBatch->addTask(spTask1));
			CHECK_NO_THROW(spBatch->addTask(spTask2));
			CHECK_EQUAL(2, spBatch->getTasks().size());
			CHECK_NO_THROW(spBatch->clear());
			CHECK_EQUAL(0, spBatch->getTasks().size());

			CHECK_NO_THROW(spBatch->addTask(spTask1));
			CHECK_NO_THROW(spBatch->addTask(spTask2));
			CHECK_NO_THROW(spBatch->addTask(spTask3));
			CHECK_NO_THROW(spBatch->addTask(spTask4));
			CHECK_EQUAL(4, spBatch->getTasks().size());

			CHECK_EQUAL(true, spBatch->process(spRegistration2));
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask1->getRegistration());
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask2->getRegistration());
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask3->getRegistration());
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask4->getRegistration());

			CHECK_EQUAL(4, spNextCommand->getEventCount());
			CHECK_EQUAL(4, spSuccesCommand->getEventCount());
			CHECK_EQUAL(0, spFailedCommand->getEventCount());
			spNextCommand->resetEventCount();
			spSuccesCommand->resetEventCount();
			spFailedCommand->resetEventCount();

			spTask2->_failExecution = true;
			spTask4->_failExecution = true;

			spBatch->setMaxThreadCount(1);

			CHECK_EQUAL(false, spBatch->process(spRegistration2));
			CHECK_EQUAL(2, spBatch->getFailedTasks().size());

			bool spTask2_in_failedList = std::find(spBatch->getFailedTasks().begin(),
												   spBatch->getFailedTasks().end(), spTask2.GetPointer()) != spBatch->getFailedTasks().end();
			bool spTask4_in_failedList = std::find(spBatch->getFailedTasks().begin(),
												   spBatch->getFailedTasks().end(), spTask4.GetPointer()) != spBatch->getFailedTasks().end();

			CHECK(spTask2_in_failedList == true);
			CHECK(spTask4_in_failedList == true);

			CHECK_EQUAL(4, spNextCommand->getEventCount());
			CHECK_EQUAL(2, spSuccesCommand->getEventCount());
			CHECK_EQUAL(2, spFailedCommand->getEventCount());
			spNextCommand->resetEventCount();
			spSuccesCommand->resetEventCount();
			spFailedCommand->resetEventCount();

			spTask2->_failExecution = false;
			spTask4->_failExecution = false;
			spTask2->setRegistration(spRegistration);
			spTask4->setRegistration(spRegistration);

			CHECK_EQUAL(true, spBatch->process());
			CHECK_EQUAL(0, spBatch->getFailedTasks().size());
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask1->getRegistration());
			CHECK_EQUAL(spRegistration.GetPointer(), spTask2->getRegistration());
			CHECK_EQUAL(spRegistration2.GetPointer(), spTask3->getRegistration());
			CHECK_EQUAL(spRegistration.GetPointer(), spTask4->getRegistration());

			CHECK_EQUAL(4, spNextCommand->getEventCount());
			CHECK_EQUAL(4, spSuccesCommand->getEventCount());
			CHECK_EQUAL(0, spFailedCommand->getEventCount());
			spNextCommand->resetEventCount();
			spSuccesCommand->resetEventCount();
			spFailedCommand->resetEventCount();


			spTask2->setIsExceptionNeutral(true);
			spTask2->_failExecution = true;

			CHECK_THROW_EXPLICIT(spBatch->process(), core::ExceptionObject);

			CHECK_EQUAL(2, spNextCommand->getEventCount());
			CHECK_EQUAL(1, spSuccesCommand->getEventCount());
			CHECK_EQUAL(1, spFailedCommand->getEventCount());

			RETURN_AND_REPORT_TEST_SUCCESS;
		}
	} //namespace testing
} //namespace map
