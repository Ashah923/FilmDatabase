#include "Window.h"


int Window::firstWindow(sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	// text, font, characterSize, textPositionX, textPositionY,  PositionX, positionY, width, height 
	Button button1("Logowanie", font, 30, 335.f, 185.f, 320.f, 180.f, 150, 50);
	Button button2("Rejestracja", font, 30, 335.f, 305.f, 320.f, 300.f, 150, 50);
	Button button3("Wyjscie", font, 30, 355.f, 425.f, 320.f, 420.f, 150, 50);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			case sf::Event::Closed:
			{
				window.close();
				return EXIT;
			}
		}
		
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		//boundingBox, texture, PositionX, PositionY, width, height, window
		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 310.f, 170.f, 170, 70, window) != 0)
			return LOGIN;
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 310.f, 290.f, 170, 70, window) != 0)
			return SIGNUP;
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 310.f, 410.f, 170, 70, window) != 0)
		{
			window.close();
			return EXIT;
		}
		
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.display();
	}

}

int Window::logInWindow(MovieDataBase& movieDataBase, sf::RenderWindow& window, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	TextSupport textSupport;
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	sf::Event event;

	sf::Text textLogin("", textFont);
	sf::Text textPassword("", textFont);
	int numberOfLettersL = 0;
	int numberOfLettersP = 0;
	int check=0;

	Border border1(370.f, 180.f, 250, 50);  //nick
	Border border2(370.f, 280.f, 250, 50);  //password
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	
	while (window.isOpen())
	{	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
			if (check == 1)				
				// event, numberOfLetters, window, text, font, x, y
				textLogin = eventSupport.enterWord(event, numberOfLettersL, window, textLogin, textFont, 380.f, 180.f, border1, 19);
			else if (check == 2)
				textPassword = eventSupport.enterWord(event, numberOfLettersP, window, textPassword, textFont, 380.f, 280.f, border2, 19);
			if (event.key.code == sf::Keyboard::Enter)
			{
			   LogIn logIn; 
			   try { return logIn.logIn(movieDataBase, textLogin.getString(), textPassword.getString(), user, window, spriteBackground, font, textFont); }
			   catch (const char* e) { std::cout << "Message: " << e << std::endl; statement(window, "Wystapily problemy techniczne.", "Prosze sprobowac pozniej.", 0, spriteBackground, font, textFont); }
			}
		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0)
		{
			check = 1;
			border2.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border2.getRectangle().getGlobalBounds(),  window) != 0)
		{
			check = 2;
			border1.setColor(sf::Color::White);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(border2);
		window.draw(textLogin);
		window.draw(textPassword);
		textSupport.printText("Wpisz nazwe uzytkownika:", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		textSupport.printText("Wpisz haslo uzytkownika:", textFont, 35, 30.f, 280.f, sf::Color::Black, window);
		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 560.f, 490.f, 170, 70, window) != 0)
			return FIRST;
		window.draw(button1);
		window.display();
	}
}

int Window::signUpWindow(sf::RenderWindow& window, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	sf::Text textLogin("", textFont);
	sf::Text textPassword("", textFont);
	int numberOfLettersL = 0;
	int numberOfLettersP = 0;
	Border border1( 470.f, 180.f, 250, 50);  //nick
	Border border2(470.f, 280.f, 250, 50);  //password
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	int check = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
			if (check == 1)
				// event, numberOfLetters, window, text, font, x, y
				textLogin = eventSupport.enterWord(event, numberOfLettersL, window, textLogin, textFont, 480.f, 180.f, border1, 19);
			else if (check == 2)
				textPassword = eventSupport.enterWord(event, numberOfLettersP, window, textPassword, textFont, 480.f, 280.f, border2, 19);
			if (event.key.code == sf::Keyboard::Enter)
			{
				LogIn logIn;
				try { return logIn.signUp(textLogin.getString(), textPassword.getString(), window, spriteBackground, font, textFont); }
				catch (const char* e) { std::cout << "Message: " << e << std::endl; statement(window, "Wystapily problemy techniczne.", "Prosze sprobowac pozniej.", 0, spriteBackground, font, textFont); }
			}
		}

		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0)
		{
			check = 1;
			border2.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border2.getRectangle().getGlobalBounds(), window) != 0)
		{
			check = 2;
			border1.setColor(sf::Color::White);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(border2);
		window.draw(textLogin);
		window.draw(textPassword);
		textSupport.printText("Podaj nazwe nowego uzytkownika:", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		textSupport.printText("Podaj haslo nowego uzytkownika:", textFont, 35, 30.f, 280.f, sf::Color::Black, window);
		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 560.f, 490.f, 170, 70, window) != 0)
		{
			return FIRST;
		}
		window.draw(button1);
		window.display();
	}
}

