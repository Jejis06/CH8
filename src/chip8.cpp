#include "chip8.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

//useful macros

#define VF 0xF
#define VX 0x0F00u
#define VY 0x00F0u
#define V0 0

#define getVX\
	uint8_t Vx = (opc & VX) >> 8u;

#define getVY\
	uint8_t Vy = (opc & VY) >> 4u;

#define getByte\
	uint8_t bt = opc & 0x00FFu;

#define Debugger(T1, str , size)\
	T1 arr[]; Debug<T1>(str,arr,size);





Chip8::Chip8(bool dbg){
	//debug
	debug=dbg;
	//init program counter
	pc = OFFSET;
	//load font to memory
	for(int i=0;i<FONT_SIZE;i++){
		mem[FONT_OFFSET + i] = fontset[i];
	}
	//init instruction table

	//category unique
	ITable[0x1] = &Chip8::_1NNN;
	ITable[0x2] = &Chip8::_2NNN;
	ITable[0x3] = &Chip8::_3XKK;
	ITable[0x4] = &Chip8::_4XKK;
	ITable[0x5] = &Chip8::_5XY0;
	ITable[0x6] = &Chip8::_6XKK;
	ITable[0x7] = &Chip8::_7XKK;
	ITable[0x9] = &Chip8::_9XY0;
	ITable[0xA] = &Chip8::_ANNN;
	ITable[0xB] = &Chip8::_BNNN;
	ITable[0xC] = &Chip8::_CXKK;
	ITable[0xD] = &Chip8::_DXYN;

	ITable[0x0] = &Chip8::_GET_0;
	ITable[0xF] = &Chip8::_GET_F;
	ITable[0xE] = &Chip8::_GET_E;
	ITable[0x8] = &Chip8::_GET_8;

	for(size_t i = 0;i<=0xE;i++){
		catE[i] = &Chip8::_NULL;
		cat8[i] = &Chip8::_NULL;
		cat0[i] = &Chip8::_NULL;
	}

	//category 0
	cat0[0x0] = &Chip8::_00E0; 
	cat0[0xE] = &Chip8::_00EE;

	//category 8 
	cat8[0x0] = &Chip8::_8XY0;
	cat8[0x1] = &Chip8::_8XY1;
	cat8[0x2] = &Chip8::_8XY2;
	cat8[0x3] = &Chip8::_8XY3;
	cat8[0x4] = &Chip8::_8XY4;
	cat8[0x5] = &Chip8::_8XY5;
	cat8[0x6] = &Chip8::_8XY6;
	cat8[0x7] = &Chip8::_8XY7;
	cat8[0xE] = &Chip8::_8XYE;

	//category E

	catE[0xE] = &Chip8::_EX9E;
	catE[0x1] = &Chip8::_EXA1;

	//category F


	for(uint8_t i = 0;i<=0x65;i++){
		catF[i] = &Chip8::_NULL;
	}

	catF[0x07] = &Chip8::_FX07;
	catF[0x0A] = &Chip8::_FX0A;
	catF[0x15] = &Chip8::_FX15;
	catF[0x18] = &Chip8::_FX18;
	catF[0x1E] = &Chip8::_FX1E;
	catF[0x29] = &Chip8::_FX29;
	catF[0x33] = &Chip8::_FX33;
	catF[0x55] = &Chip8::_FX55;
	catF[0x65] = &Chip8::_FX65;

}
void Chip8::_GET_0(){
	((*this).*(cat0[opc & 0x000Fu]))();
}
void Chip8::_GET_8(){
	((*this).*(cat8[opc & 0x000Fu]))();
}

void Chip8::_GET_E(){
	((*this).*(catE[opc & 0x000Fu]))();
}

void Chip8::_GET_F(){
	((*this).*(catF[opc & 0x00FFu]))();
}
void Chip8::_NULL(){}

template <class INT> void Chip8::Debug(const char* message,  INT arr[], int s){
	if(!debug) return;
	std::cout << message;
	for(int i=0;i<s;i++){
		std::cout << ' '<<std::hex << arr[i];
	}
	std::cout << '\n';
}

void Chip8::rROM(const char* filename){
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		std::streampos S = file.tellg();
		char* buff = new char[S];

		file.seekg(0, std::ios::beg);
		file.read(buff, S);
		file.close();

		for (long i = 0; i < S; ++i)
		{
			mem[OFFSET + i] = buff[i];
		}
		delete[] buff;
	}

}

uint8_t Chip8::randomByte(){
	srand((unsigned)time(NULL));
	return rand()%(1<<8); 
}

// Instructions

//CLS
void Chip8::_00E0(){ 
	memset(video_mem, 0, sizeof(video_mem));
}

//RET
void Chip8::_00EE(){
	sp--;
	pc = stack[sp];

}

//JMP NNN

void Chip8::_1NNN(){
	uint16_t addr = opc & 0x0FFFu;
	pc = addr;
	//Debug<uint16_t>("JMP NNN",[addr], 1);
}

//CALL addr

void Chip8::_2NNN(){
	uint16_t addr = opc & 0x0FFFu;
	stack[sp] = pc;
	sp++;
	pc = addr;
}

//SE Vx, bt
void Chip8::_3XKK(){
	getVX
	getByte

	if(reg[Vx] == bt) pc += 2;
}

//SNE Vx, bt
void Chip8::_4XKK(){
	getVX
	getByte

	if(reg[Vx] != bt) pc += 2;
}

//SN Vx, Vy
void Chip8::_5XY0(){
	getVX
	getVY

	if(reg[Vx] == reg[Vy]) pc += 2;
}

//LS Vx, bt
void Chip8::_6XKK(){
	getVX
	getByte
	
	reg[Vx] = bt;
}

