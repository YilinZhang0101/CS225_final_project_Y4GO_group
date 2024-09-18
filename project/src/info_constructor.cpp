#include "info_constructor.h"

/*
    distance of edges in graph calculator
    input: nothing
    output: vector of double type distances corresponding to the vector storing routes
    calculate distance of current foutes using longtitude and latitude data stored
*/
std::vector<double> info_container::calculate_dist()
{
    std::vector<double> calculated_dists;
    for (unsigned i = 0; i < routes_s.size(); i++)
    {
        auto departure = code_airport.find(routes_s[i].src_code_);
        auto arrival = code_airport.find(routes_s[i].dest_code_);
        calculated_dists.push_back(cal_dist(departure->second.longtitude_, departure->second.latitude_,
                                            arrival->second.longtitude_, arrival->second.latitude_));
    }
    return calculated_dists;
}

/*
    airport in graph getter
    input: nothing
    output: return vector of vertices of current graph
*/
std::vector<std::string> info_container::generate_vertices()
{
    return vertices;
}

/*
    input: nothing
    output: return vector of pair (edges of current graph) which first is the departure vertex, second is the arrival vertex
    return vector of pair (edges of current graph) which first is the departure vertex, second is the arrival vertex
*/
std::vector<std::pair<std::string, std::string>> info_container::generate_edges()
{
    return route_pair;
}

/*
    airline information getter
    input: a vector of vertices which order is the order of airports visited
    output: return vector of strings of available airline information of routes
    the airline information string is stored as a string of airline codes sepered by a comma, need to seperate and than find corresponding airline data
*/
std::vector<std::string> info_container::airlineinfo(const std::vector<std::string> &route)
{
    std::vector<std::string> result;
    if (route[0] == "Destination not reachable!")
        return result;

    for (unsigned idx = 1; idx < route.size(); idx++)
    {
        std::string source_code = name_airport.find(route[idx - 1])->second.airport_IATA_;
        if (source_code == "")
        {
            source_code = name_airport.find(route[idx - 1])->second.airport_ICAO_;
        }
        std::string dest_code = name_airport.find(route[idx])->second.airport_IATA_;
        if (dest_code == "")
        {
            dest_code = name_airport.find(route[idx])->second.airport_ICAO_;
        }
        auto it = pair_route.find(source_code + "-" + dest_code);
        if (it == pair_route.end())
        {
            result.clear();
            result.push_back("no recorded airline, but route is available.");
            break;
        }
        std::string airline_codes = it->second;
        std::vector<std::string> airline_codes_vector;
        divide(airline_codes, ',', airline_codes_vector);
        std::string airline_names = "";
        for (auto it = airline_codes_vector.begin(); it != airline_codes_vector.end(); ++it)
        {
            airline_names += code_airline.find(*it)->second.airline_name_ + "(" + code_airline.find(*it)->second.airline_country_ + "),";
        }
        airline_names[airline_names.length() - 1] = ' ';
        result.push_back(airline_names);
    }
    return result;
}

/*
    information container constructor
    input: path of data files
    output: nothing
    initializes maps needed and store path of files
*/
info_container::info_container(std::string airports, std::string routes, std::string airlines)
    : code_airport(std::unordered_map<std::string, airport_s>()), name_airport(std::unordered_map<std::string, airport_s>()),
      pair_route(std::unordered_map<std::string, std::string>()),
      code_airline(std::unordered_map<std::string, airline_s>())
{
    airports_ = airports;
    routes_ = routes;
    airlines_ = airlines;
}

/*
    data cleaner
    input: nothing
    output: nothing
    clean all of current data by using helper functions
*/
void info_container::clean()
{
    cleanAirport();
    cleanAirline();
    cleanRoute();
    return;
}

/*
    airport data cleaner&airport map constructor
    input: nothing
    output: nothing
    clean airport datas, exclude data entries of following type:
        1. airport name is empty
        2. all airport codes are empty
        3. airport name is "Airbase" or "Air Base"
        4. airport codes are not at correct length
        5. airports that are at impossible longitudes or latitudes or altitudes
        6. all airport codes are \N
    construct airport maps, one using airport name as key and airport struct as value,
    another using airport code as key and airport struct as value. (3-length code is preferred)

*/
void info_container::cleanAirport()
{
    std::vector<int> erase_or_not;
    std::vector<airport_s> new_airports;
    erase_or_not.resize(airports_s.size(), 1);
    for (unsigned idx = 0; idx < airports_s.size(); idx++)
    {
        if (airports_s[idx].airport_name_ == "" ||
            (airports_s[idx].airport_IATA_ == "" && airports_s[idx].airport_ICAO_ == ""))
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].airport_name_.find("Airbase") != std::string::npos)
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].airport_name_.find("Air Base") != std::string::npos)
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].airport_IATA_.length() != 5)
        {
            airports_s[idx].airport_IATA_ = "\\N";
            if (airports_s[idx].airport_ICAO_.length() != 6)
            {
                erase_or_not[idx] = -1;
            }
        }
        else if (airports_s[idx].airport_IATA_ == "\\N" && airports_s[idx].airport_ICAO_ == "\\N")
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].longtitude_ > 180 || airports_s[idx].longtitude_ < -180)
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].latitude_ > 90 || airports_s[idx].latitude_ < -90)
        {
            erase_or_not[idx] = -1;
        }
        else if (airports_s[idx].altitude_ > 5500 || airports_s[idx].altitude_ < -500)
        {
            erase_or_not[idx] = -1;
        }
    }
    for (unsigned idx = 0; idx < airports_s.size(); idx++)
    {
        if (erase_or_not[idx] == 1)
        {
            vertices.push_back(airports_s[idx].airport_name_);
            if (airports_s[idx].airport_IATA_ != "\\N")
            {
                code_airport[airports_s[idx].airport_IATA_] = airports_s[idx];
            }
            else
            {
                code_airport[airports_s[idx].airport_ICAO_] = airports_s[idx];
            }
            name_airport[airports_s[idx].airport_name_] = airports_s[idx];
            new_airports.push_back(airports_s[idx]);
        }
    }
    airports_s = new_airports;
}

