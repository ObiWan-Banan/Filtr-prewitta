#pragma once

#ifdef PREWITTCPP_EXPORTS
#define PREWITTCPP_API __declspec(dllexport)
#else
#define PREWITTCPP_API __declspec(dllimport)
#endif


/*Funkcja stosuje na przekazanej tablicy pikseli filtr Prewitta i zapisuje go do tablicy wynikowej
* Funkcja nie sprawdza poprawnoœci danych wejœciowych.
* @param inputArray: char* tablica pikseli bez paddingu
* @param outputArray: char* tablica o takiej samej wielkoœci co inputArray, do której zapisywany jest wynik dzia³ania algorytmu.
* @param width: int Szerokoœæ bitmapy w pikselach.
* @param start_height: int kolumna bitmapy od której funkcja zacznie wykonywanie algorytmu. W przypadku dzia³ania na 1 w¹tku podaæ 0,
  w przypadku dzia³ania na 2 podaæ po³owe wysokoœci bitmapy w pikselach itd.
* @param stop_height: int kolumna bitmapy na której algorytm skoñczy prace. W przypadku pracy na wielu w¹tkach ka¿dy w¹tek z wyj¹tkiem ostatniego
  (lub pierwszego jeœli jest tylko jeden) musi dostaæ ten parametr powiêkszony o 2.
* @result Wynik dzia³ania funkcji zapisany jest w tablicy outputArray.
*/
extern "C" PREWITTCPP_API void prewittFilter(char* inputArray, char* outputArray, int width, int start_height, int stop_height);