#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

static int squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225 };
#define n_squares 14
static void printAdjacencyGraph(vector<vector<size_t>> &G);
static void printSolution(vector<size_t>& solution);
static void enlargeConnectionGraph(vector<vector<size_t>>& G);
static void addConnections(vector<vector<size_t>>& G);
static void findHamiltonianPath(vector<vector<size_t>>& G);
static void extendHamiltonianPath(vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);

int main()
{
	cout << "hello world" << endl;
	vector<vector<size_t>> G;
	static int LAST(100);
	for (int i = 1; i <= LAST; ++i) {
		cout << "graph size: " << i << endl;
		enlargeConnectionGraph(G);
		//printAdjacencyGraph(G);
		findHamiltonianPath(G);
	}
	std::cin.ignore();
	return 0;
}

void printAdjacencyGraph(vector<vector<size_t>>& G) {
	const size_t G_size = G.size();
	for (size_t i = 0; i < G_size; ++i) {
		cout << "vertex " << i + 1 << ": [ ";
		const size_t row_size = G[i].size();
		for (size_t j = 0; j < row_size; ++j) {
			cout << G[i][j] + 1 << " ";
		}
		cout << "]" << endl;
	}
}

void printSolution(vector<size_t>& solution) {
	cout << "solution: [ ";
	for (size_t i = 0; i < solution.size(); ++i) {
		cout << solution[i] + 1 << " ";
	}
	cout << "]" << endl;
}

void enlargeConnectionGraph(vector<vector<size_t>>& G) {
	const size_t size = G.size();
	vector<size_t> new_row;
	G.push_back(new_row);
	addConnections(G);
}

void addConnections(vector<vector<size_t>>& G) {
	const size_t size = G.size();
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = 0; j < n_squares; ++j) {
			if (i + size == squares[j]) {
				G[i - 1].push_back(size - 1);
				G[size - 1].push_back(i - 1);
			}
		}
	}
}

void findHamiltonianPath(vector<vector<size_t>>& G) {
	const size_t size = G.size();
	vector<bool> visited;
	vector<size_t> partial_solution;
	for (size_t i = 0; i < size; ++i) {
		visited.push_back(false);
	}
	bool found_solution(false);
	for (size_t i = 0; i < size && !found_solution; ++i) {
		visited[i] = true;
		partial_solution.push_back(i);
		extendHamiltonianPath(G, visited, partial_solution, found_solution);
		partial_solution.pop_back();
		visited[i] = false;
	}
}

void extendHamiltonianPath(vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
	//printSolution(partial_solution);

	if (found_solution) {
		return;
	}

	const size_t size = visited.size();
	if (partial_solution.size() == size) {
		found_solution = true;
		printSolution(partial_solution);
	}
	else {
		const size_t last_visited = partial_solution[partial_solution.size() - 1];

		const vector<size_t> last_visited_adjacency_list = G[last_visited];
		const size_t last_visited_adjacency_list_size = last_visited_adjacency_list.size();
		for (size_t i = 0; i < last_visited_adjacency_list_size; ++i) {
			const size_t next_visit = last_visited_adjacency_list[i];
			if (!visited[next_visit]) {
				visited[next_visit] = true;
				partial_solution.push_back(next_visit);
				extendHamiltonianPath(G, visited, partial_solution, found_solution);
				partial_solution.pop_back();
				visited[next_visit] = false;
			}
		}
	}
}