#include <string>
#include <iostream>

using namespace std;

class Music{
private:
	string tid;
	string tArtist;
	string tTitle;
	string mxmid;
	string mArtist;
	string mTitle;
public:
	Music::Music(string id, string art, string title, string mid, string mart, string mtitl);
	void Music::setTid(string id);
	string Music::getTid();
	void Music::setTArtist(string art);
	string Music::getTArtist();
	void Music::setTTitle(string title);
	string Music::getTTitle();
	void Music::setMid(string mid);
	string Music::getMid();
	void Music::setMArtist(string mart);
	string Music::getMArtist();
	void Music::setMTitle(string mtitl);
	string Music::getMTitle();
};