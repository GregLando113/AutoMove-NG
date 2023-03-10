#pragma once

namespace AutoMove
{ 
	namespace Hooks
	{
		void Install();


		class CSetDialogueWithPlayerHook : public RE::Actor
		{
		public:
			bool SetDialogueWithPlayerHook(bool a_flag, bool a_forceGreet, RE::TESTopicInfo* a_topic);

			static void Install();
		};


		class CPlacePlayerMarkerCallbackFunctor : public RE::BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto VTABLE = RE::VTABLE___PlacePlayerMarkerCallbackFunctor;

			void RunHook(RE::IMessageBoxCallback::Message a_msg);

			static void Install();
		};

	}
}