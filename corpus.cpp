#include "corpus.hpp"

#include <fstream> // ifstream
#include <iostream> // cerr, endl
#include <iomanip> // quoted
#include <random> // random_device, mt19937_64, uniform_int_distribution


corpus corpus_from_file(
    std::filesystem::path path,
    size_t min_word_len)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "error opening file " << std::quoted(path.string()) << std::endl;
        return corpus{};
    }

    corpus corp;
    std::string line;
    while (file >> line)
        if (line.size() >= min_word_len)
            corp.words.push_back(line);
    return corp;
}

std::string_view corpus::get_random_word(void) const
{
    static std::random_device rd;
    static std::mt19937_64 rng(rd());

    if (num_words() == 0)
        return std::string_view{};

    std::uniform_int_distribution<size_t> distr(0, num_words());
    return words[distr(rng)];
}
