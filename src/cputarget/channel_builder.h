#pragma once
#include <unordered_map>
#include "common/types.h"

namespace llvm
{
class Constant;
class Function;
class GlobalVariable;
class Module;
class Type;
}

namespace Frontend
{
class WrappedLLVMContext;
}

namespace StreamGraph
{
class Filter;
class Split;
class Join;
}

namespace CPUTarget
{
class ChannelBuilder
{
public:
  ChannelBuilder(Frontend::WrappedLLVMContext* context, llvm::Module* mod);
  ~ChannelBuilder();

  Frontend::WrappedLLVMContext* GetContext() const { return m_context; }

  // TODO: Enum for mode, 0=roundrobin, 1=duplicate
  bool GenerateCode(StreamGraph::Filter* filter);
  bool GenerateCode(StreamGraph::Split* split);
  bool GenerateCode(StreamGraph::Join* join);

private:
  bool GenerateFilterGlobals(StreamGraph::Filter* filter);
  bool GenerateFilterPeekFunction(StreamGraph::Filter* filter);
  bool GenerateFilterPopFunction(StreamGraph::Filter* filter);
  bool GenerateFilterPushFunction(StreamGraph::Filter* filter);

  bool GenerateSplitGlobals(StreamGraph::Split* split);
  bool GenerateSplitPushFunction(StreamGraph::Split* split);

  bool GenerateJoinGlobals(StreamGraph::Join* join);
  bool GenerateJoinSyncFunction(StreamGraph::Join* join);
  bool GenerateJoinPushFunction(StreamGraph::Join* join);

  Frontend::WrappedLLVMContext* m_context;
  llvm::Module* m_module;
  std::string m_instance_name;

  u32 m_input_buffer_size = 0;
  llvm::Type* m_input_buffer_type = nullptr;
  llvm::GlobalVariable* m_input_buffer_var = nullptr;
  llvm::GlobalVariable* m_last_index_var = nullptr;
  llvm::GlobalVariable* m_written_var = nullptr;
  llvm::GlobalVariable* m_distribution_var = nullptr;
};

} // namespace CPUTarget