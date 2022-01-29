#include <iostream>
#include <SFML/Graphics.hpp> // библиотека для 2d грифики 

using namespace std;
using namespace sf;

const int SH = 20; //ширина
const int DL = 20; //длина

int field[SH][DL] = { 0 };

int w = 34; // размер ячеек у фигур ;


//Структура плитки
struct Point 
{
	int x, y;
}a[4],b[4];

int figures[7][4] = {
	1,3,5,7, //0 Прямоугольник
	2,4,5,7, //1 Cleveland Z влево
	3,5,4,6, //2 Cleveland Z вправо
	3,5,4,7, //3 T
	2,3,5,7, //4 Г 
	3,5,7,6, //5 Г вниз 
	2,3,4,5, //6 Квадрат 
};

int main()
{
	RenderWindow window(VideoMode(DL * w, SH * w), "Tetris");

	Texture t;
	t.loadFromFile("C:/Users/besia/source/repos/TetrisC++/TetrisC++/figures/figures.png");

	Sprite tiles(t);//загружаем плитки
	tiles.setTextureRect(IntRect(0, 0, w, w));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		int n = 4; //Выбераем фигуру

		for (int i=0;i<4;i++) 
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

		window.clear(Color::White);

		for (int i = 0; i < 4; i++)
		{
			tiles.setPosition(a[i].x * w, a[i].y * w);
			window.draw(tiles);
		}

		window.display();

	}



	return 0;
}
