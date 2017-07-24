#include <iostream>
#include <vector>
#include <typeinfo>
#include <cstdlib>

#include "csvparser.h"

int main() {
    int line = 0;
    std::vector< std::vector<unsigned> > graph(100);
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new("tiny100.csv", ",", 0);
    CsvRow *row;

    while ( (row = CsvParser_getRow(csvparser)) ) {

    	std::cout << "edge: " << line++ << std::endl;
        const char **rowFields = CsvParser_getFields(row);
        unsigned src = atoi(rowFields[0]);
        unsigned dst = atoi(rowFields[1]);
        std::cout << src << " -> " << dst << std::endl;
        graph.at(src).push_back(dst);
        std::cout << atoi(rowFields[0]) << std::endl;
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);

    for (unsigned i = 0; i < graph.size(); i++) {
        std::cout << i << ": ";
        for (std::vector<unsigned>::iterator it = graph[i].begin(); it != graph[i].end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << "\n";
    }
	
    return 0;
}