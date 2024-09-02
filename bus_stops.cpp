#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string bus_stops(const vector<string>& commands) {
    // Map to store bus routes (bus -> list of stops)
    map<string, vector<string>> buses;
    
    // Map to store which buses pass through each stop (stop -> list of buses)
    map<string, vector<string>> stops;
    
    stringstream output;

    for (const string& command_line : commands) {
        stringstream ss(command_line);
        string command;
        ss >> command;

        if (command == "NEW_BUS") {
            string bus;
            int stop_count;
            ss >> bus >> stop_count;
            vector<string> stop_list(stop_count);

            // Reading stops for the bus
            for (int j = 0; j < stop_count; ++j) {
                ss >> stop_list[j];
                stops[stop_list[j]].push_back(bus);
            }

            // Storing the bus route
            buses[bus] = stop_list;

        } else if (command == "BUSES_FOR_STOP") {
            string stop;
            ss >> stop;

            if (stops.count(stop) == 0) {
                output << "No stop" << endl;
            } else {
                for (const string& bus : stops[stop]) {
                    output << bus << " ";
                }
                output << endl;
            }

        } else if (command == "STOPS_FOR_BUS") {
            string bus;
            ss >> bus;

            if (buses.count(bus) == 0) {
                output << "No bus" << endl;
            } else {
                for (const string& stop : buses[bus]) {
                    output << "Stop " << stop << ": ";
                    if (stops[stop].size() == 1) {
                        output << "no interchange" << endl;
                    } else {
                        for (const string& other_bus : stops[stop]) {
                            if (other_bus != bus) {
                                output << other_bus << " ";
                            }
                        }
                        output << endl;
                    }
                }
            }

        } else if (command == "ALL_BUSES") {
            if (buses.empty()) {
                output << "No buses" << endl;
            } else {
                for (const auto& bus_item : buses) {
                    output << "Bus " << bus_item.first << ": ";
                    for (const string& stop : bus_item.second) {
                        output << stop << " ";
                    }
                    output << endl;
                }
            }
        }
    }
    
    return output.str();
}

void run_test() {
    vector<string> commands = {
        "ALL_BUSES",
        "BUSES_FOR_STOP Marushkino",
        "STOPS_FOR_BUS 32K",
        "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo",
        "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo",
        "BUSES_FOR_STOP Vnukovo",
        "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo",
        "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo",
        "STOPS_FOR_BUS 272",
        "ALL_BUSES"
    };

    string expected_result = 
        "No buses\n"
        "No stop\n"
        "No bus\n"
        "32 32K \n"
        "Stop Vnukovo: 32 32K 950 \n"
        "Stop Moskovsky: no interchange\n"
        "Stop Rumyantsevo: no interchange\n"
        "Stop Troparyovo: 950 \n"
        "Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo \n"
        "Bus 32: Tolstopaltsevo Marushkino Vnukovo \n"
        "Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo \n"
        "Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo \n";

    string actual_result = bus_stops(commands);

    cout << "Expected Result:\n" << expected_result << endl;
    cout << "Actual Result:\n" << actual_result << endl;

    if (actual_result == expected_result) {
        cout << "Test Passed!" << endl;
    } else {
        cout << "Test Failed!" << endl;
    }
}

int main() {
    // Run predefined test cases
    // run_test();

    int q; 
    cin >> q;
    vector<string> commands(q);
    cin.ignore();  

    for (int i = 0; i < q; ++i) {
        getline(cin, commands[i]);
    }
    
    cout << bus_stops(commands);
    return 0;
}
