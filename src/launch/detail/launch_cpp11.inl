#include "launch_cpp11.hpp"
#include "shared_storage_requirements_calculator.hpp"
#include <iostream>

template<typename Function, typename... Args>
  void launch(std::size_t num_blocks, std::size_t num_threads_per_block, Function &&f, Args&&... args)
{
  shared_storage_requirements_calculator calc;

  static const std::size_t num_dynamic_smem_bytes = calc.calculate(f, args...);

  std::cout << "launch: needs to dynamically allocate " << num_dynamic_smem_bytes << " bytes" << std::endl;
}

