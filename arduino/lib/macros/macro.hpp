template <typename Word, typename Sentence, typename Sentence_Iterator>
class Macro {
    public:
    virtual bool match(const Word word) const = 0;
    virtual void execute(   Sentence& stack,
                            Sentence_Iterator&  match) const = 0;
};