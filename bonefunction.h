#ifndef BONEFUNCTION_H_INCLUDED
#define BONEFUNCTION_H_INCLUDED

// Package
#include <string>

// Datatype Declarations
struct MusicData {
    std::string name;
    std::string name_search;
    std::string artist;
    int length;
};
struct PlaylistData{
    std::string genre;
    std::string genre_search;
    int musicCount; 
};
// Node Declarations
typedef struct PlaylistNode *adrPlayNode; // Declare Address of Parent Node
typedef struct MusicNode *adrMusicNode; // Declare Address of Children Node
struct PlaylistNode { // Parent Node Structure
    PlaylistData infotype;
    adrMusicNode attach;
    adrPlayNode next;
    adrPlayNode prev;
};
struct MusicNode { // Children Node Structure
    MusicData infotype;
    adrMusicNode next;
};
struct Structure { // Structure of First and Last of Parent Node
    adrPlayNode first;
    adrPlayNode last;
};

// Functions Declaration
// Create Node
void createMLLNode(Structure &S); // Create Node which applies nullptr to Structure's value as fresh start
adrPlayNode createPlayNode(std::string name); // Create Playlist Node with 1 input of std::string and applies null to linkage of DLL
adrMusicNode createMusicNode(std::string nameMusic, std::string nameArtist, int intLen); // Create Music Node with 2 inputs of std::string and 1 input of int and applies null to linkage of SLL
// Node Checker
bool checkEmptyPlaylist(Structure S); // Returning True(1) if S.first and S.last are empty, returning False(0) otherwise
bool checkEmptySong(adrMusicNode Check); // Returning True(1) if Playlist->attach contains nullptr, returning False(0) otherwise

// Node Modifier | Add
void addPlaylist(Structure &S, adrPlayNode Playlist); // Add Playlist to Structure Struct
void transferPlaylist(Structure &TargetStruct, Structure &InsertStruct); // Transfer Inserted Structure Data to Targeted Structure
void addMusic(Structure &S, adrMusicNode Music, std::string Genre); // Add Music to Parent Structure[Playlist]
void attachMusic(adrPlayNode &Playlist, adrMusicNode Music); // Attaching algorithm for "void addMusic(args...)"

// Node Modifier | Delete
void deletePlaylist(Structure &S, std::string Target, bool &DeleteStatus); // Delete Structure[Playlist] based off 1 input of std::string
void deleteAllPlaylists(Structure &S); // Delete all playlist with deleteFirst algorithm
void deleteTargetSong(adrPlayNode &PLAttach, std::string TargetMusic, bool &DeleteStatus); // Delete Targeted Music by traversing through Data of Playlist then traverse through Playlist->attach
void deleteAllSongs(adrMusicNode &MusicAttach, int &Count); // Delete all song datas on Music->attach bone
// Node Actions
adrPlayNode findPlaylist(Structure S, std::string target); // Find address of Playlist through loop
adrMusicNode findPrevNodeMusic(adrMusicNode MusicAttach, std::string target); // Find the previous node of targeted music node
void playPlaylist(adrMusicNode MusicAttach, int LoopState); // Queue algorithm of Structure[Playlist]
int countPlaylist(Structure S); // Count the amount of Playlist on Structure[Playlist] Struct
int countWithDataPlaylist(Structure S);
bool checkPlaylistRedundancy(Structure S, std::string TargetPL); // Check whether data with same name already exist, Returning True(1) if Found, returning False(0) otherwise [nullptr] 

// Miscellanous
std::string convertToLower(std::string Input); // Convert std::string from any cases into lower case
void fakeSleep(int duration); // Simulates sleep function with loop (performance risk)
std::string OutputBorder(int Width, bool StartIndentation, bool Indentation1, std::string TitleParam, bool NewSpace);

#endif // BONEFUNCTION_H_INCLUDED