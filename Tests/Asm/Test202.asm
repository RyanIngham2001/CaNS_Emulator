LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
LD #0x00C7
MVI B,#0x0093
CMP A,B
BHI J506
LD #0x0036
J506:
ST 0x01FA
LD #0x00CD
MVI B,#0x005C
CMP A,B
BHI J507
LD #0x003F
J507:
ST 0x01FB
LD #0x00D0
MVI B,#0x0057
CMP A,B
BHI J508
LD #0x002D
J508:
ST 0x01FC
LD #0x0045
MVI B,#0x0054
CMP A,B
BHI J509
LD #0x00F4
J509:
ST 0x01FD
LD #0x0038
MVI B,#0x004A
CMP A,B
BHI J510
LD #0x00C4
J510:
ST 0x01FE
LD #0x0073
MVI B,#0x00A8
CMP A,B
BHI J511
LD #0x008C
J511:
ST 0x01FF
LD #0x00F7
MVI B,#0x00AE
CMP A,B
BHI J512
LD #0x009C
J512:
ST 0x0200
LD #0x006C
MVI B,#0x0056
CMP A,B
BHI J513
LD #0x00C6
J513:
ST 0x0201
LD #0x00BD
MVI B,#0x00F0
CMP A,B
BHI J514
LD #0x005B
J514:
ST 0x0202
LD #0x001E
MVI B,#0x0083
CMP A,B
BHI J515
LD #0x009D
J515:
ST 0x0203
LD #0x000A
MVI B,#0x00E1
CMP A,B
BHI J516
LD #0x00CC
J516:
ST 0x0204
LD #0x00B2
MVI B,#0x0028
CMP A,B
BHI J517
LD #0x0047
J517:
ST 0x0205
WAI 
