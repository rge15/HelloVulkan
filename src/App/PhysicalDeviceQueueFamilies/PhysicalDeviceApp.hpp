#include <App/BaseApplication.hpp>
#include <utilities/graphicInclude.hpp>

struct PhysicalDeviceApp : BaseApplication
{
    PhysicalDeviceApp() = default;
    ~PhysicalDeviceApp() = default;
    void run() override;

    bool checkDeviceSuitability(VkPhysicalDevice p_device);
};
