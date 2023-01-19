#include "WindowSurfacePresentApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/APP_VERSIONS/WindowSurfacePresent/DeviceMng_WindowAPP.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"

void
WindowSurfacePresentApp::run()
{
    UniqPtr<WindowMng> windowMng = std::make_unique<WindowMng>();
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<SurfaceMng> surfaceMng = std::make_unique<SurfaceMng>( instanceMng.get()->_vkInstance, windowMng.get()->getWindow() );
    UniqPtr<DeviceMng_WindowAPP> deviceMng_WindowAPP = std::make_unique<DeviceMng_WindowAPP>( instanceMng.get()->_vkInstance, surfaceMng.get()->getSurface() );
}