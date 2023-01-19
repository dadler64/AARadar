#include "RadarGaugeCallback.h"

using namespace Radar;

///----------------------------------------------------------------------------
/// RadarGaugeCallback Function Definitions
///----------------------------------------------------------------------------
DEFINE_PANEL_CALLBACK_REFCOUNT(RadarGaugeCallback)

RadarGaugeCallback::RadarGaugeCallback(UINT32 containerId, ISimulatedRadarV400* pSimRadar)
	: m_RefCount(1), m_containerId(containerId), m_pRadar(pSimRadar), m_bRadarNeedsDeinit(false)
{}

RadarGaugeCallback::~RadarGaugeCallback()
{
	// if this gauge callback was responsible for initializing the radar then
	// it should deinitialize it.
	if (m_pRadar && m_pRadar->IsInitialized() && m_bRadarNeedsDeinit)
	{
		m_pRadar->DeInit();
	}
}

//
// Getting float/numeric values
//
bool RadarGaugeCallback::GetPropertyValue(SINT32 id, FLOAT64* pValue)
{
	if (!pValue || !m_pRadar)
	{
		return false;
	}

	*pValue = 1.0;      // Start with a reasonable default

	P3DRADAR_VAR eP3DRADARVar = (P3DRADAR_VAR)id;
	double x, y;
	LLA lla;
	switch (eP3DRADARVar)
	{
	case P3DRADAR_ShowRangeRings:
		*pValue = m_pRadar->ShowRangeRings();
		break;
	case P3DRADAR_ShowCursor:
		*pValue = m_pRadar->ShowCursor();
		break;
	case P3DRADAR_FarShoreEnhance:
		*pValue = m_pRadar->FarShoreEnhance();
		break;
	case P3DRADAR_VisualZoom:
		*pValue = m_pRadar->GetVisualZoom();
		break;
	case P3DRADAR_DataZoom:
		*pValue = m_pRadar->GetDataZoom();
		break;
	case P3DRADAR_ScanAzimuth:
		*pValue = m_pRadar->GetScanAzimuth();
		break;
	case P3DRADAR_SweepRate:
		*pValue = m_pRadar->GetSweepRate();
		break;
	case P3DRADAR_RangeMiles:
		*pValue = m_pRadar->GetRangeMiles();
		break;
	case P3DRADAR_RenderingEnabled:
		*pValue = m_pRadar->RenderingEnabled();
		break;
	case P3DRADAR_CursorPositionX:
		m_pRadar->GetCursorPositionXY(x, y);
		*pValue = x;
		break;
	case P3DRADAR_CursorPositionY:
		m_pRadar->GetCursorPositionXY(x, y);
		*pValue = y;
		break;
	case P3DRADAR_CursorPositionLat:
		m_pRadar->GetCursorPositionLLA(lla);
		*pValue = lla.Lat;
		break;
	case P3DRADAR_CursorPositionLon:
		m_pRadar->GetCursorPositionLLA(lla);
		*pValue = lla.Lon;
		break;
	case P3DRADAR_FreezeEnabled:
		if (m_pRadar->FreezeEnabled())
		{
			*pValue = 1.0;
		}
		else
		{
			*pValue = 0.0;
		}
		break;
	case P3DRADAR_FrontBlindSpotDegrees:
		*pValue = m_pRadar->GetFrontBlindspotDegrees();
		break;
	case P3DRADAR_SideBlindSpotDegrees:
		*pValue = m_pRadar->GetSideBlindspotDegrees();
		break;
	case P3DRADAR_RadarResolutionX:
		m_pRadar->GetRadarResolution(x, y);
		*pValue = x;
		break;
	case P3DRADAR_RadarResolutionY:
		m_pRadar->GetRadarResolution(x, y);
		*pValue = y;
		break;
	case P3DRADAR_GaugeResolutionX:
		m_pRadar->GetGaugeResolution(x, y);
		*pValue = x;
		break;
	case P3DRADAR_GaugeResolutionY:
		m_pRadar->GetGaugeResolution(x, y);
		*pValue = y;
		break;
	case P3DRADAR_CurrentRadarScanElevationDegrees:
		*pValue = m_pRadar->GetCurrentRadarScanElevationDegrees();
		break;
	case P3DRADAR_CurrentRadarBeamOffset:
		*pValue = m_pRadar->GetCurrentRadarBeamOffsetDegrees();
		break;
	default:
		return false;
	}
	return true;
}

