#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "info_constructor.h"

using namespace std;

TEST_CASE("try read correct airports and routes and airlines", "[weight=0][part=1]")
{
    info_container information("../tests/information_test_airports_correct.txt", "../tests/information_test_routes_correct.txt", "../tests/information_test_airlines_correct.txt");
    information.read();
    information.clean();
    vector<string> airports = information.generate_vertices();
    vector<pair<string, string>> routes = information.generate_edges();
    vector<string> test_routes = {"\"Goroka Airport\"", "\"Madang Airport\"", "\"Mount Hagen Kagamuga Airport\""};
    vector<string> airlines = information.airlineinfo(test_routes);

    REQUIRE(airports.size() == 5);
    REQUIRE(airports[0] == "\"Goroka Airport\"");
    REQUIRE(airports[1] == "\"Madang Airport\"");
    REQUIRE(airports[2] == "\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(airports[3] == "\"Nadzab Airport\"");
    REQUIRE(airports[4] == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes.size() == 4);
    REQUIRE(routes[0].first == "\"Goroka Airport\"");
    REQUIRE(routes[0].second == "\"Madang Airport\"");
    REQUIRE(routes[1].first == "\"Madang Airport\"");
    REQUIRE(routes[1].second == "\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(routes[2].first == "\"Nadzab Airport\"");
    REQUIRE(routes[2].second == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes[3].first == "\"Goroka Airport\"");
    REQUIRE(routes[3].second == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(airlines.size() == 2);
    REQUIRE(airlines[0] == "\"Ansett Australia\"(\"Australia\") ");
    REQUIRE(airlines[1] == "\"40-Mile Air\"(\"United States\") ");
}

TEST_CASE("try read correct airports and routes, some airports and routes need to be delete", "[weight=0][part=1]")
{

    info_container information("../tests/information_test_airports_uncorrect.txt", "../tests/information_test_routes_uncorrect.txt", "../tests/information_test_airlines_uncorrect.txt");
    information.read();
    information.clean();
    vector<string> airports = information.generate_vertices();
    vector<pair<string, string>> routes = information.generate_edges();
    vector<string> test_routes = {"\"Goroka Airport\"", "\"Madang Airport\"", "\"Mount Hagen Kagamuga Airport\""};
    vector<string> airlines = information.airlineinfo(test_routes);
    REQUIRE(airports.size() == 5);
    REQUIRE(airports[0] == "\"Goroka Airport\"");
    REQUIRE(airports[1] == "\"Madang Airport\"");
    REQUIRE(airports[2] == "\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(airports[3] == "\"Nadzab Airport\"");
    REQUIRE(airports[4] == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes.size() == 4);
    REQUIRE(routes[0].first == "\"Goroka Airport\"");
    REQUIRE(routes[0].second == "\"Madang Airport\"");
    REQUIRE(routes[1].first == "\"Madang Airport\"");
    REQUIRE(routes[1].second == "\"Mount Hagen Kagamuga Airport\"");
    REQUIRE(routes[2].first == "\"Nadzab Airport\"");
    REQUIRE(routes[2].second == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(routes[3].first == "\"Goroka Airport\"");
    REQUIRE(routes[3].second == "\"Port Moresby Jacksons International Airport\"");
    REQUIRE(airlines.size() == 2);
    REQUIRE(airlines[0] == "\"Ansett Australia\"(\"Australia\") ");
    REQUIRE(airlines[1] == "\"40-Mile Air\"(\"United States\") ");
}
