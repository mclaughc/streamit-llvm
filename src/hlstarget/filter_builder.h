#pragma once
#include <unordered_map>

namespace llvm
{
class Constant;
class Function;
class GlobalVariable;
class Module;
class Type;
class Value;
}

namespace AST
{
class Declaration;
class FilterDeclaration;
class FilterWorkBlock;
class VariableDeclaration;
}

namespace Frontend
{
class WrappedLLVMContext;
}

namespace StreamGraph
{
class FilterPermutation;
}

namespace HLSTarget
{
class FilterBuilder
{
public:
  FilterBuilder(Frontend::WrappedLLVMContext* context, llvm::Module* mod,
                const StreamGraph::FilterPermutation* filter_perm);
  ~FilterBuilder();

  Frontend::WrappedLLVMContext* GetContext() const { return m_context; }
  const AST::FilterDeclaration* GetFilterDeclaration() const { return m_filter_decl; }
  llvm::Function* GetFunction() const { return m_function; }
  bool CanMakeCombinational() const;

  bool GenerateCode();

private:
  llvm::Function* GenerateFunction(AST::FilterWorkBlock* block, const std::string& name);
  bool GenerateGlobals();
  bool GenerateBuiltinFilter();
  bool GenerateBuiltinFilter_Identity();

  Frontend::WrappedLLVMContext* m_context;
  llvm::Module* m_module;
  const StreamGraph::FilterPermutation* m_filter_permutation = nullptr;
  const AST::FilterDeclaration* m_filter_decl = nullptr;
  std::unordered_map<const AST::Declaration*, llvm::Value*> m_global_variable_map;

  llvm::Function* m_function = nullptr;
};

} // namespace HLSTarget