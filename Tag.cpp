#include "Tag.h"

Tag::Tag()
{
	std::pair<std::vector<Movie*>, int> tag;

	for (int i = 0; i < 9; i++)
	{
		tag.second = i;
		movies.push_back(tag);
	}
}

void Tag::removeFromTags( Movie& movie)
{
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itTagList;

	for (int i = 0; i < 3; i++)
	{
		itTagList = movies.begin();
		for (int j = 0; j < movie.getTag(i); j++)
			itTagList++;

		std::vector<Movie*>::iterator itMovies;
		for (itMovies = (*itTagList).first.begin(); itMovies != (*itTagList).first.end(); itMovies++)
		{
			if ((*itMovies)->getName() == movie.getName() && (*itMovies)->getProductionYear() == movie.getProductionYear())
			{
				(*itTagList).first.erase(itMovies);
				break;
			}
		}

		movie.setTempTag(nullptr, i);
	}

	return;
}

void Tag::addToTag(Movie& movie, int tagsNumber[])
{
	std::vector<std::pair<std::vector<Movie*>, int>>::iterator itTagList;

	for (int i = 0; i < 3; i++)
	{
		itTagList = movies.begin();

		for (int j = 0; j < tagsNumber[i]; j++)
			itTagList++;
		
		movie.setTag((*itTagList).second, i);
		(*itTagList).first.push_back(&movie);
	}
}

std::string Tag::toString(int genreNumber)
{
	switch (genreNumber)
	{
	case animacja:
		return "animacja";
	case dla_dzieci:
		return "dla dzieci";
	case wzruszajacy:
		return "wzruszajacy";
	case emocjonujacy:
		return "emocjonujacy";
	case zabawny:
		return "zabawny";
	case straszny:
		return "straszny";
	case przygodowy:
		return "przygodowy";
	case zwariowany:
		return "zwariowany";
	case pogodny:
		return "pogodny";
	}

	return "";
}