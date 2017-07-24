#ifndef TARJAN_SCC_H_
#define TARJAN_SCC_H_

#include <vector>
#include <stack>
#include <ctime>

class TarjanSCC {
 public:
  typedef std::vector< std::vector<unsigned> > AdjacencyList;

  TarjanSCC(const TarjanSCC::AdjacencyList & graph);
  ~TarjanSCC();

  void RunTarjan();
  double GetTarjanRunTime() const;  // Unit is seconds.
  TarjanSCC::AdjacencyList GetTarjanSCC() const;

 private:
  void DFS(const unsigned v);
  inline unsigned min(unsigned a, unsigned b) { return (a < b ? a : b); }

  unsigned time_stamp_;
  double duration;
  std::clock_t start;
  std::size_t vertices_num_;
  std::vector<bool> is_visited_;
  std::vector<bool> is_on_stack_;
  std::vector<unsigned> num_;
  std::vector<unsigned> lowlink_;
  std::stack<unsigned> dfs_path_;
  TarjanSCC::AdjacencyList graph_;
  TarjanSCC::AdjacencyList strongly_connected_components_;
};

#endif // TARJAN_SCC_H_