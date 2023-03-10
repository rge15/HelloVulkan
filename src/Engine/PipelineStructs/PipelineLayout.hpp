#pragma once
#include <utilities/graphicInclude.hpp>
#include <utilities/typeAliases.hpp>

class PipelineLayout
{
private:
    
    VkDevice& _device;

    VkPipelineLayoutCreateInfo _layoutInfo {};

    VkPipelineLayout _pipeLayout { VK_NULL_HANDLE };

public:
    PipelineLayout( VkDevice& p_device );

    ~PipelineLayout();

    inline
    VkPipelineLayout&
    getLayout(){ return _pipeLayout; };

private:

    void
    initCreateInfo();

    void
    createLayout();

};