/*
    [DIBUAT PADA 22 JUNI 2023]

    GAME TEBAK ANGKA
    PERINGATAN : (GUNAKAN PROGRAM INI DENGAN BIJAK, JANGAN UNTUK JUDI. SEMUA AKIBAT DITANGGUNG PEMAIN DAN PENGGUNA PROGRAM INI)


    Lukmanul Hakim | A11.2022.14197 | UDINUS SEMARANG
    Dosen  : Ifan Rizqa
    Matkul : Algoritma Pemrograman [ALPRO]
*/

// library yang digunakan
#include <iostream>  // sebagai standar input output
#include <fstream>   // lib untuk operasi file
#include <vector>    // lib untuk array dinamik
#include <algorithm> // lib untuk menagacak isi array yang telah diinputkan user
#include <ctime>     // lib untuk mendapatkan waktu saat ini

using namespace std;

class GuessingGame
{
private:
    // variabel untuk mentukan kesempatan menebak dalam sekali bermain
    int remainingGuesses = 3;

    // array untuk menampung inputan angka dari user
    vector<int> storeNumValue;

    // menampung hasil kombinasi acak dari inputan user
    string result = "";
    
    // status menang atau kalah
    bool win = false;
    
    // menampung nama player
    string playerName = "";
    
    // variabel untuk menampung waktu saat ini
    string currentTime;
    // menampung total kemenangan dan kekalahan
    int totalWins;
    int totalLosses;
    
    // menampung gabungan inputan user (kasus angkanya, misal 123 / 290 / 321 /dst...)
    string numberCase;
    
    // opsi untuk bermain atau tidak
    char playOption;

public:
    // fungsi untuk memasukkan nama player, serta menampilkan aturan bermain
    void PlayerName()
    {
        system("cls");
        cout << "\033[97m\n";
        cout << "-------------------------------\n";
        cout << "Masukkan nama anda : ";
        getline(cin, playerName);
        cout << "-------------------------------\n";

        // menyimpan nama player ke file
        ofstream outputFile("game_data.txt", ios::app);
        if (outputFile.is_open())
        {
            outputFile << "Nama Pemain : " << playerName << endl;
            outputFile.close();
        }
        else
        {
            cout << "Gagal membuka file." << endl;
        }

        // menampilkan intro dan aturan bermain
        cout << "============================================================\n";
        cout << "Selamat datang \033[93m" << playerName << "\033[97m di permainan tebak angka kombinasi!\n";
        cout << "Cara Bermain :\n1. Inputkan angka sebanyak 3 kali input. Setiap input, pemain boleh memasukkan lebih dari satu digit.\n2. Angka yang telah diinputkan akan diacak oleh system.\n3. Masukkan kombinasi angka agar sesuai dengan kombinasi yang telah diacak.\n";
        cout << "Anda memiliki 3 kesempatan untuk menebak kombinasi tersebut.\n";
        cout << "CLUE : Jumlah digit kombinasi yang telah diacak = jumlah digit keseluruhan dari angka yang diinputkan.\n";
        cout << "============================================================\n\n";
        cout << "Menu :\n1. Mulai Bermain\n2. Keluar\nPilih : ";
        cin >> playOption;
    }

    // fungsi untuk menampung angka inputan user ke tipe array storeNumValue
    void inputNumForRand()
    {
        int i = 0;
        while (i < 3)
        {
            // menampung sementara angka dari inputan user yang kemudian akan disimpan jadi satu di variable storageNumValue
            cout << "Inputan ke-" << i + 1 << " : ";
            int caseNumber;
            cin >> caseNumber;

            // memasukkan angka tiap inputan ke array
            storeNumValue.push_back(caseNumber);
            i++;
        }

        // mengubah integer array menjadi string
        for (int i = 0; i < 3; i++)
        {
            numberCase += to_string(storeNumValue[i]);
        }
    }

    // membuat kombinasi kunci jawaban dengan menagacak semua angka yang diinput user
    void createSecretNumber()
    {
        srand(time(NULL)); // menggunakan waktu internal untuk memili seed, sehingga kombinasi angka akan langsung teracak setalh user menginputkan angka angka nya.
        random_shuffle(storeNumValue.begin(), storeNumValue.end());

        // menampung hasil acakan ke variabel result dan mengubahnya menjadi string
        for (int i = 0; i < 3; ++i)
        {
            // menampung serta mengubah hasil acakan ke var result
            result += to_string(storeNumValue[i]);
        }

        cout << "\033[92mAngka berhasil diacak\033[97m\n";
        cout << "\033[93mSilahkan masukkan kombinasi angka untuk menebaknya (misal : 789)\033[97m\n";
    }

    // meminta user untuk menembak kombinasi hasil acakan, apakah tebakanya sama dengan kombinasi yang diacak sistem atau tidak,
    // jika sama maka setatus win berubah menjadi true jika tidak maka false
    bool answerCheck()
    {
        while (remainingGuesses > 0)
        {
            // meminta user untuk memasukkan tebakan
            cout << "Masukkan tebakkan anda: ";
            string guess;
            cin >> guess;

            // penegcekan tebakan user apakah sama dengan kombinasi di variabel result atau tidak
            // jika sama maka status win akan berubah menjadi true
            if (guess == result)
            {
                cout << "\033[92mSelamat Jawaban anda benar\033[97m";
                win = true;
                break;
            }
            // jika tidak maka game akan tetap berjalan dengan mengurangi kesempatan menebak
            else
            {
                cout << "\033[91mJawaban Salah\033[97m" << endl;
                remainingGuesses--;
            }
        }

        return win;
    }

