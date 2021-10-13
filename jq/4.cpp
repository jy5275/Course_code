#include <algorithm>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <iostream>

class table_generator {
    using table_t = std::vector<std::tuple<std::string, std::size_t>>;

private:
    // Remove to improve performance
    // auto const & add_word() {
    //     table_.reserve(table_.size() + 1);
    //     table_.emplace_back(word_, hash_word(word_));
    //     return table_.back();
    // }

    bool next_word() {
        return std::next_permutation(word_.begin(), word_.end());
    }

    static std::size_t hash_word(std::string const & word) {
        return std::hash<std::string>{}(word);
    }

public:
    table_generator(std::string alphabet)
        : word_{alphabet}
    {}

    bool operator()(std::string & word, std::size_t & hash) { // `hash` should be a reference type
        if (!begin) {
            std::sort(word_.begin(), word_.end());
            begin = true;
        }

        if (!next_word())
            return false;

        // std::tie(word, hash) = add_word();
        hash = hash_word(word_);
        word = word_;
        return true;
    }

private:
    // table_t table_;      // Remove to improve performance
    bool begin = false;
    std::string word_;  
    // `word_` should not be a reference since the constructor make 
    // take an ephemeral right value as initialize argument. 
    // String should be deep copied in constructor.
};

int main() {
    table_generator proble4Input("12345");

    std::string word;
    std::size_t hash;
    while (proble4Input(word, hash))
        std::cout << word << " " << std::hex << hash << "\n";
    return 0;
}
