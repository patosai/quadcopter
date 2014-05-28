#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Kalman.h>
#include <PID_v1.h>
#include <Servo.h>
#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23

Adafruit_LSM303_Accel accel = Adafruit_LSM303_Accel(54321);
Adafruit_LSM303_Mag mag = Adafruit_LSM303_Mag(12345);

Kalman kalmanX;
Kalman kalmanY;

//*******************************************************************//
double Kp = 1.4;                           //
double Ki = 0;                           //
double Kd = 0;                           //
int SampleTime = 10; //PID is calculated every 10ms
//*******************************************************************//

unsigned long TIMER;
unsigned long lastTime1;
unsigned long time;
float time2;

// CONTROL INPUTS /////////////////////
double pitchInput;
double rollInput;
double pitchinputhelper;
double rollinputhelper;
double yawCommand;
double throttle;
double throttlehelper;

double ch5;
double ch5helper;
double ch6;
double ch6helper;
///////////////////////////////////////

double throttle1;
double throttle2;
double throttle3;
double throttle4;
double throttle5;

// VARIABLES FOR PID LOOP ////////////////////
                                            //
double nsOutput;                            //
double ewOutput;                            //
//////////////////////////////////////////////
// VARIABLES FOR ACCELEROMETER ///////////////
float ax, ay, az, ar;                       //
float thetaX, thetaY, thetaZ;               //
//////////////////////////////////////////////
// VARIABLES FOR GYROSCOPE                  //
int Addr = 105;      // I2C address of gyro //
float gx, gy, gz, t;                        //
float gx1, gy1, gz1;
const float gscale = 14.2857142;            //
//////////////////////////////////////////////
// VARIABLES FOR MAGNETOMETER               //
float mx, my, mz, heading;                  //
float tiltheading;                          //
float Mminx = -38.45, Mminy = -63.27, Mminz = -53.57;
float Mmaxx = 57.00, Mmaxy = 45.51, Mmaxz = 45.51;
//////////////////////////////////////////////

// COMPLEMENTARY FILTER ///////////////
const float GyroPercentage = 0.97;   // between 0.9 and 1.0
float dt = 0.01;                     //
float GyroXAngle;                    //
float GyroYAngle;                    //
float GyroZAngle;                    //
float filteredAngleX;                //
float filteredAngleY;                //
float filteredYaw;                   //
///////////////////////////////////////

// KALMAN FILTER //////////////////////
double pitch;                        //
double roll;                         //
double yaw;                          //
///////////////////////////////////////

Servo esc1; // top left
Servo esc2; // bottom left
Servo esc3; // bottom right
Servo esc4; // top right

void setup() 
{
  Wire.begin();
  writeI2C(CTRL_REG1, 0b00001111);
  writeI2C(CTRL_REG2, 0b00000000);
  writeI2C(CTRL_REG3, 0b00001000);
  writeI2C(CTRL_REG4, 0b00110000);
  delay(100);
  
  
  while(!accel.begin() || !mag.begin())
  {
 
  }

  esc1.attach(7);
  esc2.attach(6);
  esc3.attach(5);
  esc4.attach(4);
  
  setupPIDs();
  
  ESCWarmUp();
  throttle = 60.0;
  throttle1 = 60.0;
  throttle2 = 60.0;
  throttle3 = 60.0;
  throttle4 = 60.0;
  throttle5 = 60.0;
}

void loop() 
{
  TIMER = millis();
  getAccelValues();              // Gets acceleration thetas from the accelerometer 
  getMagValues();                // Gets heading from magnetometer
  
  time = (micros() - lastTime1);   // Used for gyroscope angle calculation
  getGyroValues();                 // Does what it does best
  lastTime1 = micros();            // Also used for gyro angle calculation
  time2 = float(time)/1000000.0;

  getKalmanAngles();            // Kalman filter; calculates pitch and roll. currently defunct.

  computePIDs();                // Calculates PIDs for pitch, roll, and yaw
  PIDOutputCorrection();        // Converts PID output to a servo control
  writeServoValues();           // Uses PID values to write a servo value to the ESC
  
  //InputControls();              // Gets inputs from receiver/controller
  
  if (abs(thetaZ) > 160.0)      // FUSE 1
  {
    esc1.write(10);
    esc2.write(10);
    esc3.write(10);
    esc4.write(10);
    while(true)
      {}
  }
  /*
  while (ch6 > 200)             // FUSE 2
  {
    esc1.write(10);
    esc2.write(10);
    esc3.write(10);
    esc4.write(10);
    InputControls(); 
  }
  */
}
