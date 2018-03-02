#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>
#include <limits>

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
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361 };
//#define n_squares 18
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400 };
//#define n_squares 19
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441 };
//#define n_squares 20
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484 };
//#define n_squares 21
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529 };
//#define n_squares 22
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576 };
//#define n_squares 23
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625 };
//#define n_squares 24
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676 };
//#define n_squares 25
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729 };
//#define n_squares 26
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784 };
//#define n_squares 27
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841 };
//#define n_squares 28
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900 };
//#define n_squares 29
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961 };
//#define n_squares 30
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024 };
//#define n_squares 31
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089 };
//#define n_squares 32
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156 };
//#define n_squares 33
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225 };
//#define n_squares 34
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296 };
//#define n_squares 35
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369 };
//#define n_squares 36
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444 };
//#define n_squares 37
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521 };
//#define n_squares 38
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600 };
//#define n_squares 39
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681 };
//#define n_squares 40
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764 };
//#define n_squares 41
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849 };
//#define n_squares 42
//static size_t square[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936 };
//#define n_squares 43
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025 };
//#define n_squares 44
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116 };
//#define n_squares 45
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209 };
//#define n_squares 46
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304 };
//#define n_squares 47
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401 };
//#define n_squares 48
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500 };
//#define n_squares 49
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601 };
//#define n_squares 50
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704 };
//#define n_squares 51
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809 };
//#define n_squares 52
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916 };
//#define n_squares 53
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025 };
//#define n_squares 54
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136 };
//#define n_squares 55
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249 };
//#define n_squares 56
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364 };
//#define n_squares 57
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481 };
//#define n_squares 58
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600 };
//#define n_squares 59
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721 };
//#define n_squares 60
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844 };
//#define n_squares 61
//static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969 };
//#define n_squares 62
static size_t squares[] = { 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400, 441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025, 3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969, 4096 };
#define n_squares 63

void square_solver(const size_t thread, size_t* next_size, const time_t t_s);
static string printSolution(const vector<size_t>& solution);
static void enlargeConnectionGraph(vector<vector<size_t>>& G);
static void addConnections(vector<vector<size_t>>& G);
static string findHamiltonianPath(const vector<vector<size_t>>& G);
static void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution);

#define LAST 2000

void square_solver(const size_t thread, size_t* next_size, const time_t t_s) {
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
	}
	buffer << "end of thread " << thread << endl;
	cout << buffer.str();
}

int main()
{
	size_t next(1);
	static const size_t THREADS(1);
	time_t t_s;
	time(&t_s);

	vector<thread> threads;
	this_thread::sleep_for(chrono::milliseconds(1000));
	for (size_t i = 0; i < THREADS; ++i) {
		threads.push_back(thread(square_solver, i, &next, t_s));
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
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = 0; j < n_squares; ++j) {
			if (i + size == squares[j]) {
				G[i - 1].push_back(size - 1);
				G[size - 1].push_back(i - 1);
			}
		}
	}
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
		//return printSolution(partial_solution);
		return "";
	}
	partial_solution.pop_back();
	visited[vertex] = false;

	for (size_t i = 0; (i < size) && (i != vertex) && (!found_solution); ++i) {
		visited[i] = true;
		partial_solution.push_back(i);
		extendHamiltonianPath(G, visited, partial_solution, found_solution);
		if (found_solution) {
			break;
		}
		partial_solution.pop_back();
		visited[i] = false;
	}

	if (found_solution) {
		//return printSolution(partial_solution);
		return "";
	}
	else {
		return "no solutions";
	}
}

void extendHamiltonianPath(const vector<vector<size_t>>& G, vector<bool>& visited, vector<size_t>& partial_solution, bool& found_solution) {
	if (found_solution) {
		return;
	}

	if (partial_solution.size() == visited.size()) {
		found_solution = true;
	}
	else {
		const size_t last_visited = partial_solution[partial_solution.size() - 1];

		size_t vertex(numeric_limits<size_t>::max());
		size_t leastNeighbors(numeric_limits<size_t>::max());
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
				if (unvisited_neighbors < leastNeighbors) {
					vertex = current_neighbor;
					leastNeighbors = unvisited_neighbors;
				}
			}
		}
		if (neighbors_with_one_unvisited_neighbors > 2) {
			return;
		}
		if (neighbors_with_one_unvisited_neighbors == 1) {
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

		if (leastNeighbors != numeric_limits<size_t>::max()) {
			visited[vertex] = true;
			partial_solution.push_back(vertex);
			extendHamiltonianPath(G, visited, partial_solution, found_solution);
			if (found_solution) {
				return;
			}
			partial_solution.pop_back();
			visited[vertex] = false;
		}

		for (size_t i = 0; i < G[last_visited].size() && i != vertex; ++i) {
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