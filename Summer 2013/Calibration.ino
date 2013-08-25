int i;
int zeelol = 500;       //THE HIGHER I AM, THE MORE ACCURATE, BUT I TAKE LONGER TO FINISH

void Calibrate()
{
  if (i < zeelol)
  {
    gx1 += pitch;
    gy1 += roll;
    //gz1 += gz;
    i++;
  }
  if (i >= zeelol)
  {
    gx1 /= float(zeelol);
    gy1 /= float(zeelol);
    //gz1 /= float(zeelol);
    Serial.print(gx1); Serial.print("\t");
    Serial.print(gy1); Serial.print("\t");
    //Serial.print(gz1);
    while(true)
      {}
  }
}
