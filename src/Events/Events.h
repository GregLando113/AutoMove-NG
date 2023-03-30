#pragma once

#include "OnPlayerDialogue.h"
#include "OnMarkerChange.h"
#include "OnCustomDestinationArrived.h"

namespace AutoMove
{
	namespace Events
	{
		void InstallHooks();
		void RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm);
	}
}