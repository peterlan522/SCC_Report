#include <stack>
#include <vector>
#include <ctime>
#include "tarjan_scc.h"

TarjanSCC::TarjanSCC(const TarjanSCC::AdjacencyList & graph) {
  graph_ = graph;
  vertices_num_ = graph_.size();
  time_stamp_ = 0;
  is_visited_.assign(vertices_num_, false);
  is_on_stack_.assign(vertices_num_, false);
  lowlink_.resize(vertices_num_);
  num_.resize(vertices_num_);
}

TarjanSCC::~TarjanSCC() {}

void TarjanSCC::DFS(const unsigned v) {
  lowlink_[v] = num_[v] = time_stamp_++;
  dfs_path_.push(v);
  is_visited_[v] = true;
  is_on_stack_[v] = true;

  for ( unsigned w : graph_[v] ) {
    if ( !is_visited_[w] ) {
      DFS(w);
      lowlink_[v] = min( lowlink_[v], lowlink_[w] );
    } else if ( num_[w] < num_[v] && is_on_stack_[w] ) {
      lowlink_[v] = min( lowlink_[v], num_[w] );
    }
  }

  // Check if vertex v is the root of scc or not.
  if ( num_[v] == lowlink_[v] ) {
    std::vector<unsigned> component;
    while ( !dfs_path_.empty() && num_[dfs_path_.top()] >= num_[v] ) {
      component.push_back( dfs_path_.top() );
      is_on_stack_[ dfs_path_.top() ] = false;
      dfs_path_.pop();
    }
    strongly_connected_components_.push_back(component);
  }
}

void TarjanSCC::RunTarjan() {
  start = std::clock();
  for (std::size_t v = 0; v < vertices_num_; ++v) {
    if ( !is_visited_[v] ) {
      DFS(v);
    }
  }
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}

TarjanSCC::AdjacencyList TarjanSCC::GetTarjanSCC() const {
  return strongly_connected_components_;
}

// Unit is seconds.
double TarjanSCC::GetTarjanRunTime() const {
  return duration;
}
