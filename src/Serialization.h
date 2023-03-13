#pragma once

#include "SKSE/Interfaces.h"

namespace AutoMove
{
	void OnGameSave(SKSE::SerializationInterface* a_inf);
	void OnGameLoad(SKSE::SerializationInterface* a_inf);
	void OnGameRevert(SKSE::SerializationInterface* a_inf);
}