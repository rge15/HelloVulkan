#include "SwapchainApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"

void
SwapchainApp::run()
{
    UniqPtr<WindowMng> windowMng = std::make_unique<WindowMng>();
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<SurfaceMng> surfaceMng = std::make_unique<SurfaceMng>( instanceMng.get()->_vkInstance, windowMng.get()->getWindow() );
    UniqPtr<DeviceMng> deviceMng = std::make_unique<DeviceMng>( instanceMng.get()->_vkInstance, surfaceMng.get()->getSurface() );
    UniqPtr<SwapchainMng> swapMng = std::make_unique<SwapchainMng>( 
        deviceMng.get()->getDevice(), surfaceMng.get()->getSurface(), deviceMng.get()->getSwapchainDetails(), deviceMng.get()->getFamilyQueueIds() );
}