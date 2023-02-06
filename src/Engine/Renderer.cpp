#include "Renderer.hpp"

Renderer::Renderer(DeviceMng& p_deviceMng, SwapchainMng& p_swapMng, DrawerMng& p_drawer, PipelineFrameBuffers& p_buffers ) noexcept
: _deviceMng { p_deviceMng }, _device { p_deviceMng.getDevice() }, _swapMng{ p_swapMng }, _drawer { p_drawer }, _frameBuffers { p_buffers }
{
    createSyncObjects();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

Renderer::~Renderer()
{
    vkDestroySemaphore( _device, _imageAvailable, nullptr );
    vkDestroySemaphore( _device, _imageRendered, nullptr );
    vkDestroyFence( _device, _cmdBufferAvailable, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Renderer::drawFrame()
{
    auto imageId        = getFrameBufferIndex();
    auto frameBuffer    = _frameBuffers.getFramebufferByIndex( imageId );

    vkWaitForFences( _device, 1, &_cmdBufferAvailable, true, UINT64_MAX );
    vkResetFences( _device, 1, &_cmdBufferAvailable );

    _drawer.recordDrawCommand( frameBuffer );

    submitCommands( imageId );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Renderer::createSyncObjects()
{
    VkSemaphoreCreateInfo semaInfo {};
    semaInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaInfo.pNext = nullptr;
    semaInfo.flags = 0;

    vkCreateSemaphore( _device, &semaInfo, nullptr, &_imageAvailable );
    vkCreateSemaphore( _device, &semaInfo, nullptr, &_imageRendered );

    VkFenceCreateInfo fenceInfo {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = nullptr;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateFence( _device, &fenceInfo, nullptr, &_cmdBufferAvailable);

    std::cout << "Sync objects created succesfully \n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

uint32_t
Renderer::getFrameBufferIndex()
{
    uint32_t imageId { 0 };

    vkAcquireNextImageKHR( _device, _swapMng.getSwapchain(), UINT64_MAX, _imageAvailable, VK_NULL_HANDLE, &imageId);

    return imageId;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Renderer::submitCommands( uint32_t p_imageId ) noexcept
{
    VkPipelineStageFlags stageFlags { VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT };
    VkSubmitInfo _subInfo {};
    _subInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    _subInfo.pNext = nullptr;
    _subInfo.commandBufferCount = 1;
    _subInfo.pCommandBuffers = &_drawer.getCmdBuffer();
    _subInfo.waitSemaphoreCount = 1;
    _subInfo.pWaitSemaphores = &_imageAvailable;    
    _subInfo.pWaitDstStageMask = &stageFlags;
    _subInfo.signalSemaphoreCount = 1;
    _subInfo.pSignalSemaphores = &_imageRendered;

    vkQueueSubmit( _deviceMng.getGraphicQueueHandler(), 1, &_subInfo, _cmdBufferAvailable );

    VkPresentInfoKHR presentInfo {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &_imageRendered;
    
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &_swapMng.getSwapchain();
    presentInfo.pImageIndices = &p_imageId;

    presentInfo.pResults = nullptr;

    vkQueuePresentKHR( _deviceMng.getPresentQueueHandler(), &presentInfo );

}