int Window::userWindow(MovieDataBase& movieDataBase, sf::RenderWindow& window, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	TextSupport textSupport;
	MouseSupport mouseSupport;
	sf::Event event;

	Button button0("Wyswietl filmy", font, 25, 593.f, 157.f, 570.f, 150.f, 180, 50);
	Button button1("Wyszukaj film", font, 25, 593.f, 227.f, 570.f, 220.f, 180, 50);
	Button button2("Dodaj film", font, 25, 610.f, 297.f, 570.f, 290.f, 180, 50);
	Button button3("Wyswietl z gatunku", font, 20, 588.f, 366.f, 570.f, 360.f, 180, 50);
	Button button4("Wyswietl z tagu", font, 25, 589.f, 436.f, 570.f, 430.f, 180, 50);
	Button button5("Wyloguj", font, 25, 620.f, 506.f, 570.f, 500.f, 180, 50);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		textSupport.printText("Strona uzytkownika", textFont, 40, 240.f, 130.f, sf::Color::Black, window);
		textSupport.printText(("Nazwa uzytkownika: " + user.getNick()), textFont, 30, 60.f, 190.f, sf::Color::Black, window);
		textSupport.printText("Ostatnio ocenione: ", textFont, 30, 30.f, 230.f, sf::Color::Black, window);
		user.showRecentlyRated(textFont, window);
		textSupport.printText("Rekomendowane filmy: ", textFont, 30, 280.f, 230.f, sf::Color::Black, window);
		user.showRecommended(textFont, window, movieDataBase.genre, movieDataBase.tag);

		if (mouseSupport.pressButton(button0.getRectangle().getGlobalBounds(), 560.f, 140.f, 200, 70, window) != 0) { showAllMovis(window, movieDataBase, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 560.f, 210.f, 200, 70, window) != 0) { enterTitle(window, movieDataBase, "Podaj tytul filmu", 3, user, spriteBackground, font, textFont);}
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 560.f, 280.f, 200, 70, window) != 0) { newFilmTitle(window, user, movieDataBase, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 560.f, 350.f, 200, 70, window) != 0) { enterSearchGenre(window, user, movieDataBase.genre, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 560.f, 420.f, 200, 70, window) != 0) { enterSearchTag(window, user, movieDataBase.tag, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 560.f, 490.f, 200, 70, window) != 0) { LogIn logIn; logIn.logOut(movieDataBase, user);  return FIRST; }

		window.draw(button0);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.display();
	}
}

int Window::statement(sf::RenderWindow& window, sf::String text1, sf::String text2, int toWindow, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	sf::Event event;
	MouseSupport mouseSupport;
	TextSupport textSupport;
	sf::Vector2i mousePosition;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return toWindow; }
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		textSupport.printText(text1, textFont, 40, 110.f, 150.f, sf::Color::Black, window);
		textSupport.printText(text2, textFont, 40, 110.f, 200.f, sf::Color::Black, window);
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.display();
	}
}

int Window::enterTitle(sf::RenderWindow& window, MovieDataBase& movieDataBase, std::string _text, int ret, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	sf::Text text("", textFont);
	int numberOfLetters = 0;
	Border border1(370.f, 180.f, 400, 50);  
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;
	int check = 0;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
			if (check == 1)
				text = eventSupport.enterWord(event, numberOfLetters, window, text, textFont, 380.f, 180.f, border1, 29);
			if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyReleased)
			{
				return film(window, movieDataBase, text.getString(), user, spriteBackground, font, textFont); 
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return ret; }
		}

		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) { check = 1; }
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(text);
		textSupport.printText(_text, textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.display();
	}
	return -1;
}

void Window::rateMovieWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	TextSupport textSupport;
	MouseSupport mouseSupport;
	SupportData supportData;
	Button button1("1", textFont, 30, 140.f, 335.f, 100.f, 300.f, 100, 100);
	Button button2("2", textFont, 30, 260.f, 335.f, 220.f, 300.f, 100, 100);
	Button button3("3", textFont, 30, 380.f, 335.f, 340.f, 300.f, 100, 100);
	Button button4("4", textFont, 30, 500.f, 335.f, 460.f, 300.f, 100, 100);
	Button button5("5", textFont, 30, 620.f, 335.f, 580.f, 300.f, 100, 100);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);

		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 90.f, 290.f, 120, 120, window) != 0) { supportData.saveNewRating(movieDataBase, movie, user, 1); return; }
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 210.f, 290.f, 120, 120, window) != 0) { supportData.saveNewRating(movieDataBase, movie, user, 2); return; }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 330.f, 290.f, 120, 120, window) != 0) { supportData.saveNewRating(movieDataBase, movie, user, 3); return; }
		else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 450.f, 290.f, 120, 120, window) != 0) { supportData.saveNewRating(movieDataBase, movie, user, 4); return;}
		else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 570.f, 290.f, 120, 120, window) != 0) { supportData.saveNewRating(movieDataBase, movie, user, 5); return;}

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.display();
	}
}

