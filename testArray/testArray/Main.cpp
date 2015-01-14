#include <iostream>
#include <fstream>	
#include <Windows.h>
#include <iomanip>	
#include <ctime>	
#include <string>
#include <algorithm>
#include <vector>
#include "Music.h"
#include "List.h"
#include "concol.h" // colors!
using namespace std;
using namespace eku;

int musicInfoFileLength = 779074;
//functions
bool is_number(const string& s);
Music parseMusicItem(string music);
static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w);
void readMatchFile(List &list, int count);
double calculateElapsed(clock_t start, clock_t end);
void printAscii();
void printSeperator();
double addElapsed = 0, displayElapsed = 0, sequSearchElapsed = 0;
void mainMenu();
void printMusicInfo(Music musicData);
void listAllSongs(List &list);
void searchSong(List &list);
void printStats();
List sortList(List &list);

//check if string is positive number
bool is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
Music parseMusicItem(string music)
{
	string parsed[6];

	string tmpToken;
	size_t pos = 0;
	string delimiter = "<SEP>";
	int column = 0;

	while ((pos = music.find(delimiter)) != string::npos) {
		tmpToken = music.substr(0, pos);
		parsed[column] = tmpToken;
		music.erase(0, pos + delimiter.length());
		column++;
	}
	tmpToken = music;
	parsed[5] = tmpToken;

	Music musicResult(parsed[0], parsed[1], parsed[2], parsed[3], parsed[4], parsed[5]);

	return musicResult;
}
static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w = 20)
{
	if ((x != n) && (x % (n / 100 + 1) != 0) && n >= 2000) return;

	//Get Elapsed Time
	clock_t endClock = clock();
	double elapsedSec = double(endClock - beginClock) / CLOCKS_PER_SEC;

	float ratio = x / (float)n;
	int   c = ratio * w;

	cout << setw(3) << white << "Parsed: " << cyan << x << white << "/" << green << n << yellow << " [";
	for (int x = 0; x<c; x++) cout << "=";
	for (int x = c; x<w; x++) cout << " ";
	cout << "] " << (int)(ratio * 100) << "%" << white << " Time Elapsed: " << cyan << setprecision(2) << fixed << elapsedSec;
	cout << " sec\r" << flush;
	settextcolor(white);
}

void readMatchFile(List &list, int count)
{
	bool verboseMode = false; //Enable Verbose Mode

	ifstream file("mxm_779k_matchsort.txt");
	string str;
	int internalCounter = 0;
	int progressCounter = count;
	settextcolor(white);
	if (count > musicInfoFileLength){
		cout << "Lines to read specified exceeds lines in file. Defaulting to read all" << endl;
		count = -1;
	}
	if (count == -1){
		progressCounter = musicInfoFileLength;
		cout << "As the file is extremely large, this may take a couple of minutes..." << endl;
	}
	settextcolor(yellow);
	cout << "===============" << endl;
	cout << "Reading file..." << endl;
	cout << "===============" << endl << endl;
	clock_t beginClock = clock();
	while (getline(file, str)){
		if (internalCounter >= progressCounter)
			break;
		if (verboseMode)
			cout << str << endl;

		//Check if string is a comment
		if (str[0] == '#'){
			//cout << "DEBUG: IS COMMENT" << endl;
		}
		else {
			//Parse Music Details Line
			list.add(str);
		}
		loadbar(internalCounter, progressCounter, beginClock);
		//Increment counter
		internalCounter++;
	}
	
	loadbar(progressCounter, progressCounter, beginClock);
	settextcolor(yellow);
	cout << endl << "Finished Reading and Adding File..." << endl;
	cout << yellow << "Total Lines Read: " << cyan << internalCounter << endl;
	cout << yellow << "Total Music List Length: " << cyan << list.getLength() << endl << endl;
}
double calculateElapsed(clock_t start, clock_t end)
{
	return double(end - start) / CLOCKS_PER_SEC;
}
void printAscii()
{
	ifstream file("ascii.txt");
	string print;
	while (getline(file, print)){
		cout << print << endl;
	}
}

void printSeperator()
{
	cout << yellow << "===============================================================================" << white << endl;
}

void mainMenu()
{
	printSeperator();
	cout << red << "                                  Main Menu" << endl;
	printSeperator();
	settextcolor(white);
	cout << "1) " << yellow << "View Songs in Database" << white << endl;
	cout << "2) " << yellow << "Search for a song in database with name" << white << endl;
	cout << "3) " << yellow << "View Performance Statistics" << white << endl;
	cout << "0) " << yellow << "Quit" << white << endl;
}
void printMusicInfo(Music musicData)
{
	cout << white << "Million Song Track DB ID: " << blue << musicData.getTid() << endl;
	cout << white << "Million Song Track Artist: " << blue << musicData.getTArtist() << endl;
	cout << white << "Million Song Track Title: " << blue << musicData.getTTitle() << endl;
	cout << white << "musicXmatch Track DB ID: " << blue << musicData.getMid() << endl;
	cout << white << "musicXmatch Track Artist: " << blue << musicData.getMArtist() << endl;
	cout << white << "musicXmatch Track Title: " << blue << musicData.getMTitle() << endl;
}

