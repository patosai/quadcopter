void ESCWarmUp()
{
  esc1.write(10);
  esc2.write(10);
  esc3.write(10);
  esc4.write(10);
  delay(7000);
}


void writeServoValues()
{
  esc1.write(throttle + nsOutput + ewOutput - yawCommand);
  esc2.write(throttle - nsOutput + ewOutput + yawCommand);
  esc3.write(throttle - nsOutput - ewOutput - yawCommand);
  esc4.write(throttle + nsOutput - ewOutput + yawCommand);
}
