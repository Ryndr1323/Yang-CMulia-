// Package
#include <iostream>
#include <string>
// Macro
#include "bonefunction.h" // Backbone of Program
#include "flowinterface.h" // The Interface of Program
#include "menuinterface.h" // The Menu of Program
// Namespace
using namespace std;

void RunProgram(){
    // v 0.1
    // Structure S;
    // createMLLNode(S);
    
    // deleteAllPlaylists(S);
    // string inputA;
    // int i;
    // // for(i = 1; i <= 8; i++){
    // //     cout << "Masukkan Nama Playlist: ";
    // //     cin >> inputA;
    // //     addPlaylist(S, createPlayNode(inputA));
    // // }

    // MusicData inputB;
    // string inputC;
    // for(i = 1; i <= 1; i++){
    //     cout << "Masukkan data lagu bertipekan struct: ";
    //     cin >> inputB.name >> inputB.artist >> inputB.length;
    //     cout << "Masukkan tipe genre dari lagu ini: ";
    //     cin >> inputC;
    //     addMusic(S, createMusicNode(inputB.name, inputB.artist, inputB.length), inputC);
    // }

    // printData(S);
    // deleteTargetSong(S, "Pop", "Thriller");
    // printData(S);
    // // deletePlaylist(S,"R&B");
    // // deletePlaylist(S,"Metal");
    // // printData(S);
    // // deleteAllPlaylists(S);
    // // printData(S);
    // playPlaylist(S.first->attach, true);

    // Define Variables for Program Runner
    // MLL Definition

    // v16+
    Structure Data; // Main Data
    Structure TempData; // Temporary Data Storage For Inputting
    createMLLNode(Data);
    // Loop Initiator
    bool ProgramInitiator = true;
    int menuChoose;
    // Data Initiator
    bool legendVal = true;
    bool DataPLExist;
    bool DataMusicExist;
    bool SubDataExist;
    bool createData;
    std::string test;

    // Begin the Program
    frontPageTitle();
    while(ProgramInitiator){
        // Data Refresher
        DataPLExist = !checkEmptyPlaylist(Data);
        DataMusicExist = countWithDataPlaylist != 0;

        frontPage(Data, legendVal);
        frontPageInput(menuChoose);
        if(menuChoose == 0){ // Case 0 - Close the Application
            ProgramInitiator =  false;
            closePage();
            fakeSleep(7);
        } else if(menuChoose == -1){ // Case -1 - Back to Menu
            continue;
        } else {
            switch (menuChoose){
            case 1: // Case 1 - Create New PlayList
                createMLLNode(TempData);
                ActionCreatePlaylist(TempData, Data);
                SubDataExist = !checkEmptyPlaylist(TempData);
                if(SubDataExist){
                    transferPlaylist(Data, TempData);
                };

                break;
            case 2: // Print Data of Playlist
                PrintData(Data);

                break;
            case 3: // Play Music (Enqueueing)
                if(DataPLExist){ // If there is Playlist Data, Call functions to start adding music
                    ActionSimulateMusic(Data);
                } else { // Else ask user whether they want to create new data
                    createData = false;
                    NoDataCase(createData, "Data Playlist kosong, Apakah Anda Ingin Menambahkan Data Playlist dan Musik Terlebih Dahulu?");
                    if(createData){
                        createMLLNode(TempData);
                        ActionCreatePlaylist(TempData, Data);
                        SubDataExist = !checkEmptyPlaylist(TempData);
                        if (SubDataExist){
                            ActionCreateMusic(TempData);
                            transferPlaylist(Data, TempData);
                        };
                    };
                };

                break;
            case 4: // Insert Music(s) into Existing Playlist
                if(DataPLExist){
                    ActionCreateMusic(Data);
                } else {
                    createData = false;
                    NoDataCase(createData, "Data Playlist Kosong, Apakah Anda Ingin Menambahkan Playlist untuk Mulai Memasukkan Musik?");
                    if(createData){
                        createMLLNode(TempData);
                        ActionCreatePlaylist(TempData, Data);
                        SubDataExist = !checkEmptyPlaylist(TempData);
                        if (SubDataExist){
                            ActionCreateMusic(TempData);
                            transferPlaylist(Data, TempData);
                        };
                    };
                };

                break;
            case 5: // Metadata Edit - Playlist
                if(DataPLExist){
                    ActionEditPlaylistMD(Data);
                } else {
                    createData = false;
                    NoDataCase(createData, "Playlist kosong, Apakah Anda Ingin Menambahkan Playlist Terlebih Dahulu?");
                    if(createData){
                        createMLLNode(TempData);
                        ActionCreatePlaylist(TempData, Data);
                        SubDataExist = !checkEmptyPlaylist(TempData);
                        if (SubDataExist){
                            transferPlaylist(Data, TempData);
                        };
                    };                    
                };

                break;
            case 6: // Metadata Edit - Music
                if(DataPLExist && DataMusicExist){
                    ActionEditMusicMD(Data);
                } else {
                    createData = false;
                    if (!DataPLExist){
                        NoDataCase(createData, "Playlist Masih Kosong, Apakah Anda Ingin Membuat Playlist Baru lalu Masukkan Musik?");
                        if (createData){
                            createMLLNode(TempData);
                            ActionCreatePlaylist(TempData, Data);
                            SubDataExist = !checkEmptyPlaylist(TempData);
                            if (SubDataExist){
                                ActionCreateMusic(TempData);
                                transferPlaylist(Data, TempData);
                            };
                        };
                    } else if (!DataMusicExist){
                        NoDataCase(createData, "Tidak Ada Playlist yang Memiliki Musik, Apakah Anda Ingin Memasukkan Data Musik Terlebih Dahulu?");
                        if (createData){
                            ActionCreateMusic(Data);
                        };
                    };
                };
                
                break;
            case 7: // Delete Song
                if(DataPLExist && DataMusicExist){
                    ActionDeleteSong(Data);
                } else {
                    createData = false;
                    if (!DataPLExist){
                        NoDataCase(createData, "Tidak Ada Data Playlist, Buat Playlist dan Masukkan Lagu Saja?");
                        if (createData){
                            createMLLNode(TempData);
                            ActionCreatePlaylist(TempData, Data);
                            SubDataExist = !checkEmptyPlaylist(TempData);
                            if (SubDataExist){
                                ActionCreateMusic(TempData);
                                transferPlaylist(Data, TempData);
                            };
                        };
                    } else if (!DataMusicExist){
                        NoDataCase(createData, "Tidak Ada Playlist yang Memiliki Musik, Apakah Anda Ingin Memasukkan Data Musik Saja?");
                        if (createData){
                            ActionCreateMusic(Data);
                        };
                    }
                };
            
                break;
            case 8: // Delete Playlist
                if(DataPLExist){
                    ActionDeletePlaylist(Data);
                } else {
                    createData = false;
                    NoDataCase(createData, "Data Playlist Masih Kosong, Buat Baru Saja");
                    if (createData){
                        createMLLNode(TempData);
                        ActionCreatePlaylist(TempData, Data);
                        SubDataExist = !checkEmptyPlaylist(TempData);
                        if (SubDataExist){
                            transferPlaylist(Data, TempData);
                        };
                    };
                };

                break;
            case 9: // Legend Setting
                if(legendVal){
                    legendVal = false;
                } else {
                    legendVal = true;
                };

                break;
            }
        };
    }
};
