#include <iostream>
#include <memory>
#include <vector>

#include "kompute/Kompute.hpp"

static std::vector<uint32_t>
compileSource()
{
    std::ifstream fileStream("tmp.comp.spv", std::ios::binary);
    std::vector<char> buffer;
    buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(fileStream), {});
    return {(uint32_t*)buffer.data(), (uint32_t*)(buffer.data() + buffer.size())};
}

const std::vector<unsigned char> comp = {
		#include "tmp.comp.spv.h"
	};

int main()
{
#if KOMPUTE_ENABLE_SPDLOG
    spdlog::set_level(
      static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

    kp::Manager mgr;

    auto tensorInA = mgr.tensor({ 2.0, 4.0, 6.0 });
    auto tensorInB = mgr.tensor({ 0.0, 1.0, 2.0 });
    auto tensorOut = mgr.tensor({ 0.0, 0.0, 0.0 });

    

    std::vector<std::shared_ptr<kp::Tensor>> params = { tensorInA, tensorInB, tensorOut };

    //std::shared_ptr<kp::Algorithm> algo = mgr.algorithm(params, compileSource());
    std::shared_ptr<kp::Algorithm> algo = mgr.algorithm(params, {(uint32_t*)comp.data(), (uint32_t*)(comp.data() + comp.size())});

    mgr.sequence()
        ->record<kp::OpTensorSyncDevice>(params)
        ->record<kp::OpAlgoDispatch>(algo)
        ->record<kp::OpTensorSyncLocal>(params)
        ->eval();

    // prints "Output {  0  4  12  }"
    std::cout<< "Output: {  ";
    for (const float& elem : tensorOut->vector()) {
      std::cout << elem << "  ";
    }
    std::cout << "}" << std::endl;
}