//
// Setting float/numeric values
//
bool RadarGaugeCallback::SetPropertyValue(SINT32 id, FLOAT64 value)
{
	P3DRADAR_VAR eP3DRADARVar = (P3DRADAR_VAR)id;
	double x, y;
	LLA lla;
	// If radar is being used for the first time initialize it.
	// Another plugin or Prepar3D's internal version of this callback 
	// may have already initialized the radar service so check first
	if (!m_pRadar->IsInitialized())
	{
		// Could do this in the constructor but this will prevent
		// the initialization from happening unless it is actually used
		// (Prepar3D's internal callback does this too so as to not step
		// on the toes of other plugins such as this one.) More than
		// one plugin can interface with the radar system but there
		// is only one instance to share so it should be avoided if possible.
		//
		// If another plugin gets here first then the texture name will be different
		// and your example gauge may stop displaying.  It will still be controlling 
		// the radar though.
		m_pRadar->Init(TEXT("P3DRadarExampleTexture"), 256, 256);
		m_bRadarNeedsDeinit = true;
	}
	switch (eP3DRADARVar)
	{
	case P3DRADAR_ClearRadarImage:
		m_pRadar->ClearRadarImage();
		break;
	case P3DRADAR_ShowRangeRings:
		if (value >= 1.0)
		{
			m_pRadar->SetShowRangeRings(true);
		}
		else
		{
			m_pRadar->SetShowRangeRings(false);
		}
		break;
	case P3DRADAR_ShowCursor:
		if (value >= 1.0)
		{
			m_pRadar->SetShowCursor(true);
		}
		else
		{
			m_pRadar->SetShowCursor(false);
		}
		break;
	case P3DRADAR_FarShoreEnhance:
		if (value >= 1.0)
		{
			m_pRadar->SetFarShoreEnhancementEnabled(true);
		}
		else
		{
			m_pRadar->SetFarShoreEnhancementEnabled(false);
		}
		break;
	case P3DRADAR_VisualZoom:
		m_pRadar->SetVisualZoom(value);
		break;
	case P3DRADAR_DataZoom:
		m_pRadar->SetDataZoom(value);
		break;
	case P3DRADAR_ScanAzimuth:
		m_pRadar->SetScanAzimuthDegrees(value);
		break;
	case P3DRADAR_SweepRate:
		m_pRadar->SetScanRateDegreesPerSecond(value);
		break;
	case P3DRADAR_RangeMiles:
		m_pRadar->SetRangeMiles(value);
		break;
	case P3DRADAR_RenderingEnabled:
		if (value >= 1.0)
		{
			m_pRadar->SetRenderingEnabled(true);
		}
		else
		{
			m_pRadar->SetRenderingEnabled(false);
		}
		break;
	case P3DRADAR_FreezeEnabled:
		if (value >= 1.0)
		{
			m_pRadar->SetFreeze(true);
		}
		else
		{
			m_pRadar->SetFreeze(false);
		}
		break;
	case P3DRADAR_CursorPositionX:
		m_pRadar->GetCursorPositionXY(x, y);
		x = value;
		m_pRadar->SetCursorPositionXY(x, y);
		break;
	case P3DRADAR_CursorPositionY:
		m_pRadar->GetCursorPositionXY(x, y);
		y = value;
		m_pRadar->SetCursorPositionXY(x, y);
		break;
	case P3DRADAR_CursorPositionLat:
		m_pRadar->GetCursorPositionLLA(lla);
		lla.Lat = value;
		m_pRadar->SetCursorPositionLLA(lla);
		break;
	case P3DRADAR_CursorPositionLon:
		m_pRadar->GetCursorPositionLLA(lla);
		lla.Lon = value;
		m_pRadar->SetCursorPositionLLA(lla);
		break;
	case P3DRADAR_FrontBlindSpotDegrees:
		m_pRadar->SetFrontBlindSpotDegrees(value);
		break;
	case P3DRADAR_SideBlindSpotDegrees:
		m_pRadar->SetSideBlindSpotDegrees(value);
		break;
	case P3DRADAR_RadarResolutionX:
		m_pRadar->GetRadarResolution(x, y);
		x = value;
		m_pRadar->SetRadarImageResolution(x, y);
		break;
	case P3DRADAR_RadarResolutionY:
		m_pRadar->GetRadarResolution(x, y);
		y = value;
		m_pRadar->SetRadarImageResolution(x, y);
		break;
	case P3DRADAR_GaugeResolutionX:
		m_pRadar->GetGaugeResolution(x, y);
		x = value;
		m_pRadar->SetRadarGaugeResolution(x, y);
		break;
	case P3DRADAR_GaugeResolutionY:
		m_pRadar->GetGaugeResolution(x, y);
		y = value;
		m_pRadar->SetRadarGaugeResolution(x, y);
		break;
	default:
		return false;
	}
	return true;
}

