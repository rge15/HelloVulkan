#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class DeprecatedDeviceMng
{
private:
	
	VkInstance&	_instance;

    VkPhysicalDeviceFeatures	_phDeviceFeatures {};
	VkDeviceQueueCreateInfo		_queueCreateInfo {};
	VkDeviceCreateInfo 			_deviceInfo {};

	VkPhysicalDevice	_physicalDevice { VK_NULL_HANDLE };
	VkDevice			_logicalDevice 	{ VK_NULL_HANDLE };

	VkQueue	_graphicQueueHandler { VK_NULL_HANDLE };

	Optional<uint32_t>	_graphicQueueID;
	float	_queuePriority { 1.f }; 

public:
    DeprecatedDeviceMng(VkInstance& p_instance) noexcept;
    ~DeprecatedDeviceMng();

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

};