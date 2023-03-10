#pragma once


namespace AutoMove
{
	namespace Papyrus
	{
		SKSE::RegistrationSet<RE::IMessageBoxCallback::Message>& GetOnCustomMarkerChangeEvent();
		SKSE::RegistrationSet<RE::Actor*, bool>& GetOnPlayerDialogueEvent();


		bool ForceRefToAlias(RE::TESQuest* script, unsigned int aliasID, RE::TESObjectREFR* ref);


		bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm);
	}
}