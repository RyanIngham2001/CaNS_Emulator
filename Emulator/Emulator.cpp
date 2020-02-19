

#include "stdafx.h"
#include <winsock2.h>

#pragma comment(lib, "wsock32.lib")


#define STUDENT_NUMBER    "19003311"

#define IP_ADDRESS_SERVER "127.0.0.1"

#define PORT_SERVER 0x1984 // We define a port that we are going to use.
#define PORT_CLIENT 0x1985 // We define a port that we are going to use.

#define WORD  unsigned short
#define DWORD unsigned long
#define BYTE  unsigned char

#define MAX_FILENAME_SIZE 500
#define MAX_BUFFER_SIZE   500

SOCKADDR_IN server_addr;
SOCKADDR_IN client_addr;

SOCKET sock;  // This is our socket, it is the handle to the IO address to read/write packets

WSADATA data;

char InputBuffer[MAX_BUFFER_SIZE];

char hex_file[MAX_BUFFER_SIZE];
char trc_file[MAX_BUFFER_SIZE];

//////////////////////////
//   Registers          //
//////////////////////////

#define FLAG_I  0x80
#define FLAG_N  0x20
#define FLAG_V  0x10
#define FLAG_Z  0x08
#define FLAG_C  0x01

#define REGISTER_M  7
#define REGISTER_A	6
#define REGISTER_H	5
#define REGISTER_L	4
#define REGISTER_E	3
#define REGISTER_D	2
#define REGISTER_C	1
#define REGISTER_B	0
WORD IndexRegister;

BYTE Registers[8];
BYTE Flags;
WORD ProgramCounter;
WORD StackPointer;

////////////
// Memory //
////////////

#define MEMORY_SIZE	65536

BYTE Memory[MEMORY_SIZE];

#define TEST_ADDRESS_1  0x01FA
#define TEST_ADDRESS_2  0x01FB
#define TEST_ADDRESS_3  0x01FC
#define TEST_ADDRESS_4  0x01FD
#define TEST_ADDRESS_5  0x01FE
#define TEST_ADDRESS_6  0x01FF
#define TEST_ADDRESS_7  0x0200
#define TEST_ADDRESS_8  0x0201
#define TEST_ADDRESS_9  0x0202
#define TEST_ADDRESS_10  0x0203
#define TEST_ADDRESS_11  0x0204
#define TEST_ADDRESS_12  0x0205


///////////////////////
// Control variables //
///////////////////////

bool memory_in_range = true;
bool halt = false;


///////////////////////
// Disassembly table //
///////////////////////

char opcode_mneumonics[][14] =
{
"BRA rel      ",
"BCC rel      ",
"BCS rel      ",
"BNE rel      ",
"BEQ rel      ",
"BVC rel      ",
"BVS rel      ",
"BMI rel      ",
"BPL rel      ",
"BGE rel      ",
"BLE rel      ",
"BLS rel      ",
"BHI rel      ",
"ILLEGAL     ",
"RTN impl     ",
"ILLEGAL     ",

"ST abs       ",
"PSH  ,A      ",
"POP A,       ",
"ILLEGAL     ",
"ILLEGAL     ",
"CLC impl     ",
"SEC impl     ",
"CLI impl     ",
"STI impl     ",
"SEV impl     ",
"CLV impl     ",
"DEX impl     ",
"INX impl     ",
"NOP impl     ",
"WAI impl     ",
"ILLEGAL     ",

"ST abs,X     ",
"PSH  ,s      ",
"POP s,       ",
"ILLEGAL     ",
"ILLEGAL     ",
"ADI  #       ",
"SBI  #       ",
"CPI  #       ",
"ANI  #       ",
"XRI  #       ",
"MVI  #,B     ",
"MVI  #,C     ",
"MVI  #,D     ",
"MVI  #,E     ",
"MVI  #,L     ",
"MVI  #,H     ",

"ILLEGAL     ",
"PSH  ,B      ",
"POP B,       ",
"JPR abs      ",
"CCC abs      ",
"CCS abs      ",
"CNE abs      ",
"CEQ abs      ",
"CVC abs      ",
"CVS abs      ",
"CMI abs      ",
"CPL abs      ",
"CHI abs      ",
"CLE abs      ",
"ILLEGAL     ",
"ILLEGAL     ",

"ILLEGAL     ",
"PSH  ,C      ",
"POP C,       ",
"TST abs      ",
"INC abs      ",
"DEC abs      ",
"RCR abs      ",
"RCL abs      ",
"SAL abs      ",
"ASR abs      ",
"NOT abs      ",
"ROL abs      ",
"ROR abs      ",
"ILLEGAL     ",
"LDX  #       ",
"LODS  #      ",

"STOX abs     ",
"PSH  ,D      ",
"POP D,       ",
"TST abs,X    ",
"INC abs,X    ",
"DEC abs,X    ",
"RCR abs,X    ",
"RCL abs,X    ",
"SAL abs,X    ",
"ASR abs,X    ",
"NOT abs,X    ",
"ROL abs,X    ",
"ROR abs,X    ",
"ILLEGAL     ",
"LDX abs      ",
"LODS abs     ",

"STOX abs,X   ",
"PSH  ,E      ",
"POP E,       ",
"TSTA A,A     ",
"INCA A,A     ",
"DECA A,A     ",
"RCRA A,A     ",
"RCLA A,A     ",
"SALA A,A     ",
"ASRA A,A     ",
"NOTA A,A     ",
"ROLA A,A     ",
"RORA A,A     ",
"ILLEGAL     ",
"LDX abs,X    ",
"LODS abs,X   ",

"ILLEGAL     ",
"PSH  ,L      ",
"POP L,       ",
"ILLEGAL     ",
"TAS impl     ",
"TSA impl     ",
"ILLEGAL     ",
"ILLEGAL     ",
"MOVE A,A     ",
"MOVE B,A     ",
"MOVE C,A     ",
"MOVE D,A     ",
"MOVE E,A     ",
"MOVE L,A     ",
"MOVE H,A     ",
"MOVE M,A     ",

"ILLEGAL     ",
"PSH  ,H      ",
"POP H,       ",
"ILLEGAL     ",
"ILLEGAL     ",
"SWI impl     ",
"RTI impl     ",
"ILLEGAL     ",
"MOVE A,B     ",
"MOVE B,B     ",
"MOVE C,B     ",
"MOVE D,B     ",
"MOVE E,B     ",
"MOVE L,B     ",
"MOVE H,B     ",
"MOVE M,B     ",

"ADC A,B      ",
"SBC A,B      ",
"CMP A,B      ",
"IOR A,B      ",
"AND A,B      ",
"XOR A,B      ",
"BT A,B       ",
"ILLEGAL     ",
"MOVE A,C     ",
"MOVE B,C     ",
"MOVE C,C     ",
"MOVE D,C     ",
"MOVE E,C     ",
"MOVE L,C     ",
"MOVE H,C     ",
"MOVE M,C     ",

"ADC A,C      ",
"SBC A,C      ",
"CMP A,C      ",
"IOR A,C      ",
"AND A,C      ",
"XOR A,C      ",
"BT A,C       ",
"ILLEGAL     ",
"MOVE A,D     ",
"MOVE B,D     ",
"MOVE C,D     ",
"MOVE D,D     ",
"MOVE E,D     ",
"MOVE L,D     ",
"MOVE H,D     ",
"MOVE M,D     ",

"ADC A,D      ",
"SBC A,D      ",
"CMP A,D      ",
"IOR A,D      ",
"AND A,D      ",
"XOR A,D      ",
"BT A,D       ",
"LD  #        ",
"MOVE A,E     ",
"MOVE B,E     ",
"MOVE C,E     ",
"MOVE D,E     ",
"MOVE E,E     ",
"MOVE L,E     ",
"MOVE H,E     ",
"MOVE M,E     ",

"ADC A,E      ",
"SBC A,E      ",
"CMP A,E      ",
"IOR A,E      ",
"AND A,E      ",
"XOR A,E      ",
"BT A,E       ",
"LD abs       ",
"MOVE A,L     ",
"MOVE B,L     ",
"MOVE C,L     ",
"MOVE D,L     ",
"MOVE E,L     ",
"MOVE L,L     ",
"MOVE H,L     ",
"MOVE M,L     ",

"ADC A,L      ",
"SBC A,L      ",
"CMP A,L      ",
"IOR A,L      ",
"AND A,L      ",
"XOR A,L      ",
"BT A,L       ",
"LD abs,X     ",
"MOVE A,H     ",
"MOVE B,H     ",
"MOVE C,H     ",
"MOVE D,H     ",
"MOVE E,H     ",
"MOVE L,H     ",
"MOVE H,H     ",
"MOVE M,H     ",

"ADC A,H      ",
"SBC A,H      ",
"CMP A,H      ",
"IOR A,H      ",
"AND A,H      ",
"XOR A,H      ",
"BT A,H       ",
"ILLEGAL     ",
"MOVE A,M     ",
"MOVE B,M     ",
"MOVE C,M     ",
"MOVE D,M     ",
"MOVE E,M     ",
"MOVE L,M     ",
"MOVE H,M     ",
"MOVE -,-     ",

"ADC A,M      ",
"SBC A,M      ",
"CMP A,M      ",
"IOR A,M      ",
"AND A,M      ",
"XOR A,M      ",
"BT A,M       ",
"ILLEGAL     ",
"ILLEGAL     ",
"ILLEGAL     ",
"JMP abs      ",
"ILLEGAL     ",
"ILLEGAL     ",
"ILLEGAL     ",
"ILLEGAL     ",
"ILLEGAL     ",

};

