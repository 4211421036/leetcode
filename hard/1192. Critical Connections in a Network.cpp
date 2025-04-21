#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Flat adjacency storage with perfect sizing
        vector<int> adj_flat;
        vector<int> adj_index(n + 1);
        
        // Build adjacency index
        for (const auto& conn : connections) {
            adj_index[conn[0] + 1]++;
            adj_index[conn[1] + 1]++;
        }
        
        // Prefix sum to get indices
        for (int i = 1; i <= n; ++i) {
            adj_index[i] += adj_index[i - 1];
        }
        
        // Build adjacency list
        adj_flat.resize(adj_index[n]);
        vector<int> adj_count(n, 0);
        
        for (const auto& conn : connections) {
            int u = conn[0], v = conn[1];
            adj_flat[adj_index[u] + adj_count[u]++] = v;
            adj_flat[adj_index[v] + adj_count[v]++] = u;
        }
        
        // Arrays for disc and low
        int disc[n], low[n];
        fill_n(disc, n, -1);
        fill_n(low, n, -1);
        
        vector<vector<int>> result;
        result.reserve(min(n, (int)connections.size()));
        
        int time = 0;
        int stack[n], parent[n];
        int stack_ptr = 0;
        
        for (int i = 0; i < n; ++i) {
            if (disc[i] != -1) continue;
            
            // Hot loop - iterative DFS
            stack[stack_ptr++] = i;
            parent[i] = -1;
            disc[i] = low[i] = time++;
            
            while (stack_ptr > 0) {
                int u = stack[stack_ptr - 1];
                bool processed = true;
                
                // Get adjacency range
                int start = adj_index[u];
                int end = adj_index[u + 1];
                
                for (int j = start; j < end; ++j) {
                    int v = adj_flat[j];
                    if (v == parent[u]) continue;
                    
                    if (disc[v] == -1) {
                        parent[v] = u;
                        disc[v] = low[v] = time++;
                        stack[stack_ptr++] = v;
                        processed = false;
                        break;
                    } else if (disc[v] < disc[u]) {
                        low[u] = min(low[u], disc[v]);
                    }
                }
                
                if (processed) {
                    stack_ptr--;
                    if (parent[u] != -1) {
                        low[parent[u]] = min(low[parent[u]], low[u]);
                        if (low[u] > disc[parent[u]]) {
                            if (u < parent[u])
                                result.push_back({u, parent[u]});
                            else
                                result.push_back({parent[u], u});
                        }
                    }
                }
            }
        }
        
        return result;
    }
};