int Window::film(sf::RenderWindow& window, MovieDataBase& movieDataBase, std::string movieName, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	SaveData saveData;
	TextSupport textSupport;
	MouseSupport mouseSupport;
	SupportData supportData;
	std::string avgRating, userRating;

	std::vector<Movie*> movies;
	Movie movie, *tempMovie;

	try { movies = movie.showInformation(movieName, movieDataBase.allMovies); }
    catch (const char* e) { std::cout << "Message: " << e << std::endl; return statement(window, "Podany film nie jest wprowadzony do bazy", "", 3, spriteBackground, font, textFont); }

	if (movies.size() > 1)
	{
		try { tempMovie = filmYear(window, movies, user, spriteBackground, font, textFont); }
		catch(const char* e) { std::cout << "Message: " << e << std::endl; return statement(window, "Podany film nie jest wprowadzony do bazy", "", 3, spriteBackground, font, textFont); }
	}
	else
	{
		tempMovie = movies[0];
	}

	int k;
	Button button1("Ocen film", font, 30, 65.f, 505.f, 40.f, 500.f, 150, 50);
	Button button2("Edytuj film", font, 30, 242.f, 505.f, 230.f, 500.f, 150, 50);
	Button button3("Usun film", font, 30, 440.f, 505.f, 420.f, 500.f, 150, 50);
	Button button4("Powrot", font, 30, 645.f, 505.f, 610.f, 500.f, 150, 50);
	Button button5("Wyswietl zdjecie", font, 30, 507.f, 155.f, 500.f,150.f, 200, 50 );
	HoverLight hoverLight1(600.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		if (!(tempMovie->tempUserRating))
		{ userRating = "nie oceniles filmu"; }
		else(userRating = std::to_string(*tempMovie->tempUserRating));
		if (tempMovie->getRating().getAvgRating() == 0)
		{ avgRating = "brak sredniej oceny"; }
		else(avgRating = std::to_string(tempMovie->getRating().getAvgRating()));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return EXIT;
			}
			if (mouseSupport.releaseButton(button4.getRectangle().getGlobalBounds(), window, event) != 0) { return USER; }
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		textSupport.printText(tempMovie->getName() + "   " + std::to_string(tempMovie->getProductionYear())+"r.", textFont, 40, 40.f, 150.f, sf::Color::Black, window);
		textSupport.printText(movieDataBase.genre.toString(tempMovie->getGenre()), textFont, 25, 40.f, 200.f, sf::Color::Black, window);
		k = textSupport.printDescription(tempMovie->getDescription(), textFont, sf::Color::Black, window);
		textSupport.printText("Tagi: " + movieDataBase.tag.toString(tempMovie->getTag(0)) + ", " + movieDataBase.tag.toString(tempMovie->getTag(1)) + ", " + movieDataBase.tag.toString(tempMovie->getTag(2)), textFont, 25, 40.f, k + 50.f, sf::Color::Black, window);
		textSupport.printText("Twoja ocena: "+ userRating, textFont, 25, 40.f, k + 100.f, sf::Color::Black, window);
		textSupport.printText("Srednia ocena: "+ avgRating.erase(4, avgRating.size()-4), textFont, 25, 40.f, k + 150.f, sf::Color::Black, window);

		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 30.f, 490.f, 170, 70, window) != 0) { rateMovieWindow(window, movieDataBase, *tempMovie, user, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 220.f, 490.f, 170, 70, window) != 0) { editMovieWindow(window, movieDataBase, *tempMovie, user, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 410.f, 490.f, 170, 70, window) != 0) { supportData.deleteFilm(movieDataBase, *tempMovie, user);
			statement(window, "Usunales film.", "", 0, spriteBackground, font, textFont); return USER;}
		else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 490.f, 140.f, 220, 70, window) != 0) { try { fotoWindow(window, movieName, font); }
		catch (const char* e) { std::cout << "Message: " << e << std::endl; statement(window, "Podany film nie posiada jeszcze zdjecia.", "Przepraszamy.", 0, spriteBackground, font, textFont); } }
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.display();
	}
}

Movie* Window::filmYear(sf::RenderWindow& window, std::vector<Movie*>& movies, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	SaveData saveData;

	sf::Text text("", textFont);
	int numberOfLetters = 0;

	Border border1(370.f, 180.f, 400, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	int check = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (check == 1)
				text = eventSupport.enterYear(event, numberOfLetters, window, text, textFont, 380.f, 180.f, border1, 4);
			if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyReleased)
			{
				const std::regex year_regex("[0-9]{4}");
				std::string str = text.getString();
				if (std::regex_match(str, year_regex))
				{
					std::vector<Movie*>::iterator itMovies;
					for (itMovies = movies.begin(); itMovies != movies.end(); itMovies++)
					{
						if (std::to_string((*itMovies)->getProductionYear()) == text.getString())
							return *itMovies;
					}
				}
				throw "wrong date";
			}

		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) { check = 1; }
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(text);
		textSupport.printText("Wpisz rok produkcji: ", textFont, 35, 30.f, 180.f, sf::Color::Black, window);

		for (int i = 0; i < movies.size(); i++)
		{
			textSupport.printText(movies[i]->getName() + "   "  + std::to_string(movies[i]->getProductionYear()) + "r.", textFont, 30, 40.f, 220.f + 40 * i, sf::Color::Black, window);
		}
		
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.display();
	}
}

void Window::fotoWindow(sf::RenderWindow& window, sf::String filmName, sf::Font& font)
{
	sf::Event event;
	MouseSupport mouseSupport;


	sf::Texture foto;
	if (!foto.loadFromFile("Baza/movie/" + filmName + ".jpg"))
		throw "no picture file in the database";

	sf::Sprite sfoto;
	sfoto.setTexture(foto);
	Button button1("Powrot", font, 30, 75.f, 45.f, 40.f, 40.f, 150, 50);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
		window.clear(sf::Color::White);
		window.draw(sfoto);

		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 30.f, 30.f, 170, 70, window) != 0)
			return;
		window.draw(button1);
		window.display();
	}
}

void Window::editMovieWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;

	Button button1("Edytuj gatunek", font, 25, 45.f, 305.f, 40.f, 300.f, 150, 50);
	Button button2("Edytuj opis", font, 30, 240.f, 305.f, 230.f, 300.f, 150, 50);
	Button button3("Edytuj  tagi", font, 30, 435.f, 305.f, 420.f, 300.f, 150, 50);
	Button button4("Powrot", font, 30, 635.f, 305.f, 610.f, 300.f, 150, 50);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);

		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 30.f, 290.f, 170, 70, window) != 0) { enterEditGenreWindow(window, movie, movieDataBase, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 220.f, 290.f, 170, 70, window) != 0) { enterEditDescriptionWindow(window, movieDataBase, movie, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 410.f, 290.f, 170, 70, window) != 0) { enterEditTagsWindow(window, movieDataBase, movie, spriteBackground, font, textFont); }
		else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 600.f, 290.f, 170, 70, window) != 0) { return; }

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.display();
	}
}

