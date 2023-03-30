#pragma once

namespace AutoMove
{
	namespace Events
	{
		class HKSetDialogueWithPlayer : public RE::Actor
		{
		public:
			static bool SetDialogueWithPlayerHook(RE::Actor* self, bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic);

			static void InstallHook();
			static void RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm);
			static SKSE::RegistrationSet<RE::Actor*, bool>* GetEvent();
		};

	}
}