////////////////////////////////////////////////////////////////////////////////
//                           Simulator/Emulator (Start)                       //
////////////////////////////////////////////////////////////////////////////////
BYTE fetch()
{
	BYTE byte = 0;

	if ((ProgramCounter >= 0) && (ProgramCounter <= MEMORY_SIZE))
	{
		memory_in_range = true;
		byte = Memory[ProgramCounter];
		ProgramCounter++;
	}
	else
	{
		memory_in_range = false;
	}
	return byte;
}

/// Flags ///

void set_flag_v(BYTE in1, BYTE in2, BYTE out1)
{
	BYTE reg1in;
	BYTE reg2in;
	BYTE regOut;

	reg1in = in1;
	reg2in = in2;
	regOut = out1;

	if ((((reg1in & 0x80) == 0x80) && ((reg2in & 0x80) == 0x80) && ((regOut & 0x80) != 0x80)) //overflow
		|| (((reg1in & 0x80) != 0x80) && ((reg2in & 0x80) != 0x80) && ((regOut & 0x80) == 0x80))) //overflow
	{
		Flags = Flags | FLAG_V;
	}
	else
	{
		Flags = Flags & (0xFF - FLAG_V);
	}
}

void set_flag_z(BYTE inReg) {
	BYTE reg;
	reg = inReg;
	if (reg == 0)
	{
		Flags = Flags | FLAG_Z;
	}
	else
	{
		Flags = Flags & (0xFF - FLAG_Z);
	}
}


void set_flag_n(BYTE inReg) {
	BYTE reg;
	reg = inReg;
	if ((reg & 0x80) != 0)  
	{
		Flags = Flags | FLAG_N;
	}
	else
	{
		Flags = Flags & (0xFF - FLAG_N);
	}
}

void set_flag_c(WORD inReg) {
	WORD reg;
	reg = inReg;

	if (reg >= 0x100)
	{
		Flags = Flags | FLAG_C;
	}
	else
	{
		Flags = Flags & (0xFF - FLAG_C);
	}
}


void MVI(BYTE reg)
{
	/* Function: MVI (Loads memory into register)
	   Parameters : reg (BYTE) register to load memory into
	   Returns : N/A
	   Warnings : None
	*/
	WORD data = 0;
	data = fetch();
	Registers[reg] = data;
}

void POP(BYTE reg)
{
	/*	Function : POP (Pop the top of the stack into the Register)
		Parameters : reg (BYTE) register to pop stack value into
		Returns : N/A
		Warnings : None
	*/
	if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1))
	{
		StackPointer++;
		Registers[reg] = Memory[StackPointer];
	}
}

