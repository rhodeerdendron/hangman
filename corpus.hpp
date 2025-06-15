#include <vector>
#include <filesystem>
#include <string>
#include <string_view>


struct corpus
{
    size_t num_words(void) const { return words.size(); }
    std::string_view get_random_word(void) const;

    std::vector<std::string> words;
};

corpus corpus_from_file(
    std::filesystem::path file,
    size_t min_word_len = 4);

