#include "LogicalDeviceQueuesApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeviceMng.hpp"

void
LogicaDeviceQueuesApp::run()
{
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<DeviceMng> deviceMng = std::make_unique<DeviceMng>( instanceMng.get()->_vkInstance );
}
