#ifndef MENUINTERFACE_H_INCLUDED
#define MENUINTERFACE_H_INCLUDED

// Package
#include <string>
// Macro
#include "bonefunction.h"

// Front Pages
void frontPageTitle();
void frontPage(Structure S, bool ExtraParam);
void frontPageInput(int &Input);
// Case Pages - Condition 1
void ActionSimulateMusic(Structure &S);
void ActionEditPlaylistMD(Structure &Data);
void ActionEditMusicMD(Structure &Data);
void ActionDeleteSong(Structure &Data);
void ActionDeletePlaylist(Structure &Data);
void PrintData(Structure S); // Print out whole data of Parent Structure[Playlist] and its children(s)
// Case Pages - Condition 2
void NoDataCase(bool &PassedState, std::string Question);

// Non-Page Menus
void ActionCreatePlaylist(Structure &S, Structure SRedundancy);
void ActionCreateMusic(Structure &S);
// Close Page
void closePage();

#endif // MENUINTERFACE_H_INCLUDED