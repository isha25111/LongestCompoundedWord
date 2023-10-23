#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool isCompound(const string& word, const unordered_set<string>& wordSet, unordered_map<string, bool>& memo);

bool compareWords(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() > b.length();
    }
    return a < b;
}
// Function to find the largest and second largest compound words in a given set of words
vector<string> findLargestAndSecondLargestCompoundedWords(const unordered_set<string>& wordSet) {
    vector<string> words(wordSet.begin(), wordSet.end());

// Sort words based on length and lexicographical order
    sort(words.begin(), words.end(), compareWords);

    string longest = "";
    string secondLongest = "";

    unordered_map<string, bool> memo; // Memoization table to store the word and also it reduce the complexity of searching the words.

    for (const string& word : words) {
        if (isCompound(word, wordSet, memo)) {
            if (longest.empty()) {
                longest = word;
            } else if (word.length() < longest.length()) {
                secondLongest = word;
                break;   // we have sorted the words by length then  we get second longest here.
            }
        }
    }

    return {longest, secondLongest};
}

bool isCompound(const string& word, const unordered_set<string>& wordSet, unordered_map<string, bool>& memo) {
    if (word.length() == 0) {
        return false;
    }

    if (memo.find(word) != memo.end()) {
        return memo[word];
    }

    for (int i = 1; i <= word.length(); i++) {
        string prefix = word.substr(0, i);
        string suffix = word.substr(i);

        if (wordSet.count(prefix) && (wordSet.count(suffix) || isCompound(suffix, wordSet, memo))) {
            memo[word] = true;
            return true;
        }
    }

    memo[word] = false;
    return false;
}

int main() {
    string filename = "input_02.txt"; // Here the input file will be attached accordingly

    try {
        unordered_set<string> wordSet;
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            wordSet.insert(line);
        }

        vector<string> result = findLargestAndSecondLargestCompoundedWords(wordSet);
        cout << "Longest Compound Word: " << result[0] << endl;
        cout << "Second Longest Compound Word: " << result[1] << endl;

    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
