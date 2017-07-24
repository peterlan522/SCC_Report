#include <vector>
#include <stack>
#include <ctime>
#include "ks_scc.h"

KSSCC::KSSCC(const KSSCC::AdjacencyList & graph) {
  graph_ = graph;
  vertices_num_ = graph.size();
  reversed_graph_.resize(vertices_num_);
  is_visited_.assign(vertices_num_, false);
  is_in_component_.assign(vertices_num_, false);
}

KSSCC::~KSSCC() {}

void KSSCC::DFS(const unsigned v) {
  is_visited_[v] = true;

  for ( unsigned w: graph_[v] ) {
    if ( !is_visited_[w] ) {
      DFS(w);
    }
  }
  dfs_path_.push(v);
}

void KSSCC::DFS2(const unsigned v, std::vector<unsigned> & component) {
  is_visited_[v] = true;
  component.push_back(v);
  is_in_component_[v] = true;

  for ( unsigned w: reversed_graph_[v] ) {
    if ( !is_visited_[w] ) {
      DFS2(w, component);
    }
  }
}

void KSSCC::RunKS() {
  // First dfs on original graph.
  start = std::clock();
  for (std::size_t v = 0; v < vertices_num_; ++v) {
    if ( !is_visited_[v] ) {
      DFS(v);
    }
  }

  // Reverse original graph.
  for (std::size_t v = 0; v < vertices_num_; ++v) {
    for ( unsigned w : graph_[v] ) {
      reversed_graph_[w].push_back(v);
    }
  }

  is_visited_.assign(vertices_num_, false);

  // Second dfs on the reversed graph.
  while ( !dfs_path_.empty() ) {
    unsigned w = dfs_path_.top();
    dfs_path_.pop();

    if ( !is_visited_[w] && !is_in_component_[w] ) {
      std::vector<unsigned> one_component;
      DFS2(w, one_component);
      strongly_connected_components_.push_back(one_component);
    }
  }
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
}

KSSCC::AdjacencyList KSSCC::GetKSSCC() const {
  return strongly_connected_components_;
}

// Unit is seconds.
double KSSCC::GetKSRunTime() const {
  return duration;
}