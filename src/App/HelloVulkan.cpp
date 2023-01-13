#include "HelloVulkan.hpp"
#include <Engine/InstanceMng.hpp>
#include <utilities/typeAliases.hpp>

void
HelloVulkan::run()
{
    std::cout << "HelloVulkan!\n";
    UniqPtr<InstanceMng> instMng = std::make_unique<InstanceMng>();
}