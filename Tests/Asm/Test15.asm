LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI E,#0x0053
LD #0x004E
SBC A,E
ST 0x01FA
MVI E,#0x0059
LD #0x004D
SBC A,E
ST 0x01FB
MVI E,#0x008C
LD #0x00A0
SBC A,E
ST 0x01FC
MVI E,#0x0032
LD #0x007F
SBC A,E
ST 0x01FD
MVI E,#0x006A
LD #0x002C
SBC A,E
ST 0x01FE
MVI E,#0x0052
LD #0x00A7
SBC A,E
ST 0x01FF
MVI E,#0x0079
LD #0x00DC
SBC A,E
TSA
ST 0x0200
MVI E,#0x00B7
LD #0x0090
SBC A,E
TSA
ST 0x0201
MVI E,#0x0028
LD #0x00F6
SBC A,E
TSA
ST 0x0202
MVI E,#0x00F9
LD #0x00E6
SBC A,E
TSA
ST 0x0203
MVI E,#0x00C2
LD #0x00A2
SBC A,E
TSA
ST 0x0204
MVI E,#0x000C
LD #0x00AC
SBC A,E
TSA
ST 0x0205
WAI 
