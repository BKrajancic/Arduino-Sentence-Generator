String substring(const String source, const size_t start, const size_t end)
{
    return source.substring(start, start + end);
}

size_t length(const String item)
{
  return item.length();
}

#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>
#include <esp8266wifi.h>
#include <asyncHTTPrequest.h>
#include <xbuf.h>

#include <vector>

//#define LIB_PATH "../lib"

#include "../lib/sentence_generator.hpp"
#include "sentence_printer.hpp"
#include "pushbutton.hpp"
#include "personal_info.hpp"
#include "../lib/grammar.hpp"

typedef Grammar<String,std::vector<String>, std::vector<String>::iterator> Arduino_Grammar;
typedef Sentence_Generator< Arduino_Grammar,
                            String,
                            std::vector<String>,
                            std::vector<String>::iterator> Arduino_Generator;


const unsigned int CHARS_PER_ROW = 16;
const unsigned int NUM_ROWS = 2;
Sentence_Printer<String, std::vector<String>>* sentence_printer;
Arduino_Generator* sentence_generator;

std::vector<Pushbutton*> buttons;
auto counter = 0lu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  sentence_printer   = new Sentence_Printer<String, std::vector<String>>(CHARS_PER_ROW, NUM_ROWS);
  sentence_generator = new Arduino_Generator(CHARS_PER_ROW, NUM_ROWS);
  Arduino_Grammar g = Gramamr;
#include "personal_grammar.hpp
  sentence_generator.set_grammar(g);
  asyncHTTPrequest* request = new asyncHTTPrequest();

  buttons.push_back(new Pushbutton(1, url_1, request));
  buttons.push_back(new Pushbutton(2, url_2, request));

  WiFi.begin(ssid, password);
  const auto msg = sentence_generator->get_screen();
  for (auto& row : msg)
  {
    sentence_printer->print_word(row);
  }
}

void loop() {
  for (auto button : buttons)
  {
    if (button->on_Up())
    {
      randomSeed(counter);
      button->get();
      const auto msg = sentence_generator->get_screen();
      for (auto& row : msg)
      {
        sentence_printer->print_word(row);
      }
    }
  }
  ++counter;
}
