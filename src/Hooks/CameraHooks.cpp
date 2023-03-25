#include "../PCH.h"
#include "Hooks.h"


namespace AutoMove
{
	namespace Hooks
	{
		float ActorGetSomeStateHook(RE::Actor* actor);

		static REL::Relocation<decltype(ActorGetSomeStateHook)> oActorGetSomeState;

		float ActorGetSomeStateHook(RE::Actor* actor)
		{
			auto pc = RE::PlayerCharacter::GetSingleton();
			if ((pc->GetPlayerRuntimeData().unkBDA & 8) != 0)
				return 0.0;
			return oActorGetSomeState(actor);
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


		void InstallThirdPersonState_SetFreeLookModeHook()
		{
			static REL::Relocation<uintptr_t> ThirdPersonState_SetFreeLookMode{ RELOCATION_ID(49968, 50904) };

			auto& tramp = SKSE::GetTrampoline();
			oActorGetSomeState = tramp.write_call<5>(ThirdPersonState_SetFreeLookMode.address() + 67, ActorGetSomeStateHook);
		}

		void InstallDragonCameraState_UpdRotationHook()
		{
			static REL::Relocation<uintptr_t> DragonCameraState_UpdRotation{ RELOCATION_ID(32371, 33120) };

			auto& tramp = SKSE::GetTrampoline();
			oActorGetSomeState = tramp.write_call<5>(DragonCameraState_UpdRotation.address() + 146, ActorGetSomeStateHook);
		}

		void InstallHorseCameraState_UpdRotationHook()
		{
			static REL::Relocation<uintptr_t> HorseCameraState_UpdRotation{ RELOCATION_ID(49840, 50771) };

			auto& tramp = SKSE::GetTrampoline();
			oActorGetSomeState = tramp.write_call<5>(HorseCameraState_UpdRotation.address() + 132, ActorGetSomeStateHook);
		}

		void InstallHorseCameraState_HandleLookInputHook()
		{
			static REL::Relocation<uintptr_t> HorseCameraState_HandleLookInput{ RELOCATION_ID(49839, 50770) };

			auto& tramp = SKSE::GetTrampoline();
			tramp.write_call<5>(HorseCameraState_HandleLookInput.address() + REL::Relocate(151, 140), CharGetRotationXHook);
		}

		void InstallPlayerCam_subHook()
		{
			static REL::Relocation<uintptr_t> PlayerCam_sub{ RELOCATION_ID(49907, 50840) };

			auto& tramp = SKSE::GetTrampoline();
			tramp.write_call<5>(PlayerCam_sub.address() + REL::Relocate(509, 516), CharModifyRotationXHook);
		}

		void InstallCameraHooks()
		{
			InstallThirdPersonState_SetFreeLookModeHook();
			InstallDragonCameraState_UpdRotationHook();
			InstallHorseCameraState_UpdRotationHook();
			InstallHorseCameraState_HandleLookInputHook();
			InstallPlayerCam_subHook();
		}
	}
}