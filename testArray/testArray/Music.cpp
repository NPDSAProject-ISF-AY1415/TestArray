#include <string>
#include <iostream>
#include "Music.h"
using namespace std;

Music::Music(string id, string art, string title, string mid, string mart, string mtitl){
	tid = id;
	tArtist = art;
	tTitle = title;
	mxmid = mid;
	mArtist = mart;
	mTitle = mtitl;
}
void Music::setTid(string id){ tid = id; }
string Music::getTid(){ return tid; }
void Music::setTArtist(string art){ tArtist = art; }
string Music::getTArtist(){ return tArtist; }
void Music::setTTitle(string title){ tTitle = title; }
string Music::getTTitle(){ return tTitle; }
void Music::setMid(string mid){ mxmid = mid; }
string Music::getMid(){ return mxmid; }
void Music::setMArtist(string mart){ mArtist = mart; }
string Music::getMArtist(){ return mArtist; }
void Music::setMTitle(string mtitl){ mTitle = mtitl; }
string Music::getMTitle(){ return mTitle; }