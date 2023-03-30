#pragma once


namespace AutoMove
{
	namespace Papyrus
	{



		bool ForceRefToAlias(RE::TESQuest* script, unsigned int aliasID, RE::TESObjectREFR* ref);


		bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm);
	}
}