void Window::enterEditGenreWindow(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;
	SupportData supportData;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("fantasy", textFont, 30, 85.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("romans", textFont, 30, 275.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("familijny", textFont, 30, 465.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("sci-fi", textFont, 30, 85.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("dramat", textFont, 30, 275.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("horror", textFont, 30, 465.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("akcja", textFont, 30, 85.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("kryminal", textFont, 30, 275.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("thriller", textFont, 30, 465.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			else if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }

		if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 40.f, 190.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, fantasy); return; }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 230.f, 190.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, romans); return; }
		else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 420.f, 190.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, familijny); return; }
		else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 40.f, 270.f, 170, 70, window) != 0) {
			supportData.saveNewGenre(movie, movieDataBase, scifi); return; }
		else if (mouseSupport.pressButton(button6.getRectangle().getGlobalBounds(), 230.f, 270.f, 170, 70, window) != 0) {
			supportData.saveNewGenre(movie, movieDataBase, dramat); return; }
		else if (mouseSupport.pressButton(button7.getRectangle().getGlobalBounds(), 420.f, 270.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, horror); return; }
		else if (mouseSupport.pressButton(button8.getRectangle().getGlobalBounds(), 40.f, 350.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, akcja); return; }
		else if (mouseSupport.pressButton(button9.getRectangle().getGlobalBounds(), 230.f, 350.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, kryminal); return; }
		else if (mouseSupport.pressButton(button10.getRectangle().getGlobalBounds(), 420.f, 350.f, 170, 70, window) != 0) { 
			supportData.saveNewGenre(movie, movieDataBase, thriller); return; }

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}

void Window::enterEditTagsWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;
	SupportData supportData;

	int newTags[3];
	int i = 0;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("animacja", textFont, 30, 80.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("dla dzieci", textFont, 30, 265.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("wzruszajacy", textFont, 30, 440.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("emocjonujacy", textFont, 30, 55.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("zabawny", textFont, 30, 270.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("straszny", textFont, 30, 460.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("przygodowy", textFont, 30, 60.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("zwariowany", textFont, 30, 250.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("pogodny", textFont, 30, 460.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	HoverLight hoverLight2(40.f, 190.f, 170, 70);
	HoverLight hoverLight3(230.f, 190.f, 170, 70);
	HoverLight hoverLight4(420.f, 190.f, 170, 70);
	HoverLight hoverLight5(40.f, 270.f, 170, 70);
	HoverLight hoverLight6(230.f, 270.f, 170, 70);
	HoverLight hoverLight7(420.f, 270.f, 170, 70);
	HoverLight hoverLight8(40.f, 350.f, 170, 70);
	HoverLight hoverLight9(230.f, 350.f, 170, 70);
	HoverLight hoverLight10(420.f, 350.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
			else if (mouseSupport.releaseButton(button2.getRectangle().getGlobalBounds(), window, event) != 0) { button2.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = animacja; i++; }
			else if (mouseSupport.releaseButton(button3.getRectangle().getGlobalBounds(), window, event) != 0) { button3.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = dla_dzieci; i++; }
			else if (mouseSupport.releaseButton(button4.getRectangle().getGlobalBounds(), window, event) != 0) { button4.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = wzruszajacy; i++; }
			else if (mouseSupport.releaseButton(button5.getRectangle().getGlobalBounds(), window, event) != 0) { button5.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = emocjonujacy; i++; }
			else if (mouseSupport.releaseButton(button6.getRectangle().getGlobalBounds(), window, event) != 0) { button6.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = zabawny; i++; }
			else if (mouseSupport.releaseButton(button7.getRectangle().getGlobalBounds(), window, event) != 0) { button7.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = straszny; i++; }
			else if (mouseSupport.releaseButton(button8.getRectangle().getGlobalBounds(), window, event) != 0) { button8.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = przygodowy; i++; }
			else if (mouseSupport.releaseButton(button9.getRectangle().getGlobalBounds(), window, event) != 0) { button9.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = zwariowany; i++; }
			else if (mouseSupport.releaseButton(button10.getRectangle().getGlobalBounds(), window, event) != 0) { button10.getRectangle().setFillColor(sf::Color(47, 79, 79)); newTags[i] = pogodny; i++; }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		else if (hoverLight2.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight2); }
		else if (hoverLight3.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight3); }
		else if (hoverLight4.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight4); }
		else if (hoverLight5.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight5); }
		else if (hoverLight6.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight6); }
		else if (hoverLight7.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight7); }
		else if (hoverLight8.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight8); }
		else if (hoverLight9.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight9); }
		else if (hoverLight10.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight10); }

		if (i == 3)
		{
			supportData.saveNewTags(movie, movieDataBase, newTags);
			return;
		}

		std::string text = "wybierz " + std::to_string(i + 1) + " tag:";
		textSupport.printText(text, textFont, 30, 110.f, 130.f, sf::Color::Black, window);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}

