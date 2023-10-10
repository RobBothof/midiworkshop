
const int midiChannel = 1;
const int faderMidiCtrlNumber = 11; // 11 = volume/expression

int oldFaderValue = -1;
int newFaderValue = -1;
elapsedMillis elapsedTime = 0;

void setup() {
}

void loop() {
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (elapsedTime >= 20) {
    elapsedTime = 0;
    
    newFaderValue = analogRead(A9) / 8;
    if (newFaderValue != oldFaderValue) {
      usbMIDI.sendControlChange(faderMidiCtrlNumber, newFaderValue, midiChannel);
      oldFaderValue = newFaderValue;
    }  
   }

  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
