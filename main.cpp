#include <bits/stdc++.h>
using namespace std;

class FlightSystem {
private:
    unordered_map<string, vector<pair<string, int>>> adjList; // Graph representation

public:
    // Add a city (node)
    void addCity(string city) {
        if (adjList.find(city) == adjList.end()) {
            adjList[city] = {};
            cout << "City " << city << " added successfully.\n";
        } else {
            cout << "City " << city << " already exists.\n";
        }
    }

    // Add a flight (edge) with cost
    void addFlight(string src, string dest, int cost) {
        if (adjList.find(src) == adjList.end() || adjList.find(dest) == adjList.end()) {
            cout << "One or both cities do not exist. Please add them first.\n";
            return;
        }

        adjList[src].push_back({dest, cost});
        adjList[dest].push_back({src, cost}); // Bidirectional flight
        cout << "Flight added from " << src << " to " << dest << " with cost $" << cost << endl;
    }

    // Display all available flights
    void displayFlights() {
        if (adjList.empty()) {
            cout << "No flights available.\n";
            return;
        }
        cout << "\nAvailable Flights:\n";
        for (auto &pair : adjList) {
            cout << "Flights from " << pair.first << " -> ";
            for (auto &flight : pair.second) {
                cout << "(" << flight.first << ", $" << flight.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra’s Algorithm to find the shortest flight path
    void findShortestPath(string src, string dest) {
        if (adjList.find(src) == adjList.end() || adjList.find(dest) == adjList.end()) {
            cout << "One or both cities do not exist in the flight network.\n";
            return;
        }

        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        for (auto &pair : adjList) dist[pair.first] = INT_MAX;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            string city = pq.top().second;
            int cost = pq.top().first;
            pq.pop();

            if (city == dest) break;

            for (auto &neighbor : adjList[city]) {
                int newCost = cost + neighbor.second;
                if (newCost < dist[neighbor.first]) {
                    dist[neighbor.first] = newCost;
                    parent[neighbor.first] = city;
                    pq.push({newCost, neighbor.first});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No route found from " << src << " to " << dest << ".\n";
            return;
        }

        vector<string> path;
        for (string at = dest; at != src; at = parent[at]) {
            path.push_back(at);
        }
        path.push_back(src);
        reverse(path.begin(), path.end());

        cout << "Cheapest Route from " << src << " to " << dest << ": ";
        for (string city : path) cout << city << " -> ";
        cout << "End ($" << dist[dest] << ")\n";
    }

    // Function to book a flight
    void bookFlight(string src, string dest) {
        cout << "Finding the best route...\n";
        findShortestPath(src, dest);
        cout << "Booking confirmed! Safe travels.\n";
    }
};

int main() {
    FlightSystem fs;
    int choice;
    string city1, city2;
    int cost;

    do {
        cout << "\n=========================\n";
        cout << "Flight Reservation System  \n";
        cout << "=========================\n";
        cout << "1.Add City\n";
        cout << "2.Add Flight\n";
        cout << "3.Display Flights\n";
        cout << "4.Find Cheapest Flight\n";
        cout << "5.Book a Flight\n";
        cout << "6.Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter city name: ";
                cin >> city1;
                fs.addCity(city1);
                break;
            case 2:
                cout << "Enter source city: ";
                cin >> city1;
                cout << "Enter destination city: ";
                cin >> city2;
                cout << "Enter flight cost: ";
                cin >> cost;
                fs.addFlight(city1, city2, cost);
                break;
            case 3:
                fs.displayFlights();
                break;
            case 4:
                cout << "Enter source city: ";
                cin >> city1;
                cout << "Enter destination city: ";
                cin >> city2;
                fs.findShortestPath(city1, city2);
                break;
            case 5:
                cout << "Enter source city: ";
                cin >> city1;
                cout << "Enter destination city: ";
                cin >> city2;
                fs.bookFlight(city1, city2);
                break;
            case 6:
                cout << "Exiting... Have a great day!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
