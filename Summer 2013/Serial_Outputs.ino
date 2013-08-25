void printMagneticData()
{
  Serial.print("Mag. x: "); Serial.print(mx); Serial.print("\t");
  Serial.print("Mag. y: "); Serial.print(my); Serial.print("\t");
  Serial.print("Mag. z: "); Serial.print(mz); Serial.print("\t");
}

void printAccelerationData()
{
  // Prints raw acceleration data and calculated angles in m/s^2
  Serial.print("Acc. X: "); Serial.print(ax); Serial.print("\t");
  Serial.print("Acc. Y: "); Serial.print(ay); Serial.print("\t");
  Serial.print("Acc. Z: "); Serial.print(az); Serial.print("\t");
  Serial.print("Acc. R: "); Serial.print(ar); Serial.print(" m/s^2 "); Serial.print("\t");
  Serial.print("thetaX: "); Serial.print(thetaX); Serial.print("\t");
  Serial.print("thetaY: "); Serial.print(thetaY); Serial.print("\t");
  Serial.print("thetaZ: "); Serial.print(thetaZ); Serial.print("\t");
}

void printGyroscopeData()
{
  Serial.print("Gyro X: ");  Serial.print(gx);  //they divided x, y, z by 114 to "reduce noise"
  Serial.print(" Gyro Y: "); Serial.print(gy);
  Serial.print(" Gyro Z: "); Serial.print(gz); Serial.print(" degrees per second"); Serial.print("\t");
}

void printGyroscopeAngles()
{
  Serial.print("GyroXAngle: "); Serial.print(GyroXAngle); Serial.print("\t");
  Serial.print("GyroYAngle: "); Serial.print(GyroYAngle); Serial.print("\t");
  Serial.print("GyroZAngle: "); Serial.print(GyroZAngle); Serial.print(" degrees"); Serial.print("\t");
}

void printHeading()
{
  // Calculate heading from magnetometer
  Serial.print("Heading: "); Serial.print(heading); Serial.print("\t");
}

void printTiltHeading()
{
  Serial.print("Tilt Heading: "); Serial.print(tiltheading); Serial.print("\t");
}

void printFilteredAngles()
{
  Serial.print("X: "); Serial.print(filteredAngleX); Serial.print("\t");
  Serial.print("Y: "); Serial.print(filteredAngleY); Serial.print("\t");
}

void printFilteredYaw()
{
  Serial.print("Heading: "); Serial.print(filteredYaw); Serial.print("\t");
}

void printKalmanAngles()
{
  Serial.print("Kalman pitch: "); Serial.print(pitch); Serial.print("\t");
  Serial.print("Kalman roll: "); Serial.print(roll); Serial.print("\t");
}

void printTemperature()
{
  Serial.print("Temperature: "); Serial.println(t); Serial.print("\t");
}