void POPFL()
{
	/*	Function : POPFL (Pops the top of the stack into Flags)
		Parameters : None
		Returns : N/A
		Warnings : None
	*/
	if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1))
	{
		StackPointer++;
		Flags = Memory[StackPointer];
	}
}

void PSH(BYTE reg)
{
	/*	Function : PSH (Pushes register value onto stack)
		Parameters : reg (BYTE) register to push onto stack
		Returns : N/A
		Warnings : None
	*/
	if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE))
	{
		Memory[StackPointer] = Registers[reg];
		StackPointer--;
	}
}

void PSHFL()
{
	/*	Function : PSHFL (Pushes flag value onto stack)
		Parameters : None
		Returns : N/A
		Warnings : None
	*/
	if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE))
	{
		Memory[StackPointer] = Flags;
		StackPointer--;
	}
}

void ADC(BYTE reg1, BYTE reg2)
{
	/*	Function : ADC (Register added to accumulator with carry)
		Parameters : reg1, reg2 (BYTE). Registers to be added together.
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] + (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_c(temp_word);
	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);
	set_flag_v(Registers[reg1], Registers[reg2], (BYTE)temp_word);

	Registers[reg1] = (BYTE)temp_word;

}

void SBC(BYTE reg1, BYTE reg2)
{
	/*	Function : SBC (Register subtracted to accumulator with carry)
		Parameters : reg1, reg2 (BYTE) reg2 subtracted from reg1
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] - (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_c(temp_word);
	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);
	set_flag_v(Registers[reg1], -Registers[reg2], (BYTE)temp_word);

	Registers[reg1] = (BYTE)temp_word;

}

void CMP(BYTE reg1, BYTE reg2)
{
	/*	Function : CMP (Register compared to accumulator)
		Parameters : reg1, reg2 (BYTE) reg2 subtracted from reg1 and compared
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] - (WORD)Registers[reg2];

	set_flag_c(temp_word);
	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);
	set_flag_v(Registers[reg1], -Registers[reg2], (BYTE)temp_word);
}

void IOR(BYTE reg1, BYTE reg2)
{
	/*	Function : IOR (Register bitwise inclusive or with accumulator)
		Parameters : reg1, reg2 (BYTE) two registers to be bitwise OR'ed
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] | (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);

	Registers[reg1] = (BYTE)temp_word;
}

void AND(BYTE reg1, BYTE reg2)
{
	/*	Function : AND (Register bitwise AND with accumulator
		Parameters : reg1, reg2 (BYTE) two registers to be bitwise AND'ed
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] & (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);

	Registers[reg1] = (BYTE)temp_word;
}

void XOR(BYTE reg1, BYTE reg2)
{
	/*	Function : XOR (Register bitwise XOR with accumulator)
		Parameters : reg1, reg2 (BYTE) two registers to be bitwise XOR'ed
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] ^ (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);

	Registers[reg1] = (BYTE)temp_word;
}

void BT(BYTE reg1, BYTE reg2)
{
	/*	Function : BT (Register Bit tested with accumulator)
		Parameters : reg1, reg2 (BYTE) two registers to be Bit tested
		Returns : N/A
		Warnings : None
	*/
	WORD temp_word;
	temp_word = (WORD)Registers[reg1] & (WORD)Registers[reg2];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n((BYTE)temp_word);
	set_flag_z((BYTE)temp_word);
}


void ADI(BYTE reg)
{
	/*	Function : ADI (Data added to accumulator with carry)
		Parameters : reg (BYTE) register to add data to
		Returns : N/A
		Warnings : None
	*/
	WORD data = 0;
	data = fetch();

	WORD temp_word;
	temp_word = (WORD)data + (WORD)Registers[reg];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_c(temp_word);
	set_flag_v(Registers[reg], data, (BYTE)temp_word);
	set_flag_n(Registers[reg]);
	set_flag_z(Registers[reg]);

	Registers[reg] = (BYTE)temp_word;
}

void SBI(BYTE reg)
{
	/*	Function : SBI (Data subtracted from accumulator with carry)
		Parameters : reg (BYTE) register to subtract from
		Returns : N/A
		Warnings : None
	*/
	WORD data = 0;
	data = fetch();

	WORD temp_word;
	temp_word = (WORD)data - (WORD)Registers[reg];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_c(temp_word);
	set_flag_v(data, -Registers[reg], (BYTE)temp_word);
	set_flag_n(Registers[reg]);
	set_flag_z(Registers[reg]);

	Registers[reg] = (BYTE)temp_word;
}

void CPI(BYTE reg)
{
	/*	Function : CPI (Data compared to accumulator)
		Parameters : reg (BYTE) accumulator to be compared to
		Returns : N/A
		Warnings : None
	*/
	WORD data = 0;
	data = fetch();

	WORD temp_word;
	temp_word = (WORD)data - (WORD)Registers[reg];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_c(temp_word);
	set_flag_v(data, -Registers[reg], (BYTE)temp_word);
	set_flag_n(Registers[reg]);
	set_flag_z(Registers[reg]);
}

void ANI(BYTE reg)
{
	/*	Function : ANI (Data bitwise AND with accumulator)
		Parameters : reg (BYTE) accumulator to be bitwise AND'ed with data
		Returns : N/A
		Warnings : None
	*/
	WORD data = 0;
	data = fetch();

	WORD temp_word;
	temp_word = (WORD)data & (WORD)Registers[reg];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n(Registers[reg]);
	set_flag_z(Registers[reg]);
}

void XRI(BYTE reg)
{
	/*	Function : XRI (Data bitwise XOR with accumulator)
		Parameters : reg (BYTE) accumulator to be bitwise XOR'ed with data 
		Returns : N/A
		Warnings : None
	*/
	WORD data = 0;
	data = fetch();

	WORD temp_word;
	temp_word = (WORD)data ^ (WORD)Registers[reg];

	if ((Flags & FLAG_C) != 0)
	{
		temp_word++;
	}

	set_flag_n(Registers[reg]);
	set_flag_z(Registers[reg]);
}

