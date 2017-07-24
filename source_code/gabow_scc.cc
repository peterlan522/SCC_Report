#include <vector>
#include <stack>
#include <ctime>
#include "gabow_scc.h"

GabowSCC::GabowSCC(const GabowSCC::AdjacencyList & graph) {
  graph_ = graph;
  vertices_num_ = graph_.size();
  is_visited_.assign(vertices_num_, false);
  index_.assign(vertices_num_, 0);
}

GabowSCC::~GabowSCC() {}

void GabowSCC::DFS(const unsigned v) {
  is_visited_[v] = true;
  dfs_path_.push(v);
  index_[v] = dfs_path_.size() - 1;
  contracted_path_.push( index_[v] );

  for ( unsigned w: graph_[v] ) {
    if ( !is_visited_[w] ) {
      DFS(w);
    } else {
      while ( index_[w] < contracted_path_.top() ) {
        contracted_path_.pop();
      }
    }
  }

  // Check if vertex v is the root of a scc or not.
  if ( !contracted_path_.empty() && ( index_[v] == contracted_path_.top() )) {
    std::vector<unsigned> component;
    while ( !dfs_path_.empty() && index_[v] <= dfs_path_.top() ) {
      component.push_back( dfs_path_.top() );
      dfs_path_.pop();
    }
    contracted_path_.pop();
    strongly_connected_components_.push_back(component);
  }
}

void GabowSCC::RunGabow() {
  start = std::clock();
  for (std::size_t v = 0; v < vertices_num_; ++v) {
    if ( !is_visited_[v] ) {
      DFS(v);
    }
  }
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}

GabowSCC::AdjacencyList GabowSCC::GetGabowSCC() const {
  return strongly_connected_components_;
}

// Unit is seconds.
double GabowSCC::GetGabowRunTime() const {
  return duration;
}