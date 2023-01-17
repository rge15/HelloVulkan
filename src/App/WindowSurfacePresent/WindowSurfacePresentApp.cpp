#include "WindowSurfacePresentApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"
#include "Engine/WindowMng.hpp" 
#include "Engine/SurfaceMng.hpp"

void
WindowSurfacePresentApp::run()
{
    UniqPtr<WindowMng> windowMng = std::make_unique<WindowMng>();
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<SurfaceMng> surfaceMng = std::make_unique<SurfaceMng>( instanceMng.get()->_vkInstance, windowMng.get()->getWindow() );
    UniqPtr<DeviceMng> deviceMng = std::make_unique<DeviceMng>( instanceMng.get()->_vkInstance, surfaceMng.get()->getSurface() );
}