#include "../PCH.h"
#include "Hooks.h"
#include "../Papyrus.h"
#include "../CustomDestination.h"


namespace AutoMove
{
	namespace Hooks
	{
		// AutoMoveHandler::CanProcess
		// SSE 1.5.97 ID: 263061

		namespace
		{
			bool AutoMove_CanProcessHook(RE::AutoMoveHandler* thisptr, RE::InputEvent* evt);
			static REL::Relocation<decltype(AutoMove_CanProcessHook)> oAutoMove_CanProcess;
			bool AutoMove_CanProcessHook(RE::AutoMoveHandler* thisptr, RE::InputEvent* evt)
			{
				return oAutoMove_CanProcess(thisptr, evt) && !GetPlayerCustomDestinationRef();
			}
		}


		void InstallAutoMoveCanProcessHook()
		{
			static REL::Relocation<std::uintptr_t> AutoMoveHandlerVTBL{ RE::VTABLE_AutoMoveHandler[0] };
			oAutoMove_CanProcess = AutoMoveHandlerVTBL.write_vfunc(1, AutoMove_CanProcessHook);
		}
	}
}