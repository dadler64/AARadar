// Copyright (c) 2010-2022 Lockheed Martin Corporation. All rights reserved.
// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT

// StartStopHandler.h

#pragma once

#include <Windows.h>

struct SIMCONNECT_RECV;

typedef HRESULT(*PStartStopCallback)(void*);

class StartStopHandler
{
public:

    StartStopHandler() :
        m_hSimConnect(nullptr),
        m_bIsRunning(false),
        m_pfStartCallback(nullptr),
        m_pfStopCallback(nullptr)
    {
    }

    HRESULT Init();
    HRESULT Deinit();

    HRESULT HandleDispatch(SIMCONNECT_RECV* pData, DWORD cbData);

    void SetStartCallback(PStartStopCallback pfCallback, void* pContext) { m_pfStartCallback = pfCallback; m_pStartContext = pContext; }
    void SetStopCallback (PStartStopCallback pfCallback, void* pContext) { m_pfStopCallback  = pfCallback; m_pStopContext  = pContext; }

private:

    HANDLE  m_hSimConnect;
    bool    m_bIsRunning;

    PStartStopCallback m_pfStartCallback;
    PStartStopCallback m_pfStopCallback;

    void* m_pStartContext;
    void* m_pStopContext;
};
