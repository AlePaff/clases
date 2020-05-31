#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 *  Constructor carga un grafo desde un archivo
 */
Graph::Graph(const char* path) {
    std::ifstream file(path);
    
    unsigned int numVertex;
    file >> numVertex;
    
    std::cout << "Hay " << numVertex << " vertices" << std::endl;
    this->nodeList.resize(numVertex);
    
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) { continue; }
        unsigned src, dest;
        std::stringstream ss(line);
        ss >> src >> dest;
        std::cout << "Conectando " << src << " -> " << dest << std::endl;
        this->nodeList[src].neighbours.push_back(dest);
    }
}

/**
 * Imprime todos los vertices y sus vecinos inmediatos, recorriendolos en orden ascendiente.
 */
void Graph::print() const {
    unsigned int i = 0;
    for (auto node : this->nodeList) {
        std::cout << "Vertice " << i << std::endl;
        ++i;
        for(auto neighbour : node.neighbours) {
            std::cout << "    -> " << neighbour << std::endl;
        }
    }
}

void Graph::printBFS() const {
    BfsRange range = BfsRange(*this);
    for (auto nodeIdx: range) {
        std::cout << "Vertice " << nodeIdx << std::endl;
        Node node = this->nodeList[nodeIdx];
        for(auto neighbour : node.neighbours) {
            std::cout << "    -> " << neighbour << std::endl;
        }
    }
}

BfsIterator::BfsIterator(const Graph& graph, bool finished)
    : graphRef(graph), finished(finished) {
        if (!finished) {
            this->stack.push_back(0);
            unsigned int numVertex = graph.nodeList.size();
            this->visited.resize(numVertex, false);
            this->visited[0] = true;
            ++*this;
        }
    }

BfsIterator& BfsIterator::operator++() {
    this->finished = this->stack.size() == 0;
    if (!this->finished) {
        this->curValue = this->stack.front();
        this->stack.pop_front();
        pushNeighbours();
    }
    return *this;
}

void BfsIterator::pushNeighbours() {
    auto currentNeighbours = this->graphRef.nodeList[this->curValue].neighbours;
    for (auto n : currentNeighbours) {
        if (!this->visited[n]) {
            this->stack.push_back(n);
            this->visited[n] = true;
        }
    }
}

const unsigned int BfsIterator::operator*() const {
    return this->curValue;
}

bool BfsIterator::operator!=(const BfsIterator& other) const {
    return this->finished != other.finished;
}

BfsRange::BfsRange(const Graph& graph)
    : graphRef(graph) {}

BfsIterator BfsRange::begin() {
    return BfsIterator(graphRef);
}

BfsIterator BfsRange::end() {
    return BfsIterator(graphRef, true);
}
