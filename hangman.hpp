#include <string>
#include <string_view>
#include <stdint.h>


// represents a boolean for each char a-z
struct charset
{
    int num_set(void) const;
    int num_unset(void) const { return 26 - num_set(); }

    bool is_set(char c) const;   // returns false if c is invalid
    bool is_unset(char c) const; // returns false if c is invalid

    void set(char c);
    void unset(char c);

    void set_all(void) { m_letters = (1u << 26) - 1; }
    void unset_all(void) { m_letters = 0; }

private:
    uint32_t m_letters = 0; // a-z, lsb-msb
};


struct hangman
{
    hangman(std::string_view word, int guesses);
    ~hangman(void) = default;

public:
    int guesses_total(void) const { return m_guesses_total; }
    int guesses_remaining(void) const { return m_guesses_rem; }

    int total_chars_in_word(void) const { return m_word.size(); }
    int unique_chars_in_word(void) const;

    std::string_view word(void) const { return m_word; }
    std::string_view working_word(void) const { return m_working_word; }

    charset guessed(void) const { return m_guessed; }

    // returns true iff c is valid and in word
    bool guess(char c);

private:
    int m_guesses_total = 0, m_guesses_rem = 0;
    charset m_guessed;
    std::string_view m_word;
    std::string m_working_word; // _ for un-guessed letters
};
