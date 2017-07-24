#ifndef KS_SCC_H_
#define KS_SCC_H_

#include <vector>
#include <stack>
#include <ctime>

class KSSCC {
 public:
  typedef std::vector< std::vector<unsigned> > AdjacencyList;

  KSSCC(const KSSCC::AdjacencyList & graph);
  ~KSSCC();

  void RunKS();
  double GetKSRunTime() const;  // Unit is seconds.
  KSSCC::AdjacencyList GetKSSCC() const;

 private:
  void DFS(const unsigned v);
  void DFS2(const unsigned v, std::vector<unsigned> & component);

  double duration;
  std::clock_t start;
  std::size_t vertices_num_;
  std::vector<bool> is_visited_;
  std::vector<bool> is_in_component_;
  std::vector<unsigned> component_;
  std::stack<unsigned> dfs_path_;
  KSSCC::AdjacencyList graph_;
  KSSCC::AdjacencyList reversed_graph_;
  KSSCC::AdjacencyList strongly_connected_components_;
};

#endif // KS_SCC_H_