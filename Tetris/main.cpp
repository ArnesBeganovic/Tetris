#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };
struct Point 
{ int x, y; } a[4], b[4];


int figures[7][4] =
{
	1,3,5,7,//I
	2,4,5,7,//Z
	3,5,4,6,//S
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//O

};

bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
			return 0;
		}
		else if (field[a[i].y][a[i].x]) {
			return 0;
		}
		return 1;
	}
	
}

int main()
{
	srand(time(0));

	//Render window - work place
	RenderWindow window(VideoMode(329, 480), "The Game!");

	//Load image from folder
	Texture t;
	t.loadFromFile("../Images/tiles.png");

	//Get one sprite from image
	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	//controll rotation and left/right movements
	int dx = 0; bool rotate = 0; int colorNum = 1;

	float timer = 0, delay=0.3;
	Clock clock;

	//Game play loop
	while (window.isOpen())
	{
			
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer = timer + time;

		//wait for following events
		Event e;
		while (window.pollEvent(e))
		{
			//if closed
			if (e.type == Event::Closed) {
				window.close();
			}
			//if KeyPressed
			if (e.type == Event::KeyPressed) {
				switch (e.key.code) {
					case Keyboard::Up:
						rotate = true;
						break;
					case Keyboard::Left:
						dx = -1;
						break;
					case Keyboard::Right:
						dx = 1;
						break;
				}
			}

		}

		// Move tile after event keypress. Initially it is 0 and after key press it is changed +-1
		for (int i = 0; i < 4; i++) {
			a[i].x = a[i].x + dx;
		}

		//Rotate after event.
		if (rotate == true) {
			Point p = a[1];//center of rotation
			for (int i = 0; i < 4; i++) {
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++) {
					a[i] = b[i];
				}
			}
		}


		//Tikaj vrijeme i za svakih 0.3 sekunde spustaj jednu
		if (timer > delay) {
			for (int i = 0; i < 4; i++) {
				a[i].y = a[i].y + 1;
			}

			if (!check()) {
				for (int i = 0; i < 4; i++) {
					field[b[i].y][b[i].x] = colorNum;
				}
				colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++) {
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer = 0;
		}


		

		//nuliraj pomjeranje i rotaciju za iduci krug
		dx = 0; rotate = 0;
		//make window white background
		window.clear(Color::White);


		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (field[i][j] == 0) {
					continue;
					
				}
				s.setPosition(j * 18, i * 18);
				window.draw(s);
			}
		}
		


		//show 4 tiles based on struckt
		for (int i = 0; i < 4; i++) {
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
		}


		
		window.display();
	}
	
	return 0;
}

