LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
LODS #0xAA54
LD #0x006E
MVI B,#0x0083
CMP A,B
CVC J506
LD #0x00B2
PSH A
PSH A
J506:
POP A
ST 0x01FB
LD #0x00F7
MVI B,#0x00CF
CMP A,B
CVC J508
LD #0x0045
PSH A
PSH A
J508:
POP A
ST 0x01FD
LD #0x00C5
MVI B,#0x0003
CMP A,B
CVC J510
LD #0x0066
PSH A
PSH A
J510:
POP A
ST 0x01FF
LD #0x00A0
MVI B,#0x00F4
CMP A,B
CVC J512
LD #0x0091
PSH A
PSH A
J512:
POP A
ST 0x0201
LD #0x004A
MVI B,#0x007B
CMP A,B
CVC J514
LD #0x00B6
PSH A
PSH A
J514:
POP A
ST 0x0203
LD #0x00DD
MVI B,#0x00DE
CMP A,B
CVC J516
LD #0x005F
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
