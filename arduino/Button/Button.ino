#include <Bounce.h>

const int midiChannel = 1;

// Create Bounce objects for the buttom.
// The Bounce object eliminates contact chatter or "switch bounce".
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

  // MIDI Controllers should discard incoming MIDI messages.
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
