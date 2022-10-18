#include <iostream>
#include "chip8.cpp"
#include "platform-ascii.cpp"
#include "CORE.h"

using namespace std;

int main(int argc, const char* argv[]){
	if (argc < 4){
		cout << "How to use : " << argv[0] << " <Scale> <Delay> <ROM>\n";
		return 1;
	}
	int scale = stoi(argv[1]);
	int delay = stoi(argv[2]); 
	const char* rom = argv[3];

	Platform game(VID_WIDTH,VID_HEIGHT,scale);
	Chip8 CHIP((argc >= 5));
	CHIP.rROM(rom);
	int vidp = sizeof(CHIP.video_mem[0]) * VID_WIDTH;


	auto t0 = chrono::high_resolution_clock::now();

	raw_mode_on();
	bool q = false;

	while(!q){
		//check input
		if(kbhit()){
			char t = getch(); 
			q = game.input(CHIP.keys,t);
			
			
			raw_mode_off();
			raw_mode_on();
		}	
		
			
		
		auto t1 = chrono::high_resolution_clock::now();
		float dt = chrono::duration<float, chrono::milliseconds::period>(t1 - t0).count();

		//genenerate and draw frame
		if(dt > delay){
			t0 = t1;
			
			CHIP.Cycle();
					
			game.Frame<uint32_t>(CHIP.video_mem);
			
			for(auto const& key : game.keypad){
				CHIP.keys[key.second] = 0;
			}
		}
		
	
	}
	raw_mode_on();
	tcflush(0, TCIFLUSH);
	return 0;
}
	
