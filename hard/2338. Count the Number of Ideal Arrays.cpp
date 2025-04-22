class Solution {
private:
    static const int MOD = 1e9 + 7;
    static const int MAX_N = 10004; // Mengurangi 1 untuk menghindari out of bounds
    static const int MAX_UNIQUE = 15;
    
    // Precomputed primes less than 100
    static constexpr int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    static const int PRIME_COUNT = sizeof(PRIMES) / sizeof(PRIMES[0]);
    
    // Precomputed combinations
    static int C[MAX_N][MAX_UNIQUE];
    static bool initialized;
    
    // Cache for factorization results
    static unsigned dp[10005];
    
    // Initialize combinations using Pascal's triangle (called only once)
    static void initCombinations() {
        if (initialized) return;
        
        C[0][0] = 1;
        for (int i = 1; i < MAX_N; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= min(MAX_UNIQUE - 1, i); j++) {
                C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
            }
        }
        initialized = true;
    }
    
    // Prime factorization and counting ways
    static int countWays(int x, const int n) {
        if (dp[x] != 0) return dp[x];
        if (x <= 1) return dp[x] = 1;
        
        // Quick check for primes less than 100
        for (int i = 0; i < PRIME_COUNT; i++) {
            if (x == PRIMES[i]) return dp[x] = n; // C(n, 1) for prime
        }
        
        long long cnt = 1;
        int x0 = x;
        int x_sqrt = sqrt(x);
        
        // Factor using precomputed primes
        for (int i = 0; i < PRIME_COUNT && PRIMES[i] <= x_sqrt; i++) {
            int p = PRIMES[i];
            if (x0 % p != 0) continue;
            
            int exp = 0;
            while (x0 % p == 0) {
                exp++;
                x0 /= p;
            }
            
            // Handle overflow protection for n-1+exp
            if (n-1+exp >= MAX_N) {
                // Jika n-1+exp melebihi MAX_N, gunakan pendekatan alternatif
                long long comb = 1;
                for (int k = 0; k < exp; k++) {
                    comb = (comb * (n + k)) % MOD;
                    comb = (comb * modInverse(k + 1, MOD)) % MOD;
                }
                
                // Use memoization when possible
                if (dp[x0] != 0) {
                    return dp[x] = (comb * countWays(x0, n)) % MOD;
                } else {
                    cnt = (cnt * comb) % MOD;
                }
            } else {
                // Use precomputed combinations
                if (dp[x0] != 0) {
                    return dp[x] = (1LL * C[n-1+exp][exp] * countWays(x0, n)) % MOD;
                } else {
                    cnt = (cnt * C[n-1+exp][exp]) % MOD;
                }
            }
        }
        
        // Handle remaining prime factor if any
        if (x0 > 1) {
            cnt = (cnt * n) % MOD; // x0 is a prime > sqrt(x)
        }
        
        return dp[x] = cnt;
    }
    
    // Calculate modular inverse using Fermat's little theorem
    static long long modInverse(long long a, long long m) {
        return modPow(a, m - 2, m);
    }
    
    // Calculate a^b % m
    static long long modPow(long long a, long long b, long long m) {
        long long res = 1;
        a = a % m;
        while (b > 0) {
            if (b & 1)
                res = (res * a) % m;
            b = b >> 1;
            a = (a * a) % m;
        }
        return res;
    }

public:
    static int idealArrays(int n, int maxValue) {
        // Initialize combinations
        initCombinations();
        
        // Reset memoization cache
        memset(dp, 0, sizeof(dp));
        
        // Calculate total ways
        long long ans = 0;
        for (int x = 1; x <= maxValue; x++) {
            ans = (ans + countWays(x, n)) % MOD;
        }
        
        return ans;
    }
};

// Initialize static members
bool Solution::initialized = false;
int Solution::C[Solution::MAX_N][Solution::MAX_UNIQUE] = {{0}};
unsigned Solution::dp[10005] = {0};
