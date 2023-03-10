#include "../PCH.h"
#include "Hooks.h"


namespace AutoMove
{
	namespace Hooks
	{
		void InstallCameraHooks();

		void Install()
		{
			HKPlacePlayerMarkerCallbackFunctor::Install();
			HKSetDialogueWithPlayer::Install();
			//InstallCameraHooks();
		}
	}
}