void Group_1(BYTE opcode) {
	BYTE LB = 0;
	BYTE HB = 0;
	WORD address = 0;
	WORD data = 0;
	WORD temp_word;
	WORD temp_word2;

	switch (opcode) {

		///LD (Loads memory into accumulator)///

	//LD Immediate
	case 0xB7: 
		data = fetch();
		Registers[REGISTER_A] = data;

		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		Flags = Flags & (0xFF - FLAG_C);
		break;

	// LD Absolute
	case 0xC7: 
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Registers[REGISTER_A] = Memory[address];
		}
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		Flags = Flags & (0xFF - FLAG_C);
		break;

	// LD Absolute indexed
	case 0xD7:
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Registers[REGISTER_A] = Memory[address];
		}
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		Flags = Flags & (0xFF - FLAG_C);
		break;

		///ST (Stores accumulator into memory)///

	//ST Absolute
	case 0x10:
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Memory[address] = Registers[REGISTER_A];
		}
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		Flags = Flags & (0xFF - FLAG_C);
		break;

	//ST Absolute indexed
	case 0x20:
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Memory[address] = Registers[REGISTER_A];
		}
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		Flags = Flags & (0xFF - FLAG_C);
		break;

		///MVI (Loads memory into register)///

	case 0x2A:
		MVI(REGISTER_B);
		break;

	case 0x2B:
		MVI(REGISTER_C);
		break;

	case 0x2C:
		MVI(REGISTER_D);
		break;

	case 0x2D:
		MVI(REGISTER_E);
		break;

	case 0x2E:
		MVI(REGISTER_L);
		break;

	case 0x2F:
		MVI(REGISTER_H);
		break;

		///LODS (Loads memory into stackPointer)///

	case 0x4f: //LODS immediate
		data = fetch();
		StackPointer = data << 8;
		StackPointer += fetch();
		break;

	case 0x5F: //LODS absolute
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE - 1)
		{
			StackPointer = (WORD)Memory[address] << 8;
			StackPointer += Memory[address + 1];
		}
		break;

	case 0x6F: //LODS Absolute indexed
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE - 1)
		{
			StackPointer = (WORD)Memory[address] << 8;
			StackPointer += Memory[address + 1];
		}
		break;

		///LDX (Loads memory into indexRegister)///

	case 0x4E: //LDX Immediate
		data = fetch();
		IndexRegister = (WORD)data;
		Registers[REGISTER_A] = data;
		break;

	case 0x5E: //LDX Absolute
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			IndexRegister = Memory[address];
		}

		break;

	case 0x6E: //LDX Absolute indexed
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			IndexRegister = Memory[address];
		}
		break;

		///STOX (Stores register X into memory)///

	case 0x50: //STOX Absolute
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Memory[address] = IndexRegister;
		}
		break;

	case 0x60: //Stox absolute indexed
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
		{
			Memory[address] = IndexRegister;
		}
		break;

		///PSH (Pushes register onto stack)///

	case 0x11: // for register A
		PSH(REGISTER_A);
		break;

	case 0x21: // for register FL  
		PSHFL();
		break;

	case 0x31: // for register B
		PSH(REGISTER_B);
		break;

	case 0x41: // for register C
		PSH(REGISTER_C);
		break;

	case 0x51: // for register D
		PSH(REGISTER_D);
		break;

	case 0x61: // for register E
		PSH(REGISTER_E);
		break;

	case 0x71: // for register L
		PSH(REGISTER_L);
		break;

	case 0x81: // for register H
		PSH(REGISTER_H);
		break;

		///POP (Pops stack onto register)///

	case 0x12: // for register A
		POP(REGISTER_A);
		break;

	case 0x22: // for register FL
		POPFL();
		break;

	case 0x32: // for register B
		POP(REGISTER_B);
		break;

	case 0x42: // for register C
		POP(REGISTER_C);
		break;

	case 0x52: // for register D
		POP(REGISTER_D);
		break;

	case 0x62: // for register E
		POP(REGISTER_E);
		break;

	case 0x72: // for register L
		POP(REGISTER_L);
		break;

	case 0x82: // for register H
		POP(REGISTER_H);
		break;

		///ADC (Adds registers with carry)///
	case 0x90: //ADC A-B
		ADC(REGISTER_A, REGISTER_B);
		break;

	case 0xA0: //ADC A-C
		ADC(REGISTER_A, REGISTER_C);
		break;

	case 0XB0: //ADC A-D
		ADC(REGISTER_A, REGISTER_D);
		break;

	case 0xC0: //ADC A-E
		ADC(REGISTER_A, REGISTER_E);
		break;

	case 0xD0: //ADC A-L
		ADC(REGISTER_A, REGISTER_L);
		break;

	case 0xE0: //ADC A-H
		ADC(REGISTER_A, REGISTER_H);
		break;

	case 0xF0: //ADC A-M
		ADC(REGISTER_A, REGISTER_M);
		break;

		/// SBC ///		

	case 0x91: //SBC A-B
		SBC(REGISTER_A, REGISTER_B);
		break;

	case 0xA1: //SBC A-C
		SBC(REGISTER_A, REGISTER_C);
		break;

	case 0xB1: //SBC A-D
		SBC(REGISTER_A, REGISTER_D);
		break;

	case 0xC1: //SBC A-E
		SBC(REGISTER_A, REGISTER_E);
		break;

	case 0xD1: //SBC A-L
		SBC(REGISTER_A, REGISTER_L);
		break;

	case 0xE1: //SBC A-H
		SBC(REGISTER_A, REGISTER_H);
		break;

	case 0xF1: //SBC A-M
		SBC(REGISTER_A, REGISTER_M);
		break;

		///CMP (Compares register to accumulator)/// 

	case 0x92: //CMP A-B
		CMP(REGISTER_A, REGISTER_B);
		break;

	case 0xA2: //CMP A-C
		CMP(REGISTER_A, REGISTER_C);
		break;

	case 0xB2: //CMP A-D
		CMP(REGISTER_A, REGISTER_D);
		break;

	case 0xC2: //CMP B-E
		CMP(REGISTER_A, REGISTER_E);
		break;

	case 0xD2: //CMP B-L
		CMP(REGISTER_A, REGISTER_L);
		break;

	case 0xE2: //CMP B-H
		CMP(REGISTER_A, REGISTER_H);
		break;

	case 0xF2: 
		CMP(REGISTER_A, REGISTER_M);
		break;

		///IOR (Inclusive or register with accumulator)///

	case 0x93: 
		IOR(REGISTER_A, REGISTER_B);
		break;

	case 0xA3: 
		IOR(REGISTER_A, REGISTER_C);
		break;

	case 0xB3: 
		IOR(REGISTER_A, REGISTER_D);
		break;

	case 0xC3: 
		IOR(REGISTER_A, REGISTER_E);
		break;

	case 0xD3: 
		IOR(REGISTER_A, REGISTER_L);
		break;

	case 0xE3: 
		IOR(REGISTER_A, REGISTER_H);
		break;

	case 0xF3:
		IOR(REGISTER_A, REGISTER_M);
		break;

		///AND (AND register and accumulator)///

	case 0x94: 
		AND(REGISTER_A, REGISTER_B);
		break;

	case 0xA4: 
		AND(REGISTER_A, REGISTER_C);
		break;

	case 0xB4: 
		AND(REGISTER_A, REGISTER_D);
		break;

	case 0xC4: 
		AND(REGISTER_A, REGISTER_E);
		break;

	case 0xD4: 
		AND(REGISTER_A, REGISTER_L);
		break;

	case 0xE4: 
		AND(REGISTER_A, REGISTER_H);
		break;

	case 0xF4: 
		AND(REGISTER_A, REGISTER_M);
		break;

		///XOR (Register XOR with accumulator)/// 

	case 0x95: 
		XOR(REGISTER_A, REGISTER_B);
		break;

	case 0xA5: 
		XOR(REGISTER_A, REGISTER_C);
		break;

	case 0xB5: 
		XOR(REGISTER_A, REGISTER_D);
		break;

	case 0xC5: 
		XOR(REGISTER_A, REGISTER_E);
		break;

	case 0xD5: 
		XOR(REGISTER_A, REGISTER_L);
		break;

	case 0xE5: 
		XOR(REGISTER_A, REGISTER_H);
		break;

	case 0xF5: 
		XOR(REGISTER_A, REGISTER_M);
		break;

		///BT (Bit compare register and accumulator)///

	case 0x96: 
		BT(REGISTER_A, REGISTER_B);
		break;

	case 0xA6: 
		BT(REGISTER_A, REGISTER_C);
		break;

	case 0xB6: 
		BT(REGISTER_A, REGISTER_D);
		break;

	case 0xC6: 
		BT(REGISTER_A, REGISTER_E);
		break;

	case 0xD6: 
		BT(REGISTER_A, REGISTER_L);
		break;

	case 0xE6: 
		BT(REGISTER_A, REGISTER_H);
		break;

	case 0xF6: 
		BT(REGISTER_A, REGISTER_M);
		break;

	//ADI//

	case 0x25:
		ADI(REGISTER_A);
		break;

	//SBI//
	case 0x26:
		SBI(REGISTER_A);
		break;

	//CPI//

	case 0x27:
		CPI(REGISTER_A);
		break;

	//ANI//

	case 0x28:
		ANI(REGISTER_A);
		break;

	//XRI//

	case 0x29:
		XRI(REGISTER_A);
		break;

	//TAS (Transfters accumulator to status register)//
	case 0x74: 
		Flags = Registers[REGISTER_A];
		break;

	//TSA (Transfers Status register to accumulator//
	case 0x75: 
		Registers[REGISTER_A] = Flags;
		break;

	//CLC (Clear carrry flag)
	case 0x15:  
		Flags = Flags & (0xFF - FLAG_C);
		break;

	//SEC (Set carry flag)
	case 0x16: 
		Flags = Flags | FLAG_C;

	//CLI (Clear interrupt flag)
	case 0x17:
		Flags = Flags & (0xFF - FLAG_I);

	//STI (Set interrupt flag)
	case 0x18:
		Flags = Flags | FLAG_I;

	//SEV (Set overflow flag)
	case 0x19:
		Flags = Flags | FLAG_V;

	//CLV (Clear overflow flag)
	case 0x1A: 
		Flags = Flags & (0xFF - FLAG_V);


	//JMP (Loads memory into program counter)//

	case 0xFA:
		HB = fetch();
		LB = fetch();

		address = ((WORD)HB << 8) + (WORD)LB;

		ProgramCounter = address;
		break;

	//JPR (Jump to subroutine)//
	case 0x33: 
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
		{
			Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			StackPointer--;
			Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
			StackPointer--;
		}
		ProgramCounter = address;
		break;

	//RTN (Return from subroutine)//
	case 0x0E: 
		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 2))
		{
			StackPointer++;
			HB = Memory[StackPointer];
			StackPointer++;
			LB = Memory[StackPointer];
		}
		ProgramCounter = ((WORD)HB << 8) + (WORD)LB;
		break;

	//BRA (Branch always)//

	case 0x00: 
		LB = fetch();
		WORD oﬀset;

		oﬀset = (WORD)LB;
		if ((oﬀset & 0x80) != 0)
		{
			oﬀset = oﬀset + 0xFF00;
		}
		address = ProgramCounter + oﬀset;
		ProgramCounter = address;
		break;

	///CCC (Call on carry clear)///

	case 0x34: 
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		ProgramCounter = address;
		if ((Flags & FLAG_C) != 0)
		{
			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
			{
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
			}

		}
		break;

	//CCS (Call on carry set)//

	case 0x35: 
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		ProgramCounter = address;
		if ((Flags & FLAG_C) != 0)
		{
			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
			{
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
			}
		}
		break;

	//CNE (Call on result not zero)//

	case 0x36: 
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		ProgramCounter = address;
		if ((Flags & FLAG_Z) != 0)
		{
			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
			{
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
			}

		}
		break;

	//CEQ (Call on result equal to zero)//

	case 0x37:
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		ProgramCounter = address;
		if ((Flags & FLAG_Z) != 0)
		{
			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
			{
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
			}
		}
		break;

	//CVC (Call on overflow clear)//

	case 0x38: 
		HB = fetch();
		LB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;
		ProgramCounter = address;
		if ((Flags & FLAG_V) != 0)
		{
			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
			{
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
			}
		}
		break;

	//CVS (Call on overflow set)//

	case 0x39:

		HB = fetch();
		LB = fetch();
		if ((Flags & FLAG_V) == FLAG_V) // Overflow flag set?
		{
			address += (WORD)((WORD)HB << 8) + LB;
			if (address >= 0 && address < MEMORY_SIZE)
			{
				// Push return address onto the stack
				if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE))
				{
					Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
					StackPointer--;
					Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
					StackPointer--;
				}
				ProgramCounter = (WORD)address;
			}
		}
		break;

	//BCS (Branch on carry set)//

	case 0x02: 
		LB = fetch();
		if ((Flags & FLAG_C) == FLAG_C) {
			WORD offset = (WORD)LB;
			if ((offset & 0x80) != 0) { // need to sign extend
				offset = offset + 0xFF00;
			} address = ProgramCounter + offset;
			ProgramCounter = address;
		}
		break;


		//INC absolute//
	case 0x44:
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			++Memory[address];
		}
		break;

		//INC Indexed//
	case 0x54:
		address += IndexRegister;
		HB = fetch();
		LB = fetch();
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			++Memory[address];
		}
		break;

		//INCA (Increment memory into accumulator)//
	case 0x64:
		++Registers[REGISTER_A];
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		break;

		//INX (Increment indexRegister//
	case 0x1C:
		++IndexRegister;
		set_flag_z(IndexRegister);
		break;

		//DEX (Decrement indexRegister) //
	case 0x1B:
		--IndexRegister;
		set_flag_z(IndexRegister);
		break;

	}
}

