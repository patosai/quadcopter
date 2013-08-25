void filterAngles()
{
  GyroYAngle = gx*(time2);
  GyroXAngle = gy*(time2);
  filteredAngleX = GyroPercentage*(filteredAngleX + GyroXAngle) + (1-GyroPercentage)*(thetaX);
  filteredAngleY = GyroPercentage*(filteredAngleY + GyroYAngle) + (1-GyroPercentage)*(thetaY);
}

void filterYaw()
{
  GyroZAngle = -(gz*(time2));
  filteredYaw = GyroPercentage*(filteredYaw + GyroZAngle) + (1-GyroPercentage)*(heading);
  if (filteredYaw < 0)
  {
    filteredYaw += 360;
  }
  if (filteredYaw > 360)
  {
    filteredYaw -= 360;
  }
}

