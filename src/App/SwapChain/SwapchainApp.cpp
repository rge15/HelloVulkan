#include "SwapchainApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"
#include "Engine/SwapchainMng.hpp"

void
SwapchainApp::run()
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
}