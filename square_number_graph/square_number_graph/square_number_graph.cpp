#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <limits>
//48 69 71
//works to 299
using namespace std;

//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196 };
//#define n_squares 13
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225 };
//#define n_squares 14
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256 };
//#define n_squares 15
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289 };
//#define n_squares 16
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324 };
//#define n_squares 17
static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361 };
#define n_squares 18
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400 };
//#define n_squares 19

void square_solver(const size_t thread, size_t* next_size, const time_t t_s);
//void square_solver(const size_t thread, const size_t LAST, size_t* next_size, const time_t t_s, const bool bw);
static string printSolution(const vector<size_t>& solution);
static void enlargeConnectionGraph(vector<vector<size_t>>& G);
static void addConnections(vector<vector<size_t>>& G);
static string findHamiltonianPath(const vector<vector<size_t>>& G);
//static string findHamiltonianPathBW(const vector<vector<size_t>>& G);
static void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);
//static void extendHamiltonianPathBW(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);

#define LAST 200

void square_solver(const size_t thread, size_t* next_size, const time_t t_s) {
//void square_solver(const size_t thread, const size_t LAST, size_t* next_size, const time_t t_s, const bool bw) {
	vector<vector<size_t>> G;
	enlargeConnectionGraph(G);
	size_t previous_size(1);
	time_t t_e;
	stringstream buffer;
	while (*next_size <= LAST) {
		const size_t steps = *next_size - previous_size;
		previous_size = *next_size;
		++*next_size;
		for (size_t i = 0; i < steps; ++i) {
			enlargeConnectionGraph(G);
		}
		buffer << "thread " << thread << " working size " << previous_size << endl;
		cout << buffer.str();
		stringstream clean_buffer_1;
		buffer.swap(clean_buffer_1);		
		buffer << findHamiltonianPath(G) << endl;
		time(&t_e);
		buffer << "thread " << thread << " completed size " << previous_size << " at time " << t_e - t_s << "s" << endl;
		cout << buffer.str() << endl;
		stringstream clean_buffer_2;
		buffer.swap(clean_buffer_2);
		//this_thread::sleep_for(chrono::milliseconds(3000));
	}
	buffer << "end of thread " << thread << endl;
	cout << buffer.str();
}

int main()
{
	size_t next(1);
	static const size_t THREADS(4);
	time_t t_s;
	time(&t_s);

	vector<thread> threads;
	this_thread::sleep_for(chrono::milliseconds(1000));
	for (size_t i = 0; i < THREADS; ++i) {
		threads.push_back(thread(square_solver, i, &next, t_s));
		//threads.push_back(thread(square_solver, i, LAST, &next, t_s, false));
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	for (size_t i = 0; i < THREADS; ++i) {
		threads[i].join();
	}

	cin.ignore();
	return 0;
}

string printSolution(const vector<size_t>& solution) {
	stringstream buffer;
	buffer << "solution: [ ";
	for (size_t i = 0; i < solution.size(); ++i) {
		buffer << solution[i] + 1 << " ";
	}
	buffer << "]";
	return buffer.str();
}

void enlargeConnectionGraph(vector<vector<size_t>>& G) {
	const size_t size = G.size();
	vector<size_t> new_row;
	G.push_back(new_row);
	addConnections(G);
}

void addConnections(vector<vector<size_t>>& G) {
	const size_t size = G.size();
	//cout << "size: " << size << endl;
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = 0; j < n_squares; ++j) {
			if (i + size == squares[j]) {
				G[i - 1].push_back(size - 1);
				G[size - 1].push_back(i - 1);
			}
		}
	}
	//for (size_t i = 1; i <= size; ++i) {
		//cout << i << " has " << G[i - 1].size() << " connections" << endl;
		//for (size_t j = 0; j < G[i - 1].size(); ++j) {
			//cout << "   connected to " << G[i - 1][j] + 1 << endl;
		//}
	//}
}

string findHamiltonianPath(const vector<vector<size_t>>& G) {
	const size_t size = G.size();
	size_t degree_one_vertices(0);
	size_t first_degree_one_vertex(0);
	for (size_t i = 0; i < size; ++i) {
		if (G[i].size() == 1) {
			++degree_one_vertices;
			first_degree_one_vertex = i;
		}
	}

	vector<bool> visited;
	for (size_t i = 0; i < size; ++i) {
		visited.push_back(false);
	}
	vector<size_t> partial_solution;
	bool found_solution(false);

	size_t vertex(0);
	size_t leastNeighbors(G[0].size());
	for (size_t i = 1; i < G.size(); ++i) {
		if (G[i].size() < leastNeighbors) {
			vertex = i;
			leastNeighbors = G[i].size();
		}
	}
	visited[vertex] = true;
	partial_solution.push_back(vertex);
	extendHamiltonianPath(G, visited, partial_solution, found_solution);
	if (found_solution) {
		return printSolution(partial_solution);
	}
	partial_solution.pop_back();
	visited[vertex] = false;

	for (size_t i = 0; (i < size) && (i != vertex) && (!found_solution); ++i) {
		visited[i] = true;
		partial_solution.push_back(i);
		//for (size_t k = 0; k < partial_solution.size(); ++k) {
			//cout << partial_solution[k] + 1 << endl;
		//}
		extendHamiltonianPath(G, visited, partial_solution, found_solution);
		if (found_solution) {
			//cout << "found solution" << endl;
			break;
		}
		partial_solution.pop_back();
		visited[i] = false;
	}

	if (found_solution) {
		//cout << "printing solution" << endl;
		return printSolution(partial_solution);
	}
	else {
		return "no solutions";
	}
}

