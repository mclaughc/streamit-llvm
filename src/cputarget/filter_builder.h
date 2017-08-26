#pragma once
#include <unordered_map>

class WrappedLLVMContext;

namespace llvm
{
class Constant;
class Function;
class GlobalVariable;
class Module;
class Type;
}

namespace AST
{
class FilterDeclaration;
class FilterWorkBlock;
class VariableDeclaration;
}

namespace StreamGraph
{
class FilterPermutation;
class Filter;
}

namespace CPUTarget
{
class FilterBuilder
{
public:
  FilterBuilder(WrappedLLVMContext* context, llvm::Module* mod);
  ~FilterBuilder();

  WrappedLLVMContext* GetContext() const { return m_context; }
  const AST::FilterDeclaration* GetFilterDeclaration() const { return m_filter_decl; }
  const std::string& GetNamePrefix() const { return m_instance_name; }
  llvm::Function* GetInitFunction() const { return m_init_function; }
  llvm::Function* GetPreworkFunction() const { return m_prework_function; }
  llvm::Function* GetWorkFunction() const { return m_work_function; }
  llvm::Constant* GetPeekFunction() const { return m_peek_function; }
  llvm::Constant* GetPopFunction() const { return m_pop_function; }
  llvm::Constant* GetPushFunction() const { return m_push_function; }

  bool GenerateCode(const StreamGraph::Filter* filter);

private:
  llvm::Function* GenerateFunction(AST::FilterWorkBlock* block, const std::string& name);
  bool GenerateGlobals();
  bool GenerateChannelPrototypes();

  WrappedLLVMContext* m_context;
  llvm::Module* m_module;
  const StreamGraph::FilterPermutation* m_filter_permutation = nullptr;
  const AST::FilterDeclaration* m_filter_decl = nullptr;
  std::string m_instance_name;
  std::string m_output_channel_name;
  std::unordered_map<const AST::VariableDeclaration*, llvm::GlobalVariable*> m_global_variable_map;

  llvm::Function* m_init_function = nullptr;
  llvm::Function* m_prework_function = nullptr;
  llvm::Function* m_work_function = nullptr;

  llvm::Constant* m_peek_function = nullptr;
  llvm::Constant* m_pop_function = nullptr;
  llvm::Constant* m_push_function = nullptr;
};

} // namespace CPUTarget