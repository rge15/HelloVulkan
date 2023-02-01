#include "PipelineLayout.hpp"

PipelineLayout::PipelineLayout( VkDevice& p_device )
: _device { p_device }
{
    initCreateInfo();
    createLayout();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

PipelineLayout::~PipelineLayout()
{
    vkDestroyPipelineLayout( _device, _pipeLayout, nullptr );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::initCreateInfo()
{
    _layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    _layoutInfo.pNext = nullptr;
    _layoutInfo.flags = 0;
    _layoutInfo.setLayoutCount = 0;
    _layoutInfo.pSetLayouts = nullptr;
    _layoutInfo.pushConstantRangeCount = 0;
    _layoutInfo.pPushConstantRanges = nullptr;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
PipelineLayout::createLayout()
{
    auto result = vkCreatePipelineLayout( _device, &_layoutInfo, nullptr, &_pipeLayout);

    assert(result == VK_SUCCESS);

    std::cout << "Pipeline layout created sucesfully :v) \n";
}