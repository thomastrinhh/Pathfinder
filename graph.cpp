//========================================================
// File: graph.cpp
// Author: Thomas Trinh
// Purpose: Location of the methods declared in graph.h
//========================================================

#include "graph.h"

const int INF = 100000000; // Used in Dijkstra's to represent infinity

// Dijkstra's algorithm implementation to find the paths (shortest and quickest)
void Graph::findPaths(string start, string finish)
{
    int startIndex = getVertexIndex(start);
    int finishIndex = getVertexIndex(finish);

    vector<float> shortestDistances(adjList.size(), INF);
    shortestDistances[startIndex] = 0;

    vector<float> quickestTimes(adjList.size(), INF);
    quickestTimes[startIndex] = 0;

    // Create priority queues for vertices with their distances and times
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> shortestPQ;
    shortestPQ.push({ 0, startIndex });

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> quickestPQ;
    quickestPQ.push({ 0, startIndex });

    vector<int> shortestPredecessors(adjList.size(), -1); // To store shortest path predecessors
    vector<int> quickestPredecessors(adjList.size(), -1); // To store quickest path predecessors

    // Dijkstra's algorithm for both shortest and quickest paths
    while (!shortestPQ.empty() || !quickestPQ.empty()) {
        if (!shortestPQ.empty()) {
            float currentShortest = shortestPQ.top().first;
            int currentShortestVertex = shortestPQ.top().second;
            shortestPQ.pop();

            // Skip if outdated entry
            if (currentShortest > shortestDistances[currentShortestVertex]) {
                continue;
            }

            // Explore neighboring vertices (edges)
            for (const Edge& edge : adjList[currentShortestVertex].edges) {
                int neighborIndex = getVertexIndex(edge.to);
                float newShortest = currentShortest + edge.distance;
                if (newShortest < shortestDistances[neighborIndex]) {
                    shortestDistances[neighborIndex] = newShortest;
                    shortestPredecessors[neighborIndex] = currentShortestVertex; // Update predecessor
                    shortestPQ.push({ newShortest, neighborIndex });
                }
            }
        }

        if (!quickestPQ.empty()) {
            float currentQuickest = quickestPQ.top().first;
            int currentQuickestVertex = quickestPQ.top().second;
            quickestPQ.pop();

            // Skip if outdated entry
            if (currentQuickest > quickestTimes[currentQuickestVertex]) {
                continue;
            }

            // Explore neighboring vertices (edges)
            for (const Edge& edge : adjList[currentQuickestVertex].edges) {
                int neighborIndex = getVertexIndex(edge.to);
                float newQuickest = currentQuickest + edge.distance / edge.speed; // Calculate time using speed
                if (newQuickest < quickestTimes[neighborIndex]) {
                    quickestTimes[neighborIndex] = newQuickest;
                    quickestPredecessors[neighborIndex] = currentQuickestVertex; // Update predecessor
                    quickestPQ.push({ newQuickest, neighborIndex });
                }
            }
        }
    }

    // Backtrack to construct the paths
    vector<Edge> shortestPathEdges;
    vector<Edge> quickestPathEdges;
    int currentShortest = finishIndex;
    int currentQuickest = finishIndex;

    while (currentShortest != -1) {
        int predIndex = shortestPredecessors[currentShortest];
        if (predIndex != -1) {
            for (const Edge& edge : adjList[currentShortest].edges) {
                if (edge.to == adjList[predIndex].from) {
                    shortestPathEdges.push_back(edge);
                    break;
                }
            }
        }
        currentShortest = predIndex;
    }
    reverse(shortestPathEdges.begin(), shortestPathEdges.end());

    while (currentQuickest != -1) {
        int predIndex = quickestPredecessors[currentQuickest];
        if (predIndex != -1) {
            for (const Edge& edge : adjList[currentQuickest].edges) {
                if (edge.to == adjList[predIndex].from) {
                    quickestPathEdges.push_back(edge);
                    break;
                }
            }
        }
        currentQuickest = predIndex;
    }
    reverse(quickestPathEdges.begin(), quickestPathEdges.end());

    // Print the shortest and quickest paths, respectively
    
    // 1. Shortest path
    cout << endl << "Shortest path:" << endl;
    cout << "From " << start << endl;
    float shortestTotalDistance = 0;
    for (size_t i = 0; i < shortestPathEdges.size(); ++i) {
        if (i > 0) {
            cout << endl;
        }
        cout << "Take " << shortestPathEdges[i].streetName << ". Distance: " << shortestPathEdges[i].distance << " miles";
        shortestTotalDistance += shortestPathEdges[i].distance;
    }
    cout << endl << "Arrive at " << finish << endl;
    cout << "Total distance (shortest path): " << shortestTotalDistance << " miles" << endl << endl;

    // 2. Quickest path
    cout << "Quickest path:" << endl;
    cout << "From " << start << endl;
    float quickestTotalTime = 0;
    for (size_t i = 0; i < quickestPathEdges.size(); ++i) {
        if (i > 0) {
            cout << endl;
        }
        float timeInHours = quickestPathEdges[i].distance / quickestPathEdges[i].speed;
        float timeInMinutes = timeInHours * 60; // Convert hours to minutes
        cout << "Take " << quickestPathEdges[i].streetName << ". Time: " << timeInMinutes << " minutes";
        quickestTotalTime += timeInMinutes;
    }
    cout << endl;

    cout << "Arrive at " << finish << endl;
    cout << "Total time (quickest path): " << quickestTotalTime << " minutes" << endl;
}

