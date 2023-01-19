#include "DeviceMng_WindowAPP.hpp"

DeviceMng_WindowAPP::DeviceMng_WindowAPP(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept
: _instance { p_instance }, _surface { p_surface }
{
    getSuitableDevice();
    initLogicalDeviceInfo();
    createLogicalDevice();
    getQueueHandlers();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DeviceMng_WindowAPP::~DeviceMng_WindowAPP() noexcept
{
    if(_logicalDevice != VK_NULL_HANDLE)
    {
		VkResult result = vkDeviceWaitIdle( _logicalDevice );

        assert(result == VK_SUCCESS);

        vkDestroyDevice( _logicalDevice, nullptr );
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng_WindowAPP::getSuitableDevice() noexcept
{
    uint32_t phDevicesCount { 0 };
    Vector<VkPhysicalDevice> phDevices;
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, nullptr );
    phDevices.resize( phDevicesCount );
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, &phDevices[0] );

    for(auto& device : phDevices)
    {
        _graphicQueueID.reset();
        _presentQueueID.reset();
        if(checkDeviceSuitability(device))
        {
            _physicalDevice = device;
            break;
        }
    }

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng_WindowAPP::checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept
{
    uint32_t countQueueFamilies { 0 };
    Vector<VkQueueFamilyProperties> queueFamilies {};

    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, nullptr );
    queueFamilies.resize(countQueueFamilies);
    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, &queueFamilies[0] );

    int i = 0;
    for(auto& queueFamily : queueFamilies )
    {
        if(checkQueueSuitability( p_phDevice, queueFamily, i++))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
DeviceMng_WindowAPP::checkQueueSuitability( VkPhysicalDevice p_device, VkQueueFamilyProperties p_queueFamily, uint32_t p_id ) noexcept
{
    VkBool32 presentSupport = VK_FALSE;

    if(p_queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && !(_graphicQueueID.has_value()))
        _graphicQueueID = p_id;

    vkGetPhysicalDeviceSurfaceSupportKHR( p_device, p_id, _surface, &presentSupport );
    if( presentSupport == VK_TRUE && !(_presentQueueID.has_value()) )
        _presentQueueID = p_id;
    
    if( _presentQueueID.has_value() && _graphicQueueID.has_value() )
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng_WindowAPP::createLogicalDevice() noexcept
{
    auto result = vkCreateDevice( _physicalDevice, &_deviceInfo, nullptr, &_logicalDevice );

    assert(result == VK_SUCCESS);

    std::cout << "Logical device created succesfully (;vD) \n"; 
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng_WindowAPP::initLogicalDeviceInfo() noexcept
{
    initQueueCreateInfo();
    vkGetPhysicalDeviceFeatures( _physicalDevice, &_phDeviceFeatures );

    _deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    _deviceInfo.pNext = nullptr;
    _deviceInfo.flags = 0;
    _deviceInfo.queueCreateInfoCount = (uint32_t)_queuesCreateInfo.size();
    _deviceInfo.pQueueCreateInfos = _queuesCreateInfo.data();
    _deviceInfo.enabledLayerCount = 0;
    _deviceInfo.ppEnabledLayerNames = nullptr;
    _deviceInfo.enabledExtensionCount = 0;
    _deviceInfo.ppEnabledExtensionNames = nullptr;
    _deviceInfo.pEnabledFeatures = &_phDeviceFeatures;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng_WindowAPP::initQueueCreateInfo() noexcept
{
    Set<uint32_t> queuesIds { _graphicQueueID.value() , _presentQueueID.value() };

    for(auto id : queuesIds)
    {
        VkDeviceQueueCreateInfo queueInfo;
        
        queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueInfo.pNext = nullptr;
        queueInfo.flags = 0;
        queueInfo.queueCount = 1;
        queueInfo.queueFamilyIndex = id;
        queueInfo.pQueuePriorities = &_queuePriority;

        _queuesCreateInfo.push_back(queueInfo);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeviceMng_WindowAPP::getQueueHandlers() noexcept
{
    vkGetDeviceQueue( _logicalDevice, _graphicQueueID.value(), 0, &_graphicQueueHandler );
    std::cout << "Graphical Queue Handler succesfully obtained ;D\n";
    vkGetDeviceQueue( _logicalDevice, _presentQueueID.value(), 0, &_presentQueueHandler );
    std::cout << "Presentation Queue Handler succesfully obtained ;D\n";
}
