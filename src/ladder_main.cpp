#include "ladder.h"
#include <set>

int main(int argc, char *argv[]) {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    vector<string> word_ladder1 = generate_word_ladder("bonk", "stonks", word_list);
    vector<string> word_ladder2 = generate_word_ladder("stock", "stock", word_list);
    // vector<string> word_ladder3 = generate_word_ladder("toad", "frog", word_list);
    // print_word_ladder3(word_ladder);

    return 0;
}