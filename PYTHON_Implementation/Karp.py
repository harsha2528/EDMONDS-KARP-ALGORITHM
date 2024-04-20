from collections import deque

MAX_NODES = 10

capacities = [[0] * MAX_NODES for _ in range(MAX_NODES)]
flowPassed = [[0] * MAX_NODES for _ in range(MAX_NODES)]
graph = [[] for _ in range(MAX_NODES)]
parentsList = [-1] * MAX_NODES
currentPathCapacity = [0] * MAX_NODES

def bfs(startNode, endNode):
    global parentsList, currentPathCapacity
    parentsList = [-1] * MAX_NODES
    currentPathCapacity = [0] * MAX_NODES
    queue = deque()
    queue.append(startNode)
    parentsList[startNode] = -2
    currentPathCapacity[startNode] = float('inf')

    while queue:
        currentNode = queue.popleft()
        for to in graph[currentNode]:
            if parentsList[to] == -1:
                if capacities[currentNode][to] - flowPassed[currentNode][to] > 0:
                    parentsList[to] = currentNode
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode],
                                                  capacities[currentNode][to] - flowPassed[currentNode][to])
                    if to == endNode:
                        return currentPathCapacity[endNode]
                    queue.append(to)
    return 0

def edmondsKarp(startNode, endNode):
    maxFlow = 0
    while True:
        flow = bfs(startNode, endNode)
        if flow == 0:
            break
        maxFlow += flow
        currentNode = endNode
        while currentNode != startNode:
            previousNode = parentsList[currentNode]
            flowPassed[previousNode][currentNode] += flow
            flowPassed[currentNode][previousNode] -= flow
            currentNode = previousNode
    return maxFlow

def main():
    global capacities, flowPassed, graph
    inputFile = open("input.txt", "r")
    if not inputFile:
        print("Error opening file 'input.txt'.")
        return 1

    setNumber = 1
    while True:
        nodesCount, edgesCount = map(int, inputFile.readline().split())
        if not nodesCount:
            break
        
        source, sink = map(int, inputFile.readline().split())

        print(f"Set {setNumber}:")
        
        # Initialize data structures
        graph = [[] for _ in range(MAX_NODES)]
        capacities = [[0] * MAX_NODES for _ in range(MAX_NODES)]
        flowPassed = [[0] * MAX_NODES for _ in range(MAX_NODES)]
        
        # Read edges and capacities
        for _ in range(edgesCount):
            fromNode, toNode, capacity = map(int, inputFile.readline().split())
            capacities[fromNode][toNode] = capacity
            graph[fromNode].append(toNode)
            graph[toNode].append(fromNode)

        # Calculate and output max flow
        maxFlow = edmondsKarp(source, sink)
        print(f"Max Flow: {maxFlow}\n")

        setNumber += 1

    inputFile.close()

if __name__ == "__main__":
    main()
