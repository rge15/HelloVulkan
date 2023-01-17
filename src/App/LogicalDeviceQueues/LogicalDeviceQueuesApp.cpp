#include "LogicalDeviceQueuesApp.hpp"
#include "Engine/InstanceMng.hpp"
#include "Engine/DeprecatedDeviceMng.hpp"

void
LogicaDeviceQueuesApp::run()
{
    UniqPtr<InstanceMng> instanceMng = std::make_unique<InstanceMng>();
    UniqPtr<DeprecatedDeviceMng> deprecatedDeviceMng = std::make_unique<DeprecatedDeviceMng>( instanceMng.get()->_vkInstance );
}
