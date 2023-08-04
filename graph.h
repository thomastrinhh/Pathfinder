//========================================================================
// File: graph.h
// Author: Thomas Trinh
// Purpose: Location of struct initialization and declaration of methods.
//========================================================================

#ifndef graph_h
#define graph_h

#include <iostream>
#include <vector>
#include <fstream> // For file manipulation
#include <sstream> // For string manipulation
#include <set> // For removal of duplicate elements
#include <queue> // For priority queue implementation to store vertices, edges, and other related data for Dijkstra's algorithm

using namespace std;

class Graph 
{
	struct Edge
	{
		string to; // End point (ending intersection)
		string streetName; // Name of roads (or edges)
		string direction; // Direction that corresponds to the road that leads to the ending intersection

		float distance = 0.0; // Distance of each road (edge weight)
		float speed = 0.0; // Speed limits 
	};

	struct Vertex
	{
		string from; // End point (beginning intersection)
		vector <Edge> edges; // Store edge data
	};

	vector <Vertex> adjList; // Store vertex data

	int getVertexIndex(const string& vertexName, int low, int high); // Private method to find the vertex that corresponds to each edge data (getter function)

public:
	void findPaths(string start, string finish); // Use Dijkstra's algorithm to find both the shortest and the quickest paths
	bool isValidPoint(const string& point); // Verify that valid inputs were entered for starting and ending vertices before finding shortest/quickest path
	int getVertexIndex(const string& vertexName); // Helper method for private getVertexIndex method (setter function)
	void printAdjacencyList(); // Print the adjacency list (for testing/troubleshooting)
	void addEdge(); // Add the edges and other related data to their corresponding vertices
	void setVertex(vector <string>& initialPoints); // Create vertex nodes from the vector of initial intersection names (with removed duplicates)

};

#endif