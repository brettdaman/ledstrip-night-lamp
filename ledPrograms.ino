
void twinkle() {
  if (millis() - previousProgramMillis > programSpeed){
    int randomLed = random16(0, NUM_LEDS-1);
      for(int i = 1; i < 10; i++) 
    {
      twinkle_led[i-1] = twinkle_led[i];
    }
    twinkle_led[9] = randomLed;
    for( int whichPixel = 0; whichPixel < NUM_LEDS; whichPixel++) {  
      if (isvalueinarray(whichPixel,twinkle_led,10)){
        if(whichPixel% 3 == 0){
          virtualLeds[whichPixel] = CHSV( 0, 255, ledBrightness);
        }else if(whichPixel% 3 == 1){
          virtualLeds[whichPixel] = CHSV( 64, 255, ledBrightness);
        }else{
          virtualLeds[whichPixel] = CHSV( 96, 255, ledBrightness);
        }
      }else{
         virtualLeds[whichPixel] = CRGB(8,8,8);
         //virtualLeds[whichPixel] = CRGB((ledBrightness / 3) + 10,(ledBrightness / 3) + 10,(ledBrightness / 3) + 10);
      }
    }
  previousProgramMillis = millis();
  }
}
void randomColor() {
  if (millis() - previousProgramMillis > programSpeed){
    int previousRandomHue = 0;
    for( int pixel = 0; pixel < NUM_LEDS; pixel++) { 
      int randomHue = random16(-10, 20); 
      if (pixel > 0){
        randomHue = previousRandomHue+ randomHue;
        randomHue = (randomHue > 255)? randomHue - 255 : randomHue;
        randomHue = (randomHue < 0)? 255 - randomHue : randomHue;
      }
      randomColorHue[pixel] = randomHue;
      virtualLeds[pixel] = CHSV( randomHue, 255, ledBrightness);
      previousRandomHue = randomHue;
    }
    previousProgramMillis = millis();
  }else{
    for( int pixel = 0; pixel < NUM_LEDS; pixel++) { 
      virtualLeds[pixel] = CHSV( randomColorHue[pixel], 255, ledBrightness);
    }
  }
}
void hueRingColor() {
  if (millis() - previousProgramMillis > programSpeed){
    int ringLeds = NUM_LEDS - 16;
    for( int pixel = 0; pixel < ringLeds; pixel++) { 
      virtualLeds[pixel] = CHSV( ((float((pixel + previousRunLoop) % ringLeds)/ringLeds)* 255) , 255, ledBrightness);
    }
    for( int pixel = ringLeds; pixel < NUM_LEDS; pixel++) { 
      virtualLeds[pixel] = CHSV(((float((pixel + previousRunLoop) % (50))/50)* 255) , 255, ledBrightness);
    }
    previousProgramMillis = millis();
    previousRunLoop += 1;
  }
}

