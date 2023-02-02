#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>
#include <Engine/SwapchainMng.hpp>

class PipelineFrameBuffers
{
private:
    VkDevice&       _device;
    VkRenderPass&   _renderPass;
    SwapchainMng&   _swapMng;

    using Framebuffers = Vector<VkFramebuffer>;
    Framebuffers        _buffers {};

public:
    PipelineFrameBuffers( VkDevice& p_device, VkRenderPass& p_renderPass, SwapchainMng& p_swapChainMng ) noexcept;
    ~PipelineFrameBuffers();

private:

    void
    createBuffers() noexcept;

};