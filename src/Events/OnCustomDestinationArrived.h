#pragma once

namespace AutoMove
{
	namespace Events
	{

		class HKMovementControllerGoal : public RE::MovementControllerNPC
		{
		public:

			static void InstallHook();
			static void RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm);

			static SKSE::RegistrationSet<>* GetCustomDestinationArrivedEvent();
		};

	}
}