#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class DeviceMng_WindowAPP
{
private:
	
	VkInstance&		_instance;
	VkSurfaceKHR&	_surface;

    VkPhysicalDeviceFeatures	_phDeviceFeatures {};
	VkDeviceCreateInfo 			_deviceInfo {};

	VkPhysicalDevice	_physicalDevice { VK_NULL_HANDLE };
	VkDevice			_logicalDevice 	{ VK_NULL_HANDLE };

	Vector<VkDeviceQueueCreateInfo> _queuesCreateInfo;

	VkQueue	_graphicQueueHandler { VK_NULL_HANDLE };
	VkQueue	_presentQueueHandler { VK_NULL_HANDLE };

	Optional<uint32_t>	_graphicQueueID;
	Optional<uint32_t>	_presentQueueID;

	float	_queuePriority { 1.f }; 

public:
    DeviceMng_WindowAPP(VkInstance& p_instance, VkSurfaceKHR& p_surface) noexcept;
	~DeviceMng_WindowAPP();

private:

	void
	getSuitableDevice() noexcept;

	bool
	checkDeviceSuitability( VkPhysicalDevice& p_phDevice ) noexcept;

	void
	initQueueCreateInfo() noexcept;
	
	void
    initLogicalDeviceInfo() noexcept;

	void
	createLogicalDevice() noexcept;

	void
	getQueueHandlers() noexcept;

	bool
	checkQueueSuitability( VkPhysicalDevice p_device, VkQueueFamilyProperties p_queueFamily, uint32_t p_id ) noexcept;

};