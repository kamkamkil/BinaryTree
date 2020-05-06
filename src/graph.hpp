#pragma once

#include <optional>
#include <cstdint>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <queue>
#include <iostream>

// Uwaga! Kod powinien być odporny na błędy i każda z metod jeżeli zachodzi niebezpieczeństwo wywołania z niepoprawnymi parametrami powinna zgłaszac odpowiednie wyjątki!

// klasa reprezentująca graf skierowany oparty na MACIERZY SĄSIEDZTWA
// V - dane przechowywane przez wierzcholki
// E - dane przechowywane przez krawedzie (etykiety)
template <typename V, typename E>
class Graph
{
public:
    //TODO wyciągnięcie classy z clasy
    // iterator po wierzchołkach (rosnąco po id wierzchołków)
    class VerticesIterator
    {
        // ...

    public:
        VerticesIterator(std::vector<V> *valueList_) : idVal(0), valueList(valueList_){};
        VerticesIterator(size_t id_, std::vector<V> *valueList_) : idVal(id_), valueList(valueList_){};
        bool operator==(const VerticesIterator &vi2) const { return (idVal == vi2.idVal); };
        bool operator!=(const VerticesIterator &vi2) const { return idVal != vi2.idVal; };
        VerticesIterator &operator++()
        {
            id++;
            return *this;
        };
        VerticesIterator operator++(int)
        {
            VerticesIterator iterator = *this;
            ++*this;
            return iterator;
        };
        V &operator*() { return valueList->at(idVal); } // const;
        V *operator->() const;
        // zwraca id aktualnego wierzchołka
        int id() const { return idVal; };

    private:
        int idVal;
        std::vector<V> *valueList;
    };

    // iterator po istniejących krawędziach
    class EdgesIterator
    {
    public:
        EdgesIterator(Graph<V, E> *graph_) : v1id_val(0), v2id_val(0), graph(graph_)
        {
            if (graph->edgeExist(v1id_val, v2id_val))
                ++*this;
        };
        EdgesIterator(size_t v1id_val_, size_t v2id_val_, Graph<V, E> *graph_) : v1id_val(v1id_val_), v2id_val(v2id_val_), graph(graph_){};
        bool operator==(const EdgesIterator &ei) const { return v1id_val == ei.v1id_val && v2id_val == ei.v2id_val; };
        bool operator!=(const EdgesIterator &ei) const { return v1id_val != ei.v1id_val && v2id_val != ei.v2id_val; };
        EdgesIterator &operator++()
        {
            while (graph->edgeExist(v1id_val, v2id_val))
            {
                if (v1id_val < graph->nrOfVertices())
                    v2id_val++;
                else
                {
                    v1id_val++;
                    v2id_val = 0;
                }
                if (v1id_val == graph->nrOfVertices() && v2id_val == graph->nrOfVertices())
                    break;
            }
            return *this;
        };
        EdgesIterator operator++(int)
        {
            EdgesIterator iterator = *this;
            ++*this;
            return iterator;
        };
        E &operator*() const { return graph->edgeLabel(v1id_val, v2id_val); };//?????? o co biega ??
        E *operator->() const;
        // zwraca id wierzchołka startowego
        std::size_t v1id() const { return v1id_val; };
        // zwraca id wierzchołka koncowego
        std::size_t v2id() const { return v2id_val; };

    private:
        size_t v1id_val;
        size_t v2id_val;
        Graph<V, E> *graph;
    };
    // ...

public:
    Graph() : verticesAmount(0){};
    Graph(const Graph<V, E> &source) = default;
    Graph(Graph<V, E> &&source) = default;
    Graph &operator=(const Graph<V, E> &source) = default ;
    Graph &operator=(Graph<V, E> &&source) = default ;
    ~Graph(){};

