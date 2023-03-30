#pragma once
#include "..\PCH.h"
#include "Events.h"


namespace AutoMove
{
	namespace Events
	{
		void InstallHooks()
		{
			HKSetDialogueWithPlayer::InstallHook();
			HKPlacePlayerMarkerCallbackFunctor::InstallHook();
		}

		void RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm)
		{
			HKSetDialogueWithPlayer::RegisterPapyrus(a_vm);
			HKPlacePlayerMarkerCallbackFunctor::RegisterPapyrus(a_vm);
		}
	}
}