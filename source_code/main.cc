/*
 * File: main.cc
 * -------------
 * This is the main program of showing reports of comparing 3 different
 * algorithms to find strongly connected components in a digraph.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <unistd.h>
#include "tarjan_scc.h"
#include "gabow_scc.h"
#include "ks_scc.h"
#include "csvparser.h"

typedef std::vector< std::vector<unsigned> > AdjacencyList;

const std::vector<unsigned> vertices_spectrum = { 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000 };

/*
 * Function: ReadFileToGraph
 * --------------------------
 * Input: Csv file; number of vertices within this file.
 * Output: AdjacencyList of a graph.
 */
AdjacencyList ReadFileToGraph(const std::string filename, const unsigned num_of_vertices);

/*
 * Function: PrintResults
 * --------------------------
 * Input: Algorithm name; vector of running time results of this algorithm.
 * Output: Print out algorithm name and a sequence of running time in sec.
 */
void PrintResults(const std::string alg_name, std::vector<double> & results);

/*
 * Function: RunAlgs
 * --------------------------
 * Input: AdjacencyList of a graph; 3 vectors to store the results.
 * Output: 3 vectors containing the results of running time of the 3 algorithms.
 */
void RunAlgs(const AdjacencyList & graph, std::vector<double> & r1, std::vector<double> & r2, std::vector<double> & r3);

/*
 * Function: RunCaseAReport
 * --------------------------
 * Output: Print out a report of case A, which shows the running time of 3 algorithm given constant number
 *         of edges but increase the number of vertices.
 */
void RunCaseAReport();

/*
 * Function: RunCaseBReport
 * --------------------------
 * Output: Print out a report of case B, which shows the running time of 3 algorithm given different density
 *         of graphs but increase the number of vertices.
 */
void RunCaseBReport();

/*
 * Function: PrintInstructions
 * --------------------------
 * Output: Print out an instruction of what does this program do.
 */
void PrintInstructions();


int main(int argc, char *argv[]) {
  const std::string kCaseA = "a";
  const std::string kCaseB = "b";
  const std::string kQuit = "q";
  const unsigned kOneChar = 1;
  const std::string kDirectory = "../Graph_Files";

  chdir( kDirectory.c_str() );

  PrintInstructions();

  while (true) {
    std::cout << "Enter: ";
    std::string user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    if (user_input.length() != kOneChar) {
      std::cout << "Invalid input. Please enter again. ";
    } else if (user_input == kQuit) {
      break;
    } else if (user_input == kCaseA) {

      RunCaseAReport();
      continue;
    } else if (user_input == kCaseB) {
      RunCaseBReport();
      continue;
    }
    std::cout << std::endl;
  }

  return 0;
}


AdjacencyList ReadFileToGraph(const std::string filename, const unsigned num_of_vertices) {

  AdjacencyList graph(num_of_vertices);

  CsvParser *csvparser = CsvParser_new(filename.c_str(), ",", 0); // file, delimiter, first_line_is_header? filename.c_str()
  CsvRow *row;

  while ( (row = CsvParser_getRow(csvparser)) ) {
    const char **rowFields = CsvParser_getFields(row);
    unsigned src, dst;
    std::string src_val = rowFields[0];
    std::string dst_val = rowFields[1];
    if (dst_val != "NULL") {
      src = atoi( src_val.c_str() );
      dst = atoi( dst_val.c_str() );
      graph.at(src).push_back(dst);
    }
    CsvParser_destroy_row(row);
  }
  CsvParser_destroy(csvparser);

  return graph;
}

void PrintResults(const std::string alg_name, std::vector<double> & results) {
  std::cout << std::fixed;
  std::cout << std::setprecision(3);
  std::cout << alg_name << ":\t";
  for (unsigned i = 0; i < results.size(); ++i) {
    std::cout << results[i] << '\t';
  }
  std::cout << std::endl;
}

void RunAlgs(const AdjacencyList & graph, std::vector<double> & r1, std::vector<double> & r2, std::vector<double> & r3) {
  TarjanSCC ts(graph);
  ts.RunTarjan();
  AdjacencyList ts_result = ts.GetTarjanSCC();
  double ts_run_time = ts.GetTarjanRunTime();
  r1.push_back(ts_run_time);

  GabowSCC gs(graph);
  gs.RunGabow();
  AdjacencyList gs_result = gs.GetGabowSCC();
  double gs_run_time = gs.GetGabowRunTime();
  r2.push_back(gs_run_time);

  KSSCC ks(graph);
  ks.RunKS();
  AdjacencyList ks_result = ks.GetKSSCC();
  double ks_run_time = ks.GetKSRunTime();
  r3.push_back(ks_run_time);
}

void RunCaseAReport() {
  const std::string kFileSuffix = ".csv";
  const std::vector<std::string> const_num_edges = { "1X_at_", "4X_at_", "9X_at_" };

  for (unsigned i = 0; i < const_num_edges.size(); ++i) {
    std::vector<double> tr;
    std::vector<double> gr;
    std::vector<double> kr;

    for (unsigned j = (2 * i + 1); j < vertices_spectrum.size(); ++j) {
      std::string filename = const_num_edges[i] + std::to_string( vertices_spectrum[j] ) + kFileSuffix;
      AdjacencyList graph = ReadFileToGraph(filename, vertices_spectrum[j] );
      RunAlgs(graph, tr, gr, kr);
    }

    std::cout << "Number of edges: " << const_num_edges[i] << " (unit: sec)" << std::endl;
    PrintResults("Tarjan", tr);
    PrintResults("Gabow", gr);
    PrintResults("KS", kr);
    std::cout << std::endl;
  }
}

void RunCaseBReport() {
  const std::string kFileSuffix = ".csv";
  const std::vector<std::string> density_spectrum = { "0.01", "0.05", "0.1", "0.2", "0.5", "0.8", "1.0" };

  for (std::string density : density_spectrum) {
    std::vector<double> tr;
    std::vector<double> gr;
    std::vector<double> kr;

    for (unsigned node_num : vertices_spectrum) {
      std::string filename = density + "at" + std::to_string(node_num) + kFileSuffix;
      AdjacencyList graph = ReadFileToGraph(filename, node_num);
      RunAlgs(graph, tr, gr, kr);
    }

    std::cout << "Density: " << density << " (unit: sec)" << std::endl;
    PrintResults("Tarjan", tr);
    PrintResults("Gabow", gr);
    PrintResults("KS", kr);
    std::cout << std::endl;
  }
}

void PrintInstructions() {
  std::cout << "This program is to compare running time of 3 algorithms finding\n"
            << "strongly connected components in different digraphs.\n"
            << "Case (a): constant number of edges with different number of vertices;\n"
            << "Case (b): different density graphs with different number of vertices;\n"
            << "\nEnter \'a\': run report of case a; \'b\': run report of case b; \'q\': quit.\n" << std::endl;
}
