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

void GRAPHdestroy(Graph* G) {
    if (G == nullptr) return;

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

void GRAPHshow(const Graph* G) {
    for (int v = 0; v < G->V; ++v) {
        cout << v << ":";
        for (Node* a = G->adj[v]; a != nullptr; a = a->next)
            cout << " " << a->w;
        cout << "\n";
    }
}

int main() {
    Graph* G = GRAPHinit(4);

    UGRAPHinsertEdge(G, 0, 1);
    UGRAPHinsertEdge(G, 0, 2);
    UGRAPHinsertEdge(G, 1, 3);

    cout << "grafo actual:\n";
    GRAPHshow(G);

    GRAPHdestroy(G);
    cout << "\ngrafo destruido correctamente.\n";

    return 0;
}
