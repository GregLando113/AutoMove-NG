#pragma once

namespace AutoMove
{ 
	namespace Hooks
	{
		void Install();


		class HKSetDialogueWithPlayer : public RE::Actor
		{
		public:
			static bool SetDialogueWithPlayerHook(RE::Actor* self, bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic);

			static void Install();
		};


		class HKPlacePlayerMarkerCallbackFunctor : public RE::BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto VTABLE = RE::VTABLE___PlacePlayerMarkerCallbackFunctor;

			static void RunHook(RE::BSIntrusiveRefCounted* functor, RE::IMessageBoxCallback::Message a_msg);

			static void Install();
		};

	}
}