void Window::enterEditDescriptionWindow(sf::RenderWindow& window, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	SaveData saveData;
	
	sf::Text sentence1("", textFont);
	sf::Text sentence2("", textFont);
	sf::Text sentence3("", textFont);
	int nTag1 = 0, nTag2 = 0, nTag3 = 0;
	Border border1(30.f, 250.f, 600, 50);
	Border border2(30.f, 320.f, 600, 50);
	Border border3(30.f, 390.f, 600, 50);
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	int check = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (check == 1)
				sentence1 = eventSupport.enterWord(event, nTag1, window, sentence1, textFont, 40.f, 250.f, border1, 45);
			if (check == 2)
				sentence2 = eventSupport.enterWord(event, nTag2, window, sentence2, textFont, 40.f, 320.f, border2, 45);
			if (check == 3)
				sentence3 = eventSupport.enterWord(event, nTag3, window, sentence3, textFont, 40.f, 390.f, border3, 45);
			if (event.key.code == sf::Keyboard::Enter)
			{
				std::string s1 = sentence1.getString(), s2 = sentence2.getString(), s3 = sentence3.getString();
				movie.setDescription(s1, s2, s3);
				saveData.saveDataMovie(movieDataBase);
				return;
			}
		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) {
			check = 1;
			border2.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border2.getRectangle().getGlobalBounds(), window) != 0) {
			check = 2;
			border1.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border3.getRectangle().getGlobalBounds(), window) != 0) {
			check = 3;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(border2);
		window.draw(border3);
		window.draw(sentence1);
		window.draw(sentence2);
		window.draw(sentence3);
		textSupport.printText("Wpisz maksymalnie trzy zadania opisu: ", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		if (mouseSupport.pressButton(button1.getRectangle().getGlobalBounds(), 560.f, 490.f, 170, 70, window) != 0)
		{
			return;
		}
		window.draw(button1);
		window.display();
	}
}

void Window::showAllMovis(sf::RenderWindow& window, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	std::string data;
	int k = 40, j = 10, z = 0, y;
	Button button1("<<", textFont, 30, 453.f, 155.f, 440.f, 150.f, 50, 50);
	Button button2(">>", textFont, 30, 533.f, 155.f, 520.f, 150.f, 50, 50);
	Button button3("Powrot", textFont, 30, 466.f, 255.f, 440.f, 250.f, 130, 50);
	HoverLight hoverLight1(430.f, 140.f, 70, 70);
	HoverLight hoverLight2(510.f, 140.f, 70, 70);
	HoverLight hoverLight3(430.f, 240.f, 150, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{

		sf::Event event;
		mousePosition = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0)
			{
				if (z > 0)
				{
					z = z - 10; j = j - 10;
				}
			}
			else if (mouseSupport.releaseButton(button2.getRectangle().getGlobalBounds(), window, event) != 0)
			{
				if (z < movieDataBase.allMovies.size())
				{
					z = z + 10; j = j + 10;
				}
			}
			if (mouseSupport.releaseButton(button3.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		y = 0;
		for (int i = z; i < j && i < movieDataBase.allMovies.size(); i++)
		{
			textSupport.printText(movieDataBase.allMovies[i].getName() + " " + std::to_string(movieDataBase.allMovies[i].getProductionYear()), textFont, 30, 40.f, 150.f + k * y, sf::Color::Black, window);
			y++;
		}

		if (hoverLight3.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight3); }
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		if (hoverLight2.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight2); }
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.display();
	}
}

void Window::showMovisFormGenre(sf::RenderWindow& window, int eGenre, Genre& genre, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{	

	std::vector<std::pair<std::vector<Movie*>, int>>::iterator it;
	std::vector<Movie*> movies;

	it = genre.movies.begin();
	for (int i = 0; i < eGenre; i++)
		it++;
	movies = (*it).first;

	MouseSupport mouseSupport;
	TextSupport textSupport;
	std::string data;
	int k = 40, j = 10, z = 0, y;
	Button button1("<<", textFont, 30, 453.f, 155.f, 440.f, 150.f, 50, 50);
	Button button2(">>", textFont, 30, 533.f, 155.f, 520.f, 150.f, 50, 50);
	Button button3("Powrot", textFont, 30, 466.f, 255.f, 440.f, 250.f, 130, 50);
	HoverLight hoverLight1(430.f, 140.f, 70, 70);
	HoverLight hoverLight2(510.f, 140.f, 70, 70);
	HoverLight hoverLight3(430.f, 240.f, 150, 70);
	sf::Vector2i mousePosition;
	
	while (window.isOpen())
	{
	
		sf::Event event;
		mousePosition = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) 
			{
				if (z > 0)
				{ z = z - 10; j = j - 10;} 
			}
			else if (mouseSupport.releaseButton(button2.getRectangle().getGlobalBounds(), window, event) != 0) 
			{
				if (z < movies.size()) 
				{ z = z + 10; j = j + 10; } 
			}
			if (mouseSupport.releaseButton(button3.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
	    y = 0;
		for (int i = z; i < j && i < movies.size(); i++)
		{
			textSupport.printText(movies[i]->getName() + " " + std::to_string(movies[i]->getProductionYear()), textFont, 30, 40.f, 150.f + k * y, sf::Color::Black, window);
			y++;
		}
		
		if (hoverLight3.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight3); }
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		if (hoverLight2.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight2); }
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.display();
	}
}

