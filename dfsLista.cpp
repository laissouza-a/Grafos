#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

struct Grafo {
    int numNodes;
    Node** adjList;
};

Grafo* criar(int numNodes) {
    Grafo* g = new Grafo;
    g->numNodes = numNodes;
    g->adjList = new Node*[numNodes];
    for (int i = 0; i < numNodes; i++) {
        g->adjList[i] = nullptr;
    }
    return g;
}

void destruir(Grafo* g) {
    if (g->adjList == nullptr) {
        return;
    }
    for (int i = 0; i < g->numNodes; i++) {
        Node* current = g->adjList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] g->adjList;
    delete g;
}

Node* criarNode(int val) {
    Node* newNode = new Node;
    newNode->val = val;
    newNode->next = nullptr;
    return newNode;
}

void addEdge(Grafo* g, int i, int j) {
    Node* newNode = criarNode(j);
    newNode->next = g->adjList[i];
    g->adjList[i] = newNode;
}

void removeEdge(Grafo* g, int i, int j) {
    Node* current = g->adjList[i];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->val == j) {
            if (prev == nullptr) {
                g->adjList[i] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }
}

bool hasEdge(Grafo* g, int i, int j) {
    Node* current = g->adjList[i];
    while (current != nullptr) {
        if (current->val == j) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void imprimir(Grafo* g) {
    for (int i = 0; i < g->numNodes; i++) {
        Node* current = g->adjList[i];
        while (current != nullptr) {
            cout << i << " -> " << current->val << std::endl;
            current = current->next;
        }
    }
}

void dfsUtil(Grafo* g, int v, bool* visited) {
    visited[v] = true;
    std::cout << v << " ";

    Node* current = g->adjList[v];
    while (current != nullptr) {
        int adjacent = current->val;
        if (!visited[adjacent]) {
            dfsUtil(g, adjacent, visited);
        }
        current = current->next;
    }
}

void dfs(Grafo* g, int start) {
    bool* visited = new bool[g->numNodes];
    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
    }
    dfsUtil(g, start, visited);
    delete[] visited;
}

int main() {
    Grafo* g1 = criar(5);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 3);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 4);
    addEdge(g1, 3, 4);
    imprimir(g1);

    cout << "DFS traversal starting from vertex 0: ";
    dfs(g1, 0);
    cout << std::endl;

    destruir(g1);
    return 0;
}
