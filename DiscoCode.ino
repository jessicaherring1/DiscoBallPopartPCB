//POPART PCB DISCO BALL

//buttons
#include <Bounce2.h>
#define BOUNCE_PIN 1
boolean isButton = false;
Bounce bounce = Bounce();

//neopixels
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(27, 0);

//frames
int numGrid = 27;
int numFrames = 2;
int j = 0;

char index[27] {
  0,
  1, 2, 3,
  4, 5,  6,  7,
  8, 9, 10, 11,
  12, 13, 14, 15,
  16, 17, 18, 19,
  20, 21, 22, 23,
  24, 25, 26,
};

char colors[3][3] {
  {0, 255, 255},
  {255, 0, 255},
  {0, 0, 0},
};

char frames[2][27] {
  {
    1,
    1, 0, 1,
    0, 1, 0, 1,
    1, 0, 1, 0,
    0, 1, 0, 1,
    1, 0, 1, 0,
    0, 1, 0, 1,
    1, 0, 1
  },
  {
    0,
    0, 1, 0,
    1, 0, 1, 0,
    0, 1, 0, 1,
    1, 0, 1, 0,
    0, 1, 0, 1,
    1, 0, 1, 0,
    0, 1, 0
  },

};

//programatic
int i;
int r;
int g;
int b;

//extra
boolean isOn;
boolean start;

//timer
unsigned long startTime = millis();
unsigned long endTime;
long interval = 200;
long interval2 = 20;
long interval3 = 150;

//switch case
int state = 3;


void setup() {
  // strip
  strip.begin();
  strip.clear();
  strip.show();

  // button
  bounce.attach( BOUNCE_PIN, INPUT );
  bounce.interval(5);
}

void loop() {
  button();

  switch (state) {
    case 0:
      break;

    case 1:
      framesFunc();
      break;

    case 2:
      programmatic();
      break;

    case 3:
      extra();
      break;
  }
}

void button() {
  bounce.update();

  if (bounce.changed()) {
    int debouncedInput = bounce.read();

    if (debouncedInput == HIGH) {
      strip.clear();
      strip.show();
      state = (state + 1) % 4;
    }
  }
}


void framesFunc() {
  endTime = millis();
  if (endTime - startTime >= interval) {
    if (j < numFrames - 1) {
      j++;
    } else {
      j = 0;
    }
    startTime = millis();
  }
  int whichFrame = j;
  for (int i = 0; i < numGrid; i++) {
    int whichLED  = i;
    int whichIndex = index[whichLED];
    int whichColor = frames[whichFrame][whichLED];

    int r = colors[whichColor][0];
    int g = colors[whichColor][1];
    int b = colors[whichColor][2];
    strip.setPixelColor(whichIndex, r, g, b);
  }
  strip.show();
}


void programmatic() {
  endTime = millis();
  //chooses a new neopixel index and color value every interval
  if (endTime - startTime >= interval2) {
    i = random(27);
    r = random(255);
    g = random(255);
    b = random(255);
    startTime = millis();
  }
  strip.setPixelColor(i, r, g, b);
  strip.show();
}


void extra() {
  //turns all of the neopixels blue only once at the very beggining
  while (start) {
    for (int i = 0; i < 27; i++) {
      strip.setPixelColor(i, 0, 0, 255);
      strip.show();
    }
    start = false;
  }

  endTime = millis();
  //updates the isOn boolean every interval
  if (endTime - startTime >= interval3) {
    isOn = !isOn;
    startTime = millis();
  }
  int i = random(27);
  //sets the pixel to a random color
  if (isOn) {
    r = random(255);
    g = random(255);
    b = random(255);
    strip.setPixelColor(i, r, g, b);
    strip.show();
    isOn = false;
  } 
  //resets the same pixel back to blue
  else {
    strip.setPixelColor(i, 0, 0, 255);
  }
}
