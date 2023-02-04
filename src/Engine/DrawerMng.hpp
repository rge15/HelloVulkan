#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/utilStructs/DeviceQueueFamilies.hpp>

class DrawerMng
{
private:
    VkDevice&                   _device;
    const DeviceQueueFamilies&  _queueFamilyId;
    VkRenderPass&               _renderPass;
    VkPipeline&                 _pipeline;

    const VkSwapchainCreateInfoKHR&   _swapInfo;

    VkCommandPool   _pool       { VK_NULL_HANDLE };
    VkCommandBuffer _cmdBuffer  { VK_NULL_HANDLE };

    VkCommandBufferBeginInfo _beginRecordInfo {};

public:

    DrawerMng(
        VkDevice& p_device, const DeviceQueueFamilies& p_queueFamilyId, VkRenderPass& p_renderPass,
        VkPipeline& p_pipeline, const VkSwapchainCreateInfoKHR& p_swapInfo
    ) noexcept;

    ~DrawerMng();

    void
    recordDrawCommand( VkFramebuffer& p_framebuffer ) noexcept;

private:

    void
    createCommandPool() noexcept;

    void
    createCommandBuffer() noexcept;

    void
    initCommandBufferRecordingInfo() noexcept;

    void
    beginRecording() noexcept;

    void
    recordCommands( VkFramebuffer& p_framebuffer ) noexcept;

    void
    endRecording() noexcept;

    void
    initRenderPass( VkFramebuffer& p_framebuffer ) noexcept;

    void
    initDynamicStates() noexcept;

};