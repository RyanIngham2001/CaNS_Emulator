LD #0x00BB
ST 0xAADD
LD #0x00BB
ST 0xAADE
MVI D,#0x0001
LD #0x0097
AND A,D
ST 0x01FA
MVI D,#0x003E
LD #0x000A
AND A,D
ST 0x01FB
MVI D,#0x00FD
LD #0x0013
AND A,D
ST 0x01FC
MVI D,#0x00E0
LD #0x0003
AND A,D
ST 0x01FD
MVI D,#0x0076
LD #0x001B
AND A,D
ST 0x01FE
MVI D,#0x008D
LD #0x007B
AND A,D
ST 0x01FF
MVI D,#0x00BA
LD #0x0049
AND A,D
TSA
ST 0x0200
MVI D,#0x0096
LD #0x00AB
AND A,D
TSA
ST 0x0201
MVI D,#0x0034
LD #0x004A
AND A,D
TSA
ST 0x0202
MVI D,#0x0038
LD #0x0069
AND A,D
TSA
ST 0x0203
MVI D,#0x0006
LD #0x0029
AND A,D
TSA
ST 0x0204
MVI D,#0x00BA
LD #0x00B0
AND A,D
TSA
ST 0x0205
WAI 
