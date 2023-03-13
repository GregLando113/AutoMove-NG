#include "../PCH.h"
#include "Hooks.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Hooks
	{
		static REL::Relocation<decltype(HKPlacePlayerMarkerCallbackFunctor::RunHook)> oPlacePlayerMarker;

		void HKPlacePlayerMarkerCallbackFunctor::Install()
		{
			REL::Relocation<std::uintptr_t> MarkerFunctorVTBL{ HKPlacePlayerMarkerCallbackFunctor::VTABLE[0] };
			oPlacePlayerMarker = MarkerFunctorVTBL.write_vfunc(1, HKPlacePlayerMarkerCallbackFunctor::RunHook);
		}


		void HKPlacePlayerMarkerCallbackFunctor::RunHook(RE::BSIntrusiveRefCounted* functor, RE::IMessageBoxCallback::Message a_msg)
		{
			auto onCustomMarkerChange = Papyrus::GetOnCustomMarkerChangeEvent();
			onCustomMarkerChange->QueueEvent(a_msg);
			return oPlacePlayerMarker(functor, a_msg);
		}
	}
}


