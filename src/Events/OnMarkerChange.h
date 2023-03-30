#pragma once

namespace AutoMove
{
	namespace Events
	{
		class HKPlacePlayerMarkerCallbackFunctor : public RE::BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto VTABLE = RE::VTABLE___PlacePlayerMarkerCallbackFunctor;

			static void RunHook(RE::BSIntrusiveRefCounted* functor, RE::IMessageBoxCallback::Message a_msg);

			static void InstallHook();
			static void RegisterPapyrus(RE::BSScript::IVirtualMachine* a_vm);

			static SKSE::RegistrationSet<RE::IMessageBoxCallback::Message>* GetEvent();
		};

	}
}