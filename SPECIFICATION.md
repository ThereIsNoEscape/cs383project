# Specification for Qt Tower of Lights

## Background

### Client

Bob Rinker (rinker [at] uidaho [dot] edu)

### Frames

40 "Pixels" per Frame
- 4 Pixels wide
- 10 Pixels tall

16M colors per Pixel (24-bit)

40 Frames per Second
- 25 milliseconds per Frame

### Sound Thread
.WAV file

### Animation File
.TAN file "Tower ANimation"

## Tower Animator Program

Old Version located at www2.cs.uidaho.edu/~rinker

> Just make it easier to use.  Anything else is optional.

Current Frame
- Display Frame
- Display Border
- Display Time Stamp
- Edit Frame
Effects
- Fade
- Character Generation
- Random
- Fill
- Comets
- Dual Sine Wave
- Sine/Cosine Wave
- Tweening?
- Menu of Effects
  - Presets?
  - Timing

## TAN File Format
header
 version - 0.3
 bumperframe sans timestamp, i.e. frame shown before song starts/after song ends
 framecount height width
body
 frame 0
 frame 1
 frame 2
 ...
 frame n

frame:
 timestamp
 r00 g00 b00 r10 g10 b10 ...
 r01 g01 b01 ... ... ... ... -> width
 ... ... ... ... ... ... ...
  |
  V
  height
 next frame
