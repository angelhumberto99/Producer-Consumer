#ifndef CURSOR_H
#define CURSOR_H

    #include <stdio.h>
    #if _WIN64 || _WIN32    //define los macros de CLEAR, SLEEP, GETCH, GETCHE y KBHIT para Windows
        #include <Windows.h>
        #include <conio.h>
        #define CLEAR system("cls")
        #define SLEEP(x) Sleep(x)
        #define GETCH() getch()
        #define GETCHE() getche()
        #define KBHIT() kbhit()
    #else                   //define los macros de CLEAR, SLEEP, GETCH, GETCHE y KBHIT para Linux
        #include <termios.h>
        #include <unistd.h>
        #include <fcntl.h>
        #include <chrono>
        #include <thread>
        #define CLEAR system("clear");
        #define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

        int GETCH() {
            struct termios oldattr, newatrr;
            int ch;
            tcgetattr( STDIN_FILENO, &oldattr );
            newatrr = oldattr;
            newatrr.c_lflag &= ~( ICANON | ECHO );
            tcsetattr( STDIN_FILENO, TCSANOW, &newatrr );
            ch = getchar();
            tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
            return ch;
        }

        int GETCHE() {
            struct termios oldattr, newatrr;
            int ch;
            tcgetattr( STDIN_FILENO, &oldattr );
            newatrr = oldattr;
            newatrr.c_lflag &= ~( ICANON );
            tcsetattr( STDIN_FILENO, TCSANOW, &newatrr );
            ch = getchar();
            tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
            return ch;
        }

        int KBHIT() {
            struct termios oldt, newt;
            int ch;
            int oldf;

            tcgetattr( STDIN_FILENO, &oldt );
            newt = oldt;
            newt.c_lflag &= ~( ICANON | ECHO );
            tcsetattr( STDIN_FILENO, TCSANOW, &newt);
            oldf = fcntl( STDIN_FILENO, F_GETFL, 0 );
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

            ch = GETCH();

            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, oldf);

            if(ch != EOF) {
                ungetc( ch, stdin );
                return 1;
            }
            return 0;
        }
        
    #endif


    #define GOTO_XY(x, y) printf("%c[%d;%df",0x1B,y,x);  //macro para definir las coordenadas donde imprimir
    #define HIDE_CURSOR printf("\e[?25l");   //macro para esconder el cursor
    #define SHOW_CURSOR printf("\e[?25h");   //macro para mostrar el cursor

#endif
