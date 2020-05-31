#ifndef GRAPH_H 
#define GRAPH_H

#include <vector>
#include <deque>

// Vertice en un grafo dirigido
struct Node {
    std::vector<unsigned int> neighbours;
};

// Grafo dirigido
struct Graph {
    // Carga la cantidad de vertices y sus conexiones desde un archivo
    explicit Graph(const char* file);
    // Imprime todos los vertices en orden ascendente
    void print() const;
    // Imprime los vertices haciendo un recorrido BFS
    void printBFS() const;
    // Lista de vertices en el grafo
    std::vector<Node> nodeList;
};


class BfsRange;

// Iterador BFS. Posee un vector de visitados y un stack para apilarlos
class BfsIterator {
public:
    // Recibe el grafo a iterar. End inicializa `finished` en true
    explicit BfsIterator(const Graph& graph, bool finished = false);
    // Avanza el iterador, carga un vertice y sus vecinos no visitados
    BfsIterator& operator++();
    // Devuelve el valor del vertice sobre el que está parado
    const unsigned int operator*() const;
    // Le interesa únicamente el flag "finished" para saber si llegó al final
    bool operator!=(const BfsIterator& other) const;
private:
    // Agrega los nodos adyacentes
    void pushNeighbours();
    const Graph& graphRef;
    unsigned curValue;
    bool finished;
    std::vector<bool> visited;
    std::deque<unsigned int> stack;
};

class BfsRange {
public:
    explicit BfsRange(const Graph& graph);
    BfsIterator begin();
    BfsIterator end();
private:
    const Graph& graphRef;
};


#endif // GRAPH_H
