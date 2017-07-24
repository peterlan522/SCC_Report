# SCC_Report

This repo contains both the c++ source code files and graph csv files.

Please create a folder called "Graph_Files", and move all the graph csv files (totally 71 files) into this "Graph_Files" folder. Then put both "source_code" folder and "Graph_Files" folder within same directory. Goto "source_code" folder, execute "run" or use "g++ -std=c++11 tarjan_scc.cc gabow_scc.cc ks_scc.cc main.cc -I ./CsvParser/include ./CsvParser/src/csvparser.c -o run" to compile.
