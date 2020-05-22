template <typename Word, typename Sentence, typename Sentence_Iterator>
class No_Space_Begin : public Macro<Word, Sentence, Sentence_Iterator> {
    public:

    bool match(const Word word) const override
    {
        return beginsWith(word);
    };

    void execute(Sentence& stack, Sentence_Iterator& match) const override
    {
        const auto new_text = substring((*match), length(no_space), length(*match));
        if (match != stack.begin())
        {
            --match;
            (*match) += new_text;
            ++match;
            stack.erase(match);
        }
    };

    private:
        const Word no_space = Word("[NO_SPACE]");

        /*
        Returns true if full_text starts with start_text.
        */
        bool beginsWith(const Word full_text) const
        {
        if (length(full_text) >= length(no_space))
            {
                return no_space == substring(full_text, 0, length(no_space));
            }
            return false;
        }
};
