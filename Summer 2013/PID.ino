PID nsPID(&pitch,&nsOutput,&pitchInput,Kp,Ki,Kd,DIRECT);
PID ewPID(&roll,&ewOutput,&rollInput,Kp,Ki,Kd,DIRECT);

void setupPIDs()
{
  nsPID.SetMode(AUTOMATIC);
  ewPID.SetMode(AUTOMATIC);
  nsPID.SetSampleTime(10);
  ewPID.SetSampleTime(10);
  nsPID.SetOutputLimits(-100,100);
  ewPID.SetOutputLimits(-100,100);
}

void computePIDs()
{
  nsPID.Compute();
  ewPID.Compute();
}

void PIDOutputCorrection()
{
  nsOutput /= 7.0;
  ewOutput /= 7.0;
}
