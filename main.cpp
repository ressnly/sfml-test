#include "unit.cpp"
#include "NedoGraphics.cpp"
#define N 500

void bubblesort(int a[], int n, int* m, int* c)
{
    *m = 0; *c = 0;
    int _empty;

    for(int i = 0; i < n-1; ++i)
    {
        for(int j = n-1; j > i; --j)
        {
            *c+=1;
            if (a[j] < a[j-1])
            {
                _empty = a[j];
                a[j] = a[j-1];
                a[j-1] = _empty;
                *m+=3;
            }
        }
    }

    return;
}

int main()
{
    //================SFML INIT==========================
    // Настройка шрифта
    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text head("",font,12);
    head.setPosition(10, 10);
    head.setCharacterSize(14);

    // Создание окна
    sf::RenderWindow app(sf::VideoMode(320, 520), "LAB 3");
    app.clear();

    //================BUBBLESORT=========================

    //Таблица
    drawText(&app,&head,"N",10,10);
    drawText(&app,&head,"M + C \n(theory)",70,10);
    drawText(&app,&head,"M + C (practice)",180,10);
    drawText(&app,&head,"dec",130,24);
    drawText(&app,&head,"rand",190,24);
    drawText(&app,&head,"inc",250,24);

    drawLine(&app,66,8,66,170,0);
    drawLine(&app,120,8,120,170,0);
    drawLine(&app,176,28,176,170,0);
    drawLine(&app,246,28,246,170,0);
    drawLine(&app,4,52,314,52,0);

    //Инициализация массива
    int m,c;
    int a[N];

    for (int i = 1; i<=5; i++)
    {
        drawText(&app,&head,toString(i*100),10,34+i*24);

        //Теоретическая оценка
        int n = i*100;
        drawText(&app,&head,toString(2*(n*n - n)),70,34+i*24);
        /*
        C = (N*N - N)/2
        M (max) = 3C
        */

        //Возрастающий массив
        filldec(i*100,1,i*100,a);
        bubblesort(a,i*100,&m,&c);
        drawText(&app,&head,toString(m+c),130,34+i*24);

        //Случайный массив
        fillrand(i*100,10,a);
        bubblesort(a,i*100,&m,&c);
        drawText(&app,&head,toString(m+c),190,34+i*24);

        //Убывающий массив
        fillinc(0,1,i*100,a);
        bubblesort(a,i*100,&m,&c);
        drawText(&app,&head,toString(m+c),250,34+i*24);

    }

    //================ПОСТРОЕНИЕ ГРАФИКА=============

    double t;
    int n=286;
    t = 2*(n*n - n);

    //Вертикальные линии
    for(int i=24; i<310; i+=16)
    {
        drawLine(&app,i,200,i,490,1);
    }

    //Горизонтальные линии
    for(int i=200; i<490; i+=16)
    {
        drawLine(&app,24,i,310,i,1);
    }

    //Метки
    for(int i=1;i<5;++i)
    {
        drawText(&app,&head,toString(i*56),i*56+24,490);
        drawText(&app,&head,toString((int)((1/4.)*t*i)),24,490-i*56);
    }

    //График
    drawLine(&app,24,200,24,488,0);
    drawText(&app,&head,"Operations",30,200);
    drawLine(&app,24,488,310,488,0);
    drawText(&app,&head,"Size",290,466);

    int x=24,y=488,xp,yp;

    for(int i=1;i<=n;i++)
    {
        xp = x;
        yp = y;

        x++;

        //GET Y
        fillrand(i,10,a);
        bubblesort(a,i,&m,&c);
        y = 488 - (int)((n/t)*(m+c));

        drawLine(&app,xp,yp,x,y,0);
    }

    mainLoop(&app);

    return EXIT_SUCCESS;
}
