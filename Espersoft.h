// The Espersoft library, Version 3.5, May 25, 2018
// Written by:
//      Evan Pacini (espersoft.inc@gmail.com)
//      Kasper van Maasdam (espersoft.inc@gmail.com)


// ---------------------------------------------------------------------------
//                          Notes
// ---------------------------------------------------------------------------
// * This library is still under development.
// * Please see https://espersoft.wordpress.com for information on using this library.
// * This library was made by Espersoft Inc.
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//         		      Include Directives and Defines
// ---------------------------------------------------------------------------
#ifndef ESPERSOFT_H
#define ESPERSOFT_H

#include <iostream> //Standard IN/OUT C++ library
#include <cstdlib> //Library for executing System commands
#include <conio.h> //Library mainly used for it's _getch() function
#include <ctime> //Library for Getting System Time
#include <bits/stdc++.h> //Libary for standard c++
#include <sstream> //Libary for using String Streams
#include <windows.h> //For compatibility with Windows ®
#include <winable.h> //For compatibility with Windows ®
#include <unistd.h> //For the Timeout(); function
#include <stdlib.h> //Standard library
#include <stdio.h> // Library for Strings
#include <fstream> // For writing to files

#define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//							Time Functions
// ---------------------------------------------------------------------------

//Pause Function to Wait for a Key Press to Continue (Cross-Platform)
void Pause( bool visible = true ){

	if( ( visible == true ) ){
		std::cout << "Press any key to continue...";
	}
		char ans = _getch();
		std::cout << std::endl;
}
		
//Timeout Function to Wait a Certain Amount of Milliseconds Before Continuing (Cross-Platform)
void Timeout( int milliseconds ){

	#ifdef _WIN32
		Sleep( milliseconds );
	#else
		usleep( milliseconds * 1000 );
	#endif
}
		
//TimeoutSec Function to Wait a Certain Amount of Seconds Before Continuing (Cross-Platform)
void TimeoutSec( int seconds ){

	#ifdef _WIN32
		Sleep( seconds * 1000 );
	#else
		usleep( seconds * 1000000 );
	#endif
}

//GetTime Function to Get System Time (Cross-Platform)
std::string GetTime( bool useLocalTime, bool seconds ){

	std::stringstream currentTime;
	// current time based on current system
	time_t ttNow = time( 0 );
	tm * ptmNow;

	if ( useLocalTime )
		ptmNow = localtime( &ttNow );
	else
		ptmNow = gmtime( &ttNow );

	//hours
	if ( ptmNow->tm_hour < 10 )
		currentTime << "0" << ptmNow->tm_hour;
	else
		currentTime << ptmNow->tm_hour;

	//mins
	if ( ptmNow->tm_min < 10  )
		currentTime << ":" << "0" << ptmNow->tm_min;
	else
		currentTime << ":" << ptmNow->tm_min;
	if( ( seconds == true ) )
	{
	//secs
	if ( ptmNow->tm_sec < 10  )
		currentTime << ":" << "0" << ptmNow->tm_sec;
	else
		currentTime << ":" << ptmNow->tm_sec;
	}

	return currentTime.str();
}

//GetDate Function to Get System Date (Cross-Platform)
std::string GetDate( bool useLocalTime ){

	std::stringstream currentDate;
	// current date/time based on current system
	time_t ttNow = time( 0 );
	tm * ptmNow;

	if ( useLocalTime )
		ptmNow = localtime( &ttNow );
	else
		ptmNow = gmtime( &ttNow );

	currentDate << 1900 + ptmNow->tm_year;

	//months
	if ( ptmNow->tm_mon < 9 )
		//Fill in the leading 0 if less than 10
		currentDate << "-" << "0" << 1 + ptmNow->tm_mon;
	else
		currentDate << "-" << ( 1 + ptmNow->tm_mon );

	//days
	if ( ptmNow->tm_mday < 10 )
		currentDate << "-" << "0" << ptmNow->tm_mday << " ";
	else
		currentDate << "-" <<  ptmNow->tm_mday << " ";

	return currentDate.str();
}

