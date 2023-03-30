#include "PCH.h"
#include "Serialization.h"
#include "Events/Events.h"


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
		Events::HKPlacePlayerMarkerCallbackFunctor::GetEvent()->Save(a_inf, kOnMarkerChange, kSerializationVersion);
		Events::HKSetDialogueWithPlayer::GetEvent()->Save(a_inf, kOnDialogue, kSerializationVersion);
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
				Events::HKPlacePlayerMarkerCallbackFunctor::GetEvent()->Clear();
				Events::HKPlacePlayerMarkerCallbackFunctor::GetEvent()->Load(a_inf);
				break;
			case kOnDialogue:
				Events::HKSetDialogueWithPlayer::GetEvent()->Clear();
				Events::HKSetDialogueWithPlayer::GetEvent()->Load(a_inf);
				break;
			}
		}
	}


	void OnGameRevert(SKSE::SerializationInterface* a_inf)
	{
		Events::HKPlacePlayerMarkerCallbackFunctor::GetEvent()->Revert(a_inf);
		Events::HKSetDialogueWithPlayer::GetEvent()->Revert(a_inf);
	}
}