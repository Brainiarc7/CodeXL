//=============================================================================
/// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file Wrapped_ID3D12Object.cpp
/// \brief A class used to wrap D3D12's ID3D12Object interface.
//=============================================================================

#include "Wrapped_ID3D12Object.h"
#include "../DX12ObjectDatabaseProcessor.h"
#include "../../Interception/DX12Interceptor.h"
#include "../../DX12LayerManager.h"
#include "../../../Common/IUnknownWrapperGUID.h"

class Wrapped_ID3D12Device;

//-----------------------------------------------------------------------------
/// Utility function used to wrap the D3D12 interface.
/// \param inParentDevice The parent device for the interface.
/// \param inRealObject The real runtime instance of the D3D12 interface.
/// \returns True if the interface was wrapped successfully.
//-----------------------------------------------------------------------------
bool WrapD3D12Object(Wrapped_ID3D12Device* inParentDevice, ID3D12Object** inRealObject)
{
    return GenericWrapObject<ID3D12Object, Wrapped_ID3D12Object>(inParentDevice, inRealObject, kObjectType_ID3D12Object, nullptr);
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::QueryInterface
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE Wrapped_ID3D12Object::QueryInterface(REFIID riid, void** ppvObject)
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    HRESULT result = {};

    if (riid == IID_IWrappedObject)
    {
        *ppvObject = mRealObject;
        result = S_OK;
    }
    else
    {
        DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

        if (interceptor && interceptor->ShouldCollectTrace())
        {
            ParameterEntry parameters[] =
            {
                { PARAMETER_REFIID, &riid },
                { PARAMETER_POINTER, ppvObject },
            };

            int numParameters = (sizeof(parameters) / sizeof(parameters[0]));
            DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_IUnknown_QueryInterface, numParameters, parameters);
            result = mRealObject->QueryInterface(riid, ppvObject);
            interceptor->PostCall(pNewEntry, result);
        }
        else
        {
            result = mRealObject->QueryInterface(riid, ppvObject);
        }

        if (result == S_OK)
        {
            if (riid == __uuidof(ID3D12Object))
            {
                WrapD3D12Object(nullptr, (ID3D12Object**)ppvObject);
            }
        }
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::AddRef
//-----------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE Wrapped_ID3D12Object::AddRef()
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    ULONG result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_IUnknown_AddRef, 0, nullptr);
        result = mRealObject->AddRef();
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->AddRef();
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::Release
//-----------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE Wrapped_ID3D12Object::Release()
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    ULONG result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_IUnknown_Release, 0, nullptr);
        result = mRealObject->Release();
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->Release();
    }

    if (result == 0)
    {
        DX12WrappedObjectDatabase* objectDatabase = (DX12WrappedObjectDatabase*)DX12ObjectDatabaseProcessor::Instance()->GetObjectDatabase();
        IDX12InstanceBase* objectMetadata = objectDatabase->GetMetadataObject(this);

        if (objectMetadata != nullptr)
        {
            objectMetadata->FlagAsDestroyed();
        }
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::GetPrivateData
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE Wrapped_ID3D12Object::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData)
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    HRESULT result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        ParameterEntry parameters[] =
        {
            { PARAMETER_GUID, &guid },
            { PARAMETER_POINTER, pDataSize },
            { PARAMETER_POINTER, pData },
        };

        int numParameters = (sizeof(parameters) / sizeof(parameters[0]));
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_ID3D12Object_GetPrivateData, numParameters, parameters);
        result = mRealObject->GetPrivateData(guid, pDataSize, pData);
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->GetPrivateData(guid, pDataSize, pData);
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::SetPrivateData
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE Wrapped_ID3D12Object::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData)
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    HRESULT result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        ParameterEntry parameters[] =
        {
            { PARAMETER_GUID, &guid },
            { PARAMETER_UNSIGNED_INT, &DataSize },
            { PARAMETER_POINTER, pData },
        };

        int numParameters = (sizeof(parameters) / sizeof(parameters[0]));
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_ID3D12Object_SetPrivateData, numParameters, parameters);
        result = mRealObject->SetPrivateData(guid, DataSize, pData);
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->SetPrivateData(guid, DataSize, pData);
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::SetPrivateDataInterface
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE Wrapped_ID3D12Object::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData)
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    HRESULT result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        ParameterEntry parameters[] =
        {
            { PARAMETER_GUID, &guid },
            { PARAMETER_POINTER_SPECIAL, pData },
        };

        int numParameters = (sizeof(parameters) / sizeof(parameters[0]));
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_ID3D12Object_SetPrivateDataInterface, numParameters, parameters);
        result = mRealObject->SetPrivateDataInterface(guid, pData);
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->SetPrivateDataInterface(guid, pData);
    }

    return result;
}

//-----------------------------------------------------------------------------
/// Wrapped_ID3D12Object::SetName
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE Wrapped_ID3D12Object::SetName(LPCWSTR Name)
{
#if SERIALIZE_DX12_ENTRY_POINTS
    ScopeLock lock(&s_mutex);
#endif

    HRESULT result = {};

    DX12Interceptor* interceptor = GetDX12LayerManager()->GetInterceptor();

    if (interceptor && interceptor->ShouldCollectTrace())
    {
        ParameterEntry parameters[] =
        {
            { PARAMETER_WIDE_STRING, Name },
        };

        int numParameters = (sizeof(parameters) / sizeof(parameters[0]));
        DX12APIEntry* pNewEntry = interceptor->PreCall(this, FuncId_ID3D12Object_SetName, numParameters, parameters);
        result = mRealObject->SetName(Name);
        interceptor->PostCall(pNewEntry, result);
    }
    else
    {
        result = mRealObject->SetName(Name);
    }

    return result;
}