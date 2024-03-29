#include "../PCH.h"
#include "Hooks.h"


namespace AutoMove
{
	namespace Hooks
	{
		void InstallCameraHooks();
		void InstallAutoMoveCanProcessHook();

		void Install()
		{
			InstallCameraHooks();
			InstallAutoMoveCanProcessHook();
		}
	}
}