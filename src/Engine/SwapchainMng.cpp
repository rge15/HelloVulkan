#include "SwapchainMng.hpp"

SwapchainMng::SwapchainMng(VkDevice& p_device, VkSurfaceKHR& p_surface, const SwapchainDetails& p_details, const DeviceQueueFamilies& p_queueIds )
: _device { p_device }, _surface { p_surface }, _swapDetails { p_details }, _queueIds { p_queueIds }
{
    _queueFamilies.push_back( _queueIds._graphicQueueId.value() );
    _queueFamilies.push_back( _queueIds._presentQueueId.value() );
    initCreateInfo();
    createSwapchain();
}

SwapchainMng::~SwapchainMng()
{
    vkDestroySwapchainKHR( _device, _swapchain, nullptr );
}

void
SwapchainMng::initCreateInfo()
{
    _createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    _createInfo.pNext = nullptr;
    _createInfo.flags = 0;
    _createInfo.surface = _surface;

    selectImageCount();
    selectColorAndFormat();

    _createInfo.imageExtent = _swapDetails.capabilities.currentExtent;

    _createInfo.imageArrayLayers = 1;
    _createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    selectQueueFamiliesImages();

    _createInfo.preTransform = _swapDetails.capabilities.currentTransform;
    _createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    selectPresentMode();

    _createInfo.clipped = VK_TRUE;
    _createInfo.oldSwapchain = VK_NULL_HANDLE;
}

void
SwapchainMng::createSwapchain()
{
    auto result = vkCreateSwapchainKHR( _device, &_createInfo, nullptr, &_swapchain );

    assert(result == VK_SUCCESS);

    std::cout << "Swapchain created succesfully :vD \n";
}

void
SwapchainMng::selectImageCount()
{
    uint32_t imageCount {0};

    imageCount = _swapDetails.capabilities.minImageCount + 1;
    
    if(imageCount > _swapDetails.capabilities.maxImageCount)
        imageCount = _swapDetails.capabilities.maxImageCount;
    
    std::cout << "Number of images created in Swapchain : " << imageCount << '\n';

    _createInfo.minImageCount = imageCount;
}

void
SwapchainMng::selectColorAndFormat()
{
    for(auto& format : _swapDetails.formats)
    {
        if( format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
        {
            _createInfo.imageFormat = format.format;
            _createInfo.imageColorSpace = format.colorSpace;
            return;
        }
    }
    _createInfo.imageFormat = _swapDetails.formats[0].format;
    _createInfo.imageColorSpace = _swapDetails.formats[0].colorSpace;
}

void
SwapchainMng::selectQueueFamiliesImages()
{
    if( _queueIds._graphicQueueId == _queueIds._presentQueueId )
    {
        _createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        _createInfo.queueFamilyIndexCount = 0;
        _createInfo.pQueueFamilyIndices = nullptr;
    }else{
        _createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        _createInfo.queueFamilyIndexCount = (uint32_t)_queueFamilies.size();
        _createInfo.pQueueFamilyIndices = _queueFamilies.data();
    }
}

void
SwapchainMng::selectPresentMode()
{
    for(auto& presentMode : _swapDetails.presentModes )
    {
        if(presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            _createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
            return;
        }
    }
    _createInfo.presentMode = _swapDetails.presentModes[0];
}
