#include "User.h"

User::User() {}
User::~User() {}

void User::showRecommended(sf::Font textFont, sf::RenderWindow& window, Genre& genre, Tag& tag)
{
	std::vector<Movie*> reccomendedWith2Tag;
	std::vector<Movie*> reccomendedWith1Tag;
	std::vector<Movie*> reccomendedWith0Tag;
	std::vector<Movie*>::iterator itReccomended;

	if (ratedMovies.empty()) { return; }

	TextSupport textSupport;
	std::string str;

	std::list<std::pair<Movie*, int>>::iterator itRatedMovies = ratedMovies.begin();
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itAllGenre = genre.movies.begin();

	for (int i = 0; i < ((*itRatedMovies).first)->getGenre(); i++)
		itAllGenre++;
	
	std::vector<Movie*>::iterator itMovies = (*itAllGenre).first.begin();

	int i = 0;

	while (i != 5 && itMovies != (*itAllGenre).first.end())
	{
		if (!(*itMovies)->tempUserRating)
		{
			if ((*itMovies)->getTag(0) == ((*itRatedMovies).first)->getTag(0) && (*itMovies)->getTag(1) == ((*itRatedMovies).first)->getTag(1) && (*itMovies)->getTag(2) == ((*itRatedMovies).first)->getTag(2)) // 3 tags
			{
				textSupport.printText((*itMovies)->getName()+" "+ std::to_string((*itMovies)->getProductionYear()), textFont, 30, 280.f, 270.f + i * 40, sf::Color::Black, window);
				i++;
			}
			else if (((*itMovies)->getTag(0) == ((*itRatedMovies).first)->getTag(0) && (*itMovies)->getTag(1) == ((*itRatedMovies).first)->getTag(1)) ||  // 2 tags
				((*itMovies)->getTag(0) == ((*itRatedMovies).first)->getTag(0) && (*itMovies)->getTag(2) == ((*itRatedMovies).first)->getTag(2)) ||
				((*itMovies)->getTag(1) == ((*itRatedMovies).first)->getTag(1) && (*itMovies)->getTag(2) == ((*itRatedMovies).first)->getTag(2)))
			{
				reccomendedWith2Tag.push_back((*itMovies));
			}
			else if ((*itMovies)->getTag(0) == ((*itRatedMovies).first)->getTag(0) || (*itMovies)->getTag(1) == ((*itRatedMovies).first)->getTag(1) || (*itMovies)->getTag(2) == ((*itRatedMovies).first)->getTag(2))  // 1 tag
			{
				reccomendedWith1Tag.push_back((*itMovies));
			}
			else if (!(*itMovies)->tempUserRating) // 0 tag
			{
				reccomendedWith0Tag.push_back((*itMovies));
			}
		}
		itMovies++;
	}
	if (i == 5) { return; }

	for (itReccomended = reccomendedWith2Tag.begin(); itReccomended != reccomendedWith2Tag.end(); itReccomended++)
	{ 
		textSupport.printText((*itReccomended)->getName() + " " + std::to_string((*itReccomended)->getProductionYear()), textFont, 30, 280.f, 270.f + i * 40, sf::Color::Black, window);
		i++;
		if (i == 5) { return; }
	}

	for (itReccomended = reccomendedWith1Tag.begin(); itReccomended != reccomendedWith1Tag.end(); itReccomended++)
	{
		textSupport.printText((*itReccomended)->getName() + " " + std::to_string((*itReccomended)->getProductionYear()), textFont, 30, 280.f, 270.f + i * 40, sf::Color::Black, window);
		i++;
		if (i == 5) { return; }
	}

	for (itReccomended = reccomendedWith0Tag.begin(); itReccomended != reccomendedWith0Tag.end(); itReccomended++)
	{
		textSupport.printText((*itReccomended)->getName() + " " + std::to_string((*itReccomended)->getProductionYear()), textFont, 30, 280.f, 270.f + i * 40, sf::Color::Black, window);
		i++;
		if (i == 5) { return; }
	}

	return;
}

void User::showRecentlyRated( sf::Font textFont, sf::RenderWindow& window)
{
	TextSupport textSupport;
	std::list<std::pair<Movie*, int>>::iterator it = ratedMovies.begin();

	for (int i = 0; i < 7 && it != ratedMovies.end(); i++)
	{
		textSupport.printText((*it).first->getName() + " " + std::to_string((*it).first->getProductionYear()), textFont, 30, 30.f, 270.f + i * 40, sf::Color::Black, window);
		it++;
	}
	return;
}

void User::rateMovie(int _rating, Movie& movie)
{
	if (movie.tempUserRating)
	{
		int oldRating = *movie.tempUserRating;

		movie.getRating().numbersOfRatings[oldRating - 1]--;

		movie.getRating().numbersOfRatings[_rating - 1]++;
		*movie.tempUserRating = _rating;
	}

	else
	{
		std::pair<Movie*, int> p;

		p.first = &movie;
		p.second = _rating;

		movie.getRating().numbersOfRatings[_rating - 1]++;
		ratedMovies.push_front(p);

		std::list<std::pair<Movie*, int>>::iterator itRatedMovies = ratedMovies.begin();
		(*itRatedMovies).first->tempUserRating = &(*itRatedMovies).second;
	}

	return;
}