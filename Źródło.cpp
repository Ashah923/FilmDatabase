#include <iostream>
#include <fstream>
#include "Window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	Window win;
	LoadingData loadingData;
	sf::Texture textureBackground;
	sf::Font font, textFont;
	sf::Sprite spriteBackground;

	try { loadingData.loadTexturesAndFont(font, textFont, textureBackground); }
	catch (const char* e) 
	{
		std::cout << "Message: " << e << std::endl;
		system("PAUSE");
		exit(-1);
	}

	spriteBackground.setTexture(textureBackground);

	MovieDataBase movieDataBase;
	sf::RenderWindow window{ sf::VideoMode{800,600}, "Baza Filmowa" };	
	window.setFramerateLimit(120);
	
	enum  windows
	{
		FIRST = 0,
		LOGIN = 1,
		SIGNUP = 2,
		USER = 3,
		EXIT = 4, 

	};

	User user;
	int choice=0;
	bool isTimeToExit = false;

	while (!isTimeToExit)
	{
		try 
		{
			switch (choice)
			{
			case FIRST:
				choice = win.firstWindow(window, spriteBackground, font);
				break;
			case LOGIN:
				choice = win.logInWindow(movieDataBase, window, user, spriteBackground, font, textFont);
				break;
			case SIGNUP:
				choice = win.signUpWindow(window, spriteBackground, font, textFont);
				break;
			case USER:
				choice = win.userWindow(movieDataBase, window, user, spriteBackground, font, textFont);
				break;
			case EXIT:
				isTimeToExit = true;
				break;
			}
		}
		catch (const char* e)
		{
			std::cout << "Message: " << e << std::endl;
			Window win; win.statement(window, "Wystapily problemy techniczne.", "Prosze sprobowac pozniej.", 0, spriteBackground, font, textFont);
		}
	}

	//int* i = new int;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}
