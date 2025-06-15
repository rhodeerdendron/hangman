#include "corpus.hpp"
#include "hangman.hpp"

#include <iostream>
#include <limits>


int main(int argc, char* argv[])
{
    // get words list file
    std::filesystem::path corpus_path;
    if (argc >= 2)
        corpus_path = std::filesystem::path(argv[1]);
    else
    {
        corpus_path = std::filesystem::path{ "google-10000-english" } /
            "google-10000-english-no-swears.txt";
        std::cerr << "using default corpus path "
            << std::quoted(corpus_path.string())
            << std::endl;
    }

    // read in words list
    corpus corp = corpus_from_file(corpus_path);
    if (corp.num_words() == 0)
    {
        std::cerr << "error: invalid path or other file error" << std::endl;
        return 1;
    }
    std::cout << "read in " << corp.num_words() << " words from corpus" << std::endl;

    hangman game(corp.get_random_word(), 6);
    int guesses = 0;

    // print header
    std::cout << "chosen word has "
        << game.total_chars_in_word() << " chars, "
        << game.unique_chars_in_word() << " unique.\n";
    std::cout << "you have " << game.guesses_total() << " guesses.\n";
    std::cout << "ctrl+C to quit.\n";
    std::cout << "=========================\n";

    while (game.guesses_remaining())
    {
        // print state
        std::cout << '\n';
        for (const char& c : game.working_word())
             std::cout << c << ' ';
        std::cout << "\nmisses remaining: " << game.guesses_remaining();
        std::cout << "\nguessed: ";
        for (char c = 'a'; c <= 'z'; c++)
            std::cout << ((game.guessed().is_set(c))? c : '.');
        std::cout << '\n';

        // read in char
        char guess = 0;
        do {
            std::cout << "guess: ";
            std::cin >> guess;
            // ignore rest of line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (!game.guessed().is_unset(guess));
        guesses++;

        // guess
        bool good = game.guess(guess);
        if (good)
            std::cout << "good!\n";
        else
            std::cout << "bad!\n";

        // check for win
        bool win = true;
        for (const char& c : game.working_word())
            if (c == '_')
                win = false;
        if (win)
            break;
    }

    // print summary
    std::cout << "\n=========================\n\n";
    std::cout << "GAME " << (game.guesses_remaining()? "WON" : "LOST")
        << " after " << guesses << " guesses!\n";
    std::cout << "word was: " << game.word() << "\n";
    return 0;
}

