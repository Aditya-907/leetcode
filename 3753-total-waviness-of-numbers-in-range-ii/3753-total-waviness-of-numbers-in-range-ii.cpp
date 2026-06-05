#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
private:
    
    pair<long long, long long> memo[16][11][11][2][2];
    bool visited[16][11][11][2][2];
    string target_str;

    pair<long long, long long> solve(int idx, int prev, int prev2, bool is_less, bool is_started) {
        
        if (idx == target_str.length()) {
            return {1LL, 0LL}; 
        }

        
        int p_idx = (prev == -1) ? 10 : prev;
        int p2_idx = (prev2 == -1) ? 10 : prev2;

        if (visited[idx][p_idx][p2_idx][is_less][is_started]) {
            return memo[idx][p_idx][p2_idx][is_less][is_started];
        }

        long long total_count = 0;
        long long total_wave = 0;

        
        int limit = is_less ? 9 : (target_str[idx] - '0');

        for (int d = 0; d <= limit; ++d) {
            bool next_less = is_less || (d < limit);
            bool next_started = is_started || (d > 0);

           
            int next_prev = next_started ? d : -1;
            int next_prev2 = next_started ? prev : -1;

            auto [next_count, next_wave] = solve(idx + 1, next_prev, next_prev2, next_less, next_started);

            
            bool is_wave = false;
            if (is_started && prev2 != -1 && prev != -1) {
                if ((prev > prev2 && prev > d) || (prev < prev2 && prev < d)) {
                    is_wave = true;
                }
            }

            total_count += next_count;
            total_wave += next_wave;
            
            
            if (is_wave) {
                total_wave += next_count; 
            }
        }

        visited[idx][p_idx][p2_idx][is_less][is_started] = true;
        return memo[idx][p_idx][p2_idx][is_less][is_started] = {total_count, total_wave};
    }

    long long get_waviness_up_to(long long n) {
        if (n < 100) return 0; 
        
        target_str = to_string(n);
        memset(visited, false, sizeof(visited));
        
        return solve(0, -1, -1, false, false).second;
    }

public:
    long long totalWaviness(long long num1, long long num2) {
        return get_waviness_up_to(num2) - get_waviness_up_to(num1 - 1);
    }
};
