#include "RadarAircraftCallback.h"

using namespace Radar;


///----------------------------------------------------------------------------
/// RadarAircraftCallback Function Definitions
///----------------------------------------------------------------------------
DEFINE_PANEL_CALLBACK_REFCOUNT(RadarAircraftCallback);

RadarAircraftCallback::RadarAircraftCallback(UINT32 containerId, ISimulatedRadarV400* pRadar)
	: m_containerId(containerId), m_RefCount(1), m_pRadar(pRadar)
{
}

IGaugeCCallback* RadarAircraftCallback::CreateGaugeCCallback()
{
	return new RadarGaugeCallback(GetContainerId(), m_pRadar);
}
