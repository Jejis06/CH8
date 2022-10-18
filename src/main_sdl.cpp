#include <iostream>
#include "platform.h"
#include "chip8.cpp"
using namespace std;

int main(int argc, const char* argv[]){
	if (argc < 4){
		cout << "How to use : " << argv[0] << " <Scale> <Delay> <ROM>\n";
		return 1;
	}
	int scale = stoi(argv[1]);
	int delay = stoi(argv[2]); 
	const char* rom = argv[3];

	
	Platform game("CHIP-8", VID_WIDTH*scale, VID_HEIGHT * scale, VID_WIDTH, VID_HEIGHT);
	
	Chip8 CHIP((argc >= 5));
	CHIP.rROM(rom);

	int vidp = sizeof(CHIP.video_mem[0]) * VID_WIDTH;
	auto lastCycleTime = std::chrono::high_resolution_clock::now();{}
	bool q = false;

	while(!q){
		q = game.ProcessInput(CHIP.keys);


		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > delay)
		{
			lastCycleTime = currentTime;
			CHIP.Cycle();
			game.Update(CHIP.video_mem, vidp);
		}

	}
	
	return 0;
}
	
