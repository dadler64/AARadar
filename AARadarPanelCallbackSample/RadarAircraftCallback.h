#pragma once

#include "gauges.h"
#include "ISimulatedRadar.h"

#include "RadarGaugeCallback.h"


namespace Radar
{

	class RadarAircraftCallback : public IAircraftCCallback
	{
		DECLARE_PANEL_CALLBACK_REFCOUNT(AircraftCallback);
	public:
		RadarAircraftCallback(UINT32 containerId, ISimulatedRadarV400* pRadar);

		// ******* IAircraftCCallback Methods ************* 
		virtual  IAircraftCCallback* QueryInterface(LPCSTR pszInterface) override { return nullptr; }
		virtual void Update() override {}
		virtual IGaugeCCallback* CreateGaugeCCallback() override;
	protected:
		UINT32 GetContainerId()  const { return m_containerId; }

	private:
		UINT32 m_containerId;
		CComPtr<ISimulatedRadarV400> m_pRadar;
	};
}