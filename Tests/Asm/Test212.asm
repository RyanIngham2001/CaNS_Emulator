LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
LODS #0xAA54
LD #0x0032
MVI B,#0x006F
CMP A,B
CLE J506
LD #0x000E
PSH A
PSH A
J506:
POP A
ST 0x01FB
LD #0x007A
MVI B,#0x008F
CMP A,B
CLE J508
LD #0x00FB
PSH A
PSH A
J508:
POP A
ST 0x01FD
LD #0x0054
MVI B,#0x0042
CMP A,B
CLE J510
LD #0x004B
PSH A
PSH A
J510:
POP A
ST 0x01FF
LD #0x00E7
MVI B,#0x00ED
CMP A,B
CLE J512
LD #0x005A
PSH A
PSH A
J512:
POP A
ST 0x0201
LD #0x00BD
MVI B,#0x00D2
CMP A,B
CLE J514
LD #0x00D1
PSH A
PSH A
J514:
POP A
ST 0x0203
LD #0x0060
MVI B,#0x00F4
CMP A,B
CLE J516
LD #0x00F7
PSH A
PSH A
J516:
POP A
ST 0x0205
WAI 
data506: dw J506
data508: dw J508
data510: dw J510
data512: dw J512
data514: dw J514
data516: dw J516
