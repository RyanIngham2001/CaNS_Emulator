LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI D,#0x0056
LD #0x00A6
XOR A,D
ST 0x01FA
MVI D,#0x007B
LD #0x00E2
XOR A,D
ST 0x01FB
MVI D,#0x00E7
LD #0x00E5
XOR A,D
ST 0x01FC
MVI D,#0x0051
LD #0x002A
XOR A,D
ST 0x01FD
MVI D,#0x00EA
LD #0x00CE
XOR A,D
ST 0x01FE
MVI D,#0x001F
LD #0x0083
XOR A,D
ST 0x01FF
MVI D,#0x00E4
LD #0x006C
XOR A,D
TSA
ST 0x0200
MVI D,#0x0029
LD #0x008E
XOR A,D
TSA
ST 0x0201
MVI D,#0x009D
LD #0x005E
XOR A,D
TSA
ST 0x0202
MVI D,#0x004C
LD #0x00F4
XOR A,D
TSA
ST 0x0203
MVI D,#0x0045
LD #0x00CB
XOR A,D
TSA
ST 0x0204
MVI D,#0x00F9
LD #0x00FC
XOR A,D
TSA
ST 0x0205
WAI 
