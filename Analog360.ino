

void analog360initialize()
{
  for (int i = 0; i< analogObjectsQuantity ; i++)
  {
    analog[i].setAnalogResolution(analogResolution);
  }
  calculateRads();
  
  for (int i = 0; i< analogObjectsQuantity/2 ; i++)
  {
    lastrad[i] = rad[i];
  }
  
}


void analog360loop()
{
    
}


void calculateRads()
{
  for (int i = 0; i< analogObjectsQuantity ; i++)
  {
    analog[i].update();
  }
  
  for (int i = 0; i< analogObjectsQuantity/2 ; i++)
  {
    rad[i] = atan2(analog[i*2].getValue() - analogResolution/2 - 1, analog[i*2+1].getValue() - analogResolution/2 - 1) * precision / 3.14159265359;
  }
  
}

void calculateRadsteps()
{
  for (int i = 0; i< analogObjectsQuantity/2 ; i++)
  {
    radstep[i] = lastrad[i] - rad[i];
    if (radstep[i] >  300) radstep[i] =  radstep[i] - 360;  // this one is for looping
    if (radstep[i] < -300) radstep[i] =  radstep[i] + 360;
  }
}


    





















//Analog functions
// analog.update(); // on each loop update analog and denoise
//if(analog.hasChanged()) { // if analog has changed execute update 
//    Serial.print(analog.getValue()); //the filtered analog value
//    Serial.print(analog.getRawValue()); //the raw analog read value
//  }
 
