//=====================================================================================
// File: main.cpp
// Author: Thomas Trinh
// Purpose: Location of sorting functions, .csv reading/parsing functions, and main().
//=====================================================================================

#include "graph.h"

//===================================================================
// Function to keep unique elements and remove duplicates in vector.
//===================================================================

void removeDuplicates(std::vector<std::string>& initialPoints)
{
	int i = 1;
	while (i < initialPoints.size()) {
		if (initialPoints[i] == initialPoints[i - 1]) {
			initialPoints.erase(initialPoints.begin() + i);
		}
		else {
			i++;
		}
	}
}

//================================================
// Quick sort algorithm to sort initial vertices.
//================================================

int partition(vector <string>& initialPoints, int start, int end)
{
	// Using last index as pivot point
	string pivot = initialPoints[end];

	int i = start;

	for (int j = start; j < end; j++) {
		if (initialPoints[j] <= pivot) {
			swap(initialPoints[i], initialPoints[j]);
			i++;
		}
	}

	swap(initialPoints[i], initialPoints[end]);
	return i;
}

void quickSort(vector <string>& initialPoints, int start, int end)
{
	int par;

	if (start < end) {

		// Partitioning the vector array
		par = partition(initialPoints, start, end);

		// Sorting left side
		quickSort(initialPoints, start, par - 1);

		// Sorting right side
		quickSort(initialPoints, par + 1, end);
	}
}

//==========================================
// Function to read and parse through data.
//==========================================

vector <string> readData(vector <string>& initialPoints)
{
	// Name of data file
	ifstream file("data.csv");

	// Check if file exists, if not return to main 
	if (!file)
	{
		cout << "File could not be opened." << endl;
		return initialPoints;
	}
	else
	{
		string initialPointsNames; // Variable to store inputs while parsing .csv
		stringstream ss(initialPointsNames); // Stringstream used for breaking strings by delimiter

		// Loop until EOF
		while (!file.eof())
		{
			if (getline(file, initialPointsNames, ',')) // If getline() approaches delimiter
			{
				// NOTE: Syntax of getline() = getline(name_of_file, variable_to_store_input, delimiter)
				initialPoints.push_back(initialPointsNames); // Begin appending initialPointsNames to vector
				getline(file, initialPointsNames); // Increment to next row in .csv 
			}
		}
	}
	file.close();
	return(initialPoints);
}

//============================================================================
// Function to print data inside initialPoints (for testing/troubleshooting).
//============================================================================

void printVector(vector <string>& initialPoints) {
	for (int i = 0; i < initialPoints.size(); i++) {
		cout << i << "." << initialPoints[i] << endl;
	}
	cout << "Current size of vector array: " << initialPoints.size() << endl;
}

//==============
// Driver code.
//==============

int main()
{
	// Initializing a vector array of strings to store starting intersections and their corresponding edges
	vector <string> initialPoints;
	vector <string> edges;

	// Read and parse data into vector array
	readData(initialPoints); 
	// Sort vector array using quick sort algorithm
	quickSort(initialPoints, 0, initialPoints.size() - 1); 

	// Remove duplicates and only store unique elements in vector array
	removeDuplicates(initialPoints);

	// Initializing object of class Graph
	Graph myGraph;

	// Passing object to setVertex method with vector array of initial points
	myGraph.setVertex(initialPoints);

	// Now that the adjacency list is populated with initial points (intersections), let's find the corresponding edges
	myGraph.addEdge();

	string start;
	string finish;

	cout << "Enter starting point: ";
	cin >> start;

	// Check if starting point is inside the adjacency list
	if (!myGraph.isValidPoint(start))
	{
		cout << "Invalid starting point." << endl;
		return 1; // Exit
	}

	cout << "Enter ending point: ";
	cin >> finish;

	// Check if end point is inside the adjacency list
	if (!myGraph.isValidPoint(finish))
	{
		cout << "Invalid ending point." << endl;
		return 1; // Exit
	}

	myGraph.findPaths(start, finish);

	return 0;
}