void Window::showMovisFormTag(sf::RenderWindow& window, int eTag, Tag& tag, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{

	std::vector<std::pair<std::vector<Movie*>, int>>::iterator it;
	std::vector<Movie*> movies;

	it = tag.movies.begin();
	for (int i = 0; i < eTag; i++)
		it++;
	movies = (*it).first;

	MouseSupport mouseSupport;
	TextSupport textSupport;
	std::string data;
	int k = 40, j = 10, z = 0, y;
	Button button1("<<", textFont, 30, 453.f, 155.f, 440.f, 150.f, 50, 50);
	Button button2(">>", textFont, 30, 533.f, 155.f, 520.f, 150.f, 50, 50);
	Button button3("Powrot", textFont, 30, 466.f, 255.f, 440.f, 250.f, 130, 50);
	HoverLight hoverLight1(430.f, 140.f, 70, 70);
	HoverLight hoverLight2(510.f, 140.f, 70, 70);
	HoverLight hoverLight3(430.f, 240.f, 150, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		mousePosition = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0 && z > 0)
			{
					z = z - 10; j = j - 10;
			}
			else if (mouseSupport.releaseButton(button2.getRectangle().getGlobalBounds(), window, event) != 0 && z < movies.size())
			{
				z = z + 10; j = j + 10;
			}
			if (mouseSupport.releaseButton(button3.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		y = 0;
		for (int i = z; i < j && i < movies.size(); i++)
		{
			textSupport.printText(movies[i]->getName() + " " + std::to_string(movies[i]->getProductionYear()), textFont, 30, 40.f, 150.f + k * y, sf::Color::Black, window);
			y++;
		}
		if (hoverLight3.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight3); }
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		if (hoverLight2.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight2); }
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.display();
	}
};

