#include "subway.cpp"

int main(){
    std::vector<Location> stations = {
        Location(43.79417, -79.52750),    // Vaughan Metropolitan Centre
        Location(43.78333, -79.52306),    // Highway 407
        Location(43.7768588, -79.5092824),// Pioneer Village
        Location(43.7741232, -79.4996291),// York University
        Location(43.7639743, -79.4915419),// Finch West
        Location(43.7535983, -79.4784098),// Downsview Park
        Location(43.7492988, -79.4622480),// Sheppard West
        Location(43.7344762, -79.4500619),// Wilson
        Location(43.7246418, -79.4475031),// Yorkdale
        Location(43.7152827, -79.4439143),// Lawrence West
        Location(43.7087117, -79.4406853),// Glencairn
        Location(43.7000172, -79.4363964),// Cedarvale
        Location(43.6850034, -79.4153079),// St. Clair West
        Location(43.6747046, -79.4069830),// Dupont
        Location(43.6685404, -79.4047039),// Spadina
        Location(43.6684465, -79.3988440),// St. George
        Location(43.6668462, -79.3933506),// Museum
        Location(43.6596838, -79.3901923),// Queen's Park
        Location(43.6548199, -79.3882736),// St. Patrick
        Location(43.6508016, -79.3865409),// Osgoode
        Location(43.6477917, -79.3848711),// St. Andrew
        Location(43.6456424, -79.3802085),// Union

        // Yonge branch (northbound)
        Location(43.6489494, -79.3777538),// King
        Location(43.6529083, -79.3794575),// Queen
        Location(43.6565367, -79.3810223),// TMU (formerly Dundas)
        Location(43.6606617, -79.3827952),// College
        Location(43.6655242, -79.3838011),// Wellesley
        Location(43.6707855, -79.3856867),// Bloor-Yonge
        Location(43.6765478, -79.3885409),// Rosedale
        Location(43.6816776, -79.3905037),// Summerhill
        Location(43.6879512, -79.3936947),// St. Clair
        Location(43.6979360, -79.3972908),// Davisville
        Location(43.7061229, -79.3985300),// Eglinton
        Location(43.7263483, -79.4024743),// Lawrence
        Location(43.7440391, -79.4066570),// York Mills
        Location(43.7614518, -79.4109148),// Sheppard-Yonge
        Location(43.7686787, -79.4126298),// North York Centre
        Location(43.7812974, -79.4158993) // Finch
    };

    std::vector<Segment> segments;

    // Generate a segment between every consecutive station
    for (size_t i = 0; i + 1 < stations.size(); i++) {
        segments.push_back(stations[i].print_path(stations[i + 1]));
    }

    total_path(segments);
    return 0;
}