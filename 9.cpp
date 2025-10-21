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

void UGRAPHinsertEdge(Graph* G, vertex v, vertex w) {
    if (v == w) return;
    GRAPHinsertArc(G, v, w);
    GRAPHinsertArc(G, w, v);
}

void UGRAPHremoveEdge(Graph* G, vertex v, vertex w) {
    if (v == w) return;
    GRAPHremoveArc(G, v, w);
    GRAPHremoveArc(G, w, v);
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

    cout << "grafo no dirigido inicial:\n";
    GRAPHshow(G);

    cout << "\neliminando arista 0–2\n";
    UGRAPHremoveEdge(G, 0, 2);

    cout << "\ngrafo después de la eliminacion:\n";
    GRAPHshow(G);

    GRAPHfree(G);
    return 0;
}
