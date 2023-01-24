#include "ShaderModulesApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"
#include "Engine/Sources/ShaderSrc.hpp"

void
ShaderModulesApp::run()
{
    UniqPtr<WindowMng> windowMng = std::make_unique<WindowMng>();
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<SurfaceMng> surfaceMng = std::make_unique<SurfaceMng>( instanceMng.get()->_vkInstance, windowMng.get()->getWindow() );
    UniqPtr<DeviceMng> deviceMng = std::make_unique<DeviceMng>( instanceMng.get()->_vkInstance, surfaceMng.get()->getSurface() );
    UniqPtr<SwapchainMng> swapMng = std::make_unique<SwapchainMng>( 
        deviceMng.get()->getDevice(), surfaceMng.get()->getSurface(), deviceMng.get()->getSwapchainDetails(), deviceMng.get()->getFamilyQueueIds() );

    UniqPtr<ShaderSrc> vertShader = std::make_unique<ShaderSrc>(deviceMng.get()->getDevice(), "src/shaders/vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
    UniqPtr<ShaderSrc> fragShader = std::make_unique<ShaderSrc>(deviceMng.get()->getDevice(), "src/shaders/frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
}