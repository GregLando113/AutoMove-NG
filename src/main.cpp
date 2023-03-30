#include "PCH.h"

#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <RE/Skyrim.h>

#include "Papyrus.h"
#include "Serialization.h"
#include "Hooks/Hooks.h"
#include "Events/Events.h"

#define WAIT_DEBUGGER 0

#if WAIT_DEBUGGER
#include <Windows.h>
#endif

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
#if WAIT_DEBUGGER
	while (!IsDebuggerPresent())
		Sleep(1000);
#endif
	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(1 << 9);

	SKSE::GetPapyrusInterface()->Register(AutoMove::Papyrus::RegisterFuncs);
	{
		auto s = SKSE::GetSerializationInterface();
		s->SetUniqueID('MOVE');
		s->SetSaveCallback(AutoMove::OnGameSave);
		s->SetLoadCallback(AutoMove::OnGameLoad);
		s->SetRevertCallback(AutoMove::OnGameRevert);
	}
	AutoMove::Events::InstallHooks();
	AutoMove::Hooks::Install();
	return true;
}
