#pragma once
#include <asyncHTTPrequest.h>
#include <xbuf.h>

#include <ESPAsyncTCP.h>
#include <tcp_axtls.h>
#include <async_config.h>
#include <AsyncPrinter.h>
#include <ESPAsyncTCPbuffer.h>
#include <SyncClient.h>
#include <DebugPrintMacros.h>


/*
 * A class for turning pushbutton presses, into a HTTP GET request
 */
class Pushbutton
{
public:
  Pushbutton(const size_t button_pin, const char* url, asyncHTTPrequest* request )
  : button_pin(button_pin)
  , url(url)
  , request(request)
  {
    pinMode(button_pin, INPUT);
  }

  /*
   * Gets the URL
   */
  void get()
  {
    if(request->readyState() == 0 || request->readyState() == 4)
    {
        request->open("GET",  url);
        request->send();
    }
  }

  /*
   * Halts until button is clicked
   */
  void wait() const
  {
    if (digitalRead(button_pin) == HIGH) {
      while (digitalRead(button_pin) == HIGH)
      {
        delay(10);
      }
      while (digitalRead(button_pin) == LOW)
      {
        delay(10);
      }
    }
  }

  /*
   * Returns true if this button was JUST pressed
   */
  bool on_Up() const
  {
      if (digitalRead(button_pin) == LOW) {
        while (digitalRead(button_pin) == LOW)
        {
          delay(10);
        }
        return true;
    }
    return false;
  }

  private:
  size_t button_pin;
  const char* url;
  asyncHTTPrequest* request;
};
