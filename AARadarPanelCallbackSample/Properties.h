#pragma once

#include "gauges.h"

namespace Radar
{


	// Note: The items in the property table correspond to the indices that
	// will be returned in the Get/Set Property functions
	struct PROPERTY_TABLE
	{
		PCSTRINGZ szPropertyName;
		PCSTRINGZ szUnitsName;
		ENUM      units;
	};




	// Enum that contains the properties 
	enum P3DRADAR_VAR
	{
		P3DRADAR_ClearRadarImage,
		P3DRADAR_ShowRangeRings,
		P3DRADAR_ShowCursor,
		P3DRADAR_FarShoreEnhance,
		P3DRADAR_VisualZoom,
		P3DRADAR_DataZoom,
		P3DRADAR_ScanAzimuth,
		P3DRADAR_SweepRate,
		P3DRADAR_RangeMiles,
		P3DRADAR_RenderingEnabled,
		P3DRADAR_FreezeEnabled,
		P3DRADAR_CursorPositionX,
		P3DRADAR_CursorPositionY,
		P3DRADAR_CursorPositionLat,
		P3DRADAR_CursorPositionLon,
		P3DRADAR_FrontBlindSpotDegrees,
		P3DRADAR_SideBlindSpotDegrees,
		P3DRADAR_RadarResolutionX,
		P3DRADAR_RadarResolutionY,
		P3DRADAR_GaugeResolutionX,
		P3DRADAR_GaugeResolutionY,
		P3DRADAR_CurrentRadarScanElevationDegrees,
		P3DRADAR_CurrentRadarBeamOffset,
	};
	// table of property info.  Must stay lined up with enum above
	static PROPERTY_TABLE P3DRADAR_PROPERTY_TABLE[] =
	{
		{ "ClearRadarImage",	                "Number",   UNITS_UNKNOWN },
		{ "ShowRangeRings",	                    "Number",   UNITS_UNKNOWN },
		{ "ShowCursor",			                "Number",   UNITS_UNKNOWN },
		{ "FarShoreEnhance",	                "Number",   UNITS_UNKNOWN },
		{ "VisualZoom",			                "Number",   UNITS_UNKNOWN },
		{ "DataZoom",	                        "Number",   UNITS_UNKNOWN },
		{ "ScanAzimuth",	                    "Number",   UNITS_UNKNOWN },
		{ "SweepRate",	                        "Number",   UNITS_UNKNOWN },
		{ "RangeMiles",	                        "Number",   UNITS_UNKNOWN },
		{ "RenderingEnabled",	                "Number",   UNITS_UNKNOWN },
		{ "FreezeEnabled",	                    "Number",   UNITS_UNKNOWN },
		{ "CursorPositionX",	                "Number",   UNITS_UNKNOWN },
		{ "CursorPositionY",	                "Number",   UNITS_UNKNOWN },
		{ "CursorPositionLat",	                "Number",   UNITS_UNKNOWN },
		{ "CursorPositionLon",	                "Number",   UNITS_UNKNOWN },
		{ "FrontBlindSpotDegrees",	            "Number",   UNITS_UNKNOWN },
		{ "SideBlindSpotDegrees",	            "Number",   UNITS_UNKNOWN },
		{ "RadarResolutionX",	                "Number",   UNITS_UNKNOWN },
		{ "RadarResolutionY",	                "Number",   UNITS_UNKNOWN },
		{ "GaugeResolutionX",	                "Number",   UNITS_UNKNOWN },
		{ "GaugeResolutionY",	                "Number",   UNITS_UNKNOWN },
		{ "CurrentRadarScanElevationDegrees",   "Number",   UNITS_UNKNOWN },
		{ "CurrentRadarBeamOffset",	            "Number",   UNITS_UNKNOWN },
	};
}