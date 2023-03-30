#include "../PCH.h"
#include "OnCustomDestinationArrived.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Events
	{
		SKSE::RegistrationSet<>* HKMovementControllerGoal::GetCustomDestinationArrivedEvent()
		{
			static SKSE::RegistrationSet<> onCustomDestinationArrived("OnCustomDestinationArrived");
			return &onCustomDestinationArrived;
		}
	}
}
