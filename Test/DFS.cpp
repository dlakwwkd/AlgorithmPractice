#include <stdio.h>
#include <vector>

struct Vertex
{
    enum Color
    {
        WHITE,
        BLACK,
        GRAY,
    };
    Color   color;
    int     value;
    int     discovery;
    int     finishing;
    Vertex*                 pred;
    std::vector<Vertex*>    adj;
};

struct Graph
{
    std::vector<Vertex*> allVertex;
};

void CreateVertex(Graph* graph, int num)
{
    if (!graph || num < 1)
        return;

    graph->allVertex.reserve(num);

    Vertex* vertex = new Vertex();
    vertex->color = Vertex::WHITE;
    vertex->value = 0;
    graph->allVertex.push_back(vertex);

    for (int i = 1; i < num; ++i)
    {
        Vertex* vertex = new Vertex();
        vertex->color = Vertex::WHITE;
        vertex->value = i;

        Vertex* prev = graph->allVertex.back();
        prev->adj.push_back(vertex);
        vertex->adj.push_back(prev);

        graph->allVertex.push_back(vertex);
    }
}

void DFS_Visit(Graph* graph, Vertex* vertex, int& time)
{
    if (!graph || !vertex)
        return;

    vertex->discovery = ++time;
    vertex->color = Vertex::GRAY;
    for (auto& v : vertex->adj)
    {
        if (v->color == Vertex::WHITE)
        {
            v->pred = vertex;
            DFS_Visit(graph, v, time);
        }
    }
    vertex->color = Vertex::BLACK;
    vertex->finishing = ++time;

    printf("[%d/%d]: %d\n", vertex->discovery, vertex->finishing, vertex->value);
}

void DFS(Graph* graph)
{
    if (!graph)
        return;

    for (auto& vertex : graph->allVertex)
    {
        vertex->color = Vertex::WHITE;
        vertex->pred = nullptr;
    }
    int time = 0;
    for (auto& vertex : graph->allVertex)
    {
        if (vertex->color == Vertex::WHITE)
            DFS_Visit(graph, vertex, time);
    }
}

int main()
{
    Graph* graph = new Graph();

    CreateVertex(graph, 20);
    DFS(graph);

    getchar();
}