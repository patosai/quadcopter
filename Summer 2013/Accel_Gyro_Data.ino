void getAccelValues()
{
  sensors_event_t aevent;
  accel.getEvent(&aevent); 
  
  ax = aevent.acceleration.x;
  ay = aevent.acceleration.y;
  az = aevent.acceleration.z;

  ar = sqrt(ax*ax + ay*ay + az*az);
  
  thetaX = 90.0 - (acos(ax/ar)*(180/PI));
  thetaY = 90.0 - (acos(ay/ar)*(180/PI));
  thetaZ = acos(az/ar)*(180/PI);
}

void getGyroValues()
{
  byte MSB, LSB;

  MSB = readI2C(0x29);
  LSB = readI2C(0x28);
  int x = ((MSB << 8) | LSB); //roll
  gx = ((float(x))/gscale) + 1.14;

  MSB = readI2C(0x2B);
  LSB = readI2C(0x2A);
  int y = ((MSB << 8) | LSB); //pitch
  gy = -(((float(y))/gscale));

  MSB = readI2C(0x2D);
  LSB = readI2C(0x2C);
  int z = ((MSB << 8) | LSB); //yaw
  gz = -(((float(z))/gscale) + 0.47);
}

void getMagValues()
{
  sensors_event_t mevent;
  mag.getEvent(&mevent);
  
  mx = mevent.magnetic.x;
  my = mevent.magnetic.y;
  mz = mevent.magnetic.z;
  
  heading = (atan2(my,mx))*(180/PI);
  if (heading < 0)
  {
    heading += 360;
  }
}

void getTiltHeading()
{
  float Mxc = (mx-Mminx) / (Mmaxx-Mminx) *2 - 1;
  float Myc = (my-Mminy) / (Mmaxy-Mminy) *2 - 1;
  float Mzc = (mz-Mminz) / (Mmaxz-Mminz) *2 - 1;
  
  float Mxh = Mxc*cos(pitch)+Mzc*sin(pitch);
  float Myh = Mxc*sin(roll)*sin(pitch)+Myc*cos(roll)-Mzc*sin(roll)*cos(pitch);

  tiltheading = atan2(Myh,Mxh)*(180/PI);
  if (tiltheading < 0)
  {
    tiltheading += 360;
  }
}
  
void getTemp()
{
  byte temp;
  
  temp = readI2C(0x26);
  t = (temp << 8 | temp);
}

int readI2C(byte regAddr)
{
  Wire.beginTransmission(Addr);
  Wire.write(regAddr);                // Register address to read
  Wire.endTransmission();             // Terminate request
  Wire.requestFrom(Addr, 1);          // Read a byte 
  
  while(!Wire.available()) { };       // Wait for receipt
  return(Wire.read());                // Get result
}

void writeI2C (byte regAddr, byte val)
{
  Wire.beginTransmission(Addr);
  Wire.write(regAddr);
  Wire.write(val);
  Wire.endTransmission();
}
