#include <Bounce.h>

const int midiChannel = 1;
const int faderMidiCtrlNumber = 11; // 11 = volume/expression

int oldFaderValue = -1;
int newFaderValue = -1;
elapsedMillis elapsedTime = 0;
Bounce button0 = Bounce(0, 5);

void setup() {
    pinMode(0, INPUT_PULLUP);
}

void loop() {
  // Update the buttons (as fast as possible, no delays)
  button0.update();

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  if (button0.fallingEdge()) {
    usbMIDI.sendNoteOn(60, 99, midiChannel);  // 60 = C4
  }

  // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  if (button0.risingEdge()) {
    usbMIDI.sendNoteOff(60, 0, midiChannel);  // 60 = C4
  }
  
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
