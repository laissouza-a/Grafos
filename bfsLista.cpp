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

void bfs(Grafo* g, int start) {
    bool* visited = new bool[g->numNodes];
    int* queue = new int[g->numNodes];
    int front = 0;
    int rear = 0;

    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
    }

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        std::cout << current << " ";

        Node* node = g->adjList[current];
        while (node != nullptr) {
            int adjacent = node->val;
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
            }
            node = node->next;
        }
    }

    delete[] visited;
    delete[] queue;
}

int main() {
    Grafo* g1 = criar(5);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 3);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 4);
    addEdge(g1, 3, 4);
    imprimir(g1);

    std::cout << "BFS traversal starting from vertex 0: ";
    bfs(g1, 0);
    cout << std::endl;

    destruir(g1);
    return 0;
}
