#include "unit.cpp"
#include "NedoGraphics.cpp"
#define N 500
#define RANGE 320

void bubblesort(int a[], int n, int* m, int* c)
{
    *m = 0; *c = 0;

    for(int i = 0; i < n-1; ++i)
    {
        for(int j = n-1; j > i; --j)
        {
            *c+=1;
            if (a[j] < a[j-1])
            {
                swap(a[j],a[j-1]);
                *m+=3;
            }
        }
    }

    return;
}

void shackersort(int a[], int n, int* m, int* c)
{
    *m = 0; *c = 0;
    int k = n - 1,
        r = n - 1,
        l = 0;

    do {
        for(int i = r; i > l; i--)
        {
            *c += 1;
            if(a[i] < a[i-1])
            {
                swap(a[i],a[i-1]);
                *m += 3;
                k = i;
            }
        }
        l = k;

        for(int i = l; i < r; i++)
        {
            *c += 1;
            if(a[i] > a[i+1])
            {
                swap(a[i],a[i+1]);
                *m += 3;
                k = i;
            }
        }
        r = k;
    } while(l < r);


    return;
}

int checkErrors(int a[], int n, int sum)
{
    int errors = 0;
    if(checksum(n,a) != sum) errors++;
    if(runnumber(n,a) != 1) errors++;
    if (errors) printmas(n,a);
    return errors;
}

