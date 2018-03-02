#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

static int squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225 };
#define n_squares 14
static void printGraph(vector<vector<bool>> &G);
static void printSolution(vector<size_t>& solution);
static void enlargeConnectionGraph(vector<vector<bool>>& G);
static void addConnections(vector<vector<bool>>& G);
static void findHamiltonianPath(vector<vector<bool>>& G);
static void extendHamiltonianPath(vector<vector<bool>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);

int main()
{
	cout << "hello world" << endl;
	vector<vector<bool>> G;
	static int LAST(100);
	for (int i = 1; i <= LAST; ++i) {
		cout << "graph size: " << i << endl;
		enlargeConnectionGraph(G);
		//printGraph(G);
		findHamiltonianPath(G);
	}
	std::cin.ignore();
	return 0;
}

void printGraph(vector<vector<bool>> &G) {
	const size_t size = G.size();
	for (size_t i = 0; i < size; ++i) {
		cout << "[ ";
		for (size_t j = 0; j < size; ++j) {
			if (G[i][j]) {
				cout << "1 ";
			}
			else {
				cout << "0 ";
			}
		}
		cout << "]" << endl;
	}
}

void printSolution(vector<size_t>& solution) {
	cout << "solution: [ ";
	for (size_t i = 0; i < solution.size(); ++i) {
		cout << solution[i] << " ";
	}
	cout << "]" << endl;
}

void enlargeConnectionGraph(vector<vector<bool>>& G) {
	const size_t size = G.size();
	for (size_t i = 0; i < size; ++i) {
		G[i].push_back(false);
	}
	vector<bool> new_row;
	for (size_t i = 0; i < size + 1; ++i) {
		new_row.push_back(false);
	}
	G.push_back(new_row);
	addConnections(G);
}

void addConnections(vector<vector<bool>>& G) {
	const size_t size = G.size();
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = 0; j < n_squares; ++j) {
			if (i + size == squares[j]) {
				G[i - 1][size - 1] = true;
				G[size - 1][i - 1] = true;
			}
		}
	}
}

void findHamiltonianPath(vector<vector<bool>>& G) {
	const size_t size = G.size();
	vector<bool> visited;
	vector<size_t> partial_solution;
	for (size_t i = 0; i < size; ++i) {
		visited.push_back(false);
	}
	bool found_solution(false);
	for (size_t i = 0; i < size && !found_solution; ++i) {
		visited[i] = true;
		partial_solution.push_back(i+1);
		extendHamiltonianPath(G, visited, partial_solution, found_solution);
		partial_solution.pop_back();
		visited[i] = false;
	}
}

void extendHamiltonianPath(vector<vector<bool>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
	if (found_solution) {
		return;
	}
	const size_t size = visited.size();
	const size_t last_visited = partial_solution[partial_solution.size() - 1] - 1;
	if (partial_solution.size() == size) {
		found_solution = true;
		printSolution(partial_solution);
	}
	else {
		for (size_t i = 0; i < size; ++i) {
			if (!visited[i] && G[last_visited][i]) {
				visited[i] = true;
				partial_solution.push_back(i + 1);
				extendHamiltonianPath(G, visited, partial_solution, found_solution);
				partial_solution.pop_back();
				visited[i] = false;
			}
		}
	}
}