/*
    routes cleaner&routes map constructor
    input: nothing
    output: nothing
    clean routes loaded,exclude data entries of following type:
        1. the departure airport or arrival airport cannot be found in current airports data
        2. the airline code of corresponding route cannot be found in current airlines data
    construct routes map using departure and arrival airport code as key and its airline struct
    as value(3-length code is preferred)
*/
void info_container::cleanRoute()
{
    std::vector<int> erase_or_not;
    std::vector<route_s> new_routes;
    erase_or_not.resize(routes_s.size(), 1);
    for (unsigned idx = 0; idx < routes_s.size(); idx++)
    {
        if (code_airport.find(routes_s[idx].src_code_) == code_airport.end() ||
            code_airport.find(routes_s[idx].dest_code_) == code_airport.end())
        {
            erase_or_not[idx] = -1;
        }
        else if (code_airline.find(routes_s[idx].airline_) == code_airline.end())
        {
            erase_or_not[idx] = -1;
        }
    }
    for (unsigned idx = 0; idx < routes_s.size(); idx++)
    {
        if (erase_or_not[idx] == 1)
        {
            route_pair.push_back(std::pair<std::string, std::string>(code_airport.find(routes_s[idx].src_code_)->second.airport_name_, code_airport.find(routes_s[idx].dest_code_)->second.airport_name_));
            auto it = pair_route.find(routes_s[idx].src_code_ + "-" + routes_s[idx].dest_code_);
            if (it == pair_route.end())
            {
                pair_route[routes_s[idx].src_code_ + "-" + routes_s[idx].dest_code_] = routes_s[idx].airline_;
            }
            else
            {
                it->second = it->second + "," + routes_s[idx].airline_;
            }
            new_routes.push_back(routes_s[idx]);
        }
    }
    routes_s = new_routes;
}

/*
    airline cleaner&airline map constructor
    input: nothing
    output: nothing
    clean airlines loaded,exclude data entries of following type:
        1. the airline name is empty
        2. all the airline codes are empty
        3. the active code of airline is N
        4. airline codes have incorrect length
        5. all airline codes are \N
    construct airline map using departure and arrival airport code and its airlines code as value
*/
void info_container::cleanAirline()
{
    std::vector<int> erase_or_not;
    std::vector<airline_s> new_airlines;
    erase_or_not.resize(airlines_s.size(), 1);
    for (unsigned idx = 0; idx < airlines_s.size(); idx++)
    {
        if (airlines_s[idx].airline_name_ == "" ||
            (airlines_s[idx].airline_IATA_ == "" && airlines_s[idx].airline_ICAO_ == ""))
        {
            erase_or_not[idx] = -1;
        }
        else if (airlines_s[idx].active_ == "\"N\"")
        {
            erase_or_not[idx] = -1;
        }
        else if (airlines_s[idx].airline_IATA_.length() != 4)
        {
            airlines_s[idx].airline_IATA_ = "\\N";
            if (airlines_s[idx].airline_ICAO_.length() != 5)
            {
                erase_or_not[idx] = -1;
            }
        }
        else if (airlines_s[idx].airline_IATA_ == "\\N" && airlines_s[idx].airline_ICAO_ == "\\N")
        {
            erase_or_not[idx] = -1;
        }
    }
    for (unsigned idx = 0; idx < airlines_s.size(); idx++)
    {
        if (erase_or_not[idx] == 1)
        {
            if (airlines_s[idx].airline_IATA_ != "\\N")
            {
                code_airline[airlines_s[idx].airline_IATA_] = airlines_s[idx];
            }
            else
            {
                airlines_s[idx].airline_IATA_ = "";
                code_airline[airlines_s[idx].airline_ICAO_] = airlines_s[idx];
            }
            new_airlines.push_back(airlines_s[idx]);
        }
    }
    airlines_s = new_airlines;
}

