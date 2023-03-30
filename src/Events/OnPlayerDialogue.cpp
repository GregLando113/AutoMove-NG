#include "../PCH.h"
#include "OnPlayerDialogue.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Events
	{
		// Event Hook

		SKSE::RegistrationSet<RE::Actor*, bool>* HKSetDialogueWithPlayer::GetEvent()
		{
			static SKSE::RegistrationSet<RE::Actor*, bool> onPlayerDialogue("OnPlayerDialogue");
			return &onPlayerDialogue;
		}

		static REL::Relocation<decltype(HKSetDialogueWithPlayer::SetDialogueWithPlayerHook)> oSetDialogueWithPlayer;

		void HKSetDialogueWithPlayer::InstallHook()
		{
			REL::Relocation<std::uintptr_t> CharVTBL{ RE::Character::VTABLE[0] };
			oSetDialogueWithPlayer = CharVTBL.write_vfunc(65, HKSetDialogueWithPlayer::SetDialogueWithPlayerHook);
		}
		bool HKSetDialogueWithPlayer::SetDialogueWithPlayerHook(RE::Actor* self, bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic)
		{
			auto onPlayerDialogue = HKSetDialogueWithPlayer::GetEvent();
			onPlayerDialogue->QueueEvent(self, a_flag);
			return oSetDialogueWithPlayer(self, a_flag, a_forceGreet, a_topic);
		}


		// Papyrus

		void RegisterForPlayerDialogue(RE::TESQuest* script)
		{
			auto onPlayerDialogue = HKSetDialogueWithPlayer::GetEvent();
			onPlayerDialogue->Register(script);
		}
		void UnregisterForPlayerDialogue(RE::TESQuest* script)
		{
			auto onPlayerDialogue = HKSetDialogueWithPlayer::GetEvent();
			onPlayerDialogue->Unregister(script);
		}

		void HKSetDialogueWithPlayer::RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->RegisterFunction("RegisterForPlayerDialogue", "AutoMove", RegisterForPlayerDialogue);
			a_vm->RegisterFunction("UnregisterForPlayerDialogue", "AutoMove", UnregisterForPlayerDialogue);
		}
	}
}