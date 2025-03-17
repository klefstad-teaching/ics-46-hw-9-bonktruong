#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "<ERROR> " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

string to_lowercase(string word) { 
    for (char& c : word) {
        c = tolower(c);
    }
    return word;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    // only works for d=1
    int str1_len = str1.length();
    int str2_len = str2.length();
    if (abs(str1_len - str2_len) > d) {
        return false;
    }
    
    if (str1_len == str2_len) {
        int diff_count = 0;
        for (int i = 0; i < str1_len; i++) {
            if (str1[i] != str2[i]) {
                diff_count++;
                if (diff_count > d) return false;
            }
        }
        return true;
    } 
    else if (str1_len > str2_len) {
        // Case 2: First string is longer - check for deletion
        int i = 0, j = 0;
        bool used_deletion = false;
        
        while (i < str1_len && j < str2_len) {
            if (str1[i] == str2[j]) {
                i++; j++;
            } else {
                if (used_deletion) return false;
                used_deletion = true;
                i++; // Skip one character in the longer string
            }
        }
        return (i < str1_len) ? (i == str1_len - 1) : true;
    } 
    else {
        // Case 3: Second string is longer - check for insertion
        int i = 0, j = 0;
        bool used_insertion = false;
        
        while (i < str1_len && j < str2_len) {
            if (str1[i] == str2[j]) {
                i++; j++;
            } else {
                if (used_insertion) return false;
                used_insertion = true;
                j++; // Skip one character in the longer string
            }
        }
        return (j < str2_len) ? (j == str2_len - 1) : true;
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Cannot generate ladder: start and end words are the same");
        return {};
    }

    if (begin_word == "" || end_word == "") {
        error(begin_word, end_word, "Cannot generate ladder: invalid input");
        return {};
    }

    string start_word = to_lowercase(begin_word);
    string dest_word = to_lowercase(end_word);

    if (word_list.find(dest_word) == word_list.end()) {
        error(begin_word, end_word, "End word not in dictionary");
        return {};
    }

    queue<vector<string>> ladder_q;
    ladder_q.push({start_word});
    set<string> visited;
    
    visited.insert(start_word);
    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();

        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == dest_word) {
                        return new_ladder;
                    }
                    ladder_q.push(new_ladder);
                }
            }
        }
    }
    error(begin_word, end_word, "No word ladder exists");
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cout << "Error: Cannot open file \"" << file_name << "\"";
        return;
    }

    string word;
    while (file >> word) {
        word_list.insert(to_lowercase(word));
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        for (size_t i = 0; i < ladder.size(); i++) {
            cout << ladder[i];
            if (i < ladder.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "Word ladder empty!" << endl;
    }
}

void verify_word_ladder() {
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 7);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 5);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 7);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 9);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}