//Countdown Function to Start a Countdown Timer (Cross-Platform)
void Countdown ( int seconds ) {

	for ( int i = seconds; i >= 0; i-- )
	{
		std::cout << i;
		TimeoutSec(1);
		char bck = 8;
		std::cout << bck;
	}
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//						    Window Functions
// ---------------------------------------------------------------------------	

//ClearScreen Function to Clear all the Contents of the Screen (Cross-Platform)
void ClearScreen() {

	#ifdef _WIN32
		system( "cls" );
	#elif __linux__
		system( "printf(\"\\330c\")" );
	#elif __APPLE__
		system( "clear" );
	#endif
}

//FullScreen Function to Switch to Full Screen Mode (Only works with Windows ®)
void FullScreen() {

	#ifdef _WIN32
		keybd_event( VK_MENU,0x36,0,0 );
		keybd_event( VK_RETURN,0x1c,0,0 );
		keybd_event( VK_RETURN,0x1c,KEYEVENTF_KEYUP,0 );
		keybd_event( VK_MENU,0x38,KEYEVENTF_KEYUP,0 );
	#elif __linux__
		std::cout << "This function is not yet availible for Linux...";
	#elif __APPLE__
		std::cout << "This function is not yet availible for Apple...";
	#endif
}
		
//ScreenSize Function to Change the Size of the Window (Only works with Windows ®)
void ScreenSize( int columns, int lines ) {

	char linesChar [4];
	char columnsChar [4];
	itoa(columns,columnsChar,10);
	itoa(lines,linesChar,10);

	#ifdef _WIN32
		std::string mode = "mode CON: COLS=";
		mode += columnsChar; mode += " LINES="; mode += linesChar;
		system( mode.c_str() );

	#elif __linux__
		std::cout << "This function is not yet availible for Linux...";

	#elif __APPLE__
		std::cout << "This function is not yet availible for Apple...";
	#endif
}

//Color Function to Change the Color of the Background and Foreground (Only works with Windows ®)
void Color( std::string background, std::string foreground ) {

	#ifdef _WIN32
		std::string color = "color ";
		color += background; color += foreground;
		system( color.c_str() );
	
	#elif __linux__
		std::cout << "This function is not yet availible for Linux...";
		
	#elif __APPLE__
		std::cout << "This function is not yet availible for Apple...";
	#endif
}

//Backspace Function to Send Backspace Characters (Cross-Platform)
void Backspace ( int number ) {

	char bck = 8;
	for (int i = number; i >= 0; i--)
	{
		std::cout << bck;
	}
}

//HideWindow Function to Hide Current C++ Window (Only works with Windows ®)
void HideWindow() {

	HWND hide;
	AllocConsole();
	hide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hide, 0);
}

//UnhideWindow Function to Unhide Current C++ Window (Only works with Windows ®)
void UnhideWindow() {

	HWND unhide;
	AllocConsole();
	unhide = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(unhide, 1);
}

