LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI L,#0x002F
LD #0x002B
ADC A,L
ST 0x01FA
MVI L,#0x006D
LD #0x00AD
ADC A,L
ST 0x01FB
MVI L,#0x0036
LD #0x0003
ADC A,L
ST 0x01FC
MVI L,#0x0022
LD #0x00D7
ADC A,L
ST 0x01FD
MVI L,#0x00C3
LD #0x00DE
ADC A,L
ST 0x01FE
MVI L,#0x0050
LD #0x0048
ADC A,L
ST 0x01FF
MVI L,#0x00A7
LD #0x0030
ADC A,L
TSA
ST 0x0200
MVI L,#0x00D3
LD #0x00A8
ADC A,L
TSA
ST 0x0201
MVI L,#0x0081
LD #0x00A6
ADC A,L
TSA
ST 0x0202
MVI L,#0x009C
LD #0x0099
ADC A,L
TSA
ST 0x0203
MVI L,#0x006C
LD #0x00FB
ADC A,L
TSA
ST 0x0204
MVI L,#0x0088
LD #0x000B
ADC A,L
TSA
ST 0x0205
WAI 
