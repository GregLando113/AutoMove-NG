#include "PCH.h"
#include "Serialization.h"
#include "Papyrus.h"


namespace AutoMove
{

	void OnGameSave(SKSE::SerializationInterface* a_inf)
	{
		auto markerchange = Papyrus::GetOnCustomMarkerChangeEvent();
		markerchange->Save(a_inf, 'MARK', 101);
		auto dialogue = Papyrus::GetOnPlayerDialogueEvent();
		dialogue->Save(a_inf, 'DIAL', 101);
	}

	void OnGameLoad(SKSE::SerializationInterface* a_inf)
	{
		auto markerchange = Papyrus::GetOnCustomMarkerChangeEvent();
		markerchange->Load(a_inf);
		auto dialogue = Papyrus::GetOnPlayerDialogueEvent();
		dialogue->Load(a_inf);
	}


	void OnGameRevert(SKSE::SerializationInterface* a_inf)
	{
		auto markerchange = Papyrus::GetOnCustomMarkerChangeEvent();
		markerchange->Revert(a_inf);
		auto dialogue = Papyrus::GetOnPlayerDialogueEvent();
		dialogue->Revert(a_inf);
	}
}