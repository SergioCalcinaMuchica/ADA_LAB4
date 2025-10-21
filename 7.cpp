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

bool GRAPHundir(Graph* G) {
    for (int v = 0; v < G->V; ++v) {
        for (Node* a = G->adj[v]; a != nullptr; a = a->next) {
            vertex w = a->w;
            bool existeInverso = false;
            for (Node* b = G->adj[w]; b != nullptr; b = b->next) {
                if (b->w == v) {
                    existeInverso = true;
                    break;
                }
            }

            if (!existeInverso)
                return false;
        }
    }
    return true;
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

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 1);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 2);

    GRAPHshow(G);

    if (GRAPHundir(G))
        cout << "\nel grafo es no dirigido \n";
    else
        cout << "\nel grafo es dirigido \n";

    return 0;
}
