// NearbyAircraftHarvester.h

#pragma once

#include <Windows.h>
#include <fstream>

#include "IUnknownHelper.h"
#include "IEventService.h"

class NearbyAircraftHarvester : P3D::ICallbackV400
{
    DEFAULT_REFCOUNT_INLINE_IMPL();
    STDMETHODIMP QueryInterface(REFIID riid, PVOID* ppv)
    {
        HRESULT hr = E_NOINTERFACE;

        if (ppv == NULL)
        {
            return E_POINTER;
        }

        *ppv = NULL;

        if (IsEqualIID(riid, P3D::IID_ICallbackV400))
        {
            *ppv = static_cast<P3D::ICallbackV400*>(this);
        }
        else if (IsEqualIID(riid, IID_IUnknown))
        {
            *ppv = static_cast<IUnknown*>(this);
        }
        if (*ppv)
        {
            hr = S_OK;
            AddRef();
        }

        return hr;
    };

public:

    DataHarvester() :
        m_RefCount(1),
        m_bIsHarvesting(false)
    {
    }

    virtual void Invoke(P3D::IParameterListV400* pParams);

    static HRESULT StartCallback(void* pContext);
    static HRESULT StopCallback(void* pContext);

    HRESULT Init();
    HRESULT Deinit();

private:

    HRESULT Start();
    HRESULT Stop();

    void PrintHeader();

    template<class T>
    void PrintValue(T value, bool bIsValid = true, bool bIsLast = false);

    bool            m_bIsHarvesting;
    std::wstring    m_strOutputFilePath;
    std::wstring    m_strInputFilePath;
    std::wfstream   m_fs;
    std::wfstream   m_fInputstream;

};
