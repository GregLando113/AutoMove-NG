#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <RE/Skyrim.h>


namespace AutoMove
{
	// SKSE::RegistrationSet<int> onCustomMarkerChange("OnCustomMarkerChange");
	// SKSE::RegistrationSet<RE::Actor, bool> onPlayerDialogue("OnPlayerDialogue");
	// SKSE::RegistrationSet<void> onFastTravelConfirm("OnFastTravelConfirm");
	// REL::ID id_obj2(24523);



	bool ForceRefToAlias(RE::TESQuest* script, unsigned int aliasID, RE::TESObjectREFR* ref)
	{
		REL::Relocation<decltype(ForceRefToAlias)> fn{ RELOCATION_ID(24523,25052) };
		return fn(script, aliasID, ref);
	}


	void ForceDestinationMarkerIntoAliasID(RE::TESQuest* script, unsigned int aliasID)
	{
		auto player = RE::PlayerCharacter::GetSingleton();
		RE::NiPointer<RE::TESObjectREFR> handleptr;
		bool result = RE::LookupReferenceByHandle(player->GetInfoRuntimeData().unk054.native_handle(), handleptr);
		if (handleptr)
		{
			result = ForceRefToAlias(script, aliasID, handleptr.get());
		}
	}

	bool IsCustomDestinationActive(RE::StaticFunctionTag*)
	{
		return (bool)RE::PlayerCharacter::GetSingleton()->GetInfoRuntimeData().unk054;
	}

	void RegisterForCustomMarkerChange(RE::TESQuest*)
	{
		//onCustomMarkerChange.Register();
	}
	void UnregisterForCustomMarkerChange(RE::TESQuest*)
	{
	}

	void RegisterForPlayerDialogue(RE::TESQuest*)
	{
		//onCustomMarkerChange.Register();
	}
	void UnregisterForPlayerDialogue(RE::TESQuest*)
	{
	}

	RE::Actor* GetCurrentMount(RE::StaticFunctionTag*, RE::Actor* a)
	{
		return a->QLastRiddenMount().get().get();
	}
}

bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
{
	a_vm->RegisterFunction("ForceDestinationMarkerIntoAliasID", "AutoMove", AutoMove::ForceDestinationMarkerIntoAliasID);
	a_vm->RegisterFunction("IsCustomDestinationActive", "AutoMove", AutoMove::IsCustomDestinationActive);
	a_vm->RegisterFunction("GetCurrentMount", "AutoMove", AutoMove::GetCurrentMount);
	a_vm->RegisterFunction("RegisterForCustomMarkerChange", "AutoMove", AutoMove::RegisterForCustomMarkerChange);
	a_vm->RegisterFunction("UnregisterForCustomMarkerChange", "AutoMove", AutoMove::UnregisterForCustomMarkerChange);
	a_vm->RegisterFunction("RegisterForPlayerDialogue", "AutoMove", AutoMove::RegisterForPlayerDialogue);
	a_vm->RegisterFunction("UnregisterForPlayerDialogue", "AutoMove", AutoMove::UnregisterForPlayerDialogue);
	return true;
}


SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(1 << 9);

	SKSE::GetPapyrusInterface()->Register(RegisterFuncs);

	return true;
}
