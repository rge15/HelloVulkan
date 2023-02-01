#include "PipelineLayoutApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"
#include "Engine/Sources/ShaderSrc.hpp"
#include "Engine/PipelineStructs/GraphicPipelineConfig.hpp"
#include "Engine/PipelineStructs/PipelineLayout.hpp"

void
PipelineLayoutApp::run()
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

    auto vertShader = std::make_unique<ShaderSrc>(device, "src/shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    auto fragShader = std::make_unique<ShaderSrc>(device, "src/shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

    auto pipeConfig = GraphicPipelineConfig();
    auto pipeLayout = std::make_unique<PipelineLayout>( device );

}