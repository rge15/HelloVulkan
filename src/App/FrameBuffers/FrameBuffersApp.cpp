#include "FrameBuffersApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"
#include "Engine/Sources/ShaderSrc.hpp"
#include "Engine/PipelineStructs/GraphicPipelineConfig.hpp"
#include "Engine/PipelineStructs/PipelineLayout.hpp"
#include "Engine/PipelineStructs/RenderPass.hpp"
#include "Engine/RenderPipelineMng.hpp"
#include "Engine/PipelineStructs/PipelineFrameBuffers.hpp"

void
FrameBuffersApp::run()
{
    auto windowMng   = std::make_unique<WindowMng>();
    auto instanceMng = std::make_unique<InstanceMng>();
    
    auto  instance   = instanceMng.get()->_vkInstance;
    auto& window     = windowMng.get()->getWindow();

    auto surfaceMng  = std::make_unique<SurfaceMng>( instance, window );
    auto surface     = surfaceMng.get()->getSurface();

    auto deviceMng   = std::make_unique<DeviceMng>( instance, surface);

    auto device      = deviceMng.get()->getDevice();
    auto swapDetails = deviceMng.get()->getSwapchainDetails();
    auto queueIds    = deviceMng.get()->getFamilyQueueIds();

    auto swapMng     = std::make_unique<SwapchainMng>( device, surface, swapDetails, queueIds );

    auto vertShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    auto fragShaderSrc = std::make_unique<ShaderSrc>(device, "src/shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
    
    auto vertexShaderStageInfo      = vertShaderSrc.get()->getShaderStageInfo();
    auto fragmentShaderStageInfo    = fragShaderSrc.get()->getShaderStageInfo();
    using ShaderStagesVector        = Vector<VkPipelineShaderStageCreateInfo>;
    ShaderStagesVector shaders { vertexShaderStageInfo, fragmentShaderStageInfo };

    auto pipeConfig = GraphicPipelineConfig();
    
    auto pipeLayout = std::make_unique<PipelineLayout>( device );
    auto layoutObj  = pipeLayout.get()->getLayout();

    auto renderPass     = std::make_unique<RenderPass>( device, *swapMng.get() );
    auto renderPassObj  = renderPass.get()->getRenderPass();

    auto renderPipelineMng = std::make_unique<RenderPipelineMng>( device, renderPassObj, layoutObj, pipeConfig, shaders );
    
    auto frameBuffers = std::make_unique<PipelineFrameBuffers>( device, renderPassObj, *swapMng.get());

}