// Error checker to ensure that start and finish points are valid vertices inside the adjacency list
bool Graph::isValidPoint(const string& point) 
{
    for (const Vertex& vertex : adjList)
    {
        if (vertex.from == point)
        {
            return true; // Valid point
        }
    }
    return false; // Invalid point
}

// Private method that uses binary search to find corresponding vertex
int Graph::getVertexIndex(const string& startingVertexNode, int low, int high)
{
    if (low > high) {
        return -1; // Vertex not found. Return -1 to addEdge() method
    }

    int mid = (low + high) / 2;

    if (adjList[mid].from == startingVertexNode) {
        return mid; // Vertex found at index mid
    }
    else if (adjList[mid].from < startingVertexNode) {
        return getVertexIndex(startingVertexNode, mid + 1, high);
    }
    else {
        return getVertexIndex(startingVertexNode, low, mid - 1);
    }
}

// // Helper for private getVertexIndex method
int Graph::getVertexIndex(const string& startingVertexNode)
{
    return getVertexIndex(startingVertexNode, 0, adjList.size());
}

// Method to reopen .csv, parse edge data, and push that data to adjacency list vector
void Graph::addEdge()
{
    // Name of data file
    ifstream file("data.csv");

    // Check if file exists
    if (!file) {
        cout << "File could not be opened." << endl;
        return;
    }
    else {
        string line;

        while (getline(file, line)) { // Loop as long as a line in the file can be read or until we reach EOF

            stringstream ss(line); // Use stringstream to parse the line using ',' as the delimiter

            string currentFrom, currentTo, currentStreet, currentDirection;
            float currentDistance = 0, currentSpeed = 0;

            // Read the first column (starting vertex)
            getline(ss, currentFrom, ',');

            // Read the second column (edge name)
            getline(ss, currentStreet, ',');

            // Read the third column (ending vertex)
            getline(ss, currentTo, ',');

            // Read the fourth column (direction)
            getline(ss, currentDirection, ',');

            // get float datatypes for distance and speed
            ss >> currentDistance;
            ss.ignore();  // Ignore comma in data.csv
            ss >> currentSpeed;

            Edge newEdge; // Creating object newEdge of type Edge

            // As loop iterates, data will be read and placed in the corresponding members of struct Edge
            newEdge.to = currentTo;
            newEdge.streetName = currentStreet;
            newEdge.direction = currentDirection;
            newEdge.distance = currentDistance;
            newEdge.speed = currentSpeed;
            int vertexIndex = getVertexIndex(currentFrom); // use currentFrom as starting vertex

            // If vertex is found
            if (vertexIndex != -1) {
                // Pushing data to edges vector
                adjList[vertexIndex].edges.push_back(newEdge);
            }
            else {
                // If vertex is not found
                cout << "Vertex " << currentFrom << " not found in adjList." << endl;
            }
        }

        file.close(); // Close the file after reading
    }
}

// Method to create vertex nodes using a vector array that has been sorted with no duplicate elements
void Graph::setVertex(vector <string>& initialPoints)
{
    Vertex newVertex;

    // Pushing vertex data in initialPoints vector to adjacency list vector
    for (int i = 0; i < initialPoints.size(); i++) {
        newVertex.from = initialPoints[i];
        adjList.push_back(newVertex);
    }
}

// Function to print data inside adjacency list (for testing/troubleshooting)
void Graph::printAdjacencyList()
{
    cout << "Adjacency List:" << endl;
    for (const Vertex& vertex : adjList)
    {
        cout << "Vertex " << vertex.from << ":" << endl;
        for (const Edge& edge : vertex.edges)
        {
            cout << "  To: " << edge.to << ", Street: " << edge.streetName
                << ", Direction: " << edge.direction
                << ", Distance: " << edge.distance << ", Speed: " << edge.speed << endl;
        }
        cout << endl;
    }
}