#include "ProjectManager.h"
#include "Project.h"
#include <iostream>
#include <string>
using namespace std;

ProjectManager::ProjectManager()
{
	loadProject();
	showMenu();
}

void ProjectManager::showMenu()
{
	int user = 0;
	cout << " +-------------------------------------------------+" << endl;
	cout << " |             1. View Projects                    |" << endl;
	cout << " |             2. Add Project                      |" << endl;
	cout << " |             3. Exit                             |" << endl;
	cout << " +-------------------------------------------------+" << endl;
	cout << " Enter option (1, 2, 3): ";
	cin >> user;
	cin.ignore();
	if (user == 1)
		displayProject();
	else if (user == 2)
		addProject();
	else
		exit(0);
}

void ProjectManager::addProject()
{
	try
	{
		file.open("test.txt", ios::app);

		Project project;

		// ASK MOVIE STATUS
		cout << "Enter movie status" << endl;
		cout << " 0 - UNRELEASED" << endl;
		cout << " 1 - NOW PLAYING" << endl;
		cout << " 2 - RELEASED" << endl;
		int ms;
		cin >> ms;
		cin.ignore();
		if (ms == 0)
			project.status = project.UNRELEASED;
		else if (ms == 1)
			project.status = project.NOWPLAYING;
		else if (ms == 2)
			project.status = project.RELEASED;
		else
			project.status = project.UNRELEASED;
		file << to_string(ms) << endl;

		// ASK TITLE
		cout << "Enter movie title" << endl;
		getline(cin, project.title);
		file << project.title << endl;

		// ASK SUMMARY
		cout << "Enter movie summary" << endl;
		getline(cin, project.summary);
		file << project.summary << endl;

		// ASK GENRE
		cout << "How many genres are there in this movie?" << endl;
		int num;
		string g;
		cin >> num;
		cin.ignore();
		for (int i = 0; i < num; i++)
		{
			cout << "Enter movie genre number " + to_string(i + 1) << endl;
			getline(cin, g);
			project.genre.push_back(g);
		}
		file << to_string(num) << endl;
		for (int i = 0; i < num; i++)
		{
			file << project.genre.at(i) << endl;
		}

		// ASK RELEASE DATE
		cout << "Enter release date (DD-MM-YYYY)" << endl;
		getline(cin, project.releaseDate);
		file << project.releaseDate << endl;

		// ASK LOCATIONS
		cout << "How many locations was this movie filmed at?" << endl;
		cin >> num;
		cin.ignore();
		file << to_string(num) << endl;
		for (int i = 0; i < num; i++)
		{
			cout << "Enter movie filming location " + to_string(i + 1) << endl;
			getline(cin, g);
			project.locations.push_back(g);
			file << g << endl;
		}

		// ASK LANGUAGE
		cout << "Enter the language of the movie" << endl;
		getline(cin, project.language);
		file << project.language << endl;

		// ASK RUNTIME
		cout << "Enter movie runtime (mins)" << endl;
		cin >> project.runtime;
		cin.ignore();
		file << to_string(project.runtime) << endl;

		// ASK KEYWORD
		cout << "Enter a keyword for the movie" << endl;
		getline(cin, project.keyword);
		file << project.keyword << endl;

		// ASK BOX OFFICE (NOWPLAYING OR RELEASED ONLY)
		if (project.status == 1 || project.status == 2)
		{
			cout << "Enter the weekly box office for the movie" << endl;
			cin >> project.boxOffice;
			cin.ignore();
		}
		else 
		{
			project.boxOffice = 0;
		}
		file << to_string(project.boxOffice) << endl;

		movies.push_back(project);
		cout << "file closing" << endl;
		file.close();
		showMenu();
	}
	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}

	
}

void ProjectManager::displayProject()
{
	cout << movies.size() << endl;
	for (size_t i = 0; i < movies.size(); i++)
	{
		string tempStatus;
		if (movies.at(i).status == 1)
			tempStatus = "NOW PLAYING";
		else if (movies.at(i).status == 2)
			tempStatus = "RELEASED";
		else
			tempStatus = "UNRELEASED";
		cout << "Status            : " << tempStatus << endl;
		cout << "Title             : " << movies.at(i).title << endl;
		cout << "Summary           : " << movies.at(i).summary << endl;
		cout << "Genre             : ";
		for (size_t j = 0; j < movies.at(i).genre.size(); j++)
		{
			cout << movies.at(i).genre.at(j);
			if (j < movies.at(i).genre.size() - 1) cout << ", ";
		}
		cout << endl;
		cout << "Release Date      : " << movies.at(i).releaseDate << endl;
		cout << "Filming locations : ";
		for (size_t k = 0; k < movies.at(i).locations.size(); k++)
		{
			cout << movies.at(i).locations.at(k);
			if (k < movies.at(i).locations.size() - 1) cout << ", ";
		}
		cout << endl;
		cout << "Language          : " << movies.at(i).language << endl;
		cout << "Runtime           : " << movies.at(i).runtime << " mins" << endl;
		cout << "Keyword           : " << movies.at(i).keyword << endl;
		cout << "Box Office        : " << movies.at(i).boxOffice << endl;
		cout << endl;
	}
	showMenu();
}

void ProjectManager::loadProject()
{
	cout << "Loading file..." << endl;
	try
	{
		file.open("test.txt", ios::app);
		file.close();
		infile.open("test.txt");
		
		Project p;
		string g;
		int num;
		while (!infile.eof())
		{	
			cout << "AYY LETS GO" << endl;

			// READ STATUS
			int ms;
			getline(infile, g);
			ms = stoi(g);
			if (ms == 1)
				p.status = p.NOWPLAYING;
			else if (ms == 2)
				p.status = p.RELEASED;
			else
				p.status = p.UNRELEASED;
			
			// READ TITLE
			getline(infile, p.title);
			
			// READ SUMMARY
			getline(infile, p.summary);

			
			getline(infile, g);
			//cout << typeid(g).name() << g << endl;
			num = stoi(g);
			for (int i = 0; i < num; i++)
			{
				getline(infile, g);
				p.genre.push_back(g);
			}
			getline(infile, p.releaseDate);
			
			getline(infile, g);
			//cout << typeid(g).name() << g << endl;
			num = stoi(g);
			for (int i = 0; i < num; i++)
			{
				getline(infile, g);
				cout << typeid(g).name() << g << endl;
				p.locations.push_back(g);
			}
			getline(infile, p.language);

			getline(infile, g);
			cout << typeid(g).name() << g  << "runtime" << endl;
			p.runtime = stoi(g);
			getline(infile, p.keyword);
			getline(infile, g);
			
			//cout << typeid(num).name() << num << endl;
			p.boxOffice = stod(g);

			movies.push_back(p);
			cout << "ADDED" << endl;
		}
	}
	catch(exception ex)
	{
		cerr << ex.what() << endl;
	}
	infile.close();
}