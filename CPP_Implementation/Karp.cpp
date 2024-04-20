#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

const int MAX_NODES = 10;

int capacities[MAX_NODES][MAX_NODES];
int flowPassed[MAX_NODES][MAX_NODES];
vector<int> graph[MAX_NODES];
int parentsList[MAX_NODES];
int currentPathCapacity[MAX_NODES];

int bfs(int startNode, int endNode)
{
    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));
    queue<int> q;
    q.push(startNode);
    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = INT_MAX;

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        for (size_t i = 0; i < graph[currentNode].size(); i++)
        {
            int to = graph[currentNode][i];
            if (parentsList[to] == -1)
            {
                if (capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
                {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode],
                                                  capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if (to == endNode)
                    {
                        return currentPathCapacity[endNode];
                    }
                    q.push(to);
                }
            }
        }
    }
    return 0;
}

int edmondsKarp(int startNode, int endNode)
{
    int maxFlow = 0;
    while (true)
    {
        int flow = bfs(startNode, endNode);
        if (flow == 0)
        {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while (currentNode != startNode)
        {
            int previousNode = parentsList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }
    return maxFlow;
}

int main()
{
    ifstream inputFile("graph.txt");
    if (!inputFile)
    {
        cout << "Error opening file 'graph.txt'." << endl;
        return 1;
    }

    int setNumber = 1;
    while (!inputFile.eof())
    {
        int nodesCount, edgesCount;
        inputFile >> nodesCount >> edgesCount;
        if (inputFile.eof())
            break;

        int source, sink;
        inputFile >> source >> sink;

        cout << "Set " << setNumber << ":" << endl;

        // Initialize data structures
        for (int i = 0; i < MAX_NODES; ++i)
        {
            graph[i].clear();
            for (int j = 0; j < MAX_NODES; ++j)
            {
                capacities[i][j] = 0;
                flowPassed[i][j] = 0;
            }
        }

        // Read edges and capacities
        for (int edge = 0; edge < edgesCount; ++edge)
        {
            int from, to, capacity;
            inputFile >> from >> to >> capacity;
            capacities[from][to] = capacity;
            graph[from].push_back(to);
            graph[to].push_back(from);
        }

        // Calculate and output max flow
        int maxFlow = edmondsKarp(source, sink);
        cout << "Max Flow: " << maxFlow << endl;

        setNumber++;
    }

    inputFile.close();

    return 0;
}