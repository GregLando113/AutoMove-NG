#include "PCH.h"

#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <RE/Skyrim.h>

#include "Papyrus.h"
#include "Hooks/Hooks.h"




SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(1 << 9);

	SKSE::GetPapyrusInterface()->Register(AutoMove::Papyrus::RegisterFuncs);

	AutoMove::Hooks::Install();

	return true;
}
