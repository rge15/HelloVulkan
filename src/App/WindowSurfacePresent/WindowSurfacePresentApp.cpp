#include "WindowSurfacePresentApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/APP_VERSIONS/WindowSurfacePresent/DeviceMng_WindowAPP.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"

void
WindowSurfacePresentApp::run()
{
    auto windowMng = std::make_unique<WindowMng>();
    auto instanceMng = std::make_unique<InstanceMng>();

    auto  instance = instanceMng.get()->_vkInstance;
    auto& window   = windowMng.get()->getWindow();
    
    auto surfaceMng = std::make_unique<SurfaceMng>( instance , window );
    auto surface    = surfaceMng.get()->getSurface();

    auto deviceMng_WindowAPP = std::make_unique<DeviceMng_WindowAPP>( instance, surface );
}