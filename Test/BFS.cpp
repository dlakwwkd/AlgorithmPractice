#include <stdio.h>
#include <queue>
#include <vector>

struct Vertex
{
    enum Color
    {
        WHITE,
        BLACK,
    };
    Color   color;
    int     value;
    std::vector<Vertex*> linkedVertesis;
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
        prev->linkedVertesis.push_back(vertex);
        vertex->linkedVertesis.push_back(prev);

        graph->allVertex.push_back(vertex);
    }
}

void BFS(Graph* graph, Vertex* source)
{
    if (!graph || !source)
        return;

    int n = 0;
    std::queue<Vertex*> queue;
    queue.push(source);
    while (!queue.empty())
    {
        Vertex* curVertex = queue.front();
        queue.pop();

        if (curVertex->color == Vertex::BLACK)
            continue;
        printf("[%d]: %d\n", ++n, curVertex->value);
        curVertex->color = Vertex::BLACK;

        for (auto& vertex : curVertex->linkedVertesis)
        {
            if (vertex->color == Vertex::BLACK)
                continue;
            queue.push(vertex);
        }
    }
}

int main()
{
    Graph* graph = new Graph();

    CreateVertex(graph, 20);
    BFS(graph, graph->allVertex.front());

    getchar();
}