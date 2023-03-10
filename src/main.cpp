#include "PCH.h"

#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <RE/Skyrim.h>


namespace AutoMove
{

	SKSE::RegistrationSet<RE::IMessageBoxCallback::Message>& GetOnCustomMarkerChangeEvent()
	{
		static SKSE::RegistrationSet<RE::IMessageBoxCallback::Message> onCustomMarkerChange("OnCustomMarkerChange");
		return onCustomMarkerChange;
	}

	SKSE::RegistrationSet<RE::Actor*, bool>& GetOnPlayerDialogueEvent()
	{
		static SKSE::RegistrationSet<RE::Actor*, bool> onPlayerDialogue("OnPlayerDialogue");
		return onPlayerDialogue;
	}

	bool ForceRefToAlias(RE::TESQuest* script, unsigned int aliasID, RE::TESObjectREFR* ref)
	{
		static REL::Relocation<decltype(ForceRefToAlias)> fn{ RELOCATION_ID(24523,25052) };
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

	void RegisterForCustomMarkerChange(RE::TESQuest* script)
	{
		auto& onCustomMarkerChange = GetOnCustomMarkerChangeEvent();
		onCustomMarkerChange.Register(script);
	}
	void UnregisterForCustomMarkerChange(RE::TESQuest* script)
	{
		auto& onCustomMarkerChange = GetOnCustomMarkerChangeEvent();
		onCustomMarkerChange.Unregister(script);
	}

	void RegisterForPlayerDialogue(RE::TESQuest* script)
	{
		auto& onPlayerDialogue = GetOnPlayerDialogueEvent();
		onPlayerDialogue.Register(script);
	}
	void UnregisterForPlayerDialogue(RE::TESQuest* script)
	{
		auto& onPlayerDialogue = GetOnPlayerDialogueEvent();
		onPlayerDialogue.Unregister(script);
	}

	RE::Actor* GetCurrentMount(RE::StaticFunctionTag*, RE::Actor* a)
	{
		return a->QLastRiddenMount().get().get();
	}

	namespace Hooks
	{
		class CSetDialogueWithPlayerHook : public RE::Actor
		{
		public:
			bool SetDialogueWithPlayerHook(bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic);
		};

		using SetDialogueWithPlayerHook_t = decltype(&CSetDialogueWithPlayerHook::SetDialogueWithPlayerHook);
		static SetDialogueWithPlayerHook_t oSetDialogueWithPlayer;
		bool CSetDialogueWithPlayerHook::SetDialogueWithPlayerHook(bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic)
		{
			auto& onPlayerDialogue = GetOnPlayerDialogueEvent();
			onPlayerDialogue.QueueEvent(this, a_flag);
			return (this->*oSetDialogueWithPlayer)(a_flag, a_forceGreet, a_topic);
		}

		class CPlacePlayerMarkerCallbackFunctor : public RE::BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto VTABLE = RE::VTABLE___PlacePlayerMarkerCallbackFunctor;

			void RunHook(RE::IMessageBoxCallback::Message a_msg);
		};
		using PlacePlayerMarkerHook_t = decltype(&CPlacePlayerMarkerCallbackFunctor::RunHook);
		static PlacePlayerMarkerHook_t oPlacePlayerMarker;
		void CPlacePlayerMarkerCallbackFunctor::RunHook(RE::IMessageBoxCallback::Message msg)
		{
			auto& onCustomMarkerChange = GetOnCustomMarkerChangeEvent();
			onCustomMarkerChange.QueueEvent(msg);
			return (this->*oPlacePlayerMarker)(msg);
		}


		void Install()
		{
			{
				union {
					uintptr_t ptr;
					SetDialogueWithPlayerHook_t fn;
				} cpp_bs;

				// onPlayerDialogue
				uintptr_t dialog_vt = (RE::Character::VTABLE[0].address() + 520);
				cpp_bs.ptr = *(uintptr_t*)dialog_vt;
				oSetDialogueWithPlayer = cpp_bs.fn;
				cpp_bs.fn = &CSetDialogueWithPlayerHook::SetDialogueWithPlayerHook;
				REL::safe_write(dialog_vt, cpp_bs.ptr);
			}

			{
				union {
					uintptr_t ptr;
					PlacePlayerMarkerHook_t fn;
				} cpp_bs;

				// onMarkerChange
				uintptr_t marker_vt = (CPlacePlayerMarkerCallbackFunctor::VTABLE[0].address() + 8);
				cpp_bs.ptr = *(uintptr_t*)marker_vt;
				oPlacePlayerMarker = cpp_bs.fn;
				cpp_bs.fn = &CPlacePlayerMarkerCallbackFunctor::RunHook;
				REL::safe_write(marker_vt, cpp_bs.ptr);
			}

		}
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

	//AutoMove::Hooks::Install();

	return true;
}
