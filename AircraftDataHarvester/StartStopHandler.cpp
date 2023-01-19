// Copyright (c) 2010-2022 Lockheed Martin Corporation. All rights reserved.
// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT

// StartStopHandler.cpp

#include "StartStopHandler.h"

#include "SimConnect.h"

enum EVENT_ID
{
    EVENT_ID_START,
    EVENT_ID_STOP,
};

static const char* TITLE_STRING = "Start/Stop Handler";
static const char* START_STRING = "Start Harvest (PDK)";
static const char* STOP_STRING  = "Stop Harvest (PDK)";

void CALLBACK StartStopDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
    StartStopHandler* pStartStopHandler = static_cast<StartStopHandler*>(pContext);
    if (pStartStopHandler)
    {
        pStartStopHandler->HandleDispatch(pData, cbData);
    }
}

HRESULT StartStopHandler::HandleDispatch(SIMCONNECT_RECV* pData, DWORD cbData)
{
    HRESULT hr = S_FALSE;

    switch (pData->dwID)
    {
        case SIMCONNECT_RECV_ID_EVENT:
        {
            SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

            switch (evt->uEventID)
            {
                case EVENT_ID_START:
                {
                    if (m_pfStartCallback)
                    {
                        if (SUCCEEDED(m_pfStartCallback(m_pStartContext)))
                        {
                            hr = SimConnect_MenuDeleteItem(m_hSimConnect, EVENT_ID_START);
                            hr = SimConnect_MenuAddItem(m_hSimConnect, STOP_STRING, EVENT_ID_STOP, 0);

                            m_bIsRunning = true;
                        }
                    }

                    break;
                }
                case EVENT_ID_STOP:
                {
                    if (m_pfStopCallback)
                    {
                        m_pfStopCallback(m_pStopContext);
                    }

                    hr = SimConnect_MenuDeleteItem(m_hSimConnect, EVENT_ID_STOP);
                    hr = SimConnect_MenuAddItem(m_hSimConnect, START_STRING, EVENT_ID_START, 0);

                    m_bIsRunning = false;

                    break;
                }
                default:
                {
                    break;
                }
            }

            break; // SIMCONNECT_RECV_ID_EVENT
        }
        default:
        {
            break;
        }
    }

    return hr;
}

HRESULT StartStopHandler::Init()
{
    HRESULT hr = E_FAIL;

    if (SUCCEEDED(SimConnect_Open(&m_hSimConnect, TITLE_STRING, NULL, 0, 0, 0)))
    {
        // Create the start/stop events.
        hr = SimConnect_MapClientEventToSimEvent(m_hSimConnect, EVENT_ID_START);
        hr = SimConnect_MapClientEventToSimEvent(m_hSimConnect, EVENT_ID_STOP);

        // Add the start menu item.
        hr = SimConnect_MenuAddItem(m_hSimConnect, START_STRING, EVENT_ID_START, 0);

        hr = SimConnect_CallDispatch(m_hSimConnect, StartStopDispatchProc, this);
    }

    return hr;
}

HRESULT StartStopHandler::Deinit()
{
    HRESULT hr = E_FAIL;

    if (m_hSimConnect != NULL)
    {
        // Clean up before exiting
        if (!m_bIsRunning)
        {
            hr = SimConnect_MenuDeleteItem(m_hSimConnect, EVENT_ID_START);
        }
        else
        {
            hr = SimConnect_MenuDeleteItem(m_hSimConnect, EVENT_ID_STOP);
        }

        hr = SimConnect_Close(m_hSimConnect);
    }

    return hr;
}
