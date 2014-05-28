#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

Adafruit_LSM303_Accel accel = Adafruit_LSM303_Accel(54321);
Adafruit_LSM303_Mag mag = Adafruit_LSM303_Mag(12345);

int Addr = 105;       // I2C address of gyro
int x, y, z;

void setup() 
{
  Wire.begin();
  writeI2C(CTRL_REG1, 0x1F);    // Turn on all axes, disable power down
  writeI2C(CTRL_REG3, 0x08);    // Enable control ready signal
  writeI2C(CTRL_REG4, 0x80);    // Set scale (500 deg/sec)
  writeI2C(CTRL_REG5, 0x02);    // Enables low pass filter
  delay(100);

  setupSerialData();
}

void loop() 
{
  loopSerialData();
}

void getGyroValues() //puts gyro readings into variables X, Y, and Z for those axes
{
  byte MSB, LSB;

  MSB = readI2C(0x29);
  LSB = readI2C(0x28);
  x = ((MSB << 8) | LSB);

  MSB = readI2C(0x2B);
  LSB = readI2C(0x2A);
  y = ((MSB << 8) | LSB);

  MSB = readI2C(0x2D);
  LSB = readI2C(0x2C);
  z = ((MSB << 8) | LSB);
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

void setupSerialData()
{
  Serial.begin(9600);
  Serial.println("Accelerometer Test and Magnetometer Test"); Serial.println("");
  if(!accel.begin() || !mag.begin())
  {
    Serial.println("LSM303 not detected.");
    while(1);
  }
}

void loopSerialData() //prints accelerometer, magnetic, and gyro data into serial monitor
{
  sensors_event_t aevent;
  sensors_event_t mevent;
  accel.getEvent(&aevent);
  mag.getEvent(&mevent);

  float heading = (atan2(mevent.magnetic.y,mevent.magnetic.x) * 180) / 3.14159;
  if (heading < 0)
  {
    heading = 360 + heading;
  }

  Serial.print("Compass Heading: ");
  Serial.print(heading); 
  Serial.print(" ");
  Serial.print("X: "); Serial.print(aevent.acceleration.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print(aevent.acceleration.y); Serial.print(" ");
  Serial.print("Z: "); Serial.print(aevent.acceleration.z); Serial.print(" ");
  Serial.print("m/s^2 ");Serial.print(" ");

  getGyroValues();       // Dividing by 114 reduces noise
  Serial.print("Gyro X:");  Serial.print(x / 114);  
  Serial.print(" Gyro Y:"); Serial.print(y / 114);
  Serial.print(" Gyro Z:"); Serial.println(z / 114); 
  delay(500);
}
