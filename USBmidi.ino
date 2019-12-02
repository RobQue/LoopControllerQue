void pitchBend(byte channel, int bit14Pitch) 
{
  midiEventPacket_t pitchBend = {0x0E, 0xE0 | channel, bit14Pitch % 128, bit14Pitch / 128};
  MidiUSB.sendMIDI(pitchBend);
  MidiUSB.flush(); // < important to send imediatelly
}

int receivePitchBend(byte channel)
{
  int pitchBendVal = 0;
  byte usbmidiHeader = 0x0E; //pitch bend command
  byte midiCh = 0xE0 | channel;
  
midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      
//      Serial.print("Received: ");
//      Serial.print(rx.header, HEX);
//      Serial.print("-");
//      Serial.print(rx.byte1, HEX);
//      Serial.print("-");
//      Serial.print(rx.byte2, HEX);
//      Serial.print("-");
//      Serial.println(rx.byte3, HEX);

      if (rx.header == usbmidiHeader && rx.byte1 == midiCh)
      {
        pitchBendReceived = HIGH;
        pitchBendVal = rx.byte3*128 + rx.byte2;
      }
      
      //Serial.println(pitchBendVal);
    }
  } while (rx.header != 0); 
  
return  pitchBendVal;
}

void receiveMIDI()
{
midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
    }
  } while (rx.header != 0);
}


//Unused ones------------------------------------------------------

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).


// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void noteOn(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) 
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void pitchBend(byte channel, byte pitch, byte pitchPrecise) 
{
  midiEventPacket_t pitchBend = {0x0E, 0xE0 | channel, pitch, pitchPrecise};
  MidiUSB.sendMIDI(pitchBend);
}
