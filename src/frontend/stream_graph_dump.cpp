#include <cassert>
#include <cstdarg>
#include <sstream>
#include "common/string_helpers.h"
#include "frontend/stream_graph.h"

namespace StreamGraph
{
class StreamGraphDumpVisitor : public Visitor
{
public:
  StreamGraphDumpVisitor() = default;
  ~StreamGraphDumpVisitor() = default;

  std::string ToString() const { return m_out.str(); }

  bool Visit(Filter* node) override;
  bool Visit(Pipeline* node) override;
  bool Visit(SplitJoin* node) override;
  bool Visit(Split* node) override;
  bool Visit(Join* node) override;

  void Write(const char* fmt, ...);
  void WriteLine(const char* fmt, ...);
  void Indent();
  void Deindent();
  void WriteEdgesFrom(const Node* src);

protected:
  std::stringstream m_out;
  unsigned int m_indent = 0;
};

void StreamGraphDumpVisitor::Write(const char* fmt, ...)
{
  for (unsigned int i = 0; i < m_indent; i++)
    m_out << "  ";

  va_list ap;
  va_start(ap, fmt);
  m_out << StringFromFormatV(fmt, ap);
  va_end(ap);

  m_out << std::endl;
}

void StreamGraphDumpVisitor::WriteLine(const char* fmt, ...)
{
  for (unsigned int i = 0; i < m_indent; i++)
    m_out << "  ";

  va_list ap;
  va_start(ap, fmt);
  m_out << StringFromFormatV(fmt, ap);
  va_end(ap);

  m_out << std::endl;
}

void StreamGraphDumpVisitor::Indent()
{
  m_indent++;
}

void StreamGraphDumpVisitor::Deindent()
{
  assert(m_indent > 0);
  m_indent--;
}

void StreamGraphDumpVisitor::WriteEdgesFrom(const Node* src)
{
  for (const Node* output : src->GetOutputs())
    WriteLine("%s -> %s;", src->GetName().c_str(), output->GetName().c_str());
}

bool StreamGraphDumpVisitor::Visit(Filter* node)
{
  WriteLine("%s [shape=circle];", node->GetName().c_str());
  return true;
}

bool StreamGraphDumpVisitor::Visit(Pipeline* node)
{
  WriteLine("subgraph %s {", node->GetName().c_str());
  Indent();

  WriteLine("label = \"%s\";\n", node->GetName().c_str());

  for (Node* child : node->GetChildren())
  {
    child->Accept(this);
    WriteEdgesFrom(child);
  }

  Deindent();
  WriteLine("}");

  return true;
}

bool StreamGraphDumpVisitor::Visit(SplitJoin* node)
{
  WriteLine("subgraph %s {", node->GetName().c_str());
  Indent();

  WriteLine("label = \"%s\";\n", node->GetName().c_str());

  node->GetSplitNode()->Accept(this);
  node->GetJoinNode()->Accept(this);

  for (Node* child : node->GetChildren())
  {
    child->Accept(this);
    WriteEdgesFrom(child);
  }

  Deindent();
  WriteLine("}");

  WriteEdgesFrom(node->GetSplitNode());
  WriteEdgesFrom(node->GetJoinNode());
  return true;
}

bool StreamGraphDumpVisitor::Visit(Split* node)
{
  WriteLine("%s [shape=circle];", node->GetName().c_str());
  return true;
}

bool StreamGraphDumpVisitor::Visit(Join* node)
{
  WriteLine("%s [shape=circle];", node->GetName().c_str());
  return true;
}

std::string DumpStreamGraph(Node* root)
{
  StreamGraphDumpVisitor visitor;
  visitor.WriteLine("digraph G {");
  visitor.Indent();
  root->Accept(&visitor);
  visitor.Deindent();
  visitor.WriteLine("}");
  return visitor.ToString();
}
}