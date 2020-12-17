#include "LogIn.h"

LogIn::LogIn(){}
LogIn::~LogIn(){}
int LogIn::signUp(std::string nick, std::string password, sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont) //dopisaæ sprwdzanie czy tekst faktycznie zosta³ wpisany do nazwy i hasla
{
	std::fstream file, file2;
	Window win;

	file.open("Baza/users/list.txt", std::ios::in);
	if (!file.good())
		throw "error loading file: Baza/users/list.txt";

	std::string compare, _nick;
	_nick = nick + "NICK";

	while (1)
	{
		getline(file, compare);
		if (compare == _nick)
		{
			return win.statement(window, "Nazwa uzytkownika jest zajeta", "Sprobuj jeszcze raz", 0, spriteBackground, font, textFont);
		}
		if (file.eof())
			break;
	}
	file.close();

	file.open("Baza/users/list.txt", std::ios::app);

	std::string nameFolder = "Baza/";
	nameFolder = nameFolder + nick;
	_mkdir(nameFolder.c_str());

	file2.open((nameFolder + "/MovieList.txt"), std::ios::out); //file creation
	file2.close();

	nick = nick + "NICK";
	password = password + "PASSWORD";
	file << nick << std::endl << password << std::endl;
	file.close();

	return win.statement(window, "Rejestracja udana", "Sprobuj sie zalogowac", 0, spriteBackground, font, textFont);
}

int LogIn::logIn(MovieDataBase& movieDataBase, std::string nick, std::string password, User& user, sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	Window win;
	LoadingData loadingData;
	std::string compare;
	compare = nick + "NICK";

	std::fstream file;
	file.open("Baza/users/list.txt", std::ios::in);
	if (!file.good()) 
		throw "error loading file: Baza/users/list.txt";

	std::string _nick;
	while (1)
	{
	    getline(file, _nick);
		if (compare == _nick)
			break;
		if (file.eof())
		{
			file.close();
			return win.statement(window, "Zla nazwa uzykownika", "Sprobuj jeszcze raz", 0, spriteBackground, font, textFont);
		}
	}

	compare = password + "PASSWORD";
	std::string _password;
	getline(file, _password);

	if (compare == _password)
	{
		user.setNick(nick);
		user.setPassword(password);
		file.close();

		loadingData.loadData(movieDataBase, user);

		return 3; //userWindow
	}
	else
	{
		file.close();
		return win.statement(window, "Podales zle haslo", "Sprobuj jeszcze raz", 0, spriteBackground, font, textFont);
	}
}


void LogIn::logOut(MovieDataBase& movieDataBase, User& user)
{
	movieDataBase.genre.movies.clear();
	movieDataBase.tag.movies.clear();
	movieDataBase.allMovies.clear();
	movieDataBase.ratedUsers.clear();
	user.ratedMovies.clear();
	return;
}