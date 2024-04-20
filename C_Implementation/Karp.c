#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10

int capacities[MAX_NODES][MAX_NODES];
int flowPassed[MAX_NODES][MAX_NODES];
int graph[MAX_NODES][MAX_NODES];
int parentsList[MAX_NODES];
int currentPathCapacity[MAX_NODES];

int bfs(int startNode, int endNode, int nodesCount) {
    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = startNode;
    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = __INT_MAX__;

    while (front < rear) {
        int currentNode = queue[front++];
        for (int to = 0; to < nodesCount; to++) {
            if (parentsList[to] == -1) {
                if (capacities[currentNode][to] - flowPassed[currentNode][to] > 0) {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = (currentPathCapacity[currentNode] < capacities[currentNode][to] - flowPassed[currentNode][to]) ? currentPathCapacity[currentNode] : (capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if (to == endNode) {
                        return currentPathCapacity[endNode];
                    }
                    queue[rear++] = to;
                }
            }
        }
    }
    return 0;
}

int edmondsKarp(int startNode, int endNode, int nodesCount) {
    int maxFlow = 0;
    while (1) {
        int flow = bfs(startNode, endNode, nodesCount);
        if (flow == 0) {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while (currentNode != startNode) {
            int previousNode = parentsList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }
    return maxFlow;
}

int main() {
    FILE *inputFile = fopen("graph.txt", "r");
    if (!inputFile) {
        printf("Error opening file 'graph.txt'.\n");
        return 1;
    }

    int setNumber = 1;
    while (!feof(inputFile)) {
        int nodesCount, edgesCount;
        fscanf(inputFile, "%d %d", &nodesCount, &edgesCount);

        if (feof(inputFile)) break;

        int source, sink;
        fscanf(inputFile, "%d %d", &source, &sink);

        printf("Set %d:\n", setNumber);

        // Initialize data structures
        for (int i = 0; i < MAX_NODES; ++i) {
            for (int j = 0; j < MAX_NODES; ++j) {
                capacities[i][j] = 0;
                flowPassed[i][j] = 0;
                graph[i][j] = 0;
            }
        }

        // Read edges and capacities
        for (int edge = 0; edge < edgesCount; ++edge) {
            int from, to, capacity;
            fscanf(inputFile, "%d %d %d", &from, &to, &capacity);
            capacities[from][to] = capacity;
            graph[from][to] = 1;
            graph[to][from] = 1;
        }

        // Calculate and output max flow
        int maxFlow = edmondsKarp(source, sink, nodesCount);
        printf("Max Flow: %d\n\n", maxFlow);

        setNumber++;
    }

    fclose(inputFile);

    return 0;
}
