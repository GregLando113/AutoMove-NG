#include "PCH.h"
#include "CustomDestination.h"

namespace AutoMove
{
	RE::ObjectRefHandle GetPlayerCustomDestinationRef()
	{
		auto pc = RE::PlayerCharacter::GetSingleton();
		return pc->GetInfoRuntimeData().unk054;
	}
}