    // dodaje nowy wierzchołek z danymi przyjętymi w argumencie (wierzchołek powinien posiadać kopie danych) i zwraca "VerticesIterator" na nowo utworzony wierzchołek
    VerticesIterator insertVertex(const V &vertex_data);
    // dodaje nową krawędź między wierzchołkami o id "vertex1_id" i "vertex2_id" i zwraca "EdgesIterator" na nowo dodaną krawędź, oraz informację o tym czy została dodana nowa krawędź, czy nie
    // jeśli krawędź między podanymi wierzchołkami już istnieje to działanie funkcji zależy od ostatniego argumentu
    // jeśli ostatni argument przyjmuje wartość "true" to krawędź zostaje zastąpiona, jeśli "false" to nie
    std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
    // usuwa wierzchołek o podanym id i zwraca "VerticesIterator" na kolejny wierzchołek, lub to samo co "endVertices()" w przypadku usunięcia ostatniego wierzchołka, lub braku wierzchołka o podanym id
    VerticesIterator removeVertex(std::size_t vertex_id);
    // usuwa krawedź między dwoma wierzchołkami o podanych id i zwraca "EdgesIterator" na kolejną krawędź, lub to samo co "endEdges()" w przypadku usunięcia ostatniej krawedzi, lub braku krawędzi między wierzchołkami o podanych id
    EdgesIterator removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
    ;
    // zwraca true jeśli istnieje krawędź między wierzchołkami o podanych id, false w przeciwnym razie
    // O(1)
    bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const
    {
        return vertex1_id < matrix.size() && vertex2_id < matrix.size() && matrix[vertex1_id][vertex2_id];
    };
    ;
    // zwraca ilość wierzchołków w grafie
    // O(1)
    std::size_t nrOfVertices() const { return valueList.size(); };
    // zwraca ilość krawędzi w grafie
    // O(1)
    std::size_t nrOfEdges() const { return verticesAmount; };
    // drukuje macierz sąsiedztwa na konsoli (debug)
    void printNeighborhoodMatrix() const;
    // zwraca "VerticesIterator" do wierzchołka o podanym id, lub to samo co "endVertices()" w przypadku braku wierzchołka o podanym id
    VerticesIterator vertex(std::size_t vertex_id){return vertex_id < valueList.size() ? VerticesIterator(vertex_id, &valueList) : endVertices()};
    ;
    // zwraca referencję do danych wierzchołka o podanym id
    const V &vertexData(std::size_t vertex_id) const {return valueList[vertex_id]};
    ;
    // zwraca referencję do danych wierzchołka o podanym id
    V &vertexData(std::size_t vertex_id) { return valueList[vertex_id]; };
    ;
    // zwraca "EdgesIterator" do krawędzi pomiędzy wierzchołkami o podanych id, lub to samo co "endEdges()" w przypadku braku krawędzi między wierzchołkami o podanych id
    EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id] ? EdgesIterator(vertex1_id, vertex2_id, &matrix); };
    ;
    // zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    const E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) const { return matrix[vertex1_id][vertex2_id].value(); };
    ;
    // zwraca referencję do danych (etykiety) krawędzi pomiędzy wierzchołkami o podanych id
    E &edgeLabel(std::size_t vertex1_id, std::size_t vertex2_id) { return matrix[vertex1_id][vertex2_id].value(); };
    ;
    VerticesIterator begin() { return beginVertices(); };
    VerticesIterator end() { return endVertices(); };
    // zwraca "VerticesIterator" na pierwszy wierzchołek (o najmniejszym id)
    VerticesIterator beginVertices() { return VerticesIterator(0, &valueList); };
    ;
    // zwraca "VerticesIterator" "za ostatni" wierzchołek
    VerticesIterator endVertices() { return VerticesIterator(valueList.size(), &valueList); };
    ;
    // zwraca "EdgesIterator" na pierwszą krawędz
    EdgesIterator beginEdges() { return EdgesIterator(0, 0, &matrix); };
    ;
    // zwraca "EdgesIterator" "za ostatnią" krawędz
    EdgesIterator endEdges() { return EdgesIterator(matrix.size() + 1, matrix.size() + 1, this); };
    ;

private:
    std::vector<std::vector<std::optional<E>>> matrix;
    std::vector<V> valueList;
    std::size_t verticesAmount;
};

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::insertVertex(const V &vertex_data)
{
    valueList.push_back(vertex_data);
    std::optional<E> op;
    std::vector<std::optional<E>> vec(matrix.size(), op);
    matrix.push_back(vec);
    for (auto &&i : matrix)
    {
        i.push_back(op);
    }
    VerticesIterator it(valueList.size() - 1, &valueList);
    return it;
}
template <typename V, typename E>
std::pair<typename Graph<V, E>::EdgesIterator, bool> Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label, bool replace)
{
    if (matrix[vertex1_id][vertex2_id])
    {
        if (replace)
        {
            matrix[vertex1_id][vertex2_id] = label;
            return {EdgesIterator((vertex1_id, vertex2_id, this)), true};

            verticesAmount++;
        }
        return {EdgesIterator((vertex1_id, vertex2_id, this)), false};
    }
    else
    {
        matrix[vertex1_id][vertex2_id] = label;
        verticesAmount++;

        return {EdgesIterator((vertex1_id, vertex2_id, this)), true};
    }
    return {EdgesIterator((vertex1_id, vertex2_id, this)), false};
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::removeVertex(std::size_t vertex_id)
{
    if (vertex_id >= valueList.size())
        return endVertices();
    for (size_t i = 0; i < valueList.size(); i++)
    {
        if (matrix[vertex_id][i] || matrix[i][vertex_id])
            verticesAmount--;
    }
    matrix.erase(matrix.begin() + vertex_id);
    for (auto &&column : matrix)
    {
        column.erase(column.begin() + vertex_id);
    }
    valueList.erase(valueList.begin() + vertex_id);
    return VerticesIterator(vertex_id, &valueList);
}

template <typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const
{
    for (auto &&verse : matrix)
    {
        for (auto &&value : verse)
        {
            std::cout << (value ? "1" : "0") << "  ";
        }
        std::cout << std::endl;
    }
}

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id)
{
    if (matrix[vertex1_id][vertex2_id])
    {
        matrix[vertex1_id][vertex2_id].reset();
        return EdgesIterator(vertex1_id, vertex2_id, this)++;
    }
    else
        return endEdges();
}