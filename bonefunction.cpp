// Package
#include <iostream>
#include <algorithm>
#include <cctype>
// Macro
#include "bonefunction.h"

// Functions Declaration
// Create Node
void createMLLNode(Structure &S){ // Create Node which applies nullptr to Structure's value as fresh start
    S.first = nullptr;
    S.last = nullptr;
};
adrPlayNode createPlayNode(std::string name){ // Create Playlist Node with 1 input of std::string and applies null to linkage of DLL
    adrPlayNode newPlaydata = new PlaylistNode; // Create new dataset of struct and applies it to *struct
    newPlaydata->infotype.genre = name;
    newPlaydata->infotype.genre_search = convertToLower(name); // Convert the input into safer search key
    newPlaydata->infotype.musicCount = 0;
    newPlaydata->attach = nullptr;
    newPlaydata->next = nullptr;
    newPlaydata->prev = nullptr;

    return newPlaydata; // Return the new dataset
};
adrMusicNode createMusicNode(std::string nameMusic, std::string nameArtist, int intLen){ // Create Music Node with 2 inputs of std::string and 1 input of int and applies null to linkage of SLL
    if(intLen < 0){
        return nullptr;
    };
    adrMusicNode newMusicdata = new MusicNode; // Create new dataset of struct and applies it to *struct
    newMusicdata->infotype.name = nameMusic;
    newMusicdata->infotype.name_search = convertToLower(nameMusic); // Convert the input into safer search key
    newMusicdata->infotype.artist = nameArtist;
    newMusicdata->infotype.length = intLen;
    newMusicdata->next = nullptr;

    return newMusicdata; // Return the new dataset
};
// Node Checker
bool checkEmptyPlaylist(Structure S){ // Returning True(1) if S.first and S.last are empty, returning False(0) otherwise
    return S.first == nullptr && S.last == nullptr;
};
bool checkEmptySong(adrMusicNode Check){ // Returning True(1) if Playlist->attach contains nullptr, returning False(0) otherwise
    return Check == nullptr;
};
// Node Modifier | Add
void addPlaylist(Structure &S, adrPlayNode Playlist){ // Add Playlist to Structure Struct
    if(checkEmptyPlaylist(S)){ // Check whether Structure is empty or no, if empty attach input as first data
        S.first = Playlist;
        S.last = Playlist;
    } else { // Else attach with insertLast algorithm
        S.last->next = Playlist;
        Playlist->prev = S.last;

        S.last = Playlist; // Update the S.last value
    };
};
void transferPlaylist(Structure &TargetStruct, Structure &InsertStruct){ // Transfer Inserted Structure Data to Targeted Structure
    if(checkEmptyPlaylist(TargetStruct)){ // Check whether the Old data exist or no, If no then attach new data then do flushing to new data
        TargetStruct.first = InsertStruct.first;
        TargetStruct.last = InsertStruct.last;
    } else { // Else link new data to old data then do flushing to new data
        InsertStruct.first->prev = TargetStruct.first;
        TargetStruct.last->next = InsertStruct.last;
    };

    // Set new last point on old structure
    TargetStruct.last = InsertStruct.last;
    // Flush New Structure
    InsertStruct.first = nullptr;
    InsertStruct.last = nullptr;
};
void addMusic(Structure &S, adrMusicNode Music, std::string Genre){ // Add Music to Parent Structure[Playlist]
    adrPlayNode Target = findPlaylist(S, Genre); // Find location of target

    if(Target == nullptr){ // If Target has return value of nullptr, ask if user want to create new playlist
        std::string formatting = checkEmptyPlaylist(S) ? "Playlist masih kosong untuk menambahkan lagu, tambahkan genre ini? " : "Tidak ditemukan lagu dengan genre \"" + Genre + "\", buat genre ini? ";
        std::string confirm;
        std::cout << formatting << "(masukkan \"yes\"/\"no\"): ";
        std::cin >> confirm;
        if(convertToLower(confirm) == "yes"){
            adrPlayNode newPlay = createPlayNode(Genre);
            addPlaylist(S, newPlay);
            attachMusic(newPlay, Music);
            std::cout << "Genre " << Genre << " telah dibuat dengan masukan musik " << Music->infotype.name << std::endl;
        }
    } else { // Else attach the song into Playlist->attach
        attachMusic(Target, Music);
        std::cout << "Masukan musik " << Music->infotype.name << " telah masuk di Playlist " << Target->infotype.genre << std::endl;
    }
};
void attachMusic(adrPlayNode &Playlist, adrMusicNode Music){ // Attaching algorithm for "void addMusic(args...)"
    if(checkEmptySong(Playlist->attach)){ // Check Music availability on Playlist->attach bone, attach as first music if its nullptr
        Playlist->attach = Music;
    } else { // Else traverse through Playlist->attach as traverse and inserted as insertLast
        adrMusicNode traverse = Playlist->attach;
        while(traverse->next != nullptr){
            traverse = traverse->next;
        };

        traverse->next = Music;
    };

    Playlist->infotype.musicCount += 1; // Update Music counter
};
// Node Modifier | Modify
void modifyPlaylistData(adrPlayNode &TargetPL, std::string NewData){
    if(TargetPL != nullptr){
        if (TargetPL->infotype.genre_search !=convertToLower(NewData)){
            TargetPL->infotype.genre = NewData;
            TargetPL->infotype.genre_search = convertToLower(NewData);
        };
    };
};
void modifyMusicData(adrMusicNode &TargetMusic, std::string NDName, std::string NDArtist, int NDLength, std::string Genre){
    if(TargetMusic != nullptr){
        
    };
};
// Node Modifier | Delete
void deletePlaylist(Structure &S, std::string Target, bool &DeleteStatus){ // Delete Structure[Playlist] based off 1 input of std::string
    if(checkEmptyPlaylist(S)){ // Check Playlist data's availability, if empty notify user
        std::cout << "Tidak bisa menghapus playlist kosong" << std::endl;
    } else { // Check Playlist data's availability, else, start doing deletion
        adrPlayNode p = findPlaylist(S, Target); // Find address of Target input
        if(p != nullptr){ // If Found then start deletion
            deleteAllSongs(p->attach, p->infotype.musicCount); // Flush data of Music(s) attached to Playlist

            if(p == S.first && p == S.last){ // Condition for data 1 Playlist, delete all data
                S.first = nullptr;
                S.last = nullptr;
            } else if(p == S.first){ // Condition for data of >1 Playlists, delete first node
                S.first = p->next;
                S.first->prev = nullptr;
            } else if(p == S.last){ // Condition for data of >1 Playlists, delete last node
                S.last = p->prev;
                S.last->next = nullptr;
            } else { // Condition for data of +1 Playlists, delete middle node
                p->prev->next = p->next;
                p->next->prev = p->prev;
            };

            delete p; // Delete the data after all links moved and its song flushed
            std::cout << "Genre \"" << Target << "\" terhapus" << std::endl;
        } else { // If Not Found then notify user
            std::cout << "Tidak ada playlist dengan genre \"" << Target << "\"" << std::endl;
        };
    };
};
void deleteAllPlaylists(Structure &S){ // Delete all playlist with deleteFirst algorithm
    if (!checkEmptyPlaylist(S)){
        adrPlayNode p = S.first;
        adrPlayNode temp;
        bool tempVal;
        std::string target;
        while(p != nullptr){
            target = p->infotype.genre;
            temp = p->next;
            deletePlaylist(S, target, tempVal);
            p = temp;
        };
    };
};
void deleteTargetSong(adrPlayNode &PLAttach, std::string TargetMusic, bool &DeleteStatus){ // Delete Targeted Music by traversing through Data of Playlist then traverse through Playlist->attach
    DeleteStatus = false;
    if (PLAttach != nullptr && !checkEmptySong(PLAttach->attach)){
        if(convertToLower(TargetMusic) == PLAttach->attach->infotype.name_search){
            adrMusicNode tempNode = PLAttach->attach;
            if (PLAttach->attach->next != nullptr){
                PLAttach->attach = PLAttach->attach->next;
            } else {
                PLAttach->attach = nullptr;
            };

            DeleteStatus = true;
            delete tempNode;
            PLAttach->infotype.musicCount--;
        } else {
            adrMusicNode AtPrev = findPrevNodeMusic(PLAttach->attach, TargetMusic);
            if (AtPrev != nullptr){
                adrMusicNode tempTarget = AtPrev->next;
                if (AtPrev->next->next != nullptr){
                    AtPrev->next = AtPrev->next->next;
                } else {
                    AtPrev->next = nullptr;
                };

                DeleteStatus = true;
                delete tempTarget;
                PLAttach->infotype.musicCount--;
            };
        };
    };
};
void deleteAllSongs(adrMusicNode &MusicAttach, int &Count){ // Delete all song datas on Music->attach bone
    adrMusicNode q = MusicAttach; // Copy address for traversal
    adrMusicNode temp; // Variable declaration for temporary storage during traversal
    while(q != nullptr){
        temp = q->next; // Save the next node address before get deleted
        delete q; // Delete the data
        q = nullptr; // Nullify for safefy
        Count -= 1; // Decrease the count
        q = temp; // Move temp into q for next loop
    };

    MusicAttach = nullptr; // Nullify the MusicAttach head to avoid pointer dangling
};
// Node Actions
adrPlayNode findPlaylist(Structure S, std::string target){ // Find address of Playlist through loop
    if(checkEmptyPlaylist(S)){ // Return nullptr if Playlist data is empty
        return nullptr;
    }
    std::string targetL = convertToLower(target); // Convert the target input for safer matching
    if(targetL == S.first->infotype.genre_search){ // Matching targetL with first of Structure[Playlist]
        return S.first;
    };
    if(targetL == S.last->infotype.genre_search){ // Matching targetL with last of Structure[Playlist]
        return S.last;
    };
    adrPlayNode p = S.first; // If none of both, loop through p to find middle
    while(p != nullptr && p->infotype.genre_search != targetL){
        // std::cout << "Searching on " << p->genre_search << " to " << targetL << std::endl; //[DEBUG] 
        p = p->next;
    };

    return p; // Return the Found/Not Found address of target
};
adrMusicNode findPrevNodeMusic(adrMusicNode MusicAttach, std::string target){ // Find the previous node of targeted music node
    if(MusicAttach == nullptr){ // Safety Net if Music->attach has no data attached (nullptr)
        return nullptr;
    };
    std::string targetL = convertToLower(target); // Else start doing traverse
    adrMusicNode traverse = MusicAttach;
    while(traverse->next != nullptr && convertToLower(traverse->next->infotype.name_search) != targetL){
        traverse = traverse->next;
    };

    return traverse; // Return the value of either nullptr of adrMusicNode address
};
void playPlaylist(adrMusicNode MusicAttach, int LoopState){ // Queue algorithm of Structure[Playlist]
    if(checkEmptySong(MusicAttach)){
        std::cout << "| Tidak ada musik pada playlist ini, mulai tambah musik!" << std::endl;
    } else {
        int LoopValue = 1;
        adrMusicNode headLoop = MusicAttach;
        adrMusicNode traverse = headLoop;
        adrMusicNode nextTraverse;
        std::cout << "[Playlist Player]" << std::endl;
        while(traverse != nullptr){
            int time; // Variable of for() loop
            int timeLen = traverse->infotype.length; // Variable of length of the music
            int barLen = 30; // Size of bar
            int barProg; // The percentage% of bar to be printed; always updated to new value
            int barProgTemp; // The percentage% of bar to be printed; temporary value to determine how many "=" to be added
            int barProgVS = 0; // The percentage% of bar to be printed; updated to barProg when higher than itself
            std::string formatSecond; // Format string for XX:Second
            std::string formatMin; // Format string for Minute:XX
            std::string barUI; // Variable to store assembled UI
            if(traverse->next != nullptr){
                nextTraverse = traverse->next;
            } else if(LoopValue < LoopState){
                nextTraverse = headLoop;
                LoopValue++;
            } else {
                nextTraverse = nullptr;
            };

            std::cout << "| Sekarang Memainkan: " << traverse->infotype.name << " oleh " << traverse->infotype.artist << std::endl;
            if(nextTraverse != nullptr){
                std::cout << "| Berikutnya: " << nextTraverse->next->infotype.name << " oleh " << nextTraverse->infotype.artist << std::endl;
            };

            std::string barFillVS = ""; // Update the filled bar of "=" from previous Music into empty string for new Music
            for(time = 0; time <= timeLen; time ++){ // Loop from 0 to Length of Music
                formatSecond = time%60 < 10 ? "0" + std::to_string(time%60) : std::to_string(time%60);
                formatMin = time/60 < 10 ? "0" + std::to_string(time/60) : std::to_string(time/60);
                barProg = (time * barLen) / timeLen; // Updating Percentage of progressed bar
                std::string barEmpVS = ""; // Update the filled bar of " " from previous second iteration into empty string for next second

                if(barProg > barProgVS){ // Concantenation to fill active bar; Updating on every
                    barProgTemp = barProg - barProgVS;
                    barProgVS = barProg;
                    for(int j  = 1; j <= barProgTemp; j++){
                        barFillVS += "=";
                    }
                }

                for(int i = barProg; i < barLen; i++){ // Concatenation to fill empty bar
                    barEmpVS += " ";
                }

                std::cout << "\r" << std::string(100, ' ') << "\r"; // Flush print from previous second iteration
                barUI = "| " + formatMin + ":" + formatSecond + " [" + barFillVS + barEmpVS + "]"; // Assemble all elements
                std::cout << barUI; // Print out
                
                fakeSleep(1); // Sleep for ~1 Second
            }
            std::cout << std::endl; // Print new line for new song

            traverse = nextTraverse;
        };
    };
};
int countPlaylist(Structure S){ // Count the amount of Playlist on Structure[Playlist] Struct
    if(checkEmptyPlaylist(S)){ // Check Playlist data's availability, if empty return 0
        return 0;
    };
    adrPlayNode p = S.first; // Else start counting for amoount of X Data
    int count = 0; // Declare variable and apply value to avoid bug
    while(p != nullptr){
        count += 1;
        p = p->next;
    };

    return count; // return the value of amount of Structure data
};
bool checkPlaylistRedundancy(Structure S, std::string TargetPL){
    adrPlayNode traverse = S.first;
    std::string TargetPLL = convertToLower(TargetPL);
    while(traverse != nullptr){
        if(traverse->infotype.genre_search == TargetPLL){
            return true; 
        };

        traverse = traverse->next;
    };

    return false;
};
int countWithDataPlaylist(Structure S){
    if(checkEmptyPlaylist(S)){
        return 0;
    }
    adrPlayNode p = S.first;
    int count;
    while(p != nullptr){
        if(!checkEmptySong(p->attach)){
            count++;
        };

        p = p->next;
    };

    return count;
};
// Miscellanous
std::string convertToLower(std::string Input){ // Convert std::string from any cases into lower case
    if(Input.empty()){
        return "";
    };
    std::transform(Input.begin(), Input.end(), Input.begin(),[](unsigned char c){ return std::tolower(c); });

    return Input;
};
void fakeSleep(int duration) { // Simulates sleep function with loop (performance risk)
    if(duration >= 0){
        for (volatile long long i = 0; i < duration * 1000000000; i++);
    };
};
std::string OutputBorder(int Width, bool StartIndentation, bool Indentation1, std::string TitleParam, bool NewSpace){
    if(Width <= 0){
        return "";
    } else {
        int reserveLen = 1; // Int Value of Length of Reserved 'o'
        int reserveIndentation = 3;
        std::string Finalized;
        if (StartIndentation && Width >= 2){
            Finalized += "o";
            Width--;
        };
        if (Indentation1 && (Width >= 2 + reserveIndentation)){
            Finalized += "=o=";
            Width -= reserveIndentation;
        };
        if(TitleParam != ""){
            std::string tempBuild;
            tempBuild = "[" + TitleParam + "]";
            if(tempBuild.length() + reserveLen <= Width){
                Finalized += tempBuild;
                Width -= tempBuild.length();
            };
        };
        if(Width > reserveLen){
            Finalized += std::string(Width - reserveLen, '=');
        };
        Finalized += std::string(reserveLen, 'o');
        if(NewSpace){
            Finalized += "\n";
        };

        return Finalized;
    };
};