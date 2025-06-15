#include "hangman.hpp"


int charset::num_set(void) const
{
    // TODO portability
    return __builtin_popcount(m_letters);
}

static inline bool to_letter_idx(char& c)
{
    if (c >= 'A' && c <= 'Z')
        c -= 'A';
    else if (c >= 'a' && c <= 'z')
        c -= 'a';
    else
        return false;
    return true;
}

bool charset::is_set(char c) const
{
    if (!to_letter_idx(c))
        return false;
    return m_letters & (1u << c);
}

bool charset::is_unset(char c) const
{
    if (!to_letter_idx(c))
        return false;
    return (m_letters & (1u << c)) == 0;
}

void charset::set(char c)
{
    if (!to_letter_idx(c))
        return;
    m_letters |= (1u << c);
}

void charset::unset(char c)
{
    if (!to_letter_idx(c))
        return;
    m_letters &= ~(1u << c);
}


hangman::hangman(std::string_view word, int guesses) :
    m_guesses_total(guesses), m_guesses_rem(guesses),
    m_word(word), m_working_word(word.size(), '_')
{}




int hangman::unique_chars_in_word(void) const
{
    charset chars;
    for (const char& c : m_word)
        chars.set(c);
    return chars.num_set();
}


bool hangman::guess(char c)
{
    // normalize
    if (c >= 'A' && c <= 'Z')
        c += ('a'-'A');
    if (c < 'a' || c > 'z')
        return false;

    if (m_guessed.is_set(c))
        return false;
    m_guessed.set(c);

    // is this letter in the word?
    bool changed = false;
    for (size_t i = 0; i < m_word.size(); i++)
        if (m_word[i] == c)
        {
            m_working_word[i] = c;
            changed = true;
        }

    if (!changed)
        m_guesses_rem--;
    return changed;
}

