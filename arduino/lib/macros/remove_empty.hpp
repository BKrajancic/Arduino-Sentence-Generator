/*
Removes from the stack any word which is empty.
*/
template <typename Word, typename Sentence, typename Sentence_Iterator>
class Remove_Empty : public Macro<Word, Sentence, Sentence_Iterator> {
    public:

    bool match(const Word word) const override
    {
        return word == Word("");
    };

    void execute(Sentence& stack, Sentence_Iterator& match) const override
    {
        stack.erase(match);
    };
};