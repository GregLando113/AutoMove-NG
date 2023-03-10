#include "../PCH.h"
#include "Hooks.h"


namespace AutoMove
{
	namespace Hooks
	{
		void Install()
		{
			CPlacePlayerMarkerCallbackFunctor::Install();
			CSetDialogueWithPlayerHook::Install();
		}
	}
}