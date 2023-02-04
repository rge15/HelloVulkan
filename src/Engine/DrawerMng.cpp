#include "DrawerMng.hpp"

DrawerMng::DrawerMng(
    VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId, VkRenderPass& p_renderPass,
    VkPipeline& p_pipeline, const VkSwapchainCreateInfoKHR& p_swapInfo
) noexcept
: _device { p_device }, _queueFamilyId { p_queueFamilyId }, _renderPass { p_renderPass }
, _pipeline { p_pipeline }, _swapInfo { p_swapInfo }
{
    createCommandPool();
    createCommandBuffer();
    initCommandBufferRecordingInfo();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DrawerMng::~DrawerMng()
{
    vkDestroyCommandPool( _device, _pool, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::createCommandPool() noexcept
{
    VkCommandPoolCreateInfo _info {};

    _info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _info.pNext = nullptr;
    _info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    _info.queueFamilyIndex = _queueFamilyId._graphicQueueId.value();

    auto result = vkCreateCommandPool(_device, &_info, nullptr, &_pool);

    assert(result == VK_SUCCESS);

    std::cout << "Command pool created succesfully \n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::createCommandBuffer() noexcept
{
    VkCommandBufferAllocateInfo _info {};
    
    _info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    _info.pNext = nullptr;
    _info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    
    _info.commandPool           = _pool;
    _info.commandBufferCount    = 1;

    auto result = vkAllocateCommandBuffers( _device, &_info, &_cmdBuffer );

    assert(result == VK_SUCCESS);

    std::cout << "Command buffer allocated succesfully \n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordDrawCommand( VkFramebuffer& p_framebuffer ) noexcept
{
    beginRecording();

    recordCommands( p_framebuffer );

    endRecording();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::beginRecording() noexcept
{
    vkBeginCommandBuffer(_cmdBuffer, &_beginRecordInfo);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::endRecording() noexcept
{
    vkEndCommandBuffer(_cmdBuffer);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::recordCommands(VkFramebuffer& p_framebuffer) noexcept
{
    initRenderPass( p_framebuffer );

    vkCmdBindPipeline( _cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline );

    initDynamicStates();

    vkCmdDraw( _cmdBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass( _cmdBuffer );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initRenderPass( VkFramebuffer& p_framebuffer ) noexcept
{
    VkRenderPassBeginInfo _beginInfo {};

    _beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _beginInfo.pNext = nullptr;
    
    _beginInfo.renderPass = _renderPass;
    _beginInfo.framebuffer = p_framebuffer;

    _beginInfo.renderArea.offset = { 0, 0 };
    _beginInfo.renderArea.extent = _swapInfo.imageExtent;

    _beginInfo.clearValueCount = 1;
    VkClearValue blackColor {0.f,0.f,0.f,1.f};
    _beginInfo.pClearValues = &blackColor;

    vkCmdBeginRenderPass( _cmdBuffer, &_beginInfo, VK_SUBPASS_CONTENTS_INLINE );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initCommandBufferRecordingInfo() noexcept
{
    _beginRecordInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    _beginRecordInfo.pNext = nullptr;
    _beginRecordInfo.flags = 0;
    _beginRecordInfo.pInheritanceInfo = nullptr;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
DrawerMng::initDynamicStates() noexcept
{
    VkViewport viewport{};

    viewport.x = 0;
    viewport.y = 0;
    viewport.height = _swapInfo.imageExtent.height;
    viewport.width = _swapInfo.imageExtent.width;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport( _cmdBuffer, 0, 1, &viewport );

    VkRect2D _scissor {};

    _scissor.offset = { 0 , 0 };
    _scissor.extent = _swapInfo.imageExtent;

    vkCmdSetScissor( _cmdBuffer, 0, 1, &_scissor );
}