//string findHamiltonianPathBW(const vector<vector<size_t>>& G) {
//	const size_t size = G.size();
//	size_t degree_one_vertices(0);
//	size_t first_degree_one_vertex(0);
//	for (size_t i = 0; i < size; ++i) {
//		if (G[i].size() == 1) {
//			++degree_one_vertices;
//			first_degree_one_vertex = i;
//		}
//	}
//
//	vector<bool> visited;
//	for (size_t i = 0; i < size; ++i) {
//		visited.push_back(false);
//	}
//	vector<size_t> partial_solution;
//	bool found_solution(false);
//
//	for (size_t i = size - 1; i < size && !found_solution; --i) {
//		visited[i] = true;
//		partial_solution.push_back(i);
//		extendHamiltonianPathBW(G, visited, partial_solution, found_solution);
//		partial_solution.pop_back();
//		visited[i] = false;
//	}
//
//	if (found_solution) {
//		return printSolution(partial_solution);
//	}
//	else {
//		return "no solutions";
//	}
//}

void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
	if (found_solution) {
		return;
	}

	//cout << partial_solution.size() << "   " << visited.size() << endl;
	if (partial_solution.size() == visited.size()) {
		found_solution = true;
	}
	else {
		const size_t last_visited = partial_solution[partial_solution.size() - 1];

		size_t neighbors_with_one_unvisited_neighbors(0);
		size_t neighbor;
		for (size_t i = 0; i < G[last_visited].size(); ++i) {
			const size_t current_neighbor = G[last_visited][i];
			if (!visited[current_neighbor]) {
				size_t unvisited_neighbors(0);
				for (size_t j = 0; j < G[current_neighbor].size(); ++j) {
					if (!visited[G[current_neighbor][j]]) {
						++unvisited_neighbors;
					}
				}
				if (unvisited_neighbors == 0) {
					visited[current_neighbor] = true;
					partial_solution.push_back(current_neighbor);
					extendHamiltonianPath(G, visited, partial_solution, found_solution);
					if (found_solution) {
						return;
					}
					partial_solution.pop_back();
					visited[current_neighbor] = false;
					return;
				}
				if (unvisited_neighbors == 1) {
					++neighbors_with_one_unvisited_neighbors;
					neighbor = current_neighbor;
				}
			}
		}
		if (neighbors_with_one_unvisited_neighbors > 2) {
			return;
		}
		if (neighbors_with_one_unvisited_neighbors > 0) {
			visited[neighbor] = true;
			partial_solution.push_back(neighbor);
			extendHamiltonianPath(G, visited, partial_solution, found_solution);
			if (found_solution) {
				return;
			}
			partial_solution.pop_back();
			visited[neighbor] = false;
			return;
		}

		for (size_t i = 0; i < G[last_visited].size(); ++i) {
			const size_t next_visit = G[last_visited][i];
			if (!visited[next_visit]) {
				visited[next_visit] = true;
				partial_solution.push_back(next_visit);
				extendHamiltonianPath(G, visited, partial_solution, found_solution);
				if (found_solution) {
					return;
				}
				partial_solution.pop_back();
				visited[next_visit] = false;
			}
		}
	}
}

//void extendHamiltonianPathBW(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
//	if (found_solution) {
//		return;
//	}
//
//	if (partial_solution.size() == visited.size()) {
//		found_solution = true;
//		printSolution(partial_solution);
//	}
//	else {
//		const size_t last_visited = partial_solution[partial_solution.size() - 1];
//		for (size_t i = G[last_visited].size() - 1; i < G[last_visited].size(); --i) {
//			const size_t next_visit = G[last_visited][i];
//			if (!visited[next_visit]) {
//				visited[next_visit] = true;
//				partial_solution.push_back(next_visit);
//				extendHamiltonianPath(G, visited, partial_solution, found_solution);
//				if (found_solution) {
//					return;
//				}
//				partial_solution.pop_back();
//				visited[next_visit] = false;
//			}
//		}
//	}
//}