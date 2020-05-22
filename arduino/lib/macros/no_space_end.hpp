template <typename Word, typename Sentence, typename Sentence_Iterator>
class No_Space_End : public Macro<Word, Sentence, Sentence_Iterator> {
    public:

    bool match(const Word word) const override
    {
        return endsWith(word, no_space);
    };

    void execute(Sentence& stack, Sentence_Iterator& match) const override
    {
        const auto new_match = substring((*match), 0, length(*match) - length(no_space));
        if (match != stack.end() - 1)
        {
            ++match;
            const auto prev_val = (*match);
            (*match) = new_match + prev_val;
            --match;
            stack.erase(match);
        }
        else
        {
            (*match) = new_match;
        }
    };

    private:
        const Word no_space = Word("[NO_SPACE]");
        /*
        Returns true if full_text ends with end_text.
        */
        bool endsWith(const Word full_text, const Word end_text) const
        {
            if (length(full_text) >= length(end_text))
            {
                const auto chars_to_skip = length(full_text) - (length(end_text));
                const auto full_text_ending = substring(full_text, chars_to_skip, chars_to_skip + length(end_text));
                return no_space == full_text_ending;
            }
            return false;
        }
};