void Group_2_Move(BYTE opcode) {
	int destination;
	int source;

	int destReg = 0;
	int sourceReg = 0;

	WORD address;

	destination = opcode & 0x0F;


	switch (destination) {

	case 0x08:
		destReg = REGISTER_A;
		break;

	case 0x09:
		destReg = REGISTER_B;
		break;

	case 0x0A:
		destReg = REGISTER_C;
		break;

	case 0x0B:
		destReg = REGISTER_D;
		break;

	case 0x0C:
		destReg = REGISTER_E;
		break;

	case 0x0D:
		destReg = REGISTER_L;
		break;

	case 0x0E:
		destReg = REGISTER_H;
		break;

	case 0x0F:
		destReg = REGISTER_M;
		break;

	}

	source = (opcode >> 4) & 0x0F;

	switch (source) {

	case 0x07:
	case 0x78:
	case 0x79:
	case 0x7A:
	case 0x7B:
	case 0x7C:
	case 0x7D:
	case 0x7E:
	case 0x7F:
		sourceReg = REGISTER_A;
		break;

	case 0x08:
	case 0x88:
	case 0x89:
	case 0x8A:
	case 0x8B:
	case 0x8C:
	case 0x8D:
	case 0x8E:
	case 0x8F:
		sourceReg = REGISTER_B;
		break;

	case 0x09:
	case 0x98:
	case 0x99:
	case 0x9A:
	case 0x9B:
	case 0x9C:
	case 0x9D:
	case 0x9E:
	case 0x9F:
		sourceReg = REGISTER_C;
		break;

	case 0x0A:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xAF:
		sourceReg = REGISTER_D;
		break;

	case 0x0B:
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
	case 0xBF:
		sourceReg = REGISTER_E;
		break;

	case 0x0C:
	case 0xC8:
	case 0xC9:
	case 0xCA:
	case 0xCB:
	case 0xCC:
	case 0xCD:
	case 0xCE:
	case 0xCF:
		sourceReg = REGISTER_L;
		break;

	case 0x0D:
	case 0xD8:
	case 0xD9:
	case 0xDA:
	case 0xDB:
	case 0xDC:
	case 0xDD:
	case 0xDE:
	case 0xDF:
		sourceReg = REGISTER_H;
		break;

	case 0x0E:
	case 0xE8:
	case 0xE9:
	case 0xEA:
	case 0xEB:
	case 0xEC:
	case 0xED:
	case 0xEE:
	case 0xEF:
		sourceReg = REGISTER_M;
		break;
	}

	if (sourceReg == REGISTER_M)
	{
		address = (WORD)Registers[REGISTER_H] << 8 + (WORD)Registers[REGISTER_L];
		Registers[REGISTER_M] = Memory[address];
	}

	Registers[destReg] = Registers[sourceReg];

	if (destReg == REGISTER_M)
	{
		address = (WORD)Registers[REGISTER_H] << 8 + (WORD)Registers[REGISTER_L];
		Memory[address] = Registers[REGISTER_M];
	}
}

