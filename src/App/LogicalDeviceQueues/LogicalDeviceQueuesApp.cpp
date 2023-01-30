#include "LogicalDeviceQueuesApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/APP_VERSIONS/LogicalDeviceQueues/DeviceMng_LogicalAPP.hpp"

void
LogicaDeviceQueuesApp::run()
{
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<DeviceMng_LogicalAPP> deviceMng_LogicalAPP = std::make_unique<DeviceMng_LogicalAPP>( instanceMng.get()->_vkInstance );


    //auto instMg = std::make_unique<InstanceMng>();
    //auto inst   = instMg.get()->_vkInstance;
    //auto devApp = std::make_unique<DeviceMng_LogicalAPP>( inst );
}
