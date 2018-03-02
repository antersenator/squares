#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225 };
#define n_squares 14
void test_thread(const size_t thread, const size_t LAST, size_t* next_size);
void square_solver(const size_t thread, const size_t LAST, size_t* next_size, const time_t t_s);
static void printAdjacencyGraph(const vector<vector<size_t>> &G);
static void printSolution(const vector<size_t>& solution);
static void enlargeConnectionGraph(vector<vector<size_t>>& G);
static void addConnections(vector<vector<size_t>>& G);
static void findHamiltonianPath(const vector<vector<size_t>>& G);
static void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);
static const vector<size_t> removeVertex(vector<vector<size_t>>& G, const size_t v);
static void addVertex(vector<vector<size_t>>& G, const vector<size_t>& removed_row, const size_t removed_v);

void test_thread(const size_t thread, const size_t LAST, size_t* next_size) {
	cout << "test " << thread << " last " << LAST << endl;
}

void square_solver(const size_t thread, const size_t LAST, size_t* next_size, const time_t t_s) {
	vector<vector<size_t>> G;
	enlargeConnectionGraph(G);
	size_t previous_size(1);
	time_t t_e;
	while (*next_size <= LAST) {
		const size_t steps = *next_size - previous_size;
		previous_size = *next_size;
		++*next_size;
		for (size_t i = 0; i < steps; ++i) {
			enlargeConnectionGraph(G);
		}
		cout << "thread " << thread << " working size " << previous_size << endl;
		findHamiltonianPath(G);
		time(&t_e);
		cout << "thread " << thread << " completed size " << previous_size << " at time " << t_e - t_s << "s" << endl;
	}
}

int main()
{
	static const size_t THREADS(2);
	size_t next(1);
	static const size_t LAST(100);
	time_t t_s;
	time(&t_s);

	thread first(square_solver, 0, LAST, &next, t_s);
	this_thread::sleep_for(chrono::milliseconds(10000));
	thread second(square_solver, 1, LAST, &next, t_s);
	this_thread::sleep_for(chrono::milliseconds(1000));
	thread third(square_solver, 2, LAST, &next, t_s);
	this_thread::sleep_for(chrono::milliseconds(1000));
	thread fourth(square_solver, 3, LAST, &next, t_s);
	this_thread::sleep_for(chrono::milliseconds(1000));

	first.join();
	second.join();
	third.join();
	fourth.join();

	std::cin.ignore();
	return 0;
}

void printAdjacencyGraph(const vector<vector<size_t>>& G) {
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

void printSolution(const vector<size_t>& solution) {
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

void findHamiltonianPath(const vector<vector<size_t>>& G) {
	const size_t size = G.size();
	size_t degree_one_vertices(0);
	size_t first_degree_one_vertex(0);
	for (size_t i = 0; i < size; ++i) {
		if (G[i].size() == 1) {
			++degree_one_vertices;
			first_degree_one_vertex = i;
		}
	}

	if (degree_one_vertices > 2) {
		cout << "no solutions" << endl;
		return;
	}

	vector<bool> visited;
	for (size_t i = 0; i < size; ++i) {
		visited.push_back(false);
	}
	vector<size_t> partial_solution;
	bool found_solution(false);
	if (degree_one_vertices == 1) {
		cout << "exactly one degree 1 vertex" << endl;
		visited[first_degree_one_vertex] = true;
		partial_solution.push_back(first_degree_one_vertex);
		extendHamiltonianPath(G, visited, partial_solution, found_solution);
	}
	else {
		for (size_t i = 0; i < size && !found_solution; ++i) {
			visited[i] = true;
			partial_solution.push_back(i);
			extendHamiltonianPath(G, visited, partial_solution, found_solution);
			partial_solution.pop_back();
			visited[i] = false;
		}
	}

	if (!found_solution) {
		cout << "no solutions" << endl;
	}
}

void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
	//printAdjacencyGraph(G);

	if (found_solution) {
		return;
	}

	if (partial_solution.size() == visited.size()) {
		found_solution = true;
		printSolution(partial_solution);
	}
	else {
		const size_t last_visited = partial_solution[partial_solution.size() - 1];
		for (size_t i = 0; i < G[last_visited].size(); ++i) {
			const size_t next_visit = G[last_visited][i];
			if (!visited[next_visit]) {
				visited[next_visit] = true;
				//const vector<size_t> removed_row = removeVertex(G, last_visited);
				partial_solution.push_back(next_visit);
				extendHamiltonianPath(G, visited, partial_solution, found_solution);
				partial_solution.pop_back();
				//addVertex(G, removed_row, last_visited);
				visited[next_visit] = false;
			}
		}
	}
}

const vector<size_t> removeVertex(vector<vector<size_t>>& G, const size_t v) {
	for (size_t i = 0; i < G[v].size(); ++i) {
		const size_t v_eliminate = G[v][i];
		auto it = std::find(G[v_eliminate].begin(), G[v_eliminate].end(), v);
		G[v_eliminate].erase(it);
	}
	const vector<size_t> removed_row = G[v];
	const vector<size_t> empty_row;
	G[v] = empty_row;
	return removed_row;
}

void addVertex(vector<vector<size_t>>& G, const vector<size_t>& removed_row, const size_t removed_v) {
	for (size_t i = 0; i < removed_row.size(); ++i) {
		G[removed_row[i]].push_back(removed_v);
	}
	G[removed_v] = removed_row;
}