void execute(BYTE opcode)
{
	if (((opcode >= 0x78) && (opcode <= 0x7F))
		|| ((opcode >= 0x88) && (opcode <= 0x8F))
		|| ((opcode >= 0x98) && (opcode <= 0x9F))
		|| ((opcode >= 0xA8) && (opcode <= 0xAF))
		|| ((opcode >= 0xB8) && (opcode <= 0xBF))
		|| ((opcode >= 0xC8) && (opcode <= 0xCF))
		|| ((opcode >= 0xD8) && (opcode <= 0xDF))
		|| ((opcode >= 0xE8) && (opcode <= 0xEF)))
	{
		Group_2_Move(opcode);
	}
	else
	{
		Group_1(opcode);
	}
}

void emulate()
{
	BYTE opcode;
	int sanity;
	ProgramCounter = 0;
	halt = false;
	memory_in_range = true;
	sanity = 0;
	int loop = 0;

	printf("                    A  B  C  D  E  L  H  X    SP\n");

	while ((!halt) && (memory_in_range)) {
		sanity++;
		if (sanity > 500) halt = true;
		printf("%04X ", ProgramCounter);           // Print current address
		opcode = fetch();
		execute(opcode);

		printf("%s  ", opcode_mneumonics[opcode]);  // Print current opcode

		printf("%02X ", Registers[REGISTER_A]);
		printf("%02X ", Registers[REGISTER_B]);
		printf("%02X ", Registers[REGISTER_C]);
		printf("%02X ", Registers[REGISTER_D]);
		printf("%02X ", Registers[REGISTER_E]);
		printf("%02X ", Registers[REGISTER_L]);
		printf("%02X ", Registers[REGISTER_H]);
		printf("%04X ", IndexRegister);
		printf("%04X ", StackPointer);              // Print Stack Pointer

		if ((Flags & FLAG_I) == FLAG_I)
		{
			printf("I=1 ");
		}
		else
		{
			printf("I=0 ");
		}
		if ((Flags & FLAG_N) == FLAG_N)
		{
			printf("N=1 ");
		}
		else
		{
			printf("N=0 ");
		}
		if ((Flags & FLAG_V) == FLAG_V)
		{
			printf("V=1 ");
		}
		else
		{
			printf("V=0 ");
		}
		if ((Flags & FLAG_Z) == FLAG_Z)
		{
			printf("Z=1 ");
		}
		else
		{
			printf("Z=0 ");
		}
		if ((Flags & FLAG_C) == FLAG_C)
		{
			printf("C=1 ");
		}
		else
		{
			printf("C=0 ");
		}

		printf("\n");  // New line
	}

	printf("\n");  // New line
}


