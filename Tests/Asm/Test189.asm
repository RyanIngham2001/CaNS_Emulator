LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
LODS #0xAA54
JPR J506
ST 0x01FA
JPR J507
ST 0x01FB
JPR J508
ST 0x01FC
JPR J509
ST 0x01FD
JPR J510
ST 0x01FE
JPR J511
ST 0x01FF
JPR J512
ST 0x0200
JPR J513
ST 0x0201
JPR J514
ST 0x0202
JPR J515
ST 0x0203
JPR J516
ST 0x0204
JPR J517
ST 0x0205
WAI 
J506:
LD #0x00CB
MVI B,#0x0015
CMP A,B
RTN
LD #0x0024
RTN
WAI 
J507:
LD #0x00C9
MVI B,#0x00DA
CMP A,B
RTN
LD #0x0003
RTN
WAI 
J508:
LD #0x004F
MVI B,#0x006F
CMP A,B
RTN
LD #0x002E
RTN
WAI 
J509:
LD #0x0010
MVI B,#0x006C
CMP A,B
RTN
LD #0x0040
RTN
WAI 
J510:
LD #0x00D0
MVI B,#0x0061
CMP A,B
RTN
LD #0x00FD
RTN
WAI 
J511:
LD #0x00D8
MVI B,#0x00A0
CMP A,B
RTN
LD #0x005D
RTN
WAI 
J512:
LD #0x004B
MVI B,#0x0035
CMP A,B
RTN
LD #0x006F
RTN
WAI 
J513:
LD #0x000E
MVI B,#0x0004
CMP A,B
RTN
LD #0x00DC
RTN
WAI 
J514:
LD #0x005A
MVI B,#0x007B
CMP A,B
RTN
LD #0x0081
RTN
WAI 
J515:
LD #0x00AA
MVI B,#0x0033
CMP A,B
RTN
LD #0x0064
RTN
WAI 
J516:
LD #0x0038
MVI B,#0x00D6
CMP A,B
RTN
LD #0x00C0
RTN
WAI 
J517:
LD #0x00F5
MVI B,#0x0018
CMP A,B
RTN
LD #0x004B
RTN
WAI 
