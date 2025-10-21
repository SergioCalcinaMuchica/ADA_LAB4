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
    Node* a = new Node(w, next);
    return a;
}

Graph* GRAPHinit(int V) {
    Graph* G = new Graph;
    G->V = V;
    G->A = 0;
    G->adj = new Node*[V];
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = nullptr;
    return G;
}

void GRAPHinsertArc(Graph* G, vertex v, vertex w) {
    for (Node* a = G->adj[v]; a != nullptr; a = a->next)
        if (a->w == w) return;

    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void GRAPHremoveArc(Graph* G, vertex v, vertex w) {
    Node* actual = G->adj[v];
    Node* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->w == w) {
            if (anterior == nullptr)
                G->adj[v] = actual->next;
            else
                anterior->next = actual->next;

            delete actual;
            G->A--;
            return;
        }
        anterior = actual;
        actual = actual->next;
    }
}

void GRAPHshow(const Graph* G) {
    for (vertex v = 0; v < G->V; ++v) {
        cout << v << ":";
        for (Node* a = G->adj[v]; a != nullptr; a = a->next)
            cout << " " << a->w;
        cout << "\n";
    }
}

void GRAPHfree(Graph* G) {
    for (vertex v = 0; v < G->V; ++v) {
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

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 0);
    GRAPHinsertArc(G, 2, 3);

    cout << "Grafo original:\n";
    GRAPHshow(G);

    GRAPHremoveArc(G, 2, 0);

    cout << "\nGrafo despues de eliminar el arco 2→0:\n";
    GRAPHshow(G);

    GRAPHfree(G);
    return 0;
}