//WindowTitle Function to Change the Title of the Window (Cross-Platform)
void WindowTitle( std::string title) {

	#ifdef _WIN32
		std::string WinTitle = "title ";
		WinTitle += title;
		system( WinTitle.c_str() );
	
	#else
		std::string ElseTitle = "echo -n -e \"\\033]0"
		ElseTitle += title; ElseTitle += "\\007\"";
		system( ElseTitle.c_str() );
	#endif
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//						    Loading Screens
// ---------------------------------------------------------------------------	

//LoadingScreen Function to Create Loading Screens (Cross-Platform)
void LoadingScreen( int loadingtime ) {

	ClearScreen();
	char a = 177, b = 219;
	std::cout << "\n\n\n\t\t\t\t\tLoading...";
	std::cout << "\n\n\n";
	std::cout << "\t\t\t\t\t";
	for (int i = 0; i <= 25; i++)
		std::cout << a;
		Timeout(150);
	std::cout << "\r";
	std::cout << "\t\t\t\t\t";
	for ( int i = 0; i <= 25; i++ )
	{
		std::cout << b;
		Timeout( loadingtime * 40 );
	}
	std::cout << "\n\n\t\t\t\t\tCompleted!";
	Pause( false );
	ClearScreen();
}
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//						    Sound Functions
// ---------------------------------------------------------------------------

//Beeper function to create a beep at a certain frequency for a certain amount of time (Cross-Platform)
void Beeper( int Frequency, int Duration ) {
	Beep( Frequency, Duration);
}

//Speak function to create speech synthesis (Only works with Windows ®)
void Speak( std::string text ) {

	#ifdef _WIN32
		std::ofstream speech ("speech.vbs");
		speech << "Set sapi=Createobject(\"sapi.spvoice\")" << std::endl;
		speech << "speech=(\"" << text << "\")" << std::endl;
		speech << "Sapi.Speak speech" << std::endl;
		speech.close();
		system("start speech.vbs");
		Timeout(250);
		system("del speech.vbs");

	#elif __linux__
		std::cout << "This function is not yet availible for Linux...";

	#elif __APPLE__
		std::cout << "This function is not yet availible for Apple...";
	#endif
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//						    File Functions
// ---------------------------------------------------------------------------

//Move Function to move files (Cross-Platform)
void Move( std::string location, std::string destination ) {
	
	#ifdef _WIN32
		std::string WinMove = "move /Y ";
		WinMove += "\""; WinMove += location; WinMove += "\" \""; WinMove += destination; WinMove += "\""; WinMove += " >nul";
		system( WinMove.c_str() );
	
	#else
		std::string ElseMove = "mv ";
		ElseMove += "\""; ElseMove += location; ElseMove += "\" \""; ElseMove += destination; ElseMove += "\"";
		system( ElseMove.c_str() );
	#endif	
}

//Rename Function to rename files (Cross-Platform)
void Rename( std::string name, std::string newname ) {
	
	#ifdef _WIN32
		std::string WinRename = "rename ";
		WinRename += "\""; WinRename += name; WinRename += "\" \""; WinRename += newname; WinRename += "\""; WinRename += " >nul";
		system( WinRename.c_str() );
	
	#else
		std::string ElseRename = "mv -T ";
		ElseRename += "\""; ElseRename += name; ElseRename += "\" \""; ElseRename += newname; ElseRename += "\"";
		system( ElseRename.c_str() );
	#endif	
}

//Delete Function to delete files (Cross-Platform)
void Delete( std::string file ) {
	
	#ifdef _WIN32
		std::string WinDel = "del /f /q /s ";
		WinDel += "\""; WinDel += file; WinDel += "\""; WinDel += " >nul";
		system( WinDel.c_str() );
	
	#else
		std::string ElseDel = "rm -f -R ";
		ElseDel += "\""; ElseDel += file; ElseDel += "\"";
		system( ElseDel.c_str() );
	#endif	
}

//Copy Function to copy files (Cross-Platform)
void Copy( std::string location, std::string destination ) {
	
	#ifdef _WIN32
		std::string WinCopy = "xcopy /s /c /d /e /h /i /r /y ";
		WinCopy += "\""; WinCopy += location; WinCopy += "\" \""; WinCopy += destination; WinCopy += "\""; WinCopy += " >nul";
		system( WinCopy.c_str() );
	
	#else
		std::string ElseCopy = "cp -f -R ";
		ElseCopy += "\""; ElseCopy += location; ElseCopy += "\" \""; ElseCopy += destination; ElseCopy += "\"";
		system( ElseCopy.c_str() );
	#endif	
}

//Startup function to start programs (invisibly or not) (Only works with Windows ®)
void Startup( char name[MAX_PATH], bool visible ){

	if ( ( visible == false ) ) {
		#ifdef _WIN32
			std::ofstream invis ("tempinvisible.vbs");
			invis << "Set WshShell = CreateObject(\"WScript.Shell\" ) " << std::endl;
			invis << "WshShell.Run chr(34) & \"" << name << "\" & Chr(34), 0 " << std::endl;
			invis << "Set WshShell = Nothing" << std::endl;
			invis.close();
			system("start tempinvisible.vbs");
			Timeout(250);
			system("del tempinvisible.vbs");
		
		#elif __linux__
			std::cout << "This function is not yet availible for Linux...";
			
		#elif __APPLE__
			std::cout << "This function is not yet availible for Apple...";
		#endif 
	}
	else{
			#ifdef _WIN32
				ShellExecute(NULL,"open",name,NULL,NULL,SW_SHOWNORMAL);

			#elif __linux__
				std::cout << "This function is not yet availible for Linux...";
				
			#elif __APPLE__
				std::cout << "This function is not yet availible for Apple...";
			#endif 
		}
}

//Random function to generate random numbers (Cross-Platform)
int Random(int from, int to){
	to = to-(from-1);
	srand((int)clock());
	return (rand() % to) + from;
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//							Showing Arrays
// ---------------------------------------------------------------------------	

// ---------------------------------------------------------------------------
#endif // ESPERSOFT_H
