LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
LODS #0xAA54
LD #0x00D9
MVI B,#0x0048
CMP A,B
CPL J506
LD #0x0040
PSH A
PSH A
J506:
POP A
ST 0x01FB
LD #0x00AD
MVI B,#0x007A
CMP A,B
CPL J508
LD #0x00F1
PSH A
PSH A
J508:
POP A
ST 0x01FD
LD #0x0028
MVI B,#0x00E3
CMP A,B
CPL J510
LD #0x0073
PSH A
PSH A
J510:
POP A
ST 0x01FF
LD #0x0038
MVI B,#0x0097
CMP A,B
CPL J512
LD #0x0021
PSH A
PSH A
J512:
POP A
ST 0x0201
LD #0x0010
MVI B,#0x007B
CMP A,B
CPL J514
LD #0x0013
PSH A
PSH A
J514:
POP A
ST 0x0203
LD #0x009A
MVI B,#0x0078
CMP A,B
CPL J516
LD #0x0062
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
