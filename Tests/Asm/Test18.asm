LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI H,#0x00AA
MVI L,#0x0034
LD #0x00E1
MOVE M,A
LD #0x0054
SBC A,M
ST 0x01FA
MVI H,#0x00AA
MVI L,#0x00F7
LD #0x00BE
MOVE M,A
LD #0x001C
SBC A,M
ST 0x01FB
MVI H,#0x00AA
MVI L,#0x00D3
LD #0x008F
MOVE M,A
LD #0x00A4
SBC A,M
ST 0x01FC
MVI H,#0x00AA
MVI L,#0x005F
LD #0x00D0
MOVE M,A
LD #0x0055
SBC A,M
ST 0x01FD
MVI H,#0x00AA
MVI L,#0x00A1
LD #0x0004
MOVE M,A
LD #0x0026
SBC A,M
ST 0x01FE
MVI H,#0x00AA
MVI L,#0x00D5
LD #0x005A
MOVE M,A
LD #0x00AA
SBC A,M
ST 0x01FF
MVI H,#0x00AA
MVI L,#0x002A
LD #0x00D4
MOVE M,A
LD #0x00D2
SBC A,M
TSA
ST 0x0200
MVI H,#0x00AA
MVI L,#0x0087
LD #0x0046
MOVE M,A
LD #0x0054
SBC A,M
TSA
ST 0x0201
MVI H,#0x00AA
MVI L,#0x0095
LD #0x00B6
MOVE M,A
LD #0x00ED
SBC A,M
TSA
ST 0x0202
MVI H,#0x00AA
MVI L,#0x0059
LD #0x00A5
MOVE M,A
LD #0x002E
SBC A,M
TSA
ST 0x0203
MVI H,#0x00AA
MVI L,#0x007F
LD #0x0085
MOVE M,A
LD #0x00BB
SBC A,M
TSA
ST 0x0204
MVI H,#0x00AA
MVI L,#0x00E0
LD #0x0074
MOVE M,A
LD #0x00B5
SBC A,M
TSA
ST 0x0205
WAI 
