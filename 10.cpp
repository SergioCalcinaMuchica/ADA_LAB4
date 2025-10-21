#include <iostream>
#include <cstdlib>
using namespace std;

using vertex = int;

struct Node {
    vertex w;
    Node* next;
    Node(vertex w, Node* next = nullptr) : w(w), next(next) {}
};

struct Graph {
    int V;
    int A;
    Node** adj;
};

static Node* NEWnode(vertex w, Node* next) {
    return new Node(w, next);
}

Graph* GRAPHinit(int V) {
    Graph* G = new Graph;
    G->V = V;
    G->A = 0;
    G->adj = new Node*[V];
    for (int v = 0; v < V; ++v)
        G->adj[v] = nullptr;
    return G;
}

void GRAPHinsertArc(Graph* G, vertex v, vertex w) {
    for (Node* a = G->adj[v]; a != nullptr; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void UGRAPHinsertEdge(Graph* G, vertex v, vertex w) {
    if (v == w) return;
    GRAPHinsertArc(G, v, w);
    GRAPHinsertArc(G, w, v);
}

int UGRAPHdegrees(const Graph* G) {
    int maxDegree = 0;

    for (int v = 0; v < G->V; ++v) {
        int degree = 0;
        for (Node* a = G->adj[v]; a != nullptr; a = a->next)
            degree++;

        if (degree > maxDegree)
            maxDegree = degree;
    }
    return maxDegree;
}

void GRAPHshow(const Graph* G) {
    for (int v = 0; v < G->V; ++v) {
        cout << v << ":";
        for (Node* a = G->adj[v]; a != nullptr; a = a->next)
            cout << " " << a->w;
        cout << "\n";
    }
}

void GRAPHfree(Graph* G) {
    for (int v = 0; v < G->V; ++v) {
        Node* a = G->adj[v];
        while (a != nullptr) {
            Node* temp = a;
            a = a->next;
            delete temp;
        }
    }
    delete[] G->adj;
    delete G;
}

int main() {
    Graph* G = GRAPHinit(4);

    UGRAPHinsertEdge(G, 0, 1);
    UGRAPHinsertEdge(G, 0, 2);
    UGRAPHinsertEdge(G, 1, 2);
    UGRAPHinsertEdge(G, 2, 3);

    cout << "grafo:\n";
    GRAPHshow(G);

    int maxDeg = UGRAPHdegrees(G);
    cout << "\ngrado maximo del grafo: " << maxDeg << endl;

    GRAPHfree(G);
    return 0;
}
