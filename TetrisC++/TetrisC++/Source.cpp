#include <SFML/Graphics.hpp> // библиотека для 2d грифики 
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

const int M = 20;//ширина
const int N = 10;//длина

int field[M][N] = { 0 };
int w = 34; // размер ячеек у фигур 

//Структура плитки
struct Point
{
    int x, y;
}a[4], b[4];

int figures[7][4] = {
    1,3,5,7, //0 Прямоугольник
    2,4,5,7, //1 Cleveland Z влево
    3,5,4,6, //2 Cleveland Z вправо
    3,5,4,7, //3 T
    2,3,5,7, //4 Г 
    3,5,7,6, //5 Г вниз 
    2,3,4,5, //6 Квадрат 
};

//Проверка 

bool check() { 
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return 0;
        else if (field[a[i].y][a[i].x])
            return 0;

    return 1;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(N * w, M * w), "Tetris!");

    Texture t;
    t.loadFromFile("figures/figures2.png"); //Путь к файлу 

    Sprite tiles(t);//загружаем плитки

    int dx = 0, colorNum = 1;
    bool rotate = false;

    //Движение ввниз по таймеру 
    float timer = 0, delay = 0.3;
    Clock clock;
    bool ad = true;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Up)
                    rotate = true;
                else if (event.key.code == Keyboard::Right)
                    dx = 1;
                else if (event.key.code == Keyboard::Left)
                    dx = -1;
        }


        if (Keyboard::isKeyPressed(Keyboard::Down)) // при нажатии вниз фигура ускоряется и падает ввниз 
            delay = 0.05;

        //Управление фигурой//

        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check()) {
            for (int i = 0; i < 4; i++)
                a[i] = b[i];
        }

        if (rotate) {
            Point p = a[1];
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;

                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            //проверка на лож чек
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
            }
        }

        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }
            //проверка на лож чек
            if (!check()) {
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;
                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        if (ad) {
            int n = rand() % 7;
            if (a[0].x == 0)
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            ad = false;
        }

        int k = M - 1; // Очитска строки при заполне
        for (int i = M - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if (count < N)
                k--;
        }

        dx = 0;
        rotate = false;
        delay = 0.3;

        window.clear(Color::White);

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;
                tiles.setTextureRect(IntRect(field[i][j] * w, 0, w, w));
                tiles.setPosition(j * w, i * w);
                window.draw(tiles);
            }

        for (int i = 0; i < 4; i++) {
            tiles.setTextureRect(IntRect(colorNum * w, 0, w, w));
            tiles.setPosition(a[i].x * w, a[i].y * w);
            window.draw(tiles);
        }

        window.display();
    }

    return 0;
}