String substring(const String source, const size_t start, const size_t end)
{
    return source.substring(start, start + end);
}

size_t length(const String item)
{
  return item.length();
}



#include <ESP8266HTTPClient.h>
#include <esp8266wifi.h>
#include <asyncHTTPrequest.h>
#include <xbuf.h>

#include <vector>


#include "lib/sentence_generator.hpp"

#include "lib/monospace_sizer.hpp"

#include "sentence_printer.hpp"

#include "pushbutton.hpp"
#include "personal_info.hpp"
#include "lib/grammar.hpp"


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

void setup()
{
  Serial.begin(115200);
  asyncHTTPrequest* request = new asyncHTTPrequest();

  buttons.push_back(new Pushbutton(1, url_1, request));
  buttons.push_back(new Pushbutton(2, url_2, request));
  WiFi.begin(ssid, password);
  
  sentence_printer = new Sentence_Printer<String, std::vector<String>>(CHARS_PER_ROW, NUM_ROWS);

  auto g = Arduino_Grammar();
  #include "personal_grammar.hpp"

  sentence_generator = new Arduino_Generator();
  sentence_generator->set_grammar(g);
  

  const auto msg = sentence_generator->get_screen(CHARS_PER_ROW, NUM_ROWS);
  for (auto& row : msg)
  {
    sentence_printer->print_word(row);
  }
}

void loop() {
 
  for (auto i = 0; i < buttons.size(); ++i)
  {
    auto button = buttons[i];
   
    if (button->on_Up())
    {
      randomSeed(counter);
      button->get();
      const auto msg = sentence_generator->get_screen(CHARS_PER_ROW, NUM_ROWS);
      for (auto& row : msg)
      {
        sentence_printer->print_word(row);
      }
    }
  }

  ++counter;
}
