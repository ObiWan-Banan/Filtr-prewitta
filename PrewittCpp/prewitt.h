#pragma once

#ifdef PREWITTCPP_EXPORTS
#define PREWITTCPP_API __declspec(dllexport)
#else
#define PREWITTCPP_API __declspec(dllimport)
#endif


/*Funkcja stosuje na przekazanej tablicy pikseli filtr Prewitta i zapisuje go do tablicy wynikowej
* Funkcja nie sprawdza poprawno�ci danych wej�ciowych.
* @param inputArray: char* tablica pikseli bez paddingu
* @param outputArray: char* tablica o takiej samej wielko�ci co inputArray, do kt�rej zapisywany jest wynik dzia�ania algorytmu.
* @param width: int Szeroko�� bitmapy w pikselach.
* @param start_height: int kolumna bitmapy od kt�rej funkcja zacznie wykonywanie algorytmu. W przypadku dzia�ania na 1 w�tku poda� 0,
  w przypadku dzia�ania na 2 poda� po�owe wysoko�ci bitmapy w pikselach itd.
* @param stop_height: int kolumna bitmapy na kt�rej algorytm sko�czy prace. W przypadku pracy na wielu w�tkach ka�dy w�tek z wyj�tkiem ostatniego
  (lub pierwszego je�li jest tylko jeden) musi dosta� ten parametr powi�kszony o 2.
* @result Wynik dzia�ania funkcji zapisany jest w tablicy outputArray.
*/
extern "C" PREWITTCPP_API void prewittFilter(char* inputArray, char* outputArray, int width, int start_height, int stop_height);