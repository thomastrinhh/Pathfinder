# Shortest and Quickest Path Finder

This program implements a graph-based algorithm to find the shortest and quickest paths between intersections. It uses Dijkstra's algorithm to find these paths.

## Description

This project was created as the final project for a Data Structures and Algorithms course (COP 3530). It defines a `Graph` class that contains methods to read data from a CSV file, create an adjacency list of intersections, and find the shortest and quickest paths between intersections using Dijkstra's algorithm. The program supports finding paths based on both distance and time.

## Features

- Read intersection data from a CSV file.
- Create an adjacency list of intersections.
- Find the shortest path between intersections based on distance.
- Find the quickest path between intersections based on time (distance and speed).

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/shortest-quickest-path.git
   cd shortest-quickest-path
   ```

2. Compile the code using a C++ compiler:

   ```bash
   g++ -o pathfinder main.cpp graph.cpp
   ```

## Usage

Run the compiled executable to use the program:

```bash
./pathfinder
```

Follow the prompts to enter the starting and ending intersections. The program will then display the shortest and quickest paths between the specified intersections.
