#pragma once
#include <unordered_map>
#include "llvm/IR/IRBuilder.h"
#include "parser/ast_visitor.h"

namespace Frontend
{
class FunctionBuilder;
class WrappedLLVMContext;

class ConstantExpressionBuilder : public AST::Visitor
{
public:
  ConstantExpressionBuilder(WrappedLLVMContext* context);
  ~ConstantExpressionBuilder();

  bool IsValid() const;
  llvm::Constant* GetResultValue();

  bool Visit(AST::Node* node) override;
  bool Visit(AST::IntegerLiteralExpression* node) override;
  bool Visit(AST::BooleanLiteralExpression* node) override;
  bool Visit(AST::InitializerListExpression* node) override;
  bool Visit(AST::UnaryExpression* node) override;
  bool Visit(AST::BinaryExpression* node) override;
  bool Visit(AST::CastExpression* node) override;
  bool Visit(AST::IdentifierExpression* node) override;

private:
  WrappedLLVMContext* m_context;
  llvm::Constant* m_result_value = nullptr;
};
}