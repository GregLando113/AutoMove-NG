#include "PCH.h"
#include "Papyrus.h"
#include "CustomDestination.h"


namespace AutoMove
{
	namespace Papyrus
	{
		SKSE::RegistrationSet<RE::IMessageBoxCallback::Message>* GetOnCustomMarkerChangeEvent()
		{
			static SKSE::RegistrationSet<RE::IMessageBoxCallback::Message> onCustomMarkerChange("OnCustomMarkerChange");
			return &onCustomMarkerChange;
		}

		SKSE::RegistrationSet<RE::Actor*, bool>* GetOnPlayerDialogueEvent()
		{
			static SKSE::RegistrationSet<RE::Actor*, bool> onPlayerDialogue("OnPlayerDialogue");
			return &onPlayerDialogue;
		}

		bool ForceRefToAlias(RE::TESQuest* script, unsigned int aliasID, RE::TESObjectREFR* ref)
		{
			static REL::Relocation<decltype(ForceRefToAlias)> fn{ RELOCATION_ID(24523,25052) };
			return fn(script, aliasID, ref);
		}


		void ForceDestinationMarkerIntoAliasID(RE::TESQuest* script, unsigned int aliasID)
		{
			RE::NiPointer<RE::TESObjectREFR> handleptr;
			if (!GetPlayerCustomDestinationRef())
				return;
			bool result = RE::LookupReferenceByHandle(GetPlayerCustomDestinationRef().native_handle(), handleptr);
			if (handleptr)
			{
				result = ForceRefToAlias(script, aliasID, handleptr.get());
			}
		}

		bool IsCustomDestinationActive(RE::StaticFunctionTag*)
		{
			return (bool)GetPlayerCustomDestinationRef();
		}

		void RegisterForCustomMarkerChange(RE::TESQuest* script)
		{
			auto onCustomMarkerChange = GetOnCustomMarkerChangeEvent();
			onCustomMarkerChange->Register(script);
		}
		void UnregisterForCustomMarkerChange(RE::TESQuest* script)
		{
			auto onCustomMarkerChange = GetOnCustomMarkerChangeEvent();
			onCustomMarkerChange->Unregister(script);
		}

		void RegisterForPlayerDialogue(RE::TESQuest* script)
		{
			auto onPlayerDialogue = GetOnPlayerDialogueEvent();
			onPlayerDialogue->Register(script);
		}
		void UnregisterForPlayerDialogue(RE::TESQuest* script)
		{
			auto onPlayerDialogue = GetOnPlayerDialogueEvent();
			onPlayerDialogue->Unregister(script);
		}

		// Using the GetMount new to NG
		RE::Actor* GetCurrentMount(RE::StaticFunctionTag*, RE::Actor* a)
		{
			RE::ActorPtr mount_ptr;
			if (!a->GetMount(mount_ptr))
				return nullptr;
			return mount_ptr.get();
		}


		// A faithful recreation of the original AutoMove version of GetCurrentMount.
		RE::Actor* GetCurrentMount_Original(RE::StaticFunctionTag*, RE::Actor* a)
		{
			a->IsOnMount();
			RE::ExtraInteraction* extdata = a->extraList.GetByType<RE::ExtraInteraction>();
			RE::NiPointer<RE::TESObjectREFR> handleptr;
			RE::LookupReferenceByHandle(extdata->interaction->actor.native_handle(), handleptr);
			if (!handleptr)
				return nullptr;
			return handleptr->As<RE::Actor>();
		}

		bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->RegisterFunction("ForceDestinationMarkerIntoAliasID", "AutoMove", ForceDestinationMarkerIntoAliasID);
			a_vm->RegisterFunction("IsCustomDestinationActive", "AutoMove", IsCustomDestinationActive);
			a_vm->RegisterFunction("GetCurrentMount", "AutoMove", GetCurrentMount_Original);
			a_vm->RegisterFunction("RegisterForCustomMarkerChange", "AutoMove", RegisterForCustomMarkerChange);
			a_vm->RegisterFunction("UnregisterForCustomMarkerChange", "AutoMove", UnregisterForCustomMarkerChange);
			a_vm->RegisterFunction("RegisterForPlayerDialogue", "AutoMove", RegisterForPlayerDialogue);
			a_vm->RegisterFunction("UnregisterForPlayerDialogue", "AutoMove", UnregisterForPlayerDialogue);
			return true;
		}
	}
}