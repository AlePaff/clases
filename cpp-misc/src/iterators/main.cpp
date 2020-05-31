#include "Graph.h" 
#include <iostream>

constexpr int PATH = 1;

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <grafo>" << std::endl;
    }
    Graph graph(argv[PATH]);
    std::cout << "Imprimiendo valores:\n" << std::endl;
    graph.print();
    std::cout << "\nIterando BFS valores:\n" << std::endl;
    graph.printBFS();
    return 0;
}
