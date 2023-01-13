#include <App/BaseApplication.hpp>
#include <utilities/graphicInclude.hpp>

struct PhysicalDevice : BaseApplication
{
    PhysicalDevice() = default;
    ~PhysicalDevice() = default;
    void run() override;

    bool checkDeviceSuitability(VkPhysicalDevice p_device);
};
