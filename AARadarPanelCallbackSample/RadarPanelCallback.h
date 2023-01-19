#pragma once

#include "ISimulatedRadar.h"

#include "Properties.h"
#include "RadarAircraftCallback.h"

namespace Radar {


	class RadarPanelCallback : public IPanelCCallback
	{
		DECLARE_PANEL_CALLBACK_REFCOUNT(PanelCallback);
	public:
		RadarPanelCallback(ISimulatedRadarV400* pSimRadar);

		// ******* IPanelCCallback Methods *****************    
		virtual IPanelCCallback* QueryInterface(LPCSTR pszInterface) override { return nullptr; }
		virtual UINT32 GetVersion() override { return 1; }
		virtual bool ConvertStringToProperty(PCSTRINGZ keyword, SINT32* pID) override;
		virtual bool ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword) override;
		virtual bool GetPropertyUnits(SINT32 id, ENUM* pEnum) override;
		virtual IAircraftCCallback* CreateAircraftCCallback(UINT32 ContainerID) override;
	protected:
		const PROPERTY_TABLE* GetPropertyTable(UINT& uLength);
		CComPtr<ISimulatedRadarV400> m_pRadar;
	};
}