#include "PhysicalDeviceApp.hpp"
#include <Engine/InstanceMng.hpp>
#include <utilities/typeAliases.hpp>

void
PhysicalDeviceApp::run()
{
    std::cout << "HelloVulkan!\n";
    UniqPtr<InstanceMng> instMng = std::make_unique<InstanceMng>();

    uint32_t countDevices { 0 };
    Vector<VkPhysicalDevice> _devices {};
    vkEnumeratePhysicalDevices( instMng.get()->_vkInstance, &countDevices, nullptr );
    _devices.resize(countDevices);
    vkEnumeratePhysicalDevices( instMng.get()->_vkInstance, &countDevices, &_devices[0]);
    std::cout << "Num of physical devices : " << countDevices << '\n';

    VkPhysicalDevice phDevice {VK_NULL_HANDLE};

    for(auto& device : _devices)
    {
        if( checkDeviceSuitability(device) )
        {
            phDevice = device;
            break;
        }
    }

    if(phDevice != VK_NULL_HANDLE)
    {
        VkPhysicalDeviceProperties properties {};
        vkGetPhysicalDeviceProperties(phDevice, &properties);
        std::cout << "Chosen Physical Device : " << properties.deviceName << '\n';
    }else
    {
        std::cout << "Didn't find availible util device :C \n";
    }
}

bool
PhysicalDeviceApp::checkDeviceSuitability(VkPhysicalDevice p_device)
{
    std::cout << "<----- Checking Devices Suitability ----->\n";

    uint32_t countQueueFamilies { 0 };
    Vector<VkQueueFamilyProperties> queueFamilies {};

    vkGetPhysicalDeviceQueueFamilyProperties( p_device, &countQueueFamilies, nullptr );
    queueFamilies.resize(countQueueFamilies);
    vkGetPhysicalDeviceQueueFamilyProperties( p_device, &countQueueFamilies, &queueFamilies[0] );

    for(auto& queueFamily : queueFamilies )
    {
        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            return true;
    }

    return false;
};