void hueLoopColor() {
  if (millis() - previousProgramMillis > programSpeed){
    int ringLeds = NUM_LEDS - 16;
    for( int pixel = 0; pixel < ringLeds; pixel++) { 
      uint16_t hue16bit = (previousRunLoop * 10) % 65535;
      virtualLeds[pixel] = RGBColorAtHSBWheel(hue16bit,ledBrightness);
    }
    for( int pixel = ringLeds; pixel < NUM_LEDS; pixel++) { 
      uint16_t hue16bit = (previousRunLoop * 12) % 65535;
      virtualLeds[pixel] = RGBColorAtHSBWheel(hue16bit,ledBrightness);
    }
    previousProgramMillis = millis();
    previousRunLoop += 1;
    
  }
}
void nameDanceColor() {
  if (millis() % programSpeed == 0){
     for( int pixel = 0; pixel < elenaStartLed; pixel++) { 
      uint16_t hue16bit = (previousRunLoop * 10) % 65535;
      virtualLeds[pixel] = RGBColorAtHSBWheel(hue16bit,ledBrightness);
    }
    previousRunLoop += 1;
  }
  for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/10,0,0);
  }
  if (millis() - previousProgramMillis > 20000){
    previousProgramMillis = millis();
  }else if (millis() - previousProgramMillis > 11000){ //ELENA
     for( int pixel = elenaStartLed; pixel < elenaStartLed + 16; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
    }
  }else if (millis() - previousProgramMillis > 10000){ //ELE
     for( int pixel = elenaStartLed; pixel < elenaStartLed + 13; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
    }
  }else if (millis() - previousProgramMillis > 9000){ // ELE
     for( int pixel = elenaStartLed; pixel < elenaStartLed + 10; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
    }
  }else if (millis() - previousProgramMillis > 8000){ // EL
     for( int pixel = elenaStartLed; pixel < elenaStartLed + 6; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
    }
  }else if (millis() - previousProgramMillis > 7000){ // E
     for( int pixel = elenaStartLed; pixel < elenaStartLed + 3; pixel++) { 
      virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
    }
  }else if (millis() - previousProgramMillis > 6000){ //A
     for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
      if (isvalueinarray(pixel,elanaLeds5,sizeof(elanaLeds5)/4)){
        virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
      }
    }
  }else if (millis() - previousProgramMillis > 5000){ // N
    for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
      if (isvalueinarray(pixel,elanaLeds4,sizeof(elanaLeds4)/4)){
        virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
      }
    }
  }else if (millis() - previousProgramMillis > 4000){ // E
    for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
      if (isvalueinarray(pixel,elanaLeds3,sizeof(elanaLeds3)/4)){
        virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
      }
    }
  }else if (millis() - previousProgramMillis > 3000){ // L
    for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
      if (isvalueinarray(pixel,elanaLeds2,sizeof(elanaLeds2)/4)){
        virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
      }
    }
  }else if (millis() - previousProgramMillis > 2000){ // E
    for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
      if (isvalueinarray(pixel,elanaLeds1,sizeof(elanaLeds1)/4)){
        virtualLeds[pixel] = CRGB(ledBrightness/2,ledBrightness/2,ledBrightness/2);
      }
    }
  }
}
void brokenRingColor() {
  Serial.println(nextProgramMillis - millis());
  if (millis() - nextProgramMillis > programSpeed){
    nextProgramMillis  = millis();
     for( int pixel = 0; pixel < elenaStartLed; pixel++) { 
      if ((pixel + previousRunLoop) % 16 < 8){
        virtualLeds[pixel] = CHSV( twoColorHue[0], 255, ledBrightness);
      }else{
        virtualLeds[pixel] = CHSV( twoColorHue[1], 255, ledBrightness);
      }
    }
    previousRunLoop = (previousRunLoop > 15)? 0 : previousRunLoop +1;
    if (millis() - previousProgramMillis > 5000){
      previousProgramMillis = millis();
    }else if (millis() - previousProgramMillis > 2500){ //A
       for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
        if (isvalueinarray(pixel,elanaLeds2,sizeof(elanaLeds2)/4) |
            isvalueinarray(pixel,elanaLeds4,sizeof(elanaLeds4)/4)
          ){
          virtualLeds[pixel] = CHSV( twoColorHue[1], 255, ledBrightness);
        }else{
          virtualLeds[pixel] = CHSV( twoColorHue[0], 255, ledBrightness);
        }
      }
    }else { // N
      for( int pixel = elenaStartLed; pixel < NUM_LEDS; pixel++) {  
        if (isvalueinarray(pixel,elanaLeds2,sizeof(elanaLeds2)/4) |
            isvalueinarray(pixel,elanaLeds4,sizeof(elanaLeds4)/4)
          ){
          virtualLeds[pixel] = CHSV( twoColorHue[0], 255, ledBrightness);
        }else{
          virtualLeds[pixel] = CHSV( twoColorHue[1], 255, ledBrightness);
        }
      }
    }
  }
}
void oneColor() {
  virtualLedsSpeed = 0;
  for( int pixel = 0; pixel < NUM_LEDS; pixel++) {  
    if(oneColorHue<0){
      virtualLeds[pixel] = CRGB(ledBrightness,ledBrightness,ledBrightness);
    }else{
      virtualLeds[pixel] = CHSV( oneColorHue, 255, ledBrightness);
    }
  }
}
void twoColor() {
  virtualLedsSpeed = 0;
  for( int pixel = 0; pixel < NUM_LEDS; pixel++) {  
    if (!isvalueinarray(pixel,elanaLeds,sizeof(elanaLeds)/4)){
      if(twoColorHue[0]<0){
        virtualLeds[pixel] = CRGB(ledBrightness,ledBrightness,ledBrightness);
      }else{
        virtualLeds[pixel] = CHSV( twoColorHue[0], 255, ledBrightness);
      }
    }else{
      if(twoColorHue[1]<0){
        virtualLeds[pixel] = CRGB(ledBrightness,ledBrightness,ledBrightness);
      }else{
        virtualLeds[pixel] = CHSV( twoColorHue[1], 255, ledBrightness);
      }
    }
  }
}