    // fungsi untuk menjalankan fungsi input, acak kolmbinasi dan cek tebakan user
    void playGame()
    {

        inputNumForRand();
        createSecretNumber();
        answerCheck();
    }

    // menyimpan data hasil permainan, baik nama, tanggal bermain, status kemenangan, kasus anggkanya, kunci jawabannya
    void saveGameData()
    {
        ofstream outputFile("game_data.txt", ios::app);

        if (outputFile.is_open())
        {
            // menyimpan tanggal bermain
            outputFile << "Tanggal     : " << currentTime;

            // menyimpan status bermain (kalah atau menang)
            outputFile << "Status      : " << (win ? "Menang" : "Kalah") << endl;
            outputFile << "Kasus Angka : " << numberCase;
            outputFile << "\nKunci       : " << result << "\n";
            outputFile << endl;

            outputFile.close();
        }
        else
        {
            cout << "Gagal membuka file." << endl;
        }
    }

    // menyimpan total kemenangan dan kekalahan dalam permainan
    void saveTotalWinsAndLosses()
    {
        // membuat file "game_data.txt" jika file belum tersedia, kemudian menyimpan total kemenangan dan kekalahan ke dalam file
        ofstream outputFile("game_data.txt", ios::app);

        if (outputFile.is_open())
        {
            outputFile << "=====================" << endl;
            outputFile << "Total Kemenangan : " << totalWins << endl;
            outputFile << "Total Kekalahan  : " << totalLosses << endl;
            outputFile << "====================="
                       << "\n\n";

            outputFile.close();
        }
        else
        {
            cout << "Gagal membuka file." << endl;
        }
    }

    // menghitung total menang dan kalah, tergantung setatus kemenangan dari variabel win
    void countWinsAndLosses()
    {
        // melakukan riset total kemenangan dan kekalahan
        resetTotalWinsAndLosses();
        // var untuk menampung inputan dari opsi bermain (akan lanjut bermain )
        char choice;

        do
        {
            GuessingGame game;
            game.playGame();
            game.getCurrentTime();
            game.saveGameData();

            // jika menang maka jumlah kemenangan akan ditambah
            if (game.isWin())
            {
                totalWins++;
            }

            // jika kalah, maka total kekalahan yang akan ditambah
            else
            {
                totalLosses++;
            }

            /* tawaran untuk bermain lagi, jika y (iya), maka permainan akan dimulai kembali, 
            namun pemain tidak diminta memasukkan nama pemain, melainkan akan langsung menginputkan 
            angka-angka yang akan di acak yang sselanjutnya akan dijadikan kombinasi kunci tebakan.
            Serta total kemenagan dan kekalahan akan digabungkan dengan total kemenangan atau kekalahan permainan sebelumnya 


            Jika memilih n (tidak) maka akan ditampilkan total menang dan kalahnya, dan permainan akan berhenti.
            Serta total kemenangan dan kekalahan yang ada disistem akan direset menjadi 0 kembali, 
            sehingga ketika ada pemain lain yang menjalankan program, total kemenangan dan kekalahan dimulai dari 0 lagi
            */

            cout << "\nApakah Anda ingin bermain lagi? (y/n): ";
            cin >> choice;

            // membersihkan console
            system("cls");

        } while (choice == 'y' || choice == 'Y');

        // AKAN DILAKUKAN JIKA USER MEMILIH n (TIDAK)
        // menyimpan total menang dan kalah
        saveTotalWinsAndLosses();
        // menampilkan total menang dan kalah
        cout << "PERMAINAN SELESAI, TERIMAKASIH\n";
        cout << "+---------------------------------+\n";
        cout << "\033[92mTotal Kemenangan\033[97m: " << totalWins << endl;
        cout << "\033[91mTotal Kekalahan\033[97m : " << totalLosses << endl;
        cout << "+---------------------------------+";
    }

    // mereset jumlah total kemenangan dankekalahan agar setiap prorgram pertama kali dijanlankan total menang dan kalah dimulai dari nilai 0
    void resetTotalWinsAndLosses()
    {
        totalWins = 0;
        totalLosses = 0;
    }

    // untuk mengembalikan status false atau true pada variabel win
    bool isWin() const
    {
        return win;
    }

    // mengambil waktu saat ini (sesuai waktu dari perangkat yang dipakai)
    void getCurrentTime()
    {
        // mengambil waktu saat ini
        time_t now = time(0);
        char *thisTime = ctime(&now);

        // menyimpannya ke variabel currentTime
        currentTime = thisTime;
    }

    // menjalankan game
    void run()
    {
        PlayerName();

        // opsi  bermain
        switch (playOption)
        {
            // jika pemain memilih opsi 1 maka permainan akan dijalankan,
        case '1':
            countWinsAndLosses();
            break;
            //  jika memilih selain 1 maka permainan akan berhenti
        default:
            break;
        }
    }
};
