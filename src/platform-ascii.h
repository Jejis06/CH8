#include <chrono>
#include <iostream>
#include <string>
#include <map>

class Platform{
	public:
		Platform(int w, int h, int s);

		//functions
		std::string rgb(int r, int g, int b);
		std::string Color(std::string foreground, std::string background="");

		template<class T>void Frame(const T* buf);
		bool input(uint8_t* ptr, char in);
		
		//variables
		int width;
		int height;
		int scale;

		std::string white = rgb(255,255,255);
		std::string black = rgb(0,0,0);
		std::string color_clear = "\033[0m";

		std::map <int,std::string> pixel = {
			{0, Color(black,black) + "   "},
			{1, Color(white, white) + " # "}
		};
		std::map<char, int>  keypad = {
			{'1',0x1}, {'2',0x2}, {'3',0x3}, {'4',0xC},
			{'q',0x4}, {'w',0x5}, {'e',0x6}, {'r',0xD},
			{'a',0x7}, {'s',0x8}, {'d',0x9}, {'f',0xE},
			{'z',0xA}, {'x',0x0}, {'c',0xB}, {'v',0xF}
		};




};