LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI E,#0x00E3
LD #0x0071
AND A,E
ST 0x01FA
MVI E,#0x0004
LD #0x00F1
AND A,E
ST 0x01FB
MVI E,#0x00C8
LD #0x0091
AND A,E
ST 0x01FC
MVI E,#0x0005
LD #0x0093
AND A,E
ST 0x01FD
MVI E,#0x003A
LD #0x00E9
AND A,E
ST 0x01FE
MVI E,#0x00B0
LD #0x0099
AND A,E
ST 0x01FF
MVI E,#0x0024
LD #0x00FE
AND A,E
TSA
ST 0x0200
MVI E,#0x002E
LD #0x0063
AND A,E
TSA
ST 0x0201
MVI E,#0x007B
LD #0x000C
AND A,E
TSA
ST 0x0202
MVI E,#0x0044
LD #0x00B0
AND A,E
TSA
ST 0x0203
MVI E,#0x0019
LD #0x002B
AND A,E
TSA
ST 0x0204
MVI E,#0x0084
LD #0x008C
AND A,E
TSA
ST 0x0205
WAI 
