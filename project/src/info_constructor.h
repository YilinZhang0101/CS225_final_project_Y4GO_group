#pragma once
#include <string>
#include <vector>
#include "math.h"
#include <utility>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <stdlib.h>

#define pi 3.1415926535897932384626433832795
#define EARTH_RAD 6378.137 // unit: km

// struct for storing airports
struct airport_s
{
	std::string airport_name_;
	std::string city_;
	std::string airport_country_;
	std::string airport_IATA_;
	std::string airport_ICAO_;
	double latitude_;
	double longtitude_;
	double altitude_;
};

// struct for storing routes
struct route_s
{
	std::string airline_;
	std::string src_code_;
	std::string dest_code_;
};

// struct for storing airlines
struct airline_s
{
	std::string airline_name_;
	std::string airline_IATA_;
	std::string airline_ICAO_;
	std::string airline_country_;
	std::string active_;
};

class info_container
{
public:
	info_container(std::string airports, std::string routes, std::string airlines);

	std::vector<std::string> generate_vertices();
	std::vector<std::pair<std::string, std::string>> generate_edges();
	std::vector<double> calculate_dist();

	void read();
	void clean();

	std::vector<std::string> airlineinfo(const std::vector<std::string> &route);
	std::vector<std::string> vertices;
	std::vector<std::pair<std::string, std::string>> route_pair;

private:
	bool valid_data = true;
	std::string airports_;
	std::string routes_;
	std::string airlines_;

	std::vector<std::string> AirportName;
	std::vector<std::string> AirportCode;
	std::vector<std::pair<std::string, std::string>> allRoute;

	std::vector<airport_s> airports_s;
	std::vector<route_s> routes_s;
	std::vector<airline_s> airlines_s;

	std::unordered_map<std::string, airport_s> code_airport;
	std::unordered_map<std::string, airport_s> name_airport;
	std::unordered_map<std::string, std::string> pair_route;
	std::unordered_map<std::string, airline_s> code_airline;

	void cleanAirport();
	void cleanRoute();
	void cleanAirline();

	std::string TrimRight(const std::string &str);
	std::string TrimLeft(const std::string &str);
	std::string Trim(const std::string &str);
	std::string readfile(const std::string &filename);
	std::vector<std::vector<std::string>> transferFile(const std::string &filename);
	int divide(const std::string &line, char ch, std::vector<std::string> &temp);
	double cal_dist(double longitude1, double latitude1, double longitude2, double latitude2);
};