#include "../PCH.h"
#include "Hooks.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Hooks
	{
		using SetDialogueWithPlayerHook_t = decltype(&CSetDialogueWithPlayerHook::SetDialogueWithPlayerHook);
		static SetDialogueWithPlayerHook_t oSetDialogueWithPlayer;

		void CSetDialogueWithPlayerHook::Install()
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
		bool CSetDialogueWithPlayerHook::SetDialogueWithPlayerHook(bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic)
		{
			auto& onPlayerDialogue = Papyrus::GetOnPlayerDialogueEvent();
			onPlayerDialogue.QueueEvent(this, a_flag);
			return (this->*oSetDialogueWithPlayer)(a_flag, a_forceGreet, a_topic);
		}
	}
}