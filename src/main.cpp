#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <RE/Skyrim.h>


namespace AutoMove
{
	SKSE::RegistrationSet<int> onCustomMarkerChange("OnCustomMarkerChange");
	SKSE::RegistrationSet<RE::Actor, bool> onPlayerDialogue("OnPlayerDialogue");
	SKSE::RegistrationSet<void> onFastTravelConfirm("OnFastTravelConfirm");
	REL::ID id_obj2(24523);


	bool GetPtrByRefHandle(uint32_t* a, uintptr_t* out)
	{
		REL::Relocation<decltype(GetPtrByRefHandle)> fn(19700);
		return fn(a, out);
	}


	void ForceDestinationMarkerIntoAliasID(RE::TESQuest* script, unsigned int aliasID)
	{
		auto player = RE::PlayerCharacter::GetSingleton();
		uintptr_t handleptr = 0;
		bool result = GetPtrByRefHandle(&player->unk924, &handleptr);
		if (handleptr)
		{

		}
	}

	bool IsCustomDestinationActive(RE::StaticFunctionTag*)
	{
		return RE::PlayerCharacter::GetSingleton()->unk924 != 0;
	}

	void RegisterForCustomMarkerChange(RE::TESQuest* script)
	{
		//onCustomMarkerChange.Register();
	}
	void UnregisterForCustomMarkerChange(RE::TESQuest* script)
	{
	}

	void RegisterForPlayerDialogue(RE::TESQuest* script)
	{
		//onCustomMarkerChange.Register();
	}
	void UnregisterForPlayerDialogue(RE::TESQuest* script)
	{
	}

	RE::Actor* GetCurrentMount(RE::StaticFunctionTag*, RE::Actor* actor)
	{
		return actor;
	}
}

bool RegisterFuncs(RE::BSScript::Internal::VirtualMachine* a_vm)
{
	a_vm->RegisterFunction("ForceDestinationMarkerIntoAliasID", "AutoMove", AutoMove::ForceDestinationMarkerIntoAliasID);
	a_vm->RegisterFunction("IsCustomDestinationActive", "AutoMove", AutoMove::IsCustomDestinationActive);
	a_vm->RegisterFunction("GetCurrentMount", "AutoMove", AutoMove::GetCurrentMount);
	a_vm->RegisterFunction("RegisterForCustomMarkerChange", "AutoMove", AutoMove::RegisterForCustomMarkerChange);
	a_vm->RegisterFunction("UnregisterForCustomMarkerChange", "AutoMove", AutoMove::UnregisterForCustomMarkerChange);
	a_vm->RegisterFunction("RegisterForPlayerDialogue", "AutoMove", AutoMove::RegisterForPlayerDialogue);
	a_vm->RegisterFunction("UnregisterForPlayerDialogue", "AutoMove", AutoMove::UnregisterForPlayerDialogue);
}


extern "C" __declspec(dllexport) constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;

	v.PluginVersion('AEr1');
	v.PluginName("Auto Move AE");

	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	SKSE::GetPapyrusInterface()->Register(RegisterFuncs);

	return true;
}
