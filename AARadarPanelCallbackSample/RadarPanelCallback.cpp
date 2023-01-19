// Copyright (c) 2010-2022 Lockheed Martin Corporation. All rights reserved.
// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT

// RadarPanelCallback.cpp

#define _CRT_RAND_S
#include "RadarPanelCallback.h"

using namespace Radar;

///----------------------------------------------------------------------------
/// RadarPanelPallback function  Definitions
///----------------------------------------------------------------------------
DEFINE_PANEL_CALLBACK_REFCOUNT(RadarPanelCallback);

RadarPanelCallback::RadarPanelCallback(ISimulatedRadarV400* pSimRadar)
	: m_RefCount(1), m_pRadar(pSimRadar)
{
	// init property table
	for (int n = 0; n < 5; n++)
	{
		if (ImportTable.PANELSentry.fnptr != NULL &&
			P3DRADAR_PROPERTY_TABLE[n].units == UNITS_UNKNOWN)
		{
			P3DRADAR_PROPERTY_TABLE[n].units = get_units_enum(P3DRADAR_PROPERTY_TABLE[n].szUnitsName);
		}
	}
}

bool RadarPanelCallback::ConvertStringToProperty(PCSTRINGZ keyword, SINT32* pID)
{
	if (!keyword)
	{
		return false;
	}
	if (!pID)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE* parPropertyTable = GetPropertyTable(uNumProperties);

	for (UINT i = 0; i < uNumProperties; i++)
	{
		if (_stricmp(parPropertyTable[i].szPropertyName, keyword) == 0)
		{
			*pID = i;
			return true;
		}
	}
	return false;
}

bool RadarPanelCallback::ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword)
{
	if (!pKeyword)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE* parPropertyTable = GetPropertyTable(uNumProperties);

	if (id < 0 || id >= (SINT32)uNumProperties)
	{
		return false;
	}
	*pKeyword = parPropertyTable[id].szPropertyName;
	return true;
}

bool RadarPanelCallback::GetPropertyUnits(SINT32 id, ENUM* pEnum)
{
	if (!pEnum)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE* parPropertyTable = GetPropertyTable(uNumProperties);

	if (id < 0 || id >= (SINT32)uNumProperties)
	{
		return false;
	}

	*pEnum = parPropertyTable[id].units;
	return true;
}

IAircraftCCallback* RadarPanelCallback::CreateAircraftCCallback(UINT32 ContainerID)
{
	return new RadarAircraftCallback(ContainerID, m_pRadar);
}

const PROPERTY_TABLE* RadarPanelCallback::GetPropertyTable(UINT& uLength)
{
	uLength = LENGTHOF(P3DRADAR_PROPERTY_TABLE);
	return P3DRADAR_PROPERTY_TABLE;
}


