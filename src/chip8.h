#include <cstdint>
#include <chrono>
#include <cstring>

//define offsets
#define OFFSET 0x200
#define FONT_OFFSET 0x50

#define VID_WIDTH 64
#define VID_HEIGHT 32

#define FONT_SIZE 80

class Chip8{
	public:
		//functions
		Chip8(bool dbg);

		void Cycle();

		void rROM(const char* file);
		uint8_t randomByte();

		template <class INT> void Debug(const char* message,  INT arr[]={}, int s={});

		typedef void (Chip8::*Func)();

		//Instructions separated into different categories dependig on starting digits
		Func ITable[0xF + 1];

		Func cat0[0xE + 1];
		Func cat8[0xE + 1];
		Func catE[0xE + 1];
		Func catF[0x65 + 1];

		void _GET_8();
		void _GET_E();
		void _NULL();
		void _GET_F();
		void _GET_0();		
		

		void _00E0(); 
		void _00EE();
		void _1NNN();
		void _2NNN();
		void _3XKK();
		void _4XKK();
		void _5XY0();
		void _6XKK();
		void _7XKK();
		void _8XY0();
		void _8XY1();
		void _8XY2();
		void _8XY3();
		void _8XY4();
		void _8XY5();
		void _8XY6();
		void _8XY7();
		void _8XYE();
		void _9XY0();
		void _ANNN();
		void _BNNN();
		void _CXKK();
		void _DXYN();
		void _EX9E();
		void _EXA1();
		void _FX07();
		void _FX0A();
		void _FX15();
		void _FX18();
		void _FX1E();
		void _FX29();
		void _FX33();
		void _FX55();
		void _FX65();

		uint8_t reg[16]{};

		uint8_t mem[4096]{};
		uint32_t video_mem[64*32]{};// 64*32 - resolution of chip8

		uint16_t ind{};
		uint16_t pc{};
		uint16_t opc;

		uint16_t stack[16]{};
		uint8_t sp{};

		uint8_t delay{};
		uint8_t soundTimer{};

		uint8_t keys[16]{};
		uint8_t fontset[FONT_SIZE] =
		{
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80  // F
		};
		bool debug=false;


};
