#ifndef _VK_API_INFO_H_
#define _VK_API_INFO_H_

#include "../Common/APIInfo.h"

// Local:
#include "../VulkanTrace/VulkanFunctionDefs.h"

//------------------------------------------------------------------------------------
/// DX12 API Base class
//------------------------------------------------------------------------------------
class VKAPIInfo : public APIInfo
{
public:

    /// Constructor
    VKAPIInfo();

    /// Virtual destructor
    virtual ~VKAPIInfo() {}

    /// Vulkan API Type
    vkAPIType m_apiType;

    /// Vulkan API ID, defined in VulkanFunctionDefs.h
    vk_FUNC_TYPE m_apiId;

    // The interface pointer as string
    std::string m_interfacePtrStr;

    /// True for GPU items
    bool m_isGPU;

};


class VKGPUTraceInfo : public VKAPIInfo
{
public:

    /// Constructor
    VKGPUTraceInfo();

    /// Command list type (D3D12_COMMAND_LIST_TYPE)
    int m_commandListType;

    /// The command queue pointer as string
    std::string m_commandQueuePtrStr;

    /// The command buffer pointer as string
    std::string m_commandBufferPtrStr;

    /// The GPU command sample ID
    int m_sampleId;
};


#endif //_VK_API_INFO_H_
