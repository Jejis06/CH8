#include "platform-ascii.h"

using namespace std;


Platform::Platform(int w, int h, int s){
	width = w;
	height = h;
	scale = s;
}


template<class T>void Platform::Frame(const T* buf){
	system("clear");
	for(int y=0;y<height;y++){
		//apply horizontal scale
		for(int j=0; j<scale; j++){

			for(int x=0;x<width;x++){
				int pix = (buf[y * width + x] == 0xFFFFFFFF)?1:0;
				

				//apply vertical scale
				for(int i=0;i<scale;i++){
					cout << pixel[pix];

				}
			}
			cout << color_clear << '\n';

		}
	}
	
}

string Platform::Color(string foreground, string background){
	/*
		\033[38;2;<r>;<g>;<b>m     #Select RGB foreground color
		\033[48;2;<r>;<g>;<b>m     #Select RGB background color

		\033[38;2;<r>;<g>;<b>;48;2;<r>;<g>;<b>m
	*/
	if(foreground == "") return "\033[48;2" + background + 'm';
	else if(background == "") return "\033[38;2" + foreground + 'm';
	return "\033[38;2" + foreground + ";48;2" + background + 'm';
}

string Platform::rgb(int r, int g, int b){
	return ';' + to_string(r) + ';' + to_string(g) + ';' + to_string(b);	
}

bool Platform::input(uint8_t* ptr, char in){
	bool q = false;
	if (in == ';') q = true;
	
	for(auto const& key : keypad){
		ptr[key.second] = 0;
	}
	ptr[keypad[in]] = 1;
	
	return q;
}	

/*
for(auto const& key : game.keypad){
				CHIP.keys[key.second] = 0;
			}
			*/