////////////////////////////////////////////////////////////////////////////////
//                            Simulator/Emulator (End)                        //
////////////////////////////////////////////////////////////////////////////////


void initialise_filenames() {
	int i;

	for (i = 0; i < MAX_FILENAME_SIZE; i++) {
		hex_file[i] = '\0';
		trc_file[i] = '\0';
	}
}

int find_dot_position(char* filename) {
	int  dot_position;
	int  i;
	char chr;

	dot_position = 0;
	i = 0;
	chr = filename[i];

	while (chr != '\0') {
		if (chr == '.') {
			dot_position = i;
		}
		i++;
		chr = filename[i];
	}

	return (dot_position);
}


int find_end_position(char* filename) {
	int  end_position;
	int  i;
	char chr;

	end_position = 0;
	i = 0;
	chr = filename[i];

	while (chr != '\0') {
		end_position = i;
		i++;
		chr = filename[i];
	}

	return (end_position);
}


bool file_exists(char* filename) {
	bool exists;
	FILE* ifp;

	exists = false;

	if ((ifp = fopen(filename, "r")) != NULL) {
		exists = true;

		fclose(ifp);
	}

	return (exists);
}



void create_file(char* filename) {
	FILE* ofp;

	if ((ofp = fopen(filename, "w")) != NULL) {
		fclose(ofp);
	}
}



bool getline(FILE* fp, char* buffer) {
	bool rc;
	bool collect;
	char c;
	int  i;

	rc = false;
	collect = true;

	i = 0;
	while (collect) {
		c = getc(fp);

		switch (c) {
		case EOF:
			if (i > 0) {
				rc = true;
			}
			collect = false;
			break;

		case '\n':
			if (i > 0) {
				rc = true;
				collect = false;
				buffer[i] = '\0';
			}
			break;

		default:
			buffer[i] = c;
			i++;
			break;
		}
	}

	return (rc);
}

void load_and_run(int args, _TCHAR** argv) {
	char chr;
	int  ln;
	int  dot_position;
	int  end_position;
	long i;
	FILE* ifp;
	long address;
	long load_at;
	int  code;

	// Prompt for the .hex file

	printf("\n");
	printf("Enter the hex filename (.hex): ");

	if (args == 2) {
		ln = 0;
		chr = argv[1][ln];
		while (chr != '\0')
		{
			if (ln < MAX_FILENAME_SIZE)
			{
				hex_file[ln] = chr;
				trc_file[ln] = chr;
				ln++;
			}
			chr = argv[1][ln];
		}
	}
	else {
		ln = 0;
		chr = '\0';
		while (chr != '\n') {
			chr = getchar();

			switch (chr) {
			case '\n':
				break;
			default:
				if (ln < MAX_FILENAME_SIZE) {
					hex_file[ln] = chr;
					trc_file[ln] = chr;
					ln++;
				}
				break;
			}
		}

	}
	// Tidy up the file names

	dot_position = find_dot_position(hex_file);
	if (dot_position == 0) {
		end_position = find_end_position(hex_file);

		hex_file[end_position + 1] = '.';
		hex_file[end_position + 2] = 'h';
		hex_file[end_position + 3] = 'e';
		hex_file[end_position + 4] = 'x';
		hex_file[end_position + 5] = '\0';
	}
	else {
		hex_file[dot_position + 0] = '.';
		hex_file[dot_position + 1] = 'h';
		hex_file[dot_position + 2] = 'e';
		hex_file[dot_position + 3] = 'x';
		hex_file[dot_position + 4] = '\0';
	}

	dot_position = find_dot_position(trc_file);
	if (dot_position == 0) {
		end_position = find_end_position(trc_file);

		trc_file[end_position + 1] = '.';
		trc_file[end_position + 2] = 't';
		trc_file[end_position + 3] = 'r';
		trc_file[end_position + 4] = 'c';
		trc_file[end_position + 5] = '\0';
	}
	else {
		trc_file[dot_position + 0] = '.';
		trc_file[dot_position + 1] = 't';
		trc_file[dot_position + 2] = 'r';
		trc_file[dot_position + 3] = 'c';
		trc_file[dot_position + 4] = '\0';
	}

	if (file_exists(hex_file)) {
		// Clear Registers and Memory

		Registers[REGISTER_A] = 0;
		Registers[REGISTER_B] = 0;
		Registers[REGISTER_C] = 0;
		Registers[REGISTER_D] = 0;
		Registers[REGISTER_E] = 0;
		Registers[REGISTER_L] = 0;
		Registers[REGISTER_H] = 0;
		IndexRegister = 0;
		Flags = 0;
		ProgramCounter = 0;
		StackPointer = 0;

		for (i = 0; i < MEMORY_SIZE; i++) {
			Memory[i] = 0x00;
		}

		// Load hex file

		if ((ifp = fopen(hex_file, "r")) != NULL) {
			printf("Loading file...\n\n");

			load_at = 0;

			while (getline(ifp, InputBuffer)) {
				if (sscanf(InputBuffer, "L=%x", &address) == 1) {
					load_at = address;
				}
				else if (sscanf(InputBuffer, "%x", &code) == 1) {
					if ((load_at >= 0) && (load_at <= MEMORY_SIZE)) {
						Memory[load_at] = (BYTE)code;
					}
					load_at++;
				}
				else {
					printf("ERROR> Failed to load instruction: %s \n", InputBuffer);
				}
			}

			fclose(ifp);
		}

		// Emulate

		emulate();
	}
	else {
		printf("\n");
		printf("ERROR> Input file %s does not exist!\n", hex_file);
		printf("\n");
	}
}