void searchSong(List &list)
{
	printSeperator();
	cout << yellow << "                                 Search Songs" << endl;
	printSeperator();
	string target;
	string empty;
	getline(cin, empty);
	cout << pink << "Enter Exact Song Name: " << cyan;
	getline(cin, target);
	settextcolor(white);

	clock_t start = clock();
	bool found = false;
	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		Music musIfo = parseMusicItem(res);
		if (musIfo.getMTitle() == target){
			cout << endl << yellow << "Music Found! Details of the music file is found below:" << endl;
			printMusicInfo(musIfo);
			cout << endl;
			found = true;
			break;
		}
	}
	if (!found){
		cout << endl << dark_red << "Unable to find a music file matching the search term" << endl;
	}
	clock_t end = clock();
	sequSearchElapsed = calculateElapsed(start, end);
	cout << yellow << "Elapsed Time for Sequential Search: " << cyan << setprecision(2) << fixed << sequSearchElapsed << " seconds." << endl;
}

void listAllSongs(List &list)
{
	printSeperator();
	cout << red << "                                List All Songs" << endl;
	printSeperator();

	//cout << "ITEMS IN LIST " << endl;
	//list.print();
	//cout << "=============" << endl;
	//cout << "DEBUG SIZE: " << list.getLength() << endl;
	clock_t start = clock();
	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		//cout << "DEBUG STR OF INDEX " << i << ": " << res << endl;
		Music musIfo = parseMusicItem(res);
		cout << yellow << "=========================================================" << endl;
		cout << red << "                 Song " << i << endl;
		cout << yellow << "=========================================================" << endl;
		printMusicInfo(musIfo);
		cout << yellow << "=========================================================" << endl;
	}
	clock_t end = clock();
	displayElapsed = calculateElapsed(start, end);
	cout << yellow << "Elapsed Time for display: " << cyan << setprecision(2) << fixed << displayElapsed << " seconds." << endl;
}
void printStats()
{
	printSeperator();
	cout << red << "                         Pointer-based Array Statistics" << endl;
	printSeperator();
	//Add
	cout << red << " " << "                  Add                  " << yellow << "|" << red << "        " << cyan;
	if (addElapsed != 0)
		cout << setprecision(2) << fixed << addElapsed << " Seconds ";
	else
		cout << "Untested ";
	cout << endl;

	//Display
	cout << " " << red << "                Display                " << yellow << "|" << red << "        " << cyan;
	if (displayElapsed != 0)
		cout << setprecision(2) << fixed << displayElapsed << " Seconds ";
	else
		cout << "Untested ";
	cout << endl;

	//Remove
	cout << " " << red << "              Remove Item              " << yellow << "|" << red << "        " << cyan;
	if (displayElapsed != 0)
		cout << setprecision(2) << fixed << "TODO" << " Seconds ";
	else
		cout << "Untested (TODO) ";
	cout << endl;

	//Seq Search
	cout << " " << red << "           Sequential Search           " << yellow << "|" << red << "        " << cyan;
	if (sequSearchElapsed != 0)
		cout << setprecision(2) << fixed << sequSearchElapsed << " Seconds ";
	else
		cout << "Untested ";
	cout << endl;

	printSeperator();
}

/*List sortList(List &list)
{
	string title,title2;
	List unsortedList = list;
	for (int i = 1; i <= list.getLength(); i++)
	{
		string res = list.get(i);
		string res2 = list.get(i +1);
		Music musIfo = parseMusicItem(res);
		Music musIfo = parseMusicItem(res2);
		title = musIfo.getMTitle;
		title2 = musIfo.getMTitle;
		if (title[1] < title2[1])
		{
			list.get(i) = list.get(i+1);
		}
	}
	
	
	
}*/

int main(){
	//Initialization
	SetConsoleTitle(TEXT("DSA Read File Test Project"));
	concolinit();

	printAscii();
	cout << endl;
	
	List mainList;
	cout << pink << "How many lines to read? (-1 to read all): ";
	settextcolor(cyan);
	int count;
	cin >> count;
	readMatchFile(mainList, count);
	//mainList = sortList(mainList);
	
	
	if (mainList.getLength() == 0){
		settextcolor(red);
		cout << "As Database do not have any music item, the program will quit." << endl;
		return 0;
	}

	

	//Main Menu
	while (true) {
		mainMenu();
		string selection;
		cout << pink << "Select a selection: ";
		settextcolor(cyan);
		cin >> selection;
		settextcolor(white);
		if (is_number(selection)){
			switch (stoi(selection))
			{
			case 1: listAllSongs(mainList); break;
			case 2: searchSong(mainList); break;
			case 3: printStats(); break;
			case 0: return 0;
				//case 4: mainList.print(); break;
			default: cout << dark_red << "Invalid Selection." << endl; break;
			}
		}
		else {
			cout << dark_red << "Selection must be an integer" << endl;
		}
	}
	return 0;
}