#ifndef PRINTWINDOWS__
#define  PRINTWINDOWS__
#include <io.h>     
#include <fcntl.h>  
#include <iostream>
//todo dorobić wersję na linuxa 
void lineSetup()
{
    _setmode(_fileno(stdout), _O_U16TEXT);//to nie działa na linux
}
//│
void lineUp(bool newLine = false)
{
    std::wcout << L"│";
    if (newLine)
    {
        std::wcout << std::endl;
    }
}
//─
void lineSide(bool newLine = false)
{
    std::wcout << L"─";
    if (newLine)
    {
        std::wcout << std::endl;
    }
}
//├─
void lineInter(bool newLine = false)
{
    std::wcout << L"├─";
    if (newLine)
    {
        std::wcout << std::endl;
    }
}
//└─
void lineCorner(bool newLine = false)
{               
    std::wcout << L"└─";
    if (newLine)
    {
        std::wcout << std::endl;
    }
}

#endif // !PRINTWINDOWS__