IGaugeCCallback* RadarGaugeCallback::QueryInterface(LPCSTR pszInterface)
{
	printf("\nDEBUG: Querying interface...\n");

	if (strncmp(pszInterface, ISERIALIZABLE_GAUGECCALLBACK_NAME, strlen(ISERIALIZABLE_GAUGECCALLBACK_NAME)) == 0)
	{
		return this;
	}
	return NULL;
}


////////////////////////////////////////////
//
// Network data (de)serialization functions
// 
////////////////////////////////////////////

bool RadarGaugeCallback::Serialize(NetOutPublic& netout)
{
	// Only serialize if the callback has actually used the radar and explicitly initialized it
	// this is just a safe guard in case other plug-ins use the radar.  Future versions of the radar
	// may support multiple instances but for now there is one instance.
	if (m_bRadarNeedsDeinit)
	{
		RadarGaugeSerializationData data;
		data.ShowRangeRings = m_pRadar->ShowRangeRings();
		data.ShowCursor = m_pRadar->ShowCursor();
		data.FarShoreEnhance = m_pRadar->FarShoreEnhance();
		data.VisualZoom = m_pRadar->GetVisualZoom();
		data.DataZoom = m_pRadar->GetDataZoom();
		data.ScanAzimuth = m_pRadar->GetScanAzimuth();
		data.SweepRate = m_pRadar->GetSweepRate();
		data.RangeMiles = m_pRadar->GetRangeMiles();
		data.RenderingEnabled = m_pRadar->RenderingEnabled();
		m_pRadar->GetCursorPositionXY(data.CursorPositionX, data.CursorPositionY);
		data.FreezeEnabled = m_pRadar->FreezeEnabled();
		data.FrontBlindspotDegrees = m_pRadar->GetFrontBlindspotDegrees();
		data.SideBlindspotDegrees = m_pRadar->GetSideBlindspotDegrees();
		m_pRadar->GetRadarResolution(data.RadarResolutionX, data.RadarResolutionY);
		m_pRadar->GetGaugeResolution(data.GaugeResolutionX, data.GaugeResolutionY);
		//Write the entire struct out to the network packet.
		netout.WriteData(&data, sizeof(RadarGaugeSerializationData));
	}
	return true;
}

bool RadarGaugeCallback::Deserialize(NetInPublic& netin)
{
	const RadarGaugeSerializationData* pData;
	pData = (RadarGaugeSerializationData*)netin.GetCurBuffer();
	// If this plugin serialized data a valid header should be at the current read location
	if (pData->Header.IsValid())
	{
		// found a valid header as expected so go ahead and read the size specified in the header 
		// so that the netin's current position is correct when returned to the caller
		pData = (RadarGaugeSerializationData*)netin.Read(pData->Header.SizeInBytes);
		// Only deserialize if the version and size matches.
		if (pData->Header.IsCurrentVersion() && pData->Header.ValidateSize())
		{
			// if the radar service has not been initialized then initialize it now.
			if (!m_pRadar->IsInitialized())
			{
				m_pRadar->Init(TEXT("P3DRadarExampleTexture"), 256, 256);
				m_bRadarNeedsDeinit = true;
			}
			// set all the serialized data into the radar
			m_pRadar->SetShowRangeRings(pData->ShowRangeRings);
			m_pRadar->SetShowCursor(pData->ShowCursor);
			m_pRadar->SetFarShoreEnhancementEnabled(pData->FarShoreEnhance);
			m_pRadar->SetVisualZoom(pData->VisualZoom);
			m_pRadar->SetDataZoom(pData->DataZoom);
			m_pRadar->SetScanAzimuthDegrees(pData->ScanAzimuth);
			m_pRadar->SetScanRateDegreesPerSecond(pData->SweepRate);
			m_pRadar->SetRangeMiles(pData->RangeMiles);
			m_pRadar->SetRenderingEnabled(pData->RenderingEnabled);
			m_pRadar->SetCursorPositionXY(pData->CursorPositionX, pData->CursorPositionY);
			m_pRadar->SetFreeze(pData->FreezeEnabled);
			m_pRadar->SetFrontBlindSpotDegrees(pData->FrontBlindspotDegrees);
			m_pRadar->SetSideBlindSpotDegrees(pData->SideBlindspotDegrees);
			m_pRadar->SetRadarGaugeResolution(pData->RadarResolutionX, pData->RadarResolutionY);
			m_pRadar->SetRadarGaugeResolution(pData->GaugeResolutionX, pData->GaugeResolutionY);
		}
	}
	return true;
}
