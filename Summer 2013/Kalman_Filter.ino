void getKalmanAngles()
{
  pitch = kalmanX.getAngle(thetaX, gy, time2) + 3.32;
  roll = kalmanY.getAngle(thetaY, gx, time2) + 0.86;
}