/*
    data reader
    input: nothing
    output: nothing
    read data from stored in destination file and store them in vector of structs of corresponding data
*/
void info_container::read()
{
    if (valid_data == false)
        return;
    std::vector<std::vector<std::string>> airport_v = transferFile(airports_);
    std::vector<std::vector<std::string>> route_v = transferFile(routes_);
    std::vector<std::vector<std::string>> airline_v = transferFile(airlines_);

    for (unsigned long i = 0; i < airport_v.size(); i++)
    {
        struct airport_s s;
        if (airport_v[i].size() < 9)
            continue;
        s.city_ = airport_v[i][2];
        if (s.city_.length() > 0 && s.city_[s.city_.length() - 1] != '\"')
            continue;
        s.airport_name_ = airport_v[i][1];
        if (s.airport_name_.length() > 0 && s.airport_name_[s.airport_name_.length() - 1] != '\"')
            continue;
        s.latitude_ = stod(airport_v[i][6]);
        s.longtitude_ = stod(airport_v[i][7]);
        s.altitude_ = stod(airport_v[i][8]);
        s.airport_IATA_ = airport_v[i][4]; // 3
        if (s.airport_IATA_.length() > 0 && s.airport_IATA_[s.airport_IATA_.length() - 1] != '\"')
            continue;
        s.airport_ICAO_ = airport_v[i][5]; // 4
        if (s.airport_ICAO_.length() > 0 && s.airport_ICAO_[s.airport_ICAO_.length() - 1] != '\"')
            continue;
        s.airport_country_ = airport_v[i][3];
        if (s.airport_country_.length() > 0 && s.airport_country_[s.airport_country_.length() - 1] != '\"')
            continue;
        airports_s.push_back(s);
    }

    for (unsigned long i = 0; i < route_v.size(); i++)
    {
        struct route_s s;
        if (route_v[i].size() < 5)
            continue;
        s.airline_ = "\"" + route_v[i][0] + "\"";
        s.src_code_ = "\"" + route_v[i][2] + "\"";  // 3 or 4
        s.dest_code_ = "\"" + route_v[i][4] + "\""; // 3 or 4

        routes_s.push_back(s);
    }

    for (unsigned long i = 0; i < airline_v.size(); i++)
    {
        struct airline_s s;
        if (airline_v[i].size() < 8)
            continue;
        s.airline_name_ = airline_v[i][1];
        s.airline_IATA_ = airline_v[i][3]; // 2
        s.airline_ICAO_ = airline_v[i][4]; // 3
        s.airline_country_ = airline_v[i][6];
        s.active_ = airline_v[i][7];

        airlines_s.push_back(s);
    }
}

/*
    utility function from lab, read file
*/
std::string info_container::readfile(const std::string &filename)
{
    std::ifstream in(filename);
    std::stringstream strStream;
    if (in.is_open())
    {
        strStream << in.rdbuf();
    }
    else
    {
        std::cout << "cannot read input data" << std::endl;
        valid_data = false;
    }
    return strStream.str();
}

/*
    utility function from lab, read file and return 2d vector of string
*/
std::vector<std::vector<std::string>> info_container::transferFile(const std::string &filename)
{
    std::string newString = readfile(filename);
    std::vector<std::string> rows;
    int num_row = divide(newString, '\n', rows);
    std::vector<std::vector<std::string>> newV2D;
    for (int i = 0; i < num_row; i++)
    {
        std::vector<std::string> cols;
        newV2D.push_back({});

        int num_col = divide(rows[i], ',', cols);
        for (int j = 0; j < num_col; j++)
        {
            std::string single = Trim(cols[j]);
            newV2D[i].push_back(single);
        }
    }
    return newV2D;
}

/*
    utility function from lab, split string with target char
*/
int info_container::divide(const std::string &line, char ch, std::vector<std::string> &temp)
{
    std::string newLine = line;
    std::string::size_type pos, check;
    while ((pos = newLine.find(ch)) != std::string::npos)
    {
        temp.push_back(newLine.substr(0, pos));
        newLine.erase(0, pos + 1);
    }
    temp.push_back(newLine);
    return temp.size();
}

/*
    utility function from lab, trim string
*/
std::string info_container::TrimRight(const std::string &str)
{
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

/*
    utility function from lab, trim string
*/
std::string info_container::TrimLeft(const std::string &str)
{
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

/*
    utility function from lab, trim string
*/
std::string info_container::Trim(const std::string &str)
{
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

/*
    distance calculator
    input: longitude, latitude of starting and ending point
    output: double type of distance
    calculate distance using trigonometric function，first find angle vector between start and end,
    then calculate using arc length formula
*/
double info_container::cal_dist(double longitude1, double latitude1, double longitude2, double latitude2)
{
    double rad_longtitude1 = pi * longitude1 / 180;
    double rad_latitude1 = pi * latitude1 / 180;
    double rad_longtitude2 = pi * longitude2 / 180;
    double rad_latitude2 = pi * latitude2 / 180;
    double rad_diff_longtitude = rad_longtitude1 - rad_longtitude2;
    double rad_diff_latitude = rad_latitude1 - rad_latitude2;
    double dist = 2 * asin(sqrt(pow(sin(rad_diff_latitude / 2), 2) + cos(rad_latitude1) * cos(rad_latitude2) * pow(sin(rad_diff_longtitude / 2), 2)));
    dist = dist * EARTH_RAD;
    return dist;
}