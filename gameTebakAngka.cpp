/*
    [DIBUAT PADA 22 JUNI 2023]

    GAME TEBAK ANGKA
    PERINGATAN : (GUNAKAN PROGRAM INI DENGAN BIJAK, JANGAN UNTUK JUDI. SEMUA AKIBAT DITANGGUNG PEMAIN DAN PENGGUNA PROGRAM INI)


    Lukmanul Hakim | A11.2022.14197 | UDINUS SEMARANG
    Dosen  : Ifan Rizqa
    Matkul : Algoritma Pemrograman [ALPRO]
*/

// standar input output
#include <iostream>

// mengaitkan file gameConfig yang telah dibuat
#include "gameConfig.h"
using namespace std;

int main()
{
    // membuat object game
    GuessingGame game;

    // memanggil method run, yang ada di dalam object untuk menjalankan gamenya.
    game.run();

    return 0;
}
