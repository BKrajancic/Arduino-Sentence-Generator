template <typename Word, typename Sentence>
class Sentence_Printer
{
    public:
    Sentence_Printer(const size_t chars_per_row, const size_t num_rows)
        : current_row(0)
        , num_rows(num_rows)
        {
            lcd = new LiquidCrystal_I2C(0x27, chars_per_row, num_rows);
            lcd->begin(chars_per_row, num_rows);
            lcd->init();
            lcd->clear();
            lcd->setCursor(0, 0);
        }


    void print_word(const Word word)
    {
      if (current_row == num_rows)
      {
        lcd->clear();
        current_row = 0;
      }

      lcd->setCursor(0, current_row);
      lcd->print(word.c_str());
      ++current_row;
    }

    /*
    Prints sentence on a digital display.
    limited by char_count characters per row, and row_count rows at a time
    */
    void print_sentences(const Sentence sentences)
    {
        lcd->clear();
        for (auto word = sentences.begin(); word < sentences.end(); ++word)
        {
            lcd->setCursor(0, current_row);
            lcd->print(word->c_str());

            current_row = (current_row + 1) % num_rows;
            if (current_row == 0 && word != sentences.end() - 1)
            {
                lcd->clear();
            }
        }
    }
private:
    size_t current_row;
    const size_t num_rows;
    LiquidCrystal_I2C* lcd;
};
