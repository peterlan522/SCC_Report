#ifndef GABOW_SCC_H_
#define GABOW_SCC_H_

#include <vector>
#include <stack>
#include <ctime>

class GabowSCC {
 public:
  typedef std::vector< std::vector<unsigned> > AdjacencyList;

  GabowSCC(const GabowSCC::AdjacencyList & graph);
  ~GabowSCC();

  void RunGabow();
  double GetGabowRunTime() const; // Unit is seconds.
  GabowSCC::AdjacencyList GetGabowSCC() const;

 private:
  void DFS(const unsigned v);

  double duration;
  std::clock_t start;
  std::size_t vertices_num_;
  std::vector<bool> is_visited_;
  std::vector<unsigned> index_;
  std::stack<unsigned> dfs_path_;
  std::stack<unsigned> contracted_path_;
  GabowSCC::AdjacencyList graph_;
  GabowSCC::AdjacencyList strongly_connected_components_;
};

#endif // GABOW_SCC_H_