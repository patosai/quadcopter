//middle black = left/right on left joystick
//middle white = up/down on left joystick
//bottom red = up/down on right joystick
//bottom black = left/right on right joystick

int zbee; //secondary counter
int j;
const int xbee = 2000;      //primary counter
const float xbee2 = 2000.0; //float version of primary counter

void InputControls()
{
  throttle5 = throttle4;
  throttle4 = throttle3;
  throttle3 = throttle2;
  throttle2 = throttle1;
  throttle1 = throttle;
  while (j < xbee && zbee < 50)
  {
    pitchinputhelper += digitalRead(10);
    rollinputhelper += digitalRead(11);
    throttlehelper += digitalRead(9);
    ch5helper += digitalRead(12);
    ch6helper += digitalRead(13);
    j++;
    zbee++;
  }
  zbee = 0;
  if (j >= xbee)
  {
    pitchInput = (pitchinputhelper-180)/4;
    rollInput = (rollinputhelper-180)/4;
    throttle = (throttle + throttle1 + throttle2 + throttle3 + throttle4 + throttle5 + 300 - throttlehelper)/7;
    ch5 = ch5helper;
    ch6 = ch6helper;
    j = 0;
    pitchinputhelper = 0.0;
    rollinputhelper = 0.0;
    throttlehelper = 0.0;
    ch5helper = 0.0;
    ch6helper = 0.0;
  }
}
