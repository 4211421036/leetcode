// Time: O(26*26*N)
// Space: O(N)

// Custom Union-Find data structure to track connected components
class UnionFind {
    vector<int> id, size;  // id: parent array, size: size of each component
    int cnt;  // Number of disjoint sets
public:
    // Initialize with n disjoint sets
    UnionFind(int n) : id(n), size(n, 1), cnt(n) {
        iota(begin(id), end(id), 0);  // Set each element as its own parent initially
    }
    
    // Find the root of element a with path compression
    int find(int a) {
        return id[a] == a ? a : (id[a] = find(id[a]));
    }
    
    // Connect elements a and b
    void connect(int a, int b) {
        int x = find(a), y = find(b);
        if (x == y) return;  // Already connected
        id[x] = y;  // Connect x to y
        size[y] += size[x];  // Update size of component y
        --cnt;  // Decrease the count of disjoint sets
    }
    
    // Get the size of the component containing element a
    int getSize(int a) {
        return size[find(a)];
    }
    
    // Get the count of disjoint sets
    int getCount() { return cnt; }
};

class Solution {
public:
    vector<int> groupStrings(vector<string>& A) {
        int N = A.size();
        UnionFind uf(N);  // Initialize UnionFind with N elements
        unordered_map<int, int> m;  // Map from bitmask to string index
        m.reserve(N);  // Reserve space for efficiency
        
        for (int i = 0; i < N; ++i) {
            int h = 0;
            // Convert string to bitmask
            for (char c : A[i]) h |= 1 << (c - 'a');  // Set the bit corresponding to character c
            
            // Check all possible transformations
            for (int j = 0; j < 26; ++j) {
                if (h >> j & 1) {  // If the j-th bit is set (letter j is present)
                    // Try deleting letter j
                    int del = h ^ (1 << j);  // Toggle the j-th bit (deleting it)
                    if (m.count(del)) uf.connect(i, m[del]);  // Connect if del exists
                    
                    // Try replacing letter j with any other letter
                    for (int k = 0; k < 26; ++k) {
                        // Replace j with k: delete j and add k
                        int rep = del | (1 << k);  // Add letter k after deleting j
                        // Check if this creates a different bitmask and if it exists
                        if (rep != del && m.count(rep)) uf.connect(i, m[rep]);
                    }
                } else {  // If the j-th bit is not set (letter j is not present)
                    // Try adding letter j
                    int add = h | (1 << j);  // Toggle the j-th bit (adding it)
                    if (m.count(add)) uf.connect(i, m[add]);  // Connect if add exists
                }
            }
            
            // Store the current string's bitmask
            m[h] = i;
        }
        
        // Find maximum group size
        int mx = 1;
        for (int i = 0; i < N; ++i) {
            mx = max(mx, uf.getSize(i));
        }
        
        // Return [number of groups, size of largest group]
        return {uf.getCount(), mx};
    }
};
