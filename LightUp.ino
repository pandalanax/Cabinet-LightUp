
#include <FastLED.h>
#include <avr/sleep.h>//this AVR library contains the methods
#define REED_PIN    2// Pin connected to reed switch
#define LED_PIN     5
#define SWITCH_PIN  8
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

volatile bool awake = true;

void reed(){
  sleep_disable();//Disable sleep mode
  awake = digitalRead(REED_PIN);   // read the input pin;
}


void rainbow_march(uint8_t thisdelay, uint8_t deltahue) {     // The fill_rainbow call doesn't support brightness levels.

  uint8_t thishue = millis()*(255-thisdelay)/255;             // To change the rate, add a beat or something to the result. 'thisdelay' must be a fixed value.
  
// thishue = beat8(50);                                       // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
// thishue = beatsin8(50,0,255);                              // This can change speeds on the fly. You can also add these to each other.
  
  fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            // Use FastLED's fill_rainbow routine.

}
  
void setup() 
{
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(SWITCH_PIN, OUTPUT);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  attachInterrupt(0, reed, CHANGE);//attaching a interrupt to pin d2
  ADCSRA = 0;  
}

void loop(){
  //Serial.println(awake);
  if(awake){
    digitalWrite(SWITCH_PIN, HIGH);
    delay(500);
    rainbow_march(200, 10);
    FastLED.show();
  }else{
    

    sleep_enable();//Enabling sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep

    FastLED.clear();
    FastLED.show();
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    digitalWrite(SWITCH_PIN,LOW);
    sleep_cpu();//activating sleep mode
  }
}