void getClone(int b[], int a[], int n)
{
    for (int i = 0; i<n; ++i)
    {
        *(b+i) = *(a+i);
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
    sf::RenderWindow app(sf::VideoMode(640, 544), "LAB 3");
    app.clear();

    //================BUBBLESORT===============================

    //Вывод шапки таблицы для BubbleSort
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

    //Таблица для ShackerSort
    drawText(&app,&head,"N",10+RANGE,10);
    drawText(&app,&head,"M + C \n(theory)",70+RANGE,10);
    drawText(&app,&head,"M + C (practice)",180+RANGE,10);
    drawText(&app,&head,"dec",130+RANGE,24);
    drawText(&app,&head,"rand",190+RANGE,24);
    drawText(&app,&head,"inc",250+RANGE,24);

    drawLine(&app,66+RANGE,8,66+RANGE,170,0);
    drawLine(&app,120+RANGE,8,120+RANGE,170,0);
    drawLine(&app,176+RANGE,28,176+RANGE,170,0);
    drawLine(&app,246+RANGE,28,246+RANGE,170,0);
    drawLine(&app,4+RANGE,52,314+RANGE,52,0);

    //Инициализация массива
    int m,c,sum,errors = 0;
    int a[N], b[N];

    for (int i = 1; i<=5; i++)
    {
        drawText(&app,&head,toString(i*100),10,34+i*24);
        drawText(&app,&head,toString(i*100),10+RANGE,34+i*24);

        //Теоретическая оценка
        int n = i*100;
        drawText(&app,&head,toString(2*(n*n - n)),70,34+i*24);
        drawText(&app,&head,toString(2*(n*n - n)),70+RANGE,34+i*24);
        /*
        C = (N*N - N)/2
        M (max) = 3C
        */

        //Возрастающий массив==================================
        filldec(i*100,1,i*100,a);           //Создание возрастающего массива
        getClone(b,a,i*100);                //Дублирование массива
        sum = checksum(i*100,a);            //Подсчет суммы элементов для дальнейшей проверки

        bubblesort(a,i*100,&m,&c);          //Сортировка пузырьком
        errors+=checkErrors(a,i*100,sum);   //Контрольные суммы для сортировки пузырьком
        drawText(&app,&head,toString(m+c),130,34+i*24);

        shackersort(b,i*100,&m,&c);         //Шейкерная сортировка
        errors+=checkErrors(b,i*100,sum);   //Контрольные суммы для шейкерной сортировки
        drawText(&app,&head,toString(m+c),130+RANGE,34+i*24);

        //Случайный массив=====================================
        fillrand(i*100,10,a);
        getClone(b,a,i*100);
        sum = checksum(i*100,a);

        bubblesort(a,i*100,&m,&c);
        errors+=checkErrors(a,i*100,sum);
        drawText(&app,&head,toString(m+c),190,34+i*24);

        shackersort(b,i*100,&m,&c);
        errors+=checkErrors(b,i*100,sum);
        drawText(&app,&head,toString(m+c),190+RANGE,34+i*24);

        //Убывающий массив
        fillinc(0,1,i*100,a);
        getClone(b,a,i*100);
        sum = checksum(i*100,a);

        bubblesort(a,i*100,&m,&c);
        errors+=checkErrors(a,i*100,sum);
        drawText(&app,&head,toString(m+c),250,34+i*24);

        shackersort(b,i*100,&m,&c);
        errors+=checkErrors(b,i*100,sum);
        drawText(&app,&head,toString(m+c),250+RANGE,34+i*24);

    }

    //================ПОСТРОЕНИЕ ГРАФИКА=============

    double t_bubble, t_shacker;
    int n=286;
    t_bubble = 2*(n*n - n);                    //Максимальная трудоемкость сортировки пузырьком
    t_shacker = 2*(n*n - n);//(5/4.)*(n*n - n);                   //

    //Вертикальные линии
    for(int i=24; i<310; i+=16)
    {
        drawLine(&app,i,200,i,490,1);
        drawLine(&app,i+RANGE,200,i+RANGE,490,1);
    }

    //Горизонтальные линии
    for(int i=200; i<490; i+=16)
    {
        drawLine(&app,24,i,310,i,1);
        drawLine(&app,24+RANGE,i,310+RANGE,i,1);
    }

    //Метки на шкале
    for(int i=1;i<5;++i)
    {
        drawText(&app,&head,toString(i*56),i*56+24,490);
        drawText(&app,&head,toString((int)((1/4.)*t_bubble*i)),24,490-i*56);

        drawText(&app,&head,toString(i*56),i*56+24+RANGE,490);
        drawText(&app,&head,toString((int)((1/4.)*t_shacker*i)),24+RANGE,490-i*56);
    }

    //Разыменовывание шкал (bubblesort)
    drawLine(&app,24,200,24,488,0);
    drawText(&app,&head,"Operations",30,200);
    drawLine(&app,24,488,310,488,0);
    drawText(&app,&head,"Size",290,466);
    //ShackerSort
    drawLine(&app,24+RANGE,200,24+RANGE,488,0);
    drawText(&app,&head,"Operations",30+RANGE,200);
    drawLine(&app,24+RANGE,488,310+RANGE,488,0);
    drawText(&app,&head,"Size",290+RANGE,466);

    int x=24,y_bubble,y_shacker,xp,yp_bubble,yp_shacker;
    y_bubble = y_shacker = 488;

    for(int i=1;i<=n;i++)
    {
        yp_shacker = y_shacker;
        yp_bubble = y_bubble;

        //GET Y
        fillrand(i,10,a);
        sum = checksum(i,a);
        getClone(b,a,i);

        bubblesort(a,i,&m,&c);
        errors+=checkErrors(a,i,sum);
        y_bubble = 488 - (int)((n/t_bubble)*(m+c));

        shackersort(b,i,&m,&c);
        errors+=checkErrors(b,i,sum);
        y_shacker = 488 - (int)((n/t_shacker)*(m+c));

        drawLine(&app,x,yp_bubble,x+1,y_bubble,0);
        drawLine(&app,x+RANGE,yp_shacker,x+RANGE+1,y_shacker,0);
        x++;
    }

    drawText(&app,&head,"BubbleSort",10,520);
    drawText(&app,&head,"ShackerSort",10+RANGE,520);
    drawLine(&app,RANGE,0,RANGE,544,0);

    mainLoop(&app);
    cout << "Ошибок при выполнении: " << errors << endl;

    return EXIT_SUCCESS;
}
