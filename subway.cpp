#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

struct Segment {
    std::vector<std::vector<char>> grid;
    int dxsteps;
    int dysteps;
};

class Location{
    private:    
        double latitude, longitude;
    public:
        Location(double lat, double lon);

        double get_latitude();

        double get_longitude();

        Segment print_path(Location &other);
};

// latitude
double ns_distance(double num1, double num2); 

// longitude
double ew_distance(double num1, double num2, double extra1, double extra2);

// In meters
double ns_distance(double num1, double num2){
    double distance = (num2 - num1) * 111320;
    return distance;
}

// In meters
double ew_distance(double num1, double num2, double extra1, double extra2){
    double distance = (num2 - num1) * 111320 * std::cos((extra1 + extra2) / 2.0  * M_PI / 180.0);
    return distance;
}

Location::Location(double lat, double lon): latitude{lat}, longitude{lon}{}

double Location::get_latitude(){
    return latitude;
}

double Location::get_longitude(){
    return longitude;
}

int error(int a, int b, int dx, int dy){
    return a * dy - b * dx;
}

Segment Location::print_path(Location &other){

    double vdist = ns_distance(latitude, other.latitude);

    double hdist = ew_distance(longitude, other.longitude, latitude, other.latitude);

    // Unit analysis: m / (m / unit) = m * (unit / m) = unit
    // Number of units = Distance / Distance per unit
    // 10 m / unit
    int vsteps = std::max(1, (int)std::ceil(std::abs(vdist) / 50.0));
    int hsteps = std::max(1, (int)std::ceil(std::abs(hdist) / 50.0));

    std::vector<std::vector<char>> path(vsteps + 1, std::vector<char>(hsteps + 1, ' '));

    // path = {a, 1st Want a to be ^,^,...,^     Therefore, a = std::vector<char>(hsteps, '^')
    //         a,                  1       hsteps
    //         a,
    //         a,
    //         a} vsteps(th) a
    
    // Latitude and ns distance/vdist increases to the north (up) because northern hemisphere
    // Longitude and ew distance/hdist increases to the east (right) because not crossing international date line

    // Starting and ending coordinates
    int x0 = (hdist < 0) ? hsteps : 0; // If true, travels left (start at right)
    int y0 = (vdist < 0) ? 0 : vsteps; // If true, travels down (start at top)

    int xstart = x0;
    int ystart = y0;

    int x1 = (hdist < 0) ? 0 : hsteps;
    int y1 = (vdist < 0) ? vsteps : 0;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1; // If true, travels right, so column index increments by 1
    int sy = (y0 < y1) ? 1 : -1; // If true, travels down, so row index increments by 1

    while (true) {
        path[y0][x0] = '%';
        // Stop after marking ending coordinate
        if (x0 == x1 && y0 == y1){
            break; 
        }
        
        // Move horizontally
        int error1 = error(x0 + sx - xstart, y0 - ystart, dx, dy);

        // Move vertically
        int error2 = error(x0 - xstart, y0 + sy - ystart, dx, dy);

        // Move diagonally
        int error3 = error(x0 + sx - xstart, y0 + sy - ystart, dx, dy);

        int min_error = std::min(std::abs(error1), std::abs(error2));
        min_error = std::min(std::abs(min_error), std::abs(error3));

        if(min_error == std::abs(error1)){
            if(x0 != x1){
                x0 += sx;
                continue;
            } else{
                if(y0 != y1){
                    y0 += sy;
                    continue;
                }
            }
        }
        if(min_error == std::abs(error2)){
            if(y0 != y1){
                y0 += sy;
                continue;
            } else{
                if(x0 != x1){
                    x0 += sx;
                    continue;
                }
            }
        }
        if(min_error == std::abs(error3)){
            if(x0 != x1 && y0 != y1){
                x0 += sx;
                y0 += sy;
            } else if(x0 != x1){
                x0 += sx;
            } else{
                y0 += sy;
            }
        }
        
    }

    int dxs = (hdist < 0) ? -hsteps : hsteps;
    int dys = (vdist < 0) ? -vsteps : vsteps;
    Segment s{path, dxs, dys};
    return s;
}

void total_path(std::vector<Segment> paths){
    int x = 0;
    int xmin = 0;
    int xmax = 0;
    int y = 0;
    int ymin = 0;
    int ymax = 0;
    for(int i = 0; i < paths.size(); i++){
        x += paths[i].dxsteps;
        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        y += paths[i].dysteps;
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }
    
    std::vector<std::vector<char>> map(ymax - ymin + 1, std::vector<char>(xmax - xmin + 1, ' '));
    int cx = -xmin;
    int cy = ymax;
    for(int i = 0; i < paths.size(); i++){
        std::vector<std::vector<char>> path = paths[i].grid;
        int row = path.size();
        int col = path[0].size();
        // top-left of this segment's grid
        int top  = (paths[i].dysteps >= 0) ? cy - (row - 1) : cy;
        int left = (paths[i].dxsteps >= 0) ? cx : cx - (col - 1);
        for (int k = 0; k < row; k++) {
            for (int j = 0; j < col; j++) {
                map[top + k][left + j] = path[k][j];
            }
        }
        map[cy][cx] = '*';
        cx += paths[i].dxsteps;
        cy -= paths[i].dysteps;
        if(i == paths.size() - 1){
            map[cy][cx] = '*';
        }
    }
    // Print grid
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == '*'){
                std::cout << "\033[31m" << map[i][j];
            } else{
                std::cout << "\033[30m" << map[i][j];
            }
        }
        std::cout << '\n';
    }
}