// Copyright (c) 2010-2022 Lockheed Martin Corporation. All rights reserved.
// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT
//----------------------------------------------------------------------------
//  PDK Data Harvester Sample
//  
//  Description:
//              Requests data on the user object and outputs it to a CSV file.
//              The CSV file will be created relative to the .DLL file.
//
//  Instructions:
//              1. Build this project.
//              2. Copy the "$(ProjectDir)\Output\x64\$(Configuration)\DataHarvester"
//                 directory to the "%USERPROFILE%\Documents\Prepar3D v5 Add-ons" directory.
//              3. Start Prepar3D. Enable the DataHarvester add-on when prompted.
//              4. Start and stop data harvesting from the Prepar3D Add-ons
//                 menu item.
//
//----------------------------------------------------------------------------

#include "initpdk.h"

#include "DataHarvester.h"
#include "StartStopHandler.h"

static DataHarvester    s_DataHarvester;
static StartStopHandler s_StartStopHandler;

using namespace P3D;

extern "C" __declspec(dllexport) void __stdcall DLLStart(__in __notnull IPdk* pPdk)
{
    PdkServices::Init(pPdk);

    s_DataHarvester.Init();

    s_StartStopHandler.Init();
    s_StartStopHandler.SetStartCallback(&DataHarvester::StartCallback, &s_DataHarvester);
    s_StartStopHandler.SetStopCallback(&DataHarvester::StopCallback, &s_DataHarvester);
}

extern "C" __declspec(dllexport) void __stdcall DLLStop(void)
{
    s_StartStopHandler.SetStartCallback(nullptr, nullptr);
    s_StartStopHandler.SetStopCallback(nullptr, nullptr);
    s_StartStopHandler.Deinit();

    s_DataHarvester.Deinit();    

    PdkServices::Shutdown();
}
