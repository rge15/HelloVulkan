#include "InstanceExtensionLayersApp.hpp"
#include <Engine/InstanceMng.hpp>
#include <utilities/typeAliases.hpp>

void
InstanceExtensionLayersApp::run()
{
    std::cout << "HelloVulkan!\n";
    UniqPtr<InstanceMng> instMng = std::make_unique<InstanceMng>();
}
