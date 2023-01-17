#include "DeprecatedDeviceMng.hpp"

DeprecatedDeviceMng::DeprecatedDeviceMng(VkInstance& p_instance) noexcept
: _instance { p_instance }
{
    getSuitableDevice();
    initLogicalDeviceInfo();
    createLogicalDevice();
    getQueueHandlers();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DeprecatedDeviceMng::~DeprecatedDeviceMng() noexcept
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
DeprecatedDeviceMng::getSuitableDevice() noexcept
{
    uint32_t phDevicesCount { 0 };
    Vector<VkPhysicalDevice> phDevices;
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, nullptr );
    phDevices.resize( phDevicesCount );
    vkEnumeratePhysicalDevices( _instance, &phDevicesCount, &phDevices[0] );

    for(auto& device : phDevices)
    {
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
DeprecatedDeviceMng::checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept
{
    uint32_t countQueueFamilies { 0 };
    Vector<VkQueueFamilyProperties> queueFamilies {};

    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, nullptr );
    queueFamilies.resize(countQueueFamilies);
    vkGetPhysicalDeviceQueueFamilyProperties( p_phDevice, &countQueueFamilies, &queueFamilies[0] );

    int i = 0;
    for(auto& queueFamily : queueFamilies )
    {
        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            _graphicQueueID = i;
            return true;
        }
        ++i;
    }

    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeprecatedDeviceMng::createLogicalDevice() noexcept
{
    auto result = vkCreateDevice( _physicalDevice, &_deviceInfo, nullptr, &_logicalDevice );

    assert(result == VK_SUCCESS);

    std::cout << "Logical device created succesfully (;vD) \n"; 
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeprecatedDeviceMng::initLogicalDeviceInfo() noexcept
{
    initQueueCreateInfo();
    vkGetPhysicalDeviceFeatures( _physicalDevice, &_phDeviceFeatures );

    _deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    _deviceInfo.pNext = nullptr;
    _deviceInfo.flags = 0;
    _deviceInfo.queueCreateInfoCount = 1;
    _deviceInfo.pQueueCreateInfos = &_queueCreateInfo;
    _deviceInfo.enabledLayerCount = 0;
    _deviceInfo.ppEnabledLayerNames = nullptr;
    _deviceInfo.enabledExtensionCount = 0;
    _deviceInfo.ppEnabledExtensionNames = nullptr;
    _deviceInfo.pEnabledFeatures = &_phDeviceFeatures;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeprecatedDeviceMng::initQueueCreateInfo() noexcept
{
    _queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    _queueCreateInfo.pNext = nullptr;
    _queueCreateInfo.flags = 0;
    _queueCreateInfo.queueCount = 1;
    _queueCreateInfo.queueFamilyIndex = _graphicQueueID.value();
    _queueCreateInfo.pQueuePriorities = &_queuePriority;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DeprecatedDeviceMng::getQueueHandlers() noexcept
{
    vkGetDeviceQueue( _logicalDevice, _graphicQueueID.value(), 0, &_graphicQueueHandler );
    std::cout << "Graphical Queue Handler succesfully obtained ;D\n";
}