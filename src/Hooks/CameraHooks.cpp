#include "../PCH.h"
#include "Hooks.h"


namespace AutoMove
{
	namespace Hooks
	{
		float ActorGetSomeStateHook1(RE::Actor* actor);
		float ActorGetSomeStateHook2(RE::Actor* actor);
		float ActorGetSomeStateHook3(RE::Actor* actor);

		static REL::Relocation<decltype(ActorGetSomeStateHook1)> oActorGetSomeState1;
		static REL::Relocation<decltype(ActorGetSomeStateHook2)> oActorGetSomeState2;
		static REL::Relocation<decltype(ActorGetSomeStateHook3)> oActorGetSomeState3;

		float ActorGetSomeStateHook1(RE::Actor* actor)
		{
			auto pc = RE::PlayerCharacter::GetSingleton();
			if ((pc->GetPlayerRuntimeData().unkBDA & 8) != 0)
				return 0.0;
			return oActorGetSomeState1(actor);
		}
		float ActorGetSomeStateHook2(RE::Actor* actor)
		{
			auto pc = RE::PlayerCharacter::GetSingleton();
			if ((pc->GetPlayerRuntimeData().unkBDA & 8) != 0)
				return 0.0;
			return oActorGetSomeState2(actor);
		}

		float ActorGetSomeStateHook3(RE::Actor* actor)
		{
			auto pc = RE::PlayerCharacter::GetSingleton();
			if ((pc->GetPlayerRuntimeData().unkBDA & 8) != 0)
				return 0.0;
			return oActorGetSomeState3(actor);
		}


		float CharGetRotationXHook(RE::Character*)
		{
			return RE::PlayerCharacter::GetSingleton()->GetAngleX();
		}

		void CharModifyRotationXHook(RE::Character* character, float rot)
		{
			auto pc = RE::PlayerCharacter::GetSingleton();
			character->As<RE::Actor>()->SetRotationX(rot + pc->GetAngleX());
		}

		void InstallCameraHooks()
		{
			auto& tramp = SKSE::GetTrampoline();
			static REL::Relocation<uintptr_t> DragonCameraState_UpdRotation{ RELOCATION_ID(32371, 33120) };
			const int DragonCameraState_UpdRotationOffset = 146;
			static REL::Relocation<uintptr_t> HorseCameraState_UpdRotation{ RELOCATION_ID(49840, 50771) };
			const int HorseCameraState_UpdRotationOffset = 132;
			static REL::Relocation<uintptr_t> ThirdPersonState_SetFreeLookMode{ RELOCATION_ID(49968, 50904) };
			const int ThirdPersonState_SetFreeLookModeOffset = 67;

			oActorGetSomeState1 = tramp.write_call<5>(DragonCameraState_UpdRotation.address() + DragonCameraState_UpdRotationOffset, ActorGetSomeStateHook1);
			oActorGetSomeState2 = tramp.write_call<5>(HorseCameraState_UpdRotation.address() + HorseCameraState_UpdRotationOffset, ActorGetSomeStateHook2);
			oActorGetSomeState3 = tramp.write_call<5>(ThirdPersonState_SetFreeLookMode.address() + ThirdPersonState_SetFreeLookModeOffset, ActorGetSomeStateHook3);


			static REL::Relocation<uintptr_t> HorseCameraState_HandleLookInput{ RELOCATION_ID(49839, 50904) };
			static REL::Relocation<uintptr_t> PlayerCam_sub{ RELOCATION_ID(49907, 50840) };
			int HorseCameraState_HandleLookInputOffset = 0;
			int PlayerCam_subOffset = 0;
			switch (REL::Module::GetRuntime()) {
			case REL::Module::Runtime::SE:
				HorseCameraState_HandleLookInputOffset = 151;
				PlayerCam_subOffset = 509;
				break;
			case REL::Module::Runtime::AE:
				HorseCameraState_HandleLookInputOffset = 140;
				PlayerCam_subOffset = 516;
				break;
			}

			tramp.write_call<5>(HorseCameraState_HandleLookInput.address() + REL::Relocate(151, 140), CharGetRotationXHook);
			tramp.write_call<5>(PlayerCam_sub.address() + REL::Relocate(509, 516), CharModifyRotationXHook);

		}
	}
}