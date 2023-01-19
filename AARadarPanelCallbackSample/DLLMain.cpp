#include "gauges.h"
#include "PDK.h"

#include "RadarPanelCallback.h"

using namespace Radar;

// The Panels pointer will get filled in during the loading process
// if this DLL is listed in DLL.XML
//  
//  entry in dll.xml should look like this where PATH_TO_DLL is local to the Prepar3d install directory
//  or is an absolute path:
//
//  <Launch.Addon>
//      <Name>RadarSample</Name>
//      <DLLType>PDK</DLLType>
//      <Disabled>False</Disabled>
//      <ManualLoad>False</ManualLoad>
//      <Path>PATH_TO_DLL\RadarPanelCallback.dll</Path>
//  </Launch.Addon>
//

PPANELS Panels = NULL;

static const char RADAR_EXAMPLE_CALLBACK_NAME[] = "P3DRadarExample";

GAUGESIMPORT    ImportTable =
{
	{ 0x0000000F, (PPANELS)NULL },
	{ 0x00000000, NULL }
};

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}

extern "C"
{
	void __stdcall DLLStart(__in __notnull P3D::IPdk* pPdk)
	{
		if (pPdk != nullptr && Panels != nullptr)
		{
			// Check for radar interface
			ISimulatedRadarV400* pRadar;
			pPdk->QueryService(Radar::SID_SimulatedRadar, &pRadar);
			if (pRadar != nullptr)
			{
				// create panel callback passing in the radar service pointer
				RadarPanelCallback* pPanelCallback = new RadarPanelCallback(pRadar);
				// hook up the panels table for good measure even though its not being used 
				ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
				// register the panel callback by name for mixed mode C: variables 
				panel_register_c_callback(RADAR_EXAMPLE_CALLBACK_NAME, pPanelCallback);
				// clean up local ref counted resources
				pPanelCallback->Release();
				pRadar->Release();
			}
		}
		return;
	}

	void __stdcall DLLStop(void)
	{
		// unregister the callback
		panel_register_c_callback(RADAR_EXAMPLE_CALLBACK_NAME, nullptr);
	}
}

// This is the module's export table.
GAUGESLINKAGE   Linkage =
{
	0x00000013,
	0,
	0,
	0,
	0,

	FS9LINK_VERSION, { 0 }
};