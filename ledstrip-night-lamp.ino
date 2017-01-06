#include <FastLED.h>
#include <CapacitiveSensor.h>
#include <IRremote.h>
#include <FiniteStateMachine.h>


#define LED_PIN  17
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
IRrecv irrecv(14);
decode_results results;
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

#define NUM_LEDS (79)
int elanaLeds[16] = {63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78};
int elanaLeds1[3] = {76,77,78};
int elanaLeds2[3] = {73,74,75};
int elanaLeds3[4] = {69,70,71,72};
int elanaLeds4[3] = {66,67,68};
int elanaLeds5[3] = {63,64,65};

int elenaStartLed = 63;
int elenaStartLedLength = 16;
CRGB leds[NUM_LEDS];
CRGB virtualLeds[NUM_LEDS];
int randomColorHue[NUM_LEDS];
int virtualLedsSpeed = 100;
uint32_t previousVirtualLedsMillis = 0;

int virtualBrightness = 125;
int ledBrightness = 125;

int twinkle_led[10] = { 0 };
long total1 = 0;
bool buttonPushed = false;
int oneColorHue = 0;
int twoColorHue[2] = {0,0};
uint32_t previousProgramMillis = 0;
uint32_t nextProgramMillis = 0;
int programSpeed = 1000;
int currentProgram = 0;
int previousRunLoop = 0;

const byte NUMBER_OF_STATES = 5; //how many states are we cycling through?
State stateOff = State(&off);
State stateBeforeOff = State(&twinkle);
State stateOneColor = State(&oneColor);
State stateTwoColor = State(&twoColor);
State stateRandomColor = State(&randomColor);
State stateSelectedProgram = State(&selectedProgram);
State stateAutoProgram = State(&autoProgram);

FSM ledStateMachine = FSM(stateOff);     //initialize state machine, start in state: On

void setup() {
  Serial.begin(9600);
  Serial.println("init");                  // print sensor output 1

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness( virtualBrightness );
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  irrecv.enableIRIn(); // Start the receiver

  Serial.begin(9600);

}

void loop()
{
  total1 =  cs_4_2.capacitiveSensor(30);

  //twinkle();

  while (!irrecv.isIdle());  // if not idle, wait till complete

  if (irrecv.decode(&results)) {
    Serial.println(results.value);
      switch(results.value) {
        case 0xFD00FF:  //Volume Down
          virtualBrightness -= 20;
          virtualBrightness = (virtualBrightness <0 )? 5 : virtualBrightness;
          previousProgramMillis = 0;
          break;
        case 0xFD40BF:  //Volume Up
          virtualBrightness += 20;
          virtualBrightness = (virtualBrightness >255 )? 255 : virtualBrightness;
          previousProgramMillis = 0;
          break;
        case 0xFD609F:  //Stop
          ToggleOff();
          break;
        case 0xFD807F:  //Play/Pause          
          currentProgram = 5;
          ledStateMachine.transitionTo(stateSelectedProgram);
          directUpdate();
          break;  
        case 0xFD10EF:  //<
          ledStateMachine.transitionTo(stateSelectedProgram);
          previousProgram();
          directUpdate();
          break;
        case 0xFD50AF:  //>
          ledStateMachine.transitionTo(stateSelectedProgram);
          nextProgram();
          directUpdate();
          break;
        case 0xFDA05F:  //up
          transitionTwoColorState();
          twoColorHue[0] = (twoColorHue[0] + 10 > 255) ? 0 : twoColorHue[0] + 10;
          break;
        case 0xFDB04F:  //down
          transitionTwoColorState();
          twoColorHue[1] = (twoColorHue[1] + 10 > 255) ? 0 : twoColorHue[1] + 10;
          break;
        case 0xFD906F:  //Enter
          ledStateMachine.transitionTo(stateAutoProgram);
          break;
        case 0xFD08F7:  //1
          oneColorHue = 0;
          ledStateMachine.transitionTo(stateOneColor);
          break;    
        case 0xFD8877:  //2
          oneColorHue = 42;
          ledStateMachine.transitionTo(stateOneColor);
          break;  
        case 0xFD48B7:  //3
          oneColorHue = 85;
          ledStateMachine.transitionTo(stateOneColor);
          break;  
        case 0xFD28D7:  //4
          oneColorHue = 128;
          ledStateMachine.transitionTo(stateOneColor);
          break;  
        case 0xFDA857:  //5
          oneColorHue = 171;
          ledStateMachine.transitionTo(stateOneColor);
          break;  
        case 0xFD6897:  //6
          oneColorHue = 225;
          ledStateMachine.transitionTo(stateOneColor);
          break; 
        case 0xFD18E7:  //7
          twoColorHue[0] = 150;
          twoColorHue[1] = -1;
          ledStateMachine.transitionTo(stateTwoColor);
          break;  
        case 0xFD9867:  //8
          twoColorHue[0] = 105;
          twoColorHue[1] = 0;
          ledStateMachine.transitionTo(stateTwoColor);
          break;  
        case 0xFD58A7:  //9
          twoColorHue[0] = 205;
          twoColorHue[1] = 25;
          ledStateMachine.transitionTo(stateTwoColor);
          break;  
        case 0xFD30CF:  //0
          oneColorHue = -1;
          ledStateMachine.transitionTo(stateOneColor);
          break;  
      }  
     
    irrecv.resume(); // Receive the next value
  }
 if (total1 > 1000){
    if (!buttonPushed){
      Serial.println("button pushed");
      ToggleOff();
    }
    buttonPushed = true;
  }else{
    buttonPushed = false;
  }
  if(!ledStateMachine.isInState(stateOff)){
    if(ledBrightness < virtualBrightness){
      ledBrightness = (ledBrightness > 252)? 255 : ledBrightness + 3;
    }else if(ledBrightness > virtualBrightness + 3){
      ledBrightness = (ledBrightness < 3)? 0 : ledBrightness - 3;
    }
  }
  if (millis() - previousVirtualLedsMillis > virtualLedsSpeed){
    for( int pixel = 0; pixel < NUM_LEDS; pixel++) {
      if (leds[pixel] != virtualLeds[pixel]){
        for ( int color = 0; color < 3; color++) {
          if(virtualLeds[pixel][color] < leds[pixel][color]){
            leds[pixel][color] = (virtualLedsSpeed == 0)? leds[pixel][color] -5 : leds[pixel][color] -1;
          }else if (virtualLeds[pixel][color] > leds[pixel][color]){
            leds[pixel][color] = (virtualLedsSpeed == 0)? leds[pixel][color] +5 : leds[pixel][color] +1;
          }
        leds[pixel][color] = (leds[pixel][color] > 255) ? 255 : leds[pixel][color];
        leds[pixel][color] = (leds[pixel][color] < 0) ? 0 : leds[pixel][color];
        }
      }
    }
    previousVirtualLedsMillis = millis();
  }
  ledStateMachine.update();
  FastLED.show();
  delay(10);
}
void directUpdate(){
  previousProgramMillis = 0;
  ledStateMachine.update();
}
void nextProgram(){
  currentProgram = (currentProgram >= 7) ? 0 : currentProgram + 1 ;
}
void previousProgram(){
  currentProgram = (currentProgram <= 0) ? 7 : currentProgram - 1 ;
}
void selectedProgram(){
  switch(currentProgram) {
        case 0:  
          virtualLedsSpeed = 0;
          programSpeed = 100;
          twinkle();
          break;
        case 1: 
          virtualLedsSpeed = 10;
          programSpeed = 1000;
          randomColor();
          break;
        case 2: 
          virtualLedsSpeed = 100;
          programSpeed = 10000;
          randomColor();
          break;
        case 3:
          virtualLedsSpeed = 1;
          programSpeed = 30;
          hueRingColor();
          break;
        case 4:
          virtualLedsSpeed = 1;
          programSpeed = 3;
          hueLoopColor();
          break;
        case 5:
          virtualLedsSpeed = 1;
          programSpeed = 3;
          nameDanceColor();
          break;
       case 6:
          twoColorHue[0] = 0;
          twoColorHue[1] = 171;
          virtualLedsSpeed = 5;
          programSpeed = 300;
          brokenRingColor();
          break;
       case 7:
          twoColorHue[0] = 96;
          twoColorHue[1] = 16;
          virtualLedsSpeed = 5;
          programSpeed = 300;
          brokenRingColor();
          break;
  }
}
void autoProgram(){
  
}

void off() {
  for( int pixel = 0; pixel < NUM_LEDS; pixel++) {  
   ledBrightness = (ledBrightness < 3)? 0 : ledBrightness - 3;
   leds[pixel].subtractFromRGB(3);
   virtualLeds[pixel] = leds[pixel];
  }
}
void transitionTwoColorState() {
  if(!ledStateMachine.isInState(stateTwoColor)){
    if(ledStateMachine.isInState(stateOneColor)){
      twoColorHue[0] = oneColorHue;
      twoColorHue[1] = oneColorHue;
    }
    ledStateMachine.transitionTo(stateTwoColor);
  }

}

void ToggleOff(){
  if(!ledStateMachine.isInState(stateOff)){
    Serial.println("goto off");
    stateBeforeOff = ledStateMachine.getCurrentState();
    ledStateMachine.transitionTo(stateOff);
  }else{
    Serial.println("goto last");
    ledStateMachine.transitionTo(stateBeforeOff);
    directUpdate();
  }
}

bool isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return true;
    }
    return false;
}
