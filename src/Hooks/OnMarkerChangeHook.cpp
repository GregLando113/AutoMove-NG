#include "../PCH.h"
#include "Hooks.h"

#include "../Papyrus.h"

namespace AutoMove
{
	namespace Hooks
	{
		using PlacePlayerMarkerHook_t = decltype(&CPlacePlayerMarkerCallbackFunctor::RunHook);
		static PlacePlayerMarkerHook_t oPlacePlayerMarker;

		void CPlacePlayerMarkerCallbackFunctor::Install()
		{
			union {
				uintptr_t ptr;
				PlacePlayerMarkerHook_t fn;
			} cpp_bs;

			// onMarkerChange
			uintptr_t marker_vt = (CPlacePlayerMarkerCallbackFunctor::VTABLE[0].address() + 8);
			cpp_bs.ptr = *(uintptr_t*)marker_vt;
			oPlacePlayerMarker = cpp_bs.fn;
			cpp_bs.fn = &CPlacePlayerMarkerCallbackFunctor::RunHook;
			REL::safe_write(marker_vt, cpp_bs.ptr);
		}


		void CPlacePlayerMarkerCallbackFunctor::RunHook(RE::IMessageBoxCallback::Message msg)
		{
			auto& onCustomMarkerChange = Papyrus::GetOnCustomMarkerChangeEvent();
			onCustomMarkerChange.QueueEvent(msg);
			return (this->*oPlacePlayerMarker)(msg);
		}
	}
}