void building(int args, _TCHAR** argv) {
	char buffer[1024];
	load_and_run(args, argv);
	sprintf(buffer, "0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X",
		Memory[TEST_ADDRESS_1],
		Memory[TEST_ADDRESS_2],
		Memory[TEST_ADDRESS_3],
		Memory[TEST_ADDRESS_4],
		Memory[TEST_ADDRESS_5],
		Memory[TEST_ADDRESS_6],
		Memory[TEST_ADDRESS_7],
		Memory[TEST_ADDRESS_8],
		Memory[TEST_ADDRESS_9],
		Memory[TEST_ADDRESS_10],
		Memory[TEST_ADDRESS_11],
		Memory[TEST_ADDRESS_12]
	);
	sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)& server_addr, sizeof(SOCKADDR));
}

void test_and_mark() {
	char buffer[1024];
	bool testing_complete;
	int  len = sizeof(SOCKADDR);
	char chr;
	int  i;
	int  j;
	bool end_oprogram;
	long address;
	long load_at;
	int  code;
	int  mark;
	int  passed;

	printf("\n");
	printf("Automatic Testing and Marking\n");
	printf("\n");

	testing_complete = false;

	sprintf(buffer, "Test Student %s", STUDENT_NUMBER);
	sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)& server_addr, sizeof(SOCKADDR));

	while (!testing_complete) {
		memset(buffer, '\0', sizeof(buffer));

		if (recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (SOCKADDR*)& client_addr, &len) != SOCKET_ERROR) {
			printf("Incoming Data: %s \n", buffer);

			//if (strcmp(buffer, "Testing complete") == 1)
			if (sscanf(buffer, "Testing complete %d", &mark) == 1) {
				testing_complete = true;
				printf("Current mark = %d\n", mark);

			}
			else if (sscanf(buffer, "Tests passed %d", &passed) == 1) {
				//testing_complete = true;
				printf("Passed = %d\n", passed);

			}
			else if (strcmp(buffer, "Error") == 0) {
				printf("ERROR> Testing abnormally terminated\n");
				testing_complete = true;
			}
			else {
				// Clear Registers and Memory

				Registers[REGISTER_A] = 0;
				Registers[REGISTER_B] = 0;
				Registers[REGISTER_C] = 0;
				Registers[REGISTER_D] = 0;
				Registers[REGISTER_E] = 0;
				Registers[REGISTER_L] = 0;
				Registers[REGISTER_H] = 0;
				IndexRegister = 0;
				Flags = 0;
				ProgramCounter = 0;
				StackPointer = 0;
				for (i = 0; i < MEMORY_SIZE; i++) {
					Memory[i] = 0;
				}

				// Load hex file

				i = 0;
				j = 0;
				load_at = 0;
				end_oprogram = false;
				FILE* ofp;
				fopen_s(&ofp, "branch.txt", "a");

				while (!end_oprogram) {
					chr = buffer[i];
					switch (chr) {
					case '\0':
						end_oprogram = true;

					case ',':
						if (sscanf(InputBuffer, "L=%x", &address) == 1) {
							load_at = address;
						}
						else if (sscanf(InputBuffer, "%x", &code) == 1) {
							if ((load_at >= 0) && (load_at <= MEMORY_SIZE)) {
								Memory[load_at] = (BYTE)code;
								fprintf(ofp, "%02X\n", (BYTE)code);
							}
							load_at++;
						}
						else {
							printf("ERROR> Failed to load instruction: %s \n", InputBuffer);
						}
						j = 0;
						break;

					default:
						InputBuffer[j] = chr;
						j++;
						break;
					}
					i++;
				}
				fclose(ofp);
				// Emulate

				if (load_at > 1) {
					emulate();
					// Send and store results
					sprintf(buffer, "%02X%02X %02X%02X %02X%02X %02X%02X %02X%02X %02X%02X",
						Memory[TEST_ADDRESS_1],
						Memory[TEST_ADDRESS_2],
						Memory[TEST_ADDRESS_3],
						Memory[TEST_ADDRESS_4],
						Memory[TEST_ADDRESS_5],
						Memory[TEST_ADDRESS_6],
						Memory[TEST_ADDRESS_7],
						Memory[TEST_ADDRESS_8],
						Memory[TEST_ADDRESS_9],
						Memory[TEST_ADDRESS_10],
						Memory[TEST_ADDRESS_11],
						Memory[TEST_ADDRESS_12]
					);
					sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)& server_addr, sizeof(SOCKADDR));
				}
			}
		}
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	char chr;
	char dummy;

	printf("\n");
	printf("Microprocessor Emulator\n");
	printf("UWE Computer and Network Systems Assignment 1\n");
	printf("\n");

	initialise_filenames();

	if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return(0);

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // Here we create our socket, which will be a UDP socket (SOCK_DGRAM).
	if (!sock) {
		// Creation failed! 
	}

	memset(&server_addr, 0, sizeof(SOCKADDR_IN));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS_SERVER);
	server_addr.sin_port = htons(PORT_SERVER);

	memset(&client_addr, 0, sizeof(SOCKADDR_IN));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr.sin_port = htons(PORT_CLIENT);

	chr = '\0';
	while ((chr != 'e') && (chr != 'E'))
	{
		printf("\n");
		printf("Please select option\n");
		printf("L - Load and run a hex file\n");
		printf("T - Have the server test and mark your emulator\n");
		printf("E - Exit\n");
		if (argc == 2) { building(argc, argv); exit(0); }
		printf("Enter option: ");
		chr = getchar();
		if (chr != 0x0A)
		{
			dummy = getchar();  // read in the <CR>
		}
		printf("\n");

		switch (chr)
		{
		case 'L':
		case 'l':
			load_and_run(argc, argv);
			break;

		case 'T':
		case 't':
			test_and_mark();
			break;

		default:
			break;
		}
	}

	closesocket(sock);
	WSACleanup();


	return 0;
}