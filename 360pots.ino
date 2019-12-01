

//int precision=1;
//int rad[6];
//int lastrad[6];
int potBank;

float ReadPotRad (int x, int y, int precisioun) // int x and int y are the raw analog readings of doublepot, precision can by any size around 1608 is native. 350 could srand for degrees.
{
  float rad = atan2(x-511, y-511) * precision / 3.14159265359  ; // calculation of pot position in radiants x precision.
  return rad;
}

void potFromPotSetup() // this was as inittialization of variables from the reading int the setup but since in this case reading is happening after setup, it should be ran once and from variables stored in muxBank. 
{
    rad[0] = ReadPotRad (analogRead(A2), analogRead(A3), precision); 
    rad[1] = ReadPotRad (analogRead(A0), analogRead(A1), precision);

  //for(int i=0; i<sizeof( lastrad ) / sizeof( float ); i++) lastrad[i] = rad[i];
}

void potFromPotLoop() // from loop 
{
  rad[0] = ReadPotRad (analogRead(A2), analogRead(A3), precision); 
  rad[1] = ReadPotRad (analogRead(A0), analogRead(A1), precision);

    
    int i = rad[0]/50+5;
   // potBank += potChange (lastrad[1], rad[1], precision);
  
  //for(int i=0; i<sizeof( lastrad ) / sizeof( float ); i++) lastrad[i] = rad[i];
}

// this one takes inputs processed by ReadPotRad function( last RAD value, current RAD Value, Precision would be 16383 as well ReadPotRad should have the same precision ) 
// it outputs the amount of steps changed since last time. Then after that change should be filtered, added or substracted from bank value which is received from midi input.
float potChange (float vOLD, float vNEW, int vPRECISION) // tab was called relative pot mapping // dual pot maping. ino from electronics folder in Controller Q is the originalle 
{
  float output = 0;
  
  if (vOLD > 0 && vNEW < 0) 
  {
    output = -2*vPRECISION+vOLD-vNEW;

    return output;
  }
  
  if (vOLD < 0 && vNEW > 0) 
  {
    output = 2*vPRECISION+vOLD-vNEW;

    return output;
  }
  else
    output = vNEW - vOLD;

    return output;
  
}

void rotaryPot() // function for 360 deg rotary as potentiometer
{
  
}

void rotaryEncoder() // function to use rotary as encoder  - this is pretty useless as it can only be used as CC (maybe good because you can chnage precision in software instead)
{
  
}

//// !!!! implement pointers in order for this function could directly manipulate variable of lastmuxVal which is stored outside  !!!!
// http://forum.arduino.cc/index.php?topic=223029.msg1617034#msg1617034

int noiseReduction (int& lastmuxVal, int muxVal ) // for loop runs outside, reduces noise by using delta +/- 2 and mapping it to 14 bit from 10 bit by bitshift.
  {
    if (lastmuxVal +1 != muxVal && lastmuxVal -1 != muxVal && lastmuxVal != muxVal && lastmuxVal +2 != muxVal && lastmuxVal -2 != muxVal) // do not send if value have changed only +- 1  = prevent sending all the time // 
    {
    lastmuxVal = muxVal; //save last reading
    return muxVal << 4 ;   // return as well maps from 10 bit to 14 bit
    }
    
    else if (lastmuxVal != muxVal && muxVal == 0) // send zero for sure, once
    {
    lastmuxVal = muxVal; //save last reading
    return muxVal << 4 ;   // as well maps from 10 bit to 14 bit
    }
    
    else if (lastmuxVal != muxVal && muxVal == 1023) // send maximum for sure, once
    {
    
    lastmuxVal = muxVal; //save last reading                       
    return 16383 ;   // as well maps from 10 bit to 14 bit
    }
  }
