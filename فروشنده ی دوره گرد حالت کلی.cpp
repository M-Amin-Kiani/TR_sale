// mohammad amin kiani 4003613052         محمد امین کیانی

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// The function to calculate the cost of a path
int calculate_path_cost(const vector<vector<int>>& distances, const vector<int>& path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        cost += distances[path[i]][path[i+1]];
    }
    cost += distances[path.back()][path.front()];
    return cost;
}

// The function to find the best path using branch and bound algorithm
void find_best_path(vector<int>& current_path, int& best_cost, vector<int>& best_path,
                    vector<bool>& visited, int current_cost, const vector<vector<int>>& distances) {
    // Base case: if all cities have been visited, update the best path if necessary
    if (current_path.size() == distances.size()) {
        int new_cost = current_cost + distances[current_path.back()][current_path.front()];
        if (new_cost < best_cost) {
            best_cost = new_cost;
            best_path = current_path;
        }
        return;
    }

    // For each unvisited city, add it to the path and continue the search
    for (int i = 0; i < distances.size(); ++i) {
        if (!visited[i]) {
            int new_cost = current_cost + distances[current_path.back()][i];
            // Prune the search if the current path cost is already greater than the best cost
            if (new_cost >= best_cost) {
                continue;
            }
            // Add the city to the current path and mark it as visited
            current_path.push_back(i);
            visited[i] = true;
            // Recursively search for the best path starting from the new city
            find_best_path(current_path, best_cost, best_path, visited, new_cost, distances);
            // Remove the city from the current path and mark it as unvisited
            current_path.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    int num_cities;
    cin >> num_cities;

    vector<vector<int>> distances(num_cities, vector<int>(num_cities));
    for (int i = 0; i < num_cities; ++i) {
        for (int j = 0; j < num_cities; ++j) {
            cin >> distances[i][j];
        }
    }

    vector<int> current_path = {0};
    int best_cost = INT_MAX;
    vector<int> best_path;
    vector<bool> visited(num_cities, false);
    visited[0] = true;

    find_best_path(current_path, best_cost, best_path, visited, 0, distances);

    cout << "Shortest path cost: " << best_cost << endl;
    cout << "Shortest path: ";
    for (int i = 0; i < best_path.size(); ++i) {
        cout << best_path[i] << " ";
    }
    cout << endl;

    return 0;
}
