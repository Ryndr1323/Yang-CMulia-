// Package
#include <iostream>
#include <string>
// Macro
#include "bonefunction.h"
#include "menuinterface.h"

// Constant Value of Menu Size
const int minSizeFP = 1;
const int maxSizeFP = 9;
const int SizeBuffer = 256;
// Constant Value of Int of Creator
const std::string creator1 = "XXXXXXXXXXXX";
const std::string creator2 = "XXXXXXXXXXXX";

// Front Pages
void frontPageTitle(){
    std::string FormatT2 = "[={By[" + creator1 + std::string("|") + creator2 + std::string("]}{v01}=]\n");
    std::string Finalized =
      std::string("[PROGRAM SIMULASI PLAYLIST]\n")
    + FormatT2;

    std::cout << Finalized;
};
void frontPage(Structure S, bool ExtraParam){
    bool EmptyPL = checkEmptyPlaylist(S);
    // Formatting Format follows: FormatXY, whereas X is {H = Header, A = Menu Text, F = Footer} and Y is position of Formatter
    // Headers
    std::string FormatH1    = "o=[Menu Utama]" + OutputBorder(66, false, false, "", false) + std::string("\n");
    std::string FormatH2    = "o={Legenda Menu Utama}"+ std::string("\n");
    std::string FormatH2Des = "| >>> [REC] Direkomendasikan, [NR] Tidak Direkomendasikan" + std::string("\n");
    std::string FormatH3    = "o={Legenda Sub-Menu}" + std::string("\n");
    std::string FormatH3Des = "| >>> [<] Kembali ke Menu Utama" + std::string("\n")
                            + "| >>> [!] Informasi" + std::string("\n")
                            + "| >>> [?]/[C] Permintaan Masukkan/Konfirmasi" + std::string("\n")
                            + "| >>> [S]/[A] Aksi Sukses/Diterima" + std::string("\n");
                            + "| >>> [E]/[X] Aksi Gagal/Tidak Diterima" + std::string("\n");
    // Menu Addition
    std::string FormatA1    = "o=o-(1) Buat Playlist Baru" + std::string(24, ' ') + (EmptyPL ? "[REC]\n" : "\n");
    std::string FormatA2    = "| |-(2) Lihat Playlist dan Musik Anda" + std::string(13, ' ') + (EmptyPL ? "[NR]\n" : "\n");
    std::string FormatA3    = "| |-(3) Mainkan Playlist Anda" + std::string(21, ' ') + (EmptyPL ? "[NR]\n" : countWithDataPlaylist(S) == 0 ? "\n" : "[REC]\n");
    std::string FormatA4    = "| |-(4) Sisipkan Musik ke dalam Playlist Anda" + std::string(5, ' ') + (EmptyPL ? "[NR]\n" : "[REC]\n");
    std::string FormatA5    = "| |-(5) Ubah Nama Genre pada Playlist Anda" + std::string(8, ' ') + (EmptyPL ? "[NR]\n" : "\n");
    std::string FormatA6    = "| |-(6) Ubah Data Musik Anda" + std::string(22, ' ') + (EmptyPL ? "[NR]\n" : "\n");
    std::string FormatA7    = "| |-(7) Hapus Data Musik Anda" + std::string(21, ' ') + (EmptyPL ? "[NR]\n" : "\n");
    std::string FormatA8    = "| |-(8) Hapus Data Playlist Anda" + std::string(18, ' ') + (EmptyPL ? "[NR]\n" : "\n");
    std::string FormatA9    = "| o-(9) " + std::string(ExtraParam ? "Sembunyikan Legenda" : "Tampilkan Legenda") + std::string("\n");
    // Footers
    std::string FormatF1    = "o===(0) Keluar dan Tutup Aplikasi" + std::string("\n");
    std::string Finalized   = 
            FormatH1
          + (ExtraParam ? (FormatH2 + FormatH2Des) + (FormatH3 + FormatH3Des) : "")
          + FormatA1
          + FormatA2
          + FormatA3
          + FormatA4
          + FormatA5
          + FormatA6
          + FormatA7
          + FormatA8
          + FormatA9
          + FormatF1;
    std::cout << Finalized;
};
void frontPageInput(int &Input){
    int FuncInput = 0;
    std::string errMessage;
    std::cout << "| Masukkan Nomor " << minSizeFP << "-" << maxSizeFP << " atau \"0\" untuk Memulai:" << std::flush;
    std::cin >> FuncInput;
    
    if(std::cin.fail()){
        errMessage = "|-[E] Masukan Anda Tidak Valid (Bukan Integer), akan Diaplikasikan Nilai \"-1\"\n";
        FuncInput = -1;
        std::cout << errMessage;
        std::cin.clear();
        std::cin.ignore(SizeBuffer, '\n');
    } else if((FuncInput < minSizeFP || FuncInput > maxSizeFP) && FuncInput != 0){
        errMessage = "|-[E] Masukan Anda Tidak Valid (Diluar Batas Pilihan yang Ada), akan Diaplikasikan Nilai \"-1\"\n";
        FuncInput = -1;
        std::cout << errMessage;
    }

    Input = FuncInput;
};
// Case Pages - Condition 1
void ActionSimulateMusic(Structure &S){
    // Message Assembler For Available Playlist(s)
    adrPlayNode traverse = S.first;
    std::string ExistData = "";
    while(traverse != nullptr){
        ExistData += (traverse->infotype.genre + " (" + std::to_string(traverse->infotype.musicCount) + " Lagu)");
        if(traverse->next != nullptr){
            ExistData += ", ";
        };

        traverse = traverse->next;
    };
    std::string FuncInput;
    int LoopAmount;
    // Playlist
    std::cout << "|-[!][Tersedia: " << ExistData << "]"<< std::endl << "|-[C] Masukkan Playlist yang Anda Ingin Mainkan: " << std::flush;
    std::cin >> FuncInput;
    adrPlayNode PlayPL = findPlaylist(S, FuncInput);
    if(PlayPL != nullptr){
        if(checkEmptySong(PlayPL->attach)){
            std::cout << "|-[X] Tidak Ada Musik pada Playlist Ini!" << std::endl;
        } else {
            std::cout << "| Masukkan Jumlah Repeat yang Anda Inginkan: " << std::flush;
            std::cin >> LoopAmount;
            if(std::cin.fail() || LoopAmount < 0){
                std::cout << "|-[E] Masukkan \"" << LoopAmount << "\" Tidak Valid, akan Diaplikasikan Nilai 1" << std::endl;

                LoopAmount = 1;
                std::cin.clear();
                std::cin.ignore(SizeBuffer, '\n');
            } else {
                std::cout << "|-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
            };
            
            if(LoopAmount != 0){
                playPlaylist(PlayPL->attach, LoopAmount);
            }
        };
    } else {
        std::cout << "|-[E] Tidak Dapat Menemukan Genre \"" << FuncInput << "\"" << std::endl;
    };
};
void ActionEditPlaylistMD(Structure &Data){
    std::cout << OutputBorder(80, true, true, "Ubah Metadata - Playlist", true);

    int msgIteration = 0;
    int msg2ndIteration = 0;
    bool MainChange;
    bool interuptSignal1 = false;
    bool interuptSignal2 = false;
    std::string msgBuilder;
    
    MainChange = true;
    while(!interuptSignal1){
        msg2ndIteration = 0;
        interuptSignal2 = false;
        std::string InputPlaylist;
        // Message Builder - Shows Information of Available Genre with Data
        adrPlayNode msgNode = Data.first;
        if(MainChange){
            while(msgNode != nullptr){
                msgBuilder += "| | >>> Genre " + msgNode->infotype.genre + "\n";

                msgNode = msgNode->next;
            };

            MainChange = false;
        };
        std::cout << "| |-[!] Genre yang Ada" << std::endl << msgBuilder;
        if(msgIteration == 0){
            std::cout << "| |-[!] Untuk Kembali ke Menu Utama, Masukkan \"back\" (Tanpa Tanda Petik)" << std::endl;
            msgIteration++;
        } else if(msgIteration == 3){
            msgIteration = 0;
        } else {
            msgIteration++;
        };
        std::cout << "| |-[?] Masukkan Playlist yang Anda Ingin Ubah: " << std::flush;
        std::cin >> InputPlaylist;
        if(convertToLower(InputPlaylist) == "back"){
            interuptSignal1 = true;

            std::cout << "| o-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
        } else {
            adrPlayNode TargetPL = findPlaylist(Data, InputPlaylist);
            if(TargetPL == nullptr){
                std::cout << "| |-[E] Tidak Dapat Menemukan Playlist Bergenre \"" << InputPlaylist << "\", Mengembalikan Anda ke Menu Informasi" << std::endl;
            } else {
                std::cout << "| |-[S] Playlist Ditemukan!" << std::endl;
                msg2ndIteration = 0;
                while(!interuptSignal2){
                    if(msg2ndIteration == 0){
                        std::cout << "| |-[!] Masukkan \"done\" Jika Anda Ingin Membatalkan atau Menyelesaikan Perubahan atau \"back\" untuk Kembali ke Menu Utama" << std::endl;
                        msg2ndIteration++;
                    } else if(msg2ndIteration == 2){
                        msg2ndIteration = 0;
                    } else {
                        msg2ndIteration++;
                    };
                    std::string InputSecond;
                    std::string LoweredInput;
                    std::cout << "| |-[?] Masukkan Nama Baru: " << std::flush;
                    std::cin >> InputSecond;

                    LoweredInput = convertToLower(InputSecond);
                    if (LoweredInput == "done"){
                        interuptSignal2 = true;

                        std::cout << "| |-[<] Perubahan Dibatalkan, Mengembalikan Anda ke Menu Informasi" << std::endl;
                    } else if (LoweredInput == "back"){
                        interuptSignal1 = true;
                        interuptSignal2 = true;

                        std::cout << "| o-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
                    } else {
                        if(checkPlaylistRedundancy(Data, InputSecond)){
                            std::cout << "| |-[E] Playlist dengan Genre \"" << InputSecond << "\" Sudah Ada!" << std::endl;
                        } else {
                            TargetPL->infotype.genre = InputSecond;
                            TargetPL->infotype.genre_search = LoweredInput;
                            MainChange = true;

                            std::cout << "| |-[S] Genre berhasil Diubah" << std::endl;
                        };
                    };
                };
            };
        };
    };
};
void ActionEditMusicMD(Structure &Data){
    std::cout << OutputBorder(80, true, true, "Ubah Metadata - Musik", true);
    if(countWithDataPlaylist(Data) != 0){
        std::string TargetPL;
        bool interuptSignal = false;
        bool interuptSignal2 = false;
        bool interuptSignal3 = false;
        bool MusicExist;
        bool mainChangeDetected = true;
        int hintIteration1 = 0;
        int hintIteration2 = 0;
        while(!interuptSignal){
            interuptSignal2 = false;
            MusicExist = false;
            adrPlayNode traverse = Data.first;
            std::string msgInfo = "";
                if(mainChangeDetected){
                    while(traverse != nullptr){
                        if(!checkEmptySong(traverse->attach)){
                            msgInfo  += "| | >>> " + traverse->infotype.genre + " (" + std::to_string(traverse->infotype.musicCount) + " Lagu)\n";
                            MusicExist = true;
                        };

                        traverse = traverse->next;
                    };

                    mainChangeDetected = false;
                };
            std::cout << "| |-[!] Data Playlist Dengan Musik " << std::endl << std::string(MusicExist ? msgInfo : "| | Tidak Ada Playlist yang Meiliki Data Musik");
            if(hintIteration1 == 0){
                std::cout << "| |-[!] Jika Anda Ingin Kembali ke Menu Utama, Masukkan \"back\" (Tanpa Tanda Petik)" << std::endl;
                hintIteration1++;
            } else if (hintIteration1 == 3){
                hintIteration1 = 0;
            } else {
                hintIteration1++;
            }
            std::cout << "| |-[?] Masukkan Genre yang Anda Ingin Ubah Lagunya: " << std::flush;
            std::cin >> TargetPL;
            if(convertToLower(TargetPL) == "back"){
                interuptSignal = true;

                std::cout << "| o-[<] Mengembalikan Pengguna ke Menu Utama" << std::endl;
            } else {
                adrPlayNode PLAddress = findPlaylist(Data, TargetPL);
                if(PLAddress == nullptr){
                    std::cout << "| |-[E] Tidak Dapat Menemukan Playlist dengan Genre \"" << TargetPL << "\", Mengembalikan Anda ke Menu Informasi - Genre" << std::endl;
                } else {
                    if(checkEmptySong(PLAddress->attach)){
                        std::cout << "| |-[E] Playlist Ditemukan Namun Tidak Ada Musik untuk Diubah, Mengembalikan Anda ke Menu Informasi - Genre" << std::endl;
                    } else {
                        bool subChangeDetected = true;
                        bool AtFirst = false;
                        bool AtPrev = false;
                        hintIteration2 = 0;
                        while(!interuptSignal2){
                            adrMusicNode msgNode = PLAddress->attach;
                            std::string msgBuild;
                            int paramMin;
                            int paramSec;
                            if (subChangeDetected){
                                msgBuild = "";
                                while(msgNode != nullptr){
                                    paramMin = msgNode->infotype.length/60;
                                    paramSec = msgNode->infotype.length%60;

                                    msgBuild += "| | >>> " + msgNode->infotype.name + " Oleh " + msgNode->infotype.artist + " | " + (paramMin < 10 ? "0" : "") + std::to_string(paramMin) + ":" + (paramSec < 10 ? "0" : "") + std::to_string(paramSec) +  " ("  + std::to_string(msgNode->infotype.length) +"s)\n";

                                    msgNode = msgNode->next;
                                };

                                subChangeDetected = false;
                            };

                            std::string TargetMusic;
                            std::string LoweredInput;
                            std::cout << "| |-[!] Genre " << TargetPL << std::endl << msgBuild;
                            if (hintIteration2 == 0){
                                std::cout << "| |-[!] Masukkan \"done\" untuk Kembali ke Menu Genre atau \"exit\" untuk Menu Utama" << std::endl;
                                hintIteration2++;
                            } else if (hintIteration2 == 3){
                                hintIteration2 = 0;
                            } else {
                                hintIteration2++;
                            };
                            std::cout << "| |-[?] Masukkan Musik yang Anda Ingin Ubah Datanya: " << std::flush;
                            std::cin >> TargetMusic;

                            LoweredInput = convertToLower(TargetMusic);
                            if(LoweredInput == "done"){
                                interuptSignal2 = true;

                                std::cout << "| |-[<] Mengembalikan Pengguna ke Menu Genre" << std::endl;
                            } else if(LoweredInput == "exit"){
                                interuptSignal = true;
                                interuptSignal2 = true;

                                std::cout << "| o-[<] Mengembalikan Pengguna ke Menu Utama" << std::endl;
                            } else {
                                adrMusicNode AddressStr;
                                if (LoweredInput == PLAddress->attach->infotype.name_search){
                                    AddressStr = PLAddress->attach;
                                    AtFirst = true;
                                } else {
                                    AddressStr = findPrevNodeMusic(PLAddress->attach, TargetMusic);
                                    if (AddressStr != nullptr){
                                        AtPrev = true;
                                    };
                                };

                                if (AtFirst || AtPrev){
                                    interuptSignal3 = false;
                                    while(!interuptSignal3){
                                        MusicData tempStorage;
                                        std::string tempGenre;
                                        std::string msgBuild2 = AtFirst ? "| |-[Masukan Musik " + AddressStr->infotype.name + "]" : (AtPrev ? "| |-[Masukan Musik " + AddressStr->next->infotype.name + "]" : "");
                                        std::cout << msgBuild2 << std::endl;
                                        std::cout << "| | Masukkan Nama Lagu Baru: " << std::flush;
                                        std::cin >> tempStorage.name;
                                        std::cout << "| | Masukkan Nama Artis Baru: " << std::flush;
                                        std::cin >> tempStorage.artist;
                                        std::cout << "| | Masukkan Durasi Baru: " << std::flush;
                                        std::cin >> tempStorage.length;
                                        if (std::cin.fail()){
                                            std::cout << "| |-[E] Terdapat Input yang Tidak Valid, Data Baru Tidak Disimpan" << std::endl;

                                            std::cin.clear();
                                            std::cin.ignore(SizeBuffer, '\n');
                                        } else if (tempStorage.length < 0){
                                            std::cout << "| |-[E] Masukan Durasi Anda Bernilai Negatif, Data Baru Tidak Disimpan" << std::endl;
                                        } else {
                                            if ((tempStorage.name == "0") && (tempStorage.artist == "0") && (tempStorage.length == 0)){
                                                interuptSignal3 = true;

                                                std::cout << "| |-[<] Membatalkan Perubahan, Mengembalikan Pengguna Ke Menu Informasi - Musik" << std::endl;
                                            } else {
                                                std::string DataName = "";
                                                std::string DataArtist = "";
                                                std::string DataLength = "";
                                                std::string DataGenre = "";
                                                int ParamMin = 0;
                                                int ParamSec = 0;
                                                std::cout << "| |-[!] Anda Dapat Mengisi dengan \"keep\" jika Genre Musik tidak Ingin Diubah atau \"no\" untuk Membatalkan Perubahan" << std::endl;
                                                std::cout << "| | Masukkan Genre Lagu Baru: " << std::flush;
                                                std::cin >> tempGenre;

                                                std::string LoweredInput2 =  convertToLower(tempGenre);
                                                if (LoweredInput2 == "no"){
                                                    interuptSignal3 = true;

                                                    std::cout << "| |-[<] Membatalkan Perubahan, Mengembalikan Pengguna Ke Menu Informasi - Musik" << std::endl;
                                                } else if (LoweredInput2 == "keep"){
                                                    paramMin = AddressStr->infotype.length/60;
                                                    paramSec = AddressStr->infotype.length%60;
                                                    DataName   += "|   | Nama: " + AddressStr->infotype.name;
                                                    AddressStr->infotype.name = tempStorage.name;
                                                    DataName   += " >>> " + AddressStr->infotype.name;
                                                    AddressStr->infotype.name_search = convertToLower(tempStorage.name);
                                                    DataArtist += "|   | Artis: " + AddressStr->infotype.artist;
                                                    AddressStr->infotype.artist = tempStorage.artist;
                                                    DataArtist += " >>> " + AddressStr->infotype.artist;
                                                    DataLength += "|   | Durasi: " + std::string(ParamMin < 10 ? "0" : "") + std::to_string(ParamMin) + std::string(ParamSec < 10 ? ":0" : ":") + std::to_string(ParamSec);
                                                    AddressStr->infotype.length = tempStorage.length;
                                                    DataLength += " >>> " + std::string(ParamMin < 10 ? "0" : "") + std::to_string(ParamMin) + std::string(ParamSec < 10 ? ":0" : ":") + std::to_string(ParamSec);
                                                    DataGenre  += "|   o Genre " + PLAddress->infotype.genre + "[Tetap]";

                                                    std::cout << "| |-o-[S] Data Berhasil Diubah" << std::endl << DataName << std::endl << DataArtist << std::endl << DataLength << std::endl << DataGenre << std::endl;
                                                    interuptSignal3 = true;
                                                    mainChangeDetected = true;
                                                    subChangeDetected = true;
                                                } else {
                                                    int ParamSubMin = 0;
                                                    int ParamSubSec = 0; 
                                                    adrPlayNode PLSecAddress = findPlaylist(Data, tempGenre);
                                                    if (PLSecAddress != nullptr){
                                                        adrMusicNode tempNode;
                                                        adrMusicNode newAttach;
                                                        if (AtFirst){
                                                            tempNode = PLAddress->attach;
                                                            if(PLAddress->attach->next != nullptr){
                                                                PLAddress->attach = PLAddress->attach->next;
                                                            } else {
                                                                PLAddress->attach = nullptr;
                                                            };
                                                        } else {
                                                            tempNode = AddressStr->next;
                                                            if (AddressStr->next->next != nullptr){
                                                                AddressStr->next = AddressStr->next->next;
                                                            } else {
                                                                AddressStr->next = nullptr;
                                                            }
                                                        };

                                                        newAttach = createMusicNode(tempStorage.name, tempStorage.artist, tempStorage.length);
                                                        ParamMin = tempNode->infotype.length/60;
                                                        ParamSubMin = newAttach->infotype.length/60;
                                                        ParamSec = tempNode->infotype.length/60;
                                                        ParamSubSec = newAttach->infotype.length/60;

                                                        DataName   += "|   | Nama: " + tempNode->infotype.name + " >>> " + newAttach->infotype.name;
                                                        DataArtist += "|   | Artis: " + tempNode->infotype.artist + " >>> " + newAttach->infotype.name;
                                                        DataLength += "|   | Durasi: " + std::string(ParamMin < 10 ? "0" : "") + std::to_string(ParamMin) + std::string(ParamSec < 10 ? ":0" : "") + std::to_string(ParamSec);
                                                        DataLength += " >>> " + std::string(ParamSubMin < 10 ? "0" : "") + std::to_string(ParamSubMin) + std::string(ParamSubSec < 10 ? ":0" : "") + std::to_string(ParamSubSec);
                                                        DataGenre  += "|   o Genre " + PLAddress->infotype.genre + " >>> " + PLSecAddress->infotype.genre;
                                                        delete tempNode;
                                                        attachMusic(PLSecAddress, newAttach);

                                                        std::cout << "| |-o-[S] Data Berhasil Diubah" << std::endl << DataName << std::endl << DataArtist << std::endl << DataLength << std::endl << DataGenre << std::endl;
                                                        interuptSignal3 = true;
                                                        mainChangeDetected = true;
                                                        subChangeDetected = true;
                                                    } else {
                                                        std::cout << "| |-[E] Tidak Dapat Menemukan Genre \"" << tempGenre << "\", Data Baru Tidak Disimpan" << std::endl;
                                                        interuptSignal3 = true;
                                                    };
                                                };
                                            };
                                        };
                                    };
                                } else {
                                    std::cout << "| |-[X] Musik Yang Anda Masukkan Tidak Ada Pada Playlist Ini!" << std::endl;
                                }
                            };
                        };
                    };
                };
            };
        };
    } else {
        std::cout << "| |-[X] Tidak Ada Playlist dengan Data Musik!" << std::endl;
        std::cout << "| o-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
    };
};
void ActionDeleteSong(Structure &Data){
    std::cout << OutputBorder(80, true, true, "Aksi Penghapusan - Lagu", true);
    std::string msgBuild = "";
    bool interuptSignal = false;
    bool interuptSignal2 = false;
    bool mainChangeDetected = true;
    bool HasMusic = false;
    while(!interuptSignal){
        while(mainChangeDetected){
            adrPlayNode traverse = Data.first;
            while(traverse != nullptr){
                if (!checkEmptySong(traverse->attach)){
                    msgBuild += "| | >>> " + traverse->infotype.genre + " (" + std::to_string(traverse->infotype.musicCount) + " Lagu)\n";
                    HasMusic = true;
                }

                traverse = traverse->next;
            };

            mainChangeDetected = false;
        };

        if (!HasMusic){
                msgBuild += "| | Tidak Ada Playlist yang Memiliki Lagu\n";
        };

        int hintInteration = 0;
        std::string GenreInput;
        std::string LoweredInput;
        std::cout << "| |-[!] Data Playlist Dengan Musik" << std::endl
                << msgBuild;
        if (hintInteration == 0){
            std::cout << "| |-[!] Masukkan \"back\" untuk Kembali ke Menu Utama" << std::endl;
            hintInteration++;
        } else if (hintInteration == 2){
            hintInteration = 0;
        } else {
            hintInteration++;
        };
        std::cout << "| |-[?] Masukkan Genre dari Lagu yang Anda Ingin Hapus: " << std::flush;
        std::cin >> GenreInput;
        LoweredInput = convertToLower(GenreInput);

        if(LoweredInput == "back"){
            interuptSignal = true;
            std::cout << "| o-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
        } else {
            adrPlayNode TargetPL = findPlaylist(Data, GenreInput);
            if (TargetPL != nullptr){
                if (checkEmptySong(TargetPL->attach)){
                    std::cout << "| |-[<] Playlist Ditemukan namun Tidak Ada Data Musik, Mengembalikan Anda ke Menu Informasi - Genre" << std::endl;
                } else {
                    std::string msgBuild2;
                    bool subChangeDetected = true;
                    while (!interuptSignal2){
                        if (subChangeDetected){
                            adrMusicNode musicTraverse = TargetPL->attach;
                            while (musicTraverse != nullptr){
                                msgBuild2 += "| | >>> " + musicTraverse->infotype.name + " Oleh " + musicTraverse->infotype.artist + "\n";

                                musicTraverse = musicTraverse->next;
                            };

                            subChangeDetected = false;
                        };

                        std::string TargetMusic;
                        std::string LoweredInput2;
                        std::cout << "| |-[Genre " << TargetPL->infotype.genre << "]" << std::endl << msgBuild2;
                        std::cout << "| |-[!] Informasi Tambahan" << std::endl;
                        if (checkEmptySong(TargetPL->attach)){
                            std::cout << "| | >>> Untuk Menghapus Seluruh Lagu yang Anda, Masukkan \"clearall\"" << std::endl;
                        }
                        std::cout << "| | >>> Anda Dapat Memasukkan \"back\" untuk Kembali ke Menu Informasi - Genre atau \"exit\" untuk Kembali ke Menu Utama" << std::endl;
                        std::cout << "| |-[?] Masukkan Musik yang Anda Ingin Hapus: " << std::flush;
                        std::cin >> TargetMusic;
                        LoweredInput2 =  convertToLower(TargetMusic);

                        if (LoweredInput2 == "back"){
                            interuptSignal2 = true;

                            std::cout << "| o-[<] Mengembalikan Anda ke Menu Informasi - Genre" << std::endl;
                        } else if (LoweredInput2 == "exit"){
                            interuptSignal = true;
                            interuptSignal2 = true;

                            std::cout << "| o-[<] Mengembailkan Anda ke Menu Utama" << std::endl;
                        } else if (LoweredInput2 == "clearall"){
                            std::string doubleConfirmation;
                            std::cout << "| |-[?] Konfirmasi Ulang, Masukkan \"yes\" Jika Anda Yakin: " << std::flush;
                            std::cin >> doubleConfirmation;
                            if (convertToLower(doubleConfirmation) == "yes"){
                                deleteAllSongs(TargetPL->attach, TargetPL->infotype.musicCount);
                                if (checkEmptySong(TargetPL->attach)){
                                    interuptSignal2 = true;

                                    std::cout << "| |-[S] Seluruh Musik pada Genre " << TargetPL << " Berhasil Dihapus" << std::endl;
                                    std::cout << "| |-[<] Mengembalikan Anda ke Menu Informasi - Genre" << std::endl;
                                } else {
                                    std::cout << "| |-[E] Tardapat Kasalahan Internal" << std::endl;
                                };
                            } else {
                                std::cout << "| |-[<] Mengembalikan Anda ke Menu Informasi - Musik" << std::endl;
                            }
                        } else {
                            bool IsDeleted;
                            deleteTargetSong(TargetPL, TargetMusic, IsDeleted);
                            if(IsDeleted){
                                std::cout << "| |-[S] Musik Berhasil Dihapus" << std::endl;
                                subChangeDetected = true;
                            } else {
                                std::cout << "| |-[E] Tidak Dapat Menemukan \"" << TargetMusic << "\", Mengembalikan Anda ke Menu Informasi - Musik" << std::endl;
                            };
                        };
                    };
                };
            } else {
                std::cout << std::endl;
            };
        };
    };
};
void ActionDeletePlaylist(Structure &Data){
    std::cout << OutputBorder(80, true, true, "Aksi Penghapusan - Playlist", true);
    std::string msgBuild = "";
    adrPlayNode traverseNode = Data.first;
    bool interuptSignal1 = false;
    bool mainChangeDetected = true;
    while (!interuptSignal1){
        if (checkEmptyPlaylist(Data)){
            interuptSignal1 = true;
            std::cout << "| |-[X] Data Playlist Anda Kosong, Mengembalikan Anda ke Menu Utama" << std::endl;
        } else {
            if(mainChangeDetected){
                while (traverseNode != nullptr){
                    msgBuild += "| | >>> Genre " + traverseNode->infotype.genre + " (" + std::string(traverseNode->infotype.musicCount != 0 ? std::to_string(traverseNode->infotype.musicCount) : "Tidak Ada") + " Lagu)\n";

                    traverseNode = traverseNode->next;
                };

                mainChangeDetected = false;
            };

            std::string GenreInput;
            std::string LoweredInput;
            std::cout << "| |-[!] Data Playlist Anda" << std::endl << msgBuild;
            std::cout << "| |-[!] Informasi Tambahan" << std::endl;
            std::cout << "| | >>> Menghapus Playlist Akan Menghapus Musik yang Berkaitan dengan Playlist Tersebut!" << std::endl;
            std::cout << "| | >>> Jika Anda Ingin Menghapus Seluruh Playlist, Anda Dapat Memasukkan \"deleteall\"" << std::endl;
            std::cout << "| | >>> Anda Dapat Memasukkan \"back\" untuk Kembali ke Menu Utama" << std::endl;
            std::cout << "| |-[?] Masukkan Playlist yang Anda Ingin Hapus: " << std::flush;
            std::cin >> GenreInput;
            LoweredInput = convertToLower(GenreInput);

            if (LoweredInput == "deleteall"){
                std::string secondConfirmation;
                std::cout << "| |-[?] Konfirmasi Tambahan, Jika Anda Yakin Masukkan \"yes\": " << std::flush;
                std::cin >> secondConfirmation;
                if (convertToLower(secondConfirmation) == "yes"){
                    deleteAllPlaylists(Data);
                    if (checkEmptyPlaylist(Data)){
                        interuptSignal1 = true;
                        std::cout << "| o-[S] Seluruh Playlist Berhasil Dihapus, Anda akan Dikembalikan ke Menu Utama" << std::endl;
                    } else {
                        std::cout << "| |-[E] Terjadi Kesalahan, Mengembalikan Anda ke Menu Informasi" << std::endl;
                    };
                } else {
                    std::cout << "| |-[<] Mengembalikan Anda ke Menu Informasi" << std::endl;
                };
            } else if (LoweredInput == "back"){
                interuptSignal1 = true;
                std::cout << "| o-[<] Mengembalikan Anda ke Menu Utama" << std::endl;
            } else {
                bool IsSubDeleted;
                deletePlaylist(Data, GenreInput, IsSubDeleted);
                if (IsSubDeleted){
                    mainChangeDetected = true;
                    std::cout << "| |-[S] Playlist Genre \"" << GenreInput << "\" Berhasil Dihapus" << std::endl;
                } else {
                    std::cout << "| |-[E] Tidak Dapat Menemukan Playlist Bergenre \"" << GenreInput << "\", Mengembalikan Anda ke Menu Informasi" << std::endl;
                };
            };
        };
    };
};
void PrintData(Structure S){ // Print out whole data of Parent Structure[Playlist] and its children(s)
    if(checkEmptyPlaylist(S)){ // Check Playlist Availability | If empty tell the user
        std::cout << "|=o=[Playlist Anda || 00 Playlist]" << std::endl; // Upper Border of Empty Playlist
        std::cout << "| o-[X] Kosong... Mulai Tambahkan Playlist Anda!" << std::endl;
    } else { // Check Playlist Availability | Else start initializing printer
        adrPlayNode p = S.first;
        adrMusicNode q;
        bool formatting;
        int PlayListCount = countPlaylist(S); // Count the amount of Playlist

        std::string b1 = PlayListCount < 10 ? "0" + std::to_string(PlayListCount) : std::to_string(PlayListCount); // Assembler of formatting; if < 10 =  0X, else XX
        std::cout << "|=o=[Playlist Anda || " << b1 << " Playlist]" << std::endl; // Upper Border of Filled Playlist
        while(p != nullptr){ // Loop around p = S.first
            std::cout << "| o=[Genre " << p->infotype.genre << " - " << p->infotype.musicCount << " Lagu]" << std::endl;
            q = p->attach;
            if(checkEmptySong(q)){ // Check if p->attach node is empty, if empty print empty data notice
                std::cout << "| o-x-> Tidak ada musik untuk playlist ini" << std::endl;
            } else { // Else loop through X data(s) of Music->attach
                while(q != nullptr){
                    formatting = (q->next == nullptr);
                    std::string a1 = formatting ? "| o-o-> " : "| |-o-> "; // Assembler of formatting; if value for last parent|non-last children, else for non-last parent|non-last children
                    std::string a2 = formatting ? "|   |-> " : "| | |-> "; // Assembler of formatting; if value for last parent|non-last children, else for non-last parent|non-last children
                    std::string a3 = formatting ? "|   o-> " : "| | o-> "; // Assembler of formatting; if value for last parent|last children, else for non-last parent|last children
                    std::string a4 = q->infotype.length%60 < 10 ? "0" + std::to_string(q->infotype.length%60) : std::to_string(q->infotype.length%60);
                    std::cout << a1 << "Title: " << q->infotype.name << std::endl << a2 << "Artist: " << q->infotype.artist << std::endl << a3 <<"Length: " << q->infotype.length/60 << ":" << a4 << std::endl;

                    q = q->next; // Traverse into next Music
                };
            };

            p = p->next; // Traverse into next Playlist
        };
    };
};
// Case Pages - Condition 2
void NoDataCase(bool &PassedState, std::string Question){
    if(!Question.empty()){
        std::string confirmation;
        std::cout << "|-[C] "<< Question << " (Masukkan \"yes\"/\"no\"): " << std::flush;
        std::cin >> confirmation;

        if(convertToLower(confirmation) == "yes"){
            PassedState =  true;
        } else {
            if(convertToLower(confirmation) != "no"){
                std::cout << "|-[E] Masukkan " << confirmation << " Tidak Valid, akan Diaplikasikan Nilai \"no\"" << std::endl;
            }
            PassedState = false;
        };
    } else {
        std::cout << "|-[E] Tidak Ada Pertanyaan" << std::endl;
    };
};
// Non-Page Menus
void ActionCreatePlaylist(Structure &S, Structure SRedundancy){
    int LoopState;
    std::cout << "|-[?] Masukkan Jumlah Playlist yang Anda Ingin Masukkan: " << std::flush;
    std::cin >> LoopState;
    if(std::cin.fail()){
        std::cout << "|-[E] Masukan Anda (" << LoopState << ") Tidak Valid (Bukan Integer), akan Diaplikasikan Nilai 1" << std::endl;
        
        LoopState = 1;
        std::cin.clear();
        std::cin.ignore(SizeBuffer, '\n');
    } else if (LoopState < 0){
        std::cout << "|-[E] Masukan Anda Tidak Valid (Bernilai Negatif), akan Diaplikasikan Nilai 1" << std::endl;
        LoopState = 1;
    };

    if(LoopState != 0){
        std::cout << OutputBorder(80, true, true, "", true);

        std::string InputGenre;
        std::string MsgBuilder1;
        for(int i = 1; i <= LoopState; i++){
            std::cout << "| |-[Input-" << i << "] Masukkan Genre Playlist Anda: " << std::flush;
            std::cin >> InputGenre;
            if(!checkPlaylistRedundancy(SRedundancy, InputGenre) && !checkPlaylistRedundancy(S, InputGenre)){
                addPlaylist(S, createPlayNode(InputGenre));
                MsgBuilder1 = i != LoopState ? "| |-[A] Genre \"" + InputGenre + "\" telah ditambahkan\n" : "| o-[A] Genre \"" + InputGenre + "\" telah ditambahkan\n";
                std::cout << MsgBuilder1;
            } else {
                std::cout << "| |-[E] Playlist bernamakan \"" << InputGenre << "\" sudah ada, Data tidak ditambahkan" << std::endl;
            };
        };
    } else {
        std::cout << "|-[<] Mengembalikan Pengguna ke Menu utama" << std::endl;
    }
};
void ActionCreateMusic(Structure &S){
    bool DataExist = !checkEmptyPlaylist(S);
    if(DataExist){
        int LoopState;
        std::string GenreMessage = "";
        std::string Genre;
        std::string confirmation;
        adrPlayNode adrPlaylist;
        MusicData tempMS;

        std::cout << "|-[?] Masukkan Jumlah Musik Yang Anda Ingin Masukkan: " << std::flush;
        std::cin >> LoopState;
        if(std::cin.fail()){
            std::cout << "|-[E] Masukkan Anda Bukan Bernilai Integer, Akan Diaplikasikan Nilai 1" << std::endl;
            LoopState = 1;

            std::cin.clear();
            std::cin.ignore(SizeBuffer, '\n');
        } else if (LoopState < 0){
            std::cout << "|-[E] Masukkan Anda Bernilai Negatif, Akan Diaplikasikan Nilai 1" << std::endl;
            LoopState = 1;
        };

        if(LoopState != 0){
            adrPlayNode traverse = S.first;
            while(traverse != nullptr){
                GenreMessage += traverse->infotype.genre;
                if(traverse->next != nullptr){
                    GenreMessage += std::string(", ");
                };

                traverse = traverse->next;
            };
            std::cout << "|-[!] Playlist yang Tersedia: [" << GenreMessage << "]" << std::endl;

            int CurrLoop = 1;
            bool interuptSentinel = false;
            std::cout << "|-[!] Untuk Menghentikan Proses Pemasukan Data, Anda Dapat Mengisi Nama Lagu, Artis, dan Durasi dengan 0" << std::endl;
            while(CurrLoop <= LoopState && !interuptSentinel){
                std::cout << "|-[Input " << CurrLoop << "]" << std::endl;
                std::cout << "| Masukkan nama lagu: " << std::flush;
                std::cin >> tempMS.name;
                std::cout << "| Masukkan nama artis: " << std::flush;
                std::cin >> tempMS.artist;
                std::cout << "| Masukkan durasi lagu dalam satuan detik: " << std::flush;
                std::cin >> tempMS.length;

                if(std::cin.fail()){
                    std::cout << "|-[E] Terdapat Input yang Error/Tidak Valid, Data Tidak Ditambahkan" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(SizeBuffer, '\n');
                } else if (tempMS.length < 0){
                    std::cout << "|-[E] Masukan Durasi Anda (" << tempMS.length << "s) Bernilai Negatif, Data Tidak Ditambahkan" << std::endl;
                }  else {
                    if((tempMS.name == "0") && (tempMS.artist == "0") && (tempMS.length == 0)){
                        interuptSentinel = true;

                        std::cout << "|-[<] Proses Penyisipan Lagu Diberhentikan, Mengembalikan Pengguna ke Menu Utama" << std::endl;
                        continue;
                    } else {
                        std::cout << "| Masukkan genre lagu ini: " << std::flush;
                        std::cin >> Genre;
                        adrPlaylist =  findPlaylist(S, Genre);
                        if(adrPlaylist != nullptr){
                            attachMusic(adrPlaylist, createMusicNode(tempMS.name, tempMS.artist, tempMS.length));
                        } else {
                            std::cout << "|-[E] Tidak Dapat Menemukan Genre \"" << Genre << "\" untuk Masukkan Musik \"" << tempMS.name << "\", buat Playlist Baru? (Masukkan\"yes\"/\"no\"): " << std::endl;
                            std::cin >> confirmation;

                            if(convertToLower(confirmation) ==  "yes"){
                                adrPlayNode NewPlaylist = createPlayNode(Genre);
                                addPlaylist(S, NewPlaylist);
                                attachMusic(NewPlaylist, createMusicNode(tempMS.name, tempMS.artist, tempMS.length));

                                std::cout << "|-[C] Genre\"" << Genre << "\" Telah Dibuat dan \"" << tempMS.name << "Telah Ditambahkan" << std::endl;
                            };
                        };
                    };
                }

                CurrLoop++;
            };
        } else {
            std::cout << "|-[<] Mengembalikan Pengguna ke Menu Utama" << std::endl;
        };
    } else {
        std::cout << "|-[E] Playlist yang Tersedia: [Tidak Ada!]" << std::endl << "|-[<] Terminasi Pengguna ke Menu Utama" << std::endl;
    };
};
// Close Page
void closePage(){
    std::cout << OutputBorder(80, true, false, "", true);
    std::cout << "[Sayonara] Menutup Aplikasi, Terima Kasih Sudah Menggunakan Aplikasi Simulasi Playlist" << std::endl;
};