#pragma once

/*
A grammar is equivalent to map<Word,std::vector<Sentence>>
This is implemented as arduino doesn't contain it.
*/
template <typename Word, typename Sentence, typename Sentence_Iterator>
class Grammar
{
private:
    /*
    A grammar element is a std::pair<Word, key,std::vector<Sentence>>
    This exists because std::pair doesn't exist on arduino
    */
    struct Grammar_Element
    {
        Grammar_Element(Word _key, std::vector<Sentence> _value) : key(_key), value(_value) {}
        Word key;
        std::vector<Sentence> value;
    };

    std::vector<Grammar_Element> entries;
public:
    Grammar() {}

    typename std::vector<Grammar_Element>::iterator begin()
    {
        return entries.begin();
    }

    typename std::vector<Grammar_Element>::iterator end()
    {
        return entries.end();
    }

    typename std::vector<Grammar_Element>::const_iterator find(Word key) const
    {
        for (auto it = entries.begin(); it < entries.end(); ++it)
        {
            if (it->key == key)
            {
                return it;
            }
        }
        return entries.end();
    }


    typename std::vector<Grammar_Element>::const_iterator end() const
    {
        return entries.end();
    }

    std::vector<Sentence> &operator[](Word key)
    {
        for (auto it = entries.begin(); it != entries.end(); ++it)
        {
            if (it->key == key)
            {
                return it->value;
            }
        }

        entries.push_back(Grammar_Element(key, std::vector<Sentence>()));
        auto last_item = (entries.end() - 1);
        return last_item->value;
    }

    /*
    Return the value of a key.
    Unlike std::map, if the provided key does not exist an error will not be thrown,
    instead an empty vector is returned.
    */
    const std::vector<Sentence> at(Word key) const
    {
        const auto it = find(key);
        if (it != entries.end())
        {
            return it->value;
        }
        else
        {
            return std::vector<Sentence>();
        }
    }
};
