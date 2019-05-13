#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

#define INFINITY 1 << 28
#define NO_PARENT -1

using namespace std;

struct Node {
    int index;
    int distance;
    int parent;

    Node() {}
    Node(int index, int distance, int parent) :
            index{index}, distance{distance}, parent{parent} {}

    bool operator<(const Node& other) const {
        return distance < other.distance;
    }
};

struct Edge {
    int first;
    int second;
    int weight;

    Edge() {}
    Edge(int first, int second, int weight) :
            first{first}, second{second}, weight{weight} {}
};

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("./bellman_ford <file_name>\n");
        return 0;
    }

    string file(argv[1]);
    ifstream in(file);

    int noNodes, noEdges;
    in >> noNodes >> noEdges;

    vector<Node> nodes;
    vector<Edge> edges;

    for (int i = 0; i < noNodes; i++) {
        Node node{i, INFINITY, NO_PARENT};
        nodes.push_back(node);

    }
    nodes[0].distance = 0;

    for (int i = 0; i < noEdges; i++) {
        int first, second, weight;
        in >> first >> second >> weight;

        Edge edge {first, second, weight};
        edges.push_back(edge);
    }

    priority_queue<Node> nodeQueue;
    nodeQueue.push(nodes[0]);

    while(!nodeQueue.empty()){
        Node node = nodeQueue.top();
        nodeQueue.pop();

        for (Edge edge : edges){
            int first = edge.first;
            int second = edge.second;
            int weight = edge.weight;

            if (node.index != edge.first) {
                continue;
            }

            if (nodes[second].distance > nodes[first].distance + weight) {
                nodes[second].distance = nodes[first].distance + weight;
                nodes[second].parent = first;
                nodeQueue.push(nodes[second]);
            }
        }
    }

    for (int i = 1; i < noNodes; i++) {
        cout << nodes[i].distance << " ";
    }

    cout << "\n";

    return 0;
}
