#pragma once
// graph constructer
// vector of string: vertices
// vector of double: edges weights
// vector of string: edges
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "../lib/cs225/graph.h"
class graph_container
{
public:
	graph_container(std::vector<std::string> &vertices, std::vector<std::pair<std::string, std::string>> &edges, std::vector<double> &distances);
	graph_container(std::vector<std::string> &vertices, std::vector<std::pair<std::string, std::string>> &edges);

	graph_container();

	std::vector<Vertex> solvebyBFS(Vertex start, Vertex end);
	std::vector<Vertex> solvebyDij(Vertex start, Vertex end);
	std::vector<Vertex> solvebyDeltaStepping(Vertex start, Vertex end);
	
private:
	Graph inner;
	double maxWeight = 0;
	double maxDegree = 0;

	unsigned curr = 0;
	unsigned bucketSize = 0;
	unsigned afterDeleteSize = 0;
	std::vector<Vertex> airports;

	std::unordered_map<Vertex, double> dist;
	std::unordered_map<Vertex, Vertex> prev;
	std::unordered_map<int, std::vector<Vertex>> bucket;
	
	double delta = 3.0;

	std::vector<std::pair<Vertex, std::pair<Vertex, double>>> findRoutes(vector<Vertex> newBucket, string kind);
	void extends(std::vector<std::pair<Vertex, std::pair<Vertex, double>>> all_extend);
	void extend(Vertex nowV, double changed_length, Vertex p);	
};