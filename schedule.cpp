// #include <Lucky>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    std::string* output
) {
    size_t totalSize = size * nmemb;

    output->append(
        (char*)contents,
        totalSize
    );

    return totalSize;
}

void read_schedule(int) route_id, std::string *schedule){
    //trips.txt
    ifstream file("trips.txt");
    std::string temp = "";
    std::getline(file, temp);
    temp = "";
    std::vector<int> trips;
    while(getline(file, temp, ',')){
        int route_id2;
        if(isstringstream temp_stream{temp}; temp_stream >> route_id2){
            if(route_id2 == route_id){
                std::getline(file, temp, ',');
                std::getline(file, temp, ',');
                isstringstream temp_stream2{temp};
                int trip_id;
                temp_stream2 >> trip_id;
                trips.emplace_back(trip_id);
                std::getline(file, temp);
            }
        }
    }
}