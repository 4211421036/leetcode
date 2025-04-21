#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        unordered_set<string> visited;
        visited.insert(beginWord);
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            string word = current.first;
            int length = current.second;
            
            for (int i = 0; i < word.size(); ++i) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == original) continue;
                    word[i] = c;
                    if (word == endWord) return length + 1;
                    if (wordSet.find(word) != wordSet.end() && visited.find(word) == visited.end()) {
                        visited.insert(word);
                        q.push({word, length + 1});
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
};
