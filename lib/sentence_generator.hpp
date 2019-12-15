#pragma once
#include "macros/macro.hpp"
#include "macros/no_space_begin.hpp"
#include "macros/no_space_end.hpp"
#include "macros/remove_empty.hpp"

#include "monospace_sizer.hpp"

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <memory>

template <typename Grammar, typename Word, typename Sentence, typename Sentence_Iterator>
class Sentence_Generator
{
  public:
    Sentence_Generator(std::unique_ptr<Sizer<Word>> sizer)
      : sizer(std::move(sizer))
      , elipsis(Word("..."))
      , overflow(Word("-"))
    {
        macros.push_back(new Remove_Empty<Word, Sentence, Sentence_Iterator>());
        macros.push_back(new No_Space_Begin<Word, Sentence, Sentence_Iterator>());
        macros.push_back(new No_Space_End<Word, Sentence, Sentence_Iterator>());
        g = Grammar();
        shuffle();
    }

    void set_grammar(const Grammar new_grammar)
    {
      g = new_grammar;
    }

    /*
      Given a grammar, automatically generates a sentence.

      If there are multiple transitions, a random one is selected.
      It is the caller's responsibility to call srand(2) prior to this
      function to ensure randomness.
    */
    Sentence generate_sentence(const Word start)
    {
      Sentence output;
      output.push_back(start);

      for (auto it = output.begin(); it != output.end(); ++it)
      {
        if (g.find(*it) != g.end())
        {
          auto& transitions = g[*it];
          const auto follow = transitions.back();

          for (auto jt = follow.rbegin(); jt != follow.rend(); ++jt)
          {
              const auto val = *jt;
              it = output.insert(it, val);
          }


          output.erase(it + follow.size());
          it = output.begin() - 1;


          transitions.insert(transitions.begin(), follow);
          transitions.pop_back();
        }
      }

      const auto updated_output = run_macros(output);
      return updated_output;
    }

    void shuffle()
    {
      std::random_device rd;
      std::mt19937 gen(rd());

      for (auto it = g.begin(); it != g.end(); ++it)
      {
        std::shuffle(it->value.begin(), it->value.end(), gen);
      }
    }

    void print_grammar(std::basic_ostream<char>& out)
    {
      for (auto it = g.begin(); it != g.end(); ++it)
      {
        out << it->key;
        out << '\n';
        for (auto jt = it->value.begin(); jt != it->value.end(); ++jt)
        {
          out << '\t';
          for (auto kt = jt->begin(); kt != jt->end(); ++kt)
          {
            out << *kt;
            out << ' ';
          }
          out << '\n';
        }
        out << '\n';
      }
    }

    /*
      Given two strings, returns a single string, but with a space in between
      them. If a string is empty, the other string is returned. If both strings
      are empty, the empty string is returned.

      For any string on the LHS [NO_SPACE] can be placed at the end to prevent a
      space from being added when joining two strings
    */
    Word join_strings(const Word lhs, const Word rhs) const
    {
      auto actual_lhs = lhs;
      auto actual_rhs = rhs;
      auto delimeter = Word(" ");

      if (lhs != Word("") and rhs != Word(""))
      {
        return actual_lhs + delimeter + actual_rhs;
      }
      else if (rhs != Word(""))
      {
        return actual_rhs;
      }
      else if (lhs != Word(""))
      {
        return actual_lhs;
      }
      else
      {
        return Word("");
      }
    };

    /*
      Create a text string of a character, repeated 'count' times.
      e.g: XXX (given X and 3)
    */
    Word repeating_characters(const size_t count, const Word character) const
    {
      auto whitespace = Word();

      for (auto i = 0u; i < count; ++i)
      {
        whitespace = whitespace + character;
      }
      return whitespace;
    }

    /*
      Removes whitespace at the end of a Word
    */
    Word trim_end(const Word text) const
    {
      for (auto i = text.length(); i > 0; --i)
      {
        if (text[i - 1] != ' ')
        {
          return substring(text, 0, i);
        }
      }
      return text;
    }

    size_t size_remaining() const
    {
      const auto sum_of_elems = std::accumulate(
        stack.begin(), stack.end(), Word(""),
        [&] (const Word lhs, const Word rhs){return join_strings(lhs, rhs);}
      );

      return length(sum_of_elems);
    }

    /*
     *  If there is no current sentence: A new sentence is generated and set to be
     *  the current sentence. This function will then return an empty sentence.
     *
     *  If there is a current sentence:  The next row of the current sentence.
     */
    Word pop_size(const unsigned int size)
    {
      if (stack.empty())
      {
        stack = generate_sentence("<START>");
        std::reverse(stack.begin(), stack.end());
        return Word("");
      }
      else
      {
        Word out = stack.back();
        stack.pop_back();
        if (sizer->overflow(out, size))
        {
          stack.push_back(substring(out, size, out.length()));
          out = substring(out, 0, size);
        }

        while (
          peek_next_size() != 0 &&
          sizer->word_fits(
            join_strings(out, stack.back()),
            size))
        {
          out = join_strings(out, stack.back());
          stack.pop_back();
        }
        return out;
      }
    }

    Sentence run_macros(Sentence input) const
    {
        start_macros:
        for (const auto& macro : macros)
        {
            for (auto it = input.begin(); it < input.end(); ++it)
            {
                if (macro->match(*it))
                {
                    macro->execute(input, it);
                    goto start_macros;
                }
            }
        }
        return input;
    }

    Sentence get_screen(const unsigned int width_per_row, const unsigned int rows_per_screen)
    {
        Sentence out;
        for (auto j = 0u; j < rows_per_screen - 1u && size_remaining(); ++j)
        {
            out.push_back(pop_size(width_per_row));
        }

        if (size_remaining() != 0u)
        {
          if (sizer->word_fits(remaining(), width_per_row))
          {
              out.push_back(pop_size(width_per_row));
          }
          else if (sizer->overflow(stack.back(), width_per_row))
          {
              const auto pop = pop_size(width_per_row - length(overflow));
              out.push_back(pop + overflow);
          }
          else
          {
              const auto short_size = width_per_row - length(elipsis);
              const auto pop = pop_size(short_size);
              out.push_back(pop + elipsis);
          }
        }

        if (size_remaining() == 0u)
        {
            pop_size(0);
        }

        while (out.size() < signed(rows_per_screen))
        {
          out.push_back("");
        }

        return out;
    }

  private:
    /*
    Returns the size of the next word.
    '0' means that there is no word next.
    */
    size_t peek_next_size() const
    {
      if (stack.empty())
      {
        return 0;
      }
      return length(stack.back());
    }

    Word remaining() const
    {
      const auto sum_of_elems = std::accumulate(
        stack.begin(),
        stack.end(),
        Word(""),
        [&] (const Word lhs, const Word rhs){return join_strings(lhs, rhs);}
      );
      return sum_of_elems;
    }

    std::unique_ptr<Sizer<Word>> sizer;
    const Word elipsis;
    const Word overflow;

    Grammar g;
    Sentence stack;
    std::vector<Macro<Word, Sentence, Sentence_Iterator>*> macros;
};