//ADD Vx, bt
void Chip8::_7XKK(){
	getVX
	getByte

	reg[Vx] += bt;
}

//LS Vx, Vy
void Chip8::_8XY0(){
	getVX
	getVY

	reg[Vx] = reg[Vy];
}

//OR Vx, Vy
void Chip8::_8XY1(){
	getVX
	getVY

	reg[Vx] |= reg[Vy];
}

//AND Vx, Vy
void Chip8::_8XY2(){
	getVX
	getVY

	reg[Vx] &= reg[Vy];
}

//XOR Vx, Vy
void Chip8::_8XY3(){
	getVX
	getVY

	reg[Vx] ^= reg[Vy];
}

//ADD Vx, Vy
void Chip8::_8XY4(){
	getVX
	getVY

	uint16_t sum = reg[Vx] + reg[Vy];

	//set overflow flag
	if(sum > 255U) reg[VF] = 1;
	else reg[VF] = 0;

	reg[Vx] = sum & 0xFFu;
}

//SUB Vx, Vy
void Chip8::_8XY5(){
	getVX
	getVY

	if(reg[Vx] > reg[Vy]) reg[VF] = 1;
	else reg[VF] = 0;
	
	reg[Vx] -= reg[Vy];
}

//SHR Vx
void Chip8::_8XY6(){
	getVX
	
	reg[VF] = (reg[Vx] & 0x1u); 
	reg[Vx] >>= 1;	
}

//SUBN Vx, Vy
void Chip8::_8XY7(){
	getVX
	getVY

	if(reg[Vy] > reg[Vx]) reg[VF] = 1;
	else reg[VF] = 0;

	reg[Vx] = reg[Vy] - reg[Vx];
}

//SHL Vx {Vy}
void Chip8::_8XYE(){
	getVX

	reg[VF] = (reg[Vx] & 0x80) >> 7u;
	reg[Vx] <<= 1;
}	

//SNE Vx, Vy
void Chip8::_9XY0(){
	getVX
	getVY

	if(reg[Vx] != reg[Vy]) pc+=2;
}

//LD I, addr
void Chip8::_ANNN(){
	uint16_t addr = opc & 0x0FFFu;

	ind = addr;
}

//JP V0, addr
void Chip8::_BNNN(){
	uint16_t addr = opc & 0x0FFFu;
	pc = reg[V0] + addr;
}

//RND Vx, bt
void Chip8::_CXKK(){
	getVX
	getByte
	
	reg[Vx] = randomByte() & bt;
}

//DRW Vx, Vy, nibble
void Chip8::_DXYN(){
	getVX
	getVY
	uint8_t h = opc & 0x000Fu;

	uint8_t x = reg[Vx] % VID_WIDTH;
	uint8_t y = reg[Vy] % VID_HEIGHT;

	reg[VF] = 0;
	for(unsigned int row=0;row < h;row++){
		uint8_t sprite = mem[ind + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t spritePix = sprite & (0x80u >> col);
			uint32_t* screenPix = &video_mem[(y + row) * VID_WIDTH + (x + col)];

			if (spritePix)
			{
				if (*screenPix == 0xFFFFFFFF)
				{
					reg[VF] = 1;
				}

				*screenPix ^= 0xFFFFFFFF;
			}
		}
	}
}

//SKP Vx
void Chip8::_EX9E(){
	getVX
	uint8_t button = reg[Vx];

	if(keys[button]) pc+=2;
}

//SKNP Vx
void Chip8::_EXA1(){
	getVX
	uint8_t button = reg[Vx];

	if(!keys[button]) pc+=2;
}

//LD Vx, DT
void Chip8::_FX07(){
	getVX
	reg[Vx] = delay;
}

//LD Vx, K
void Chip8::_FX0A(){
	getVX

	for(int i=0;i<16;i++){
		if(keys[i]){
			reg[Vx] = i;
			return;
		}
	}
	pc -= 2;
}

//LD DT, Vx
void Chip8::_FX15(){
	getVX
	delay = reg[Vx];
}

//LD ST, Vx
void Chip8::_FX18(){
	getVX
	soundTimer = reg[Vx];
}

//ADD I, Vx
void Chip8::_FX1E(){
	getVX
	ind += reg[Vx];
}

//LD F, Vx
void Chip8::_FX29(){
	getVX
	uint8_t num = reg[Vx];

	ind = FONT_OFFSET + (5 * num);
}

//LD B, Vx
void Chip8::_FX33(){
	getVX
	uint8_t val = reg[Vx];
	
	for(int i=2;i>=0;i--){
		mem[ind + i] = val % 10;
		val /= 10;
	}

}

//LD [I], Vx
void Chip8::_FX55(){
	getVX
	
	for(uint8_t i=0; i<= Vx; ++i){
		mem[ind + i] = reg[i];
	}	

}
//LD Vx, [I]
void Chip8::_FX65(){
	getVX
	
	for(uint8_t i=0; i<= Vx; i++){
		reg[i] = mem[ind + i];
	}	

}



	


void Chip8::Cycle(){
	opc = (mem[pc] << 8u) | mem[pc+1];
	pc += 2;
	
	((*this).*(ITable[(opc & 0xF000u) >> 12u]))();
	if(debug) 
		std::cout << std::hex \
			<< "Opcode : " << opc \
			<< " | Identifier : "<< ((opc & 0xF000u) >> 12u)\
			<< " | Linker : "<< (opc & 0x000Fu)\
			<< " | Linker(2) : "<<(opc & 0x00FFu)\
		<<'\n';
	if(delay > 0) delay--;
	if (soundTimer > 0) soundTimer--;
}