void Window::enterSearchGenre(sf::RenderWindow& window, User& user, Genre& genre, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("fantasy", textFont, 30, 85.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("romans", textFont, 30, 275.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("familijny", textFont, 30, 465.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("sci-fi", textFont, 30, 85.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("dramat", textFont, 30, 275.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("horror", textFont, 30, 465.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("akcja", textFont, 30, 85.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("kryminal", textFont, 30, 275.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("thriller", textFont, 30, 465.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			else if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		try
		{
			if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 40.f, 190.f, 170, 70, window) != 0) {showMovisFormGenre(window, fantasy, genre, user, spriteBackground, font, textFont); return;}
			else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 230.f, 190.f, 170, 70, window) != 0) { showMovisFormGenre(window, romans, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 420.f, 190.f, 170, 70, window) != 0) { showMovisFormGenre(window, familijny, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 40.f, 270.f, 170, 70, window) != 0) { showMovisFormGenre(window, scifi, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button6.getRectangle().getGlobalBounds(), 230.f, 270.f, 170, 70, window) != 0) { showMovisFormGenre(window, dramat, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button7.getRectangle().getGlobalBounds(), 420.f, 270.f, 170, 70, window) != 0) { showMovisFormGenre(window, horror, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button8.getRectangle().getGlobalBounds(), 40.f, 350.f, 170, 70, window) != 0) { showMovisFormGenre(window, akcja, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button9.getRectangle().getGlobalBounds(), 230.f, 350.f, 170, 70, window) != 0) { showMovisFormGenre(window, kryminal, genre, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button10.getRectangle().getGlobalBounds(), 420.f, 350.f, 170, 70, window) != 0) { showMovisFormGenre(window, thriller, genre, user, spriteBackground, font, textFont); return; }
		}
		catch (...) { Window win; win.statement(window, "Nie ¿adego filmu w szukanym gatunku.", "", 3, spriteBackground, font, textFont); return; }

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}

void Window::enterSearchTag(sf::RenderWindow& window, User& user, Tag& tag, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("animacja", textFont, 30, 80.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("dla_dzieci", textFont, 30, 265.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("wzruszajacy", textFont, 30, 440.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("emocjonujacy", textFont, 30, 55.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("zabawny", textFont, 30, 270.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("straszny", textFont, 30, 460.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("przygodowy", textFont, 30, 60.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("zwariowany", textFont, 30, 250.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("pogodny", textFont, 30, 460.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			else if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		try
		{
			if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 40.f, 190.f, 170, 70, window) != 0) { showMovisFormTag(window, animacja, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 230.f, 190.f, 170, 70, window) != 0) { showMovisFormTag(window, dla_dzieci, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 420.f, 190.f, 170, 70, window) != 0) { showMovisFormTag(window, wzruszajacy, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 40.f, 270.f, 170, 70, window) != 0) { showMovisFormTag(window, emocjonujacy, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button6.getRectangle().getGlobalBounds(), 230.f, 270.f, 170, 70, window) != 0) { showMovisFormTag(window, zabawny, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button7.getRectangle().getGlobalBounds(), 420.f, 270.f, 170, 70, window) != 0) { showMovisFormTag(window, straszny, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button8.getRectangle().getGlobalBounds(), 40.f, 350.f, 170, 70, window) != 0) { showMovisFormTag(window, przygodowy, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button9.getRectangle().getGlobalBounds(), 230.f, 350.f, 170, 70, window) != 0) { showMovisFormTag(window, zwariowany, tag, user, spriteBackground, font, textFont); return; }
			else if (mouseSupport.pressButton(button10.getRectangle().getGlobalBounds(), 420.f, 350.f, 170, 70, window) != 0) { showMovisFormTag(window, pogodny, tag, user, spriteBackground, font, textFont); return; }
		}
		catch (...) { Window win; win.statement(window, "Nie filmu w szukanym tagu.", "", 3, spriteBackground, font, textFont); return; }

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}

void Window::newFilmTitle(sf::RenderWindow& window, User& user, MovieDataBase& movieDataBase, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	Movie movie;
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	sf::Text text("", textFont);
	int numberOfLetters = 0;
	Border border1(370.f, 180.f, 400, 50);
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;
	int check = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (check == 1)
				text = eventSupport.enterWord(event, numberOfLetters, window, text, textFont, 380.f, 180.f, border1, 29);
			if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyReleased)
			{
				try { movie.setName(text.getString()); }
				catch (const char* e) { std::cout << "Message: " << e << std::endl; statement(window, "Wpisz tytul z duzej litery.", "", 0, spriteBackground, font, textFont); return; }
				newFilmYear(window, user, movieDataBase, movie, spriteBackground, font, textFont);
				return;
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) { check = 1; }
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(text);
		textSupport.printText("Wpisz tytul nowego filmu: ", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.display();
	}
}

void Window::newFilmYear(sf::RenderWindow& window, User& user, MovieDataBase& movieDataBase, Movie& movie, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;
	SaveData saveData;

	sf::Text text("", textFont);
	int numberOfLetters = 0;

	Border border1(370.f, 180.f, 400, 50);
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	int check = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (check == 1)
				text = eventSupport.enterYear(event, numberOfLetters, window, text, textFont, 380.f, 180.f, border1, 4);
			if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyReleased)
			{
				try { movie.setProductionYear(text.getString()); }
				catch (const char* e) { std::cout << "Message: " << e << std::endl; statement(window, "Wpisales niepoprawna date produkcji.", "", 0, spriteBackground, font, textFont); return; }
				newFilmGenre(window, movie, movieDataBase, user, spriteBackground, font, textFont);
				return;
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) { check = 1; }
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(text);
		textSupport.printText("Wpisz rok produkcji: ", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.display();
	}
}

void Window::newFilmGenre(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("fantasy", textFont, 30, 85.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("romans", textFont, 30, 275.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("familijny", textFont, 30, 465.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("sci-fi", textFont, 30, 85.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("dramat", textFont, 30, 275.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("horror", textFont, 30, 465.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("akcja", textFont, 30, 85.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("kryminal", textFont, 30, 275.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("thriller", textFont, 30, 465.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			else if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		else if (mouseSupport.pressButton(button2.getRectangle().getGlobalBounds(), 40.f, 190.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, fantasy); return; }
		else if (mouseSupport.pressButton(button3.getRectangle().getGlobalBounds(), 230.f, 190.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, romans); return; }
		else if (mouseSupport.pressButton(button4.getRectangle().getGlobalBounds(), 420.f, 190.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, familijny);
		return; }
		else if (mouseSupport.pressButton(button5.getRectangle().getGlobalBounds(), 40.f, 270.f, 170, 70, window) != 0) {  newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, scifi); return; }
		else if (mouseSupport.pressButton(button6.getRectangle().getGlobalBounds(), 230.f, 270.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, dramat); return; }
		else if (mouseSupport.pressButton(button7.getRectangle().getGlobalBounds(), 420.f, 270.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, horror); return; }
		else if (mouseSupport.pressButton(button8.getRectangle().getGlobalBounds(), 40.f, 350.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, akcja); return; }
		else if (mouseSupport.pressButton(button9.getRectangle().getGlobalBounds(), 230.f, 350.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, kryminal); return; }
		else if (mouseSupport.pressButton(button10.getRectangle().getGlobalBounds(), 420.f, 350.f, 170, 70, window) != 0) { newFilmDesc(window, movie, movieDataBase, user, spriteBackground, font, textFont, thriller); return; }

		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}

void Window::newFilmDesc(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont, int genreNuber)
{
	MouseSupport mouseSupport;
	TextSupport textSupport;
	EventSupport eventSupport;

	sf::Text sentence1("", textFont);
	sf::Text sentence2("", textFont);
	sf::Text sentence3("", textFont);
	int nTag1 = 0, nTag2 = 0, nTag3 = 0;
	Border border1(30.f, 250.f, 600, 50);
	Border border2(30.f, 320.f, 600, 50);
	Border border3(30.f, 390.f, 600, 50);
	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	sf::Vector2i mousePosition;
	int check = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (check == 1)
				sentence1 = eventSupport.enterWord(event, nTag1, window, sentence1, textFont, 40.f, 250.f, border1, 45);
			if (check == 2)
				sentence2 = eventSupport.enterWord(event, nTag2, window, sentence2, textFont, 40.f, 320.f, border2, 45);
			if (check == 3)
				sentence3 = eventSupport.enterWord(event, nTag3, window, sentence3, textFont, 40.f, 390.f, border3, 45);
			if (event.key.code == sf::Keyboard::Enter && event.type == sf::Event::KeyReleased)
			{	
				std::string s1 = sentence1.getString(), s2 = sentence2.getString(), s3 = sentence3.getString();
				movie.setDescription(s1, s2, s3);
				NewFilmTags(window, movie, movieDataBase, user, spriteBackground, font, textFont, genreNuber);
				return;
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
		}
		if (mouseSupport.pressBorder(border1.getRectangle().getGlobalBounds(), window) != 0) {
			check = 1;
			border2.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border2.getRectangle().getGlobalBounds(), window) != 0) {
			check = 2;
			border1.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		else if (mouseSupport.pressBorder(border3.getRectangle().getGlobalBounds(), window) != 0) {
			check = 3;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			check = 0;
			border1.setColor(sf::Color::White);
			border2.setColor(sf::Color::White);
			border3.setColor(sf::Color::White);
		}
		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		window.draw(border1);
		window.draw(border2);
		window.draw(border3);
		window.draw(sentence1);
		window.draw(sentence2);
		window.draw(sentence3);
		textSupport.printText("Wpisz maksymalnie trzy zadania opisu nowego filmu: ", textFont, 35, 30.f, 180.f, sf::Color::Black, window);
		mousePosition = sf::Mouse::getPosition(window);
		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		window.draw(button1);
		window.display();
	}
}

void Window::NewFilmTags(sf::RenderWindow& window, Movie& movie, MovieDataBase& movieDataBase, User& user, sf::Sprite& spriteBackground, sf::Font& font, sf::Font& textFont, int genreNuber)
{
	MouseSupport mouseSupport;
	EventSupport eventSupport;
	TextSupport textSupport;
	SupportData supportData;
	std::string message;

	int tagsNumber[3];
	int i = 0;

	Button button1("Powrot", font, 30, 605.f, 505.f, 570.f, 500.f, 150, 50);
	Button button2("animacja", textFont, 30, 80.f, 205.f, 50.f, 200.f, 150, 50);
	Button button3("dla dzieci", textFont, 30, 265.f, 205.f, 240.f, 200.f, 150, 50);
	Button button4("wzruszajacy", textFont, 30, 440.f, 205.f, 430.f, 200.f, 150, 50);
	Button button5("emocjonujacy", textFont, 30, 55.f, 285.f, 50.f, 280.f, 150, 50);
	Button button6("zabawny", textFont, 30, 270.f, 285.f, 240.f, 280.f, 150, 50);
	Button button7("straszny", textFont, 30, 460.f, 285.f, 430.f, 280.f, 150, 50);
	Button button8("przygodowy", textFont, 30, 60.f, 365.f, 50.f, 360.f, 150, 50);
	Button button9("zwariowany", textFont, 30, 250.f, 365.f, 240.f, 360.f, 150, 50);
	Button button10("pogodny", textFont, 30, 460.f, 365.f, 430.f, 360.f, 150, 50);
	HoverLight hoverLight1(560.f, 490.f, 170, 70);
	HoverLight hoverLight2(40.f, 190.f, 170, 70);
	HoverLight hoverLight3(230.f, 190.f, 170, 70);
	HoverLight hoverLight4(420.f, 190.f, 170, 70);
	HoverLight hoverLight5(40.f, 270.f, 170, 70);
	HoverLight hoverLight6(230.f, 270.f, 170, 70);
	HoverLight hoverLight7(420.f, 270.f, 170, 70);
	HoverLight hoverLight8(40.f, 350.f, 170, 70);
	HoverLight hoverLight9(230.f, 350.f, 170, 70);
	HoverLight hoverLight10(420.f, 350.f, 170, 70);
	sf::Vector2i mousePosition;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(1);
			}
			if (mouseSupport.releaseButton(button1.getRectangle().getGlobalBounds(), window, event) != 0) { return; }
			else if (mouseSupport.releaseButton(button2.getRectangle().getGlobalBounds(), window, event) != 0) { button2.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = animacja; i++;  }
			else if (mouseSupport.releaseButton(button3.getRectangle().getGlobalBounds(), window, event) != 0) { button3.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = dla_dzieci; i++;  }
			else if (mouseSupport.releaseButton(button4.getRectangle().getGlobalBounds(), window, event) != 0) { button4.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = wzruszajacy; i++;  }
			else if (mouseSupport.releaseButton(button5.getRectangle().getGlobalBounds(), window, event) != 0) { button5.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = emocjonujacy; i++;  }
			else if (mouseSupport.releaseButton(button6.getRectangle().getGlobalBounds(), window, event) != 0) { button6.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = zabawny; i++;  }
			else if (mouseSupport.releaseButton(button7.getRectangle().getGlobalBounds(), window, event) != 0) { button7.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = straszny; i++;  }
			else if (mouseSupport.releaseButton(button8.getRectangle().getGlobalBounds(), window, event) != 0) { button8.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = przygodowy; i++;  }
			else if (mouseSupport.releaseButton(button9.getRectangle().getGlobalBounds(), window, event) != 0) { button9.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = zwariowany; i++;  }
			else if (mouseSupport.releaseButton(button10.getRectangle().getGlobalBounds(),window, event) != 0) { button10.getRectangle().setFillColor(sf::Color(47, 79, 79)); tagsNumber[i] = pogodny; i++;  }
		}

		window.clear(sf::Color::White);
		window.draw(spriteBackground);
		textSupport.printText("Baza    Filmowa", font, 100, 110.f, -10.f, sf::Color::White, window);
		mousePosition = sf::Mouse::getPosition(window);

		if (hoverLight1.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight1); }
		else if (hoverLight2.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight2); }
		else if (hoverLight3.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight3); }
		else if (hoverLight4.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight4); }
		else if (hoverLight5.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight5); }
		else if (hoverLight6.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight6); }
		else if (hoverLight7.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight7); }
		else if (hoverLight8.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight8); }
		else if (hoverLight9.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight9); }
		else if (hoverLight10.getRectangle().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) { window.draw(hoverLight10); }

		if (i == 3)
		{
			message = supportData.saveNewFilm(movieDataBase, movie, user, genreNuber, tagsNumber);
			statement(window, message, "", 0, spriteBackground, font, textFont);

			return;
		}

		std::string text = "wybierz " + std::to_string(i + 1) + " tag:";
		textSupport.printText(text, textFont, 30, 110.f, 130.f, sf::Color::Black, window);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.draw(button5);
		window.draw(button6);
		window.draw(button7);
		window.draw(button8);
		window.draw(button9);
		window.draw(button10);
		window.display();
	}
}
