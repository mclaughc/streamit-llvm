#pragma once
#include "parser/ast.h"

namespace AST
{
class Visitor
{
public:
  virtual bool Visit(Program* node)
  {
    return true;
  }
  virtual bool Visit(Node* node)
  {
    return true;
  }
  virtual bool Visit(Statement* node)
  {
    return true;
  }
  virtual bool Visit(Declaration* node)
  {
    return true;
  }
  virtual bool Visit(Expression* node)
  {
    return true;
  }
  virtual bool Visit(PipelineDeclaration* node)
  {
    return true;
  }
  virtual bool Visit(PipelineAddStatement* node)
  {
    return true;
  }
  virtual bool Visit(FilterDeclaration* node)
  {
    return true;
  }
  virtual bool Visit(FilterWorkBlock* node)
  {
    return true;
  }
  virtual bool Visit(IntegerLiteralExpression* node)
  {
    return true;
  }
  virtual bool Visit(IdentifierExpression* node)
  {
    return true;
  }
  virtual bool Visit(BinaryExpression* node)
  {
    return true;
  }
  virtual bool Visit(AssignmentExpression* node)
  {
    return true;
  }
  virtual bool Visit(PeekExpression* node)
  {
    return true;
  }
  virtual bool Visit(PopExpression* node)
  {
    return true;
  }
  virtual bool Visit(PushExpression* node)
  {
    return true;
  }
  virtual bool Visit(VariableDeclaration* node)
  {
    return true;
  }
  virtual bool Visit(ExpressionStatement* node)
  {
    return true;
  }
};
}