#include "../PCH.h"
#include "Hooks.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Hooks
	{
		static REL::Relocation<decltype(HKSetDialogueWithPlayer::SetDialogueWithPlayerHook)> oSetDialogueWithPlayer;

		void HKSetDialogueWithPlayer::Install()
		{
			REL::Relocation<std::uintptr_t> CharVTBL{ RE::Character::VTABLE[0] };
			oSetDialogueWithPlayer = CharVTBL.write_vfunc(65, HKSetDialogueWithPlayer::SetDialogueWithPlayerHook);
		}
		bool HKSetDialogueWithPlayer::SetDialogueWithPlayerHook(RE::Actor* self, bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic)
		{
			auto onPlayerDialogue = Papyrus::GetOnPlayerDialogueEvent();
			onPlayerDialogue->QueueEvent(self, a_flag);
			return oSetDialogueWithPlayer(self, a_flag, a_forceGreet, a_topic);
		}
	}
}