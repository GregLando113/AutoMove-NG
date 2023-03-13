#include "PCH.h"
#include "Serialization.h"
#include "Papyrus.h"


namespace AutoMove
{
	namespace
	{
		const uint32_t kSerializationVersion = 101;
		const uint32_t kOnMarkerChange = 'MARK';
		const uint32_t kOnDialogue = 'DIAL';
	}

	void OnGameSave(SKSE::SerializationInterface* a_inf)
	{
		Papyrus::GetOnCustomMarkerChangeEvent()->Save(a_inf, kOnMarkerChange, kSerializationVersion);
		Papyrus::GetOnPlayerDialogueEvent()->Save(a_inf, kOnDialogue, kSerializationVersion);
	}

	void OnGameLoad(SKSE::SerializationInterface* a_inf)
	{
		uint32_t type;
		uint32_t version;
		uint32_t length;
		while (a_inf->GetNextRecordInfo(type, version, length))
		{
			if (version != kSerializationVersion) {
				// Data is out of date or from the SSE version
				// Dont load.
				continue;
			}

			switch (type) {
			case kOnMarkerChange:
				Papyrus::GetOnCustomMarkerChangeEvent()->Clear();
				Papyrus::GetOnCustomMarkerChangeEvent()->Load(a_inf);
				break;
			case kOnDialogue:
				Papyrus::GetOnPlayerDialogueEvent()->Clear();
				Papyrus::GetOnPlayerDialogueEvent()->Load(a_inf);
				break;
			}
		}
	}


	void OnGameRevert(SKSE::SerializationInterface* a_inf)
	{
		Papyrus::GetOnCustomMarkerChangeEvent()->Revert(a_inf);
		Papyrus::GetOnPlayerDialogueEvent()->Revert(a_inf);
	}
}