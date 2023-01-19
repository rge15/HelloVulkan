#include "LogicalDeviceQueuesApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/APP_VERSIONS/LogicalDeviceQueues/DeviceMng_LogicalAPP.hpp"

void
LogicaDeviceQueuesApp::run()
{
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<DeviceMng_LogicalAPP> deviceMng_LogicalAPP = std::make_unique<DeviceMng_LogicalAPP>( instanceMng.get()->_vkInstance );
}
