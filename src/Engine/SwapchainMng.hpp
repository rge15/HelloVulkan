#include "utilities/graphicInclude.hpp"
#include "utilities/typeAliases.hpp"
#include <Engine/utilStructs/SwapchainDetails.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class SwapchainMng
{
private:
    VkSwapchainKHR _swapchain { VK_NULL_HANDLE };

    VkDevice& _device;
    VkSurfaceKHR& _surface;
    const SwapchainDetails& _swapDetails;
    const DeviceQueueFamilies& _queueIds;
    Vector<uint32_t> _queueFamilies;

    VkSwapchainCreateInfoKHR _createInfo{};

public:
    SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds );
    ~SwapchainMng();

private:
    void
    initCreateInfo();
    
    void
    createSwapchain();

    void
    selectImageCount();

    void
    selectColorAndFormat();

    void
    selectQueueFamiliesImages();

    void
    selectPresentMode();
};