DEL bin\APP.exe

REM g++ -Iinc -Llib -obin\APP.exe src\Main.cpp -lsfml-graphics -lsfml-window -lsfml-system
mingw32-make

DEL *.o /s

CD bin
APP.exe