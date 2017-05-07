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
	cout << " |             3. Update Project                   |" << endl;
	cout << " |             4. Delete Project                   |" << endl;
	cout << " |             9. Exit                             |" << endl;
	cout << " +-------------------------------------------------+" << endl;
	cout << " Enter option (1, 2, 3, ...): ";
	cin >> user;
	cin.ignore();

	switch (user)
	{
	case 1:
		displayProject();
		break;
	case 2:
		addProject();
		break;
	case 3:
		updateProject();
		break;
	case 4:
		deleteProject();
		break;
	default:
		postProject();
		exit(0);
	}
}

void ProjectManager::addProject()
{
	try
	{
		Project project;

		// ASK MOVIE STATUS
		cout << "Enter movie status" << endl;
		cout << " 0 - UNRELEASED" << endl;
		cout << " 1 - NOW PLAYING" << endl;
		cout << " 2 - RELEASED" << endl;
		cin >> project.status;
		cin.ignore();
		//file << to_string(project.status) << endl;

		// ASK TITLE
		cout << "Enter movie title" << endl;
		getline(cin, project.title);
		//file << project.title << endl;

		// ASK SUMMARY
		cout << "Enter movie summary" << endl;
		getline(cin, project.summary);
		//file << project.summary << endl;

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

		// ASK RELEASE DATE
		cout << "Enter release date (DD-MM-YYYY)" << endl;
		getline(cin, project.releaseDate);
		//file << project.releaseDate << endl;

		// ASK LOCATIONS
		cout << "How many locations was this movie filmed at?" << endl;
		cin >> num;
		cin.ignore();
		//file << to_string(num) << endl;
		for (int i = 0; i < num; i++)
		{
			cout << "Enter movie filming location " + to_string(i + 1) << endl;
			getline(cin, g);
			project.locations.push_back(g);
			//file << g << endl;
		}

		// ASK LANGUAGE
		cout << "Enter the language of the movie" << endl;
		getline(cin, project.language);
		//file << project.language << endl;

		// ASK RUNTIME
		cout << "Enter movie runtime (mins)" << endl;
		cin >> project.runtime;
		cin.ignore();
		//file << to_string(project.runtime) << endl;

		// ASK KEYWORD
		cout << "Enter a keyword for the movie" << endl;
		getline(cin, project.keyword);
		//file << project.keyword << endl;

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
		//file << to_string(project.boxOffice) << endl;

		movies.push_back(project);
		
		showMenu();
	}
	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}

	
}

void ProjectManager::displayProject()
{	
	system("cls");
	cout << movies.size() << endl;
	for (unsigned i = 0; i < movies.size(); i++)
	{
		string tempStatus;
		//cout << to_string(movies.at(i).size()) << endl;
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
		for (unsigned j = 0; j < movies.at(i).genre.size(); j++)
		{
			cout << movies.at(i).genre.at(j);
			if (j < movies.at(i).genre.size() - 1) cout << ", ";
		}
		cout << endl;
		cout << "Release Date      : " << movies.at(i).releaseDate << endl;
		cout << "Filming locations : ";
		for (unsigned k = 0; k < movies.at(i).locations.size(); k++)
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
		//file.open("test.txt", ios::app);
		infile.open("test.txt");
		
		//Project p;
		string g;
		//string temp;
		//int test = 1;
		while (!infile.eof())
		{	
			Project p;
			//cout << test << endl;
			//test++;

			int num;

			// READ STATUS
			getline(infile, g);
			//if (g == "0" || g == "1" || g == "2")
			p.status = stoi(g);
			//else
				//break;

			// READ TITLE
			getline(infile, p.title);
			
			// READ SUMMARY
			getline(infile, p.summary);

			// READ GENRE
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

void ProjectManager::postProject()
{
	try
	{
		file.open("test.txt");

		for (unsigned i = 0; i < movies.size(); i++)
		{
			// POST STATUS
			file << to_string(movies.at(i).status) << endl;
			// POST TITLE
			file << movies.at(i).title << endl;
			// POST SUMMARY
			file << movies.at(i).summary << endl;
			// POST GENRE SIZE
			file << to_string(movies.at(i).genre.size()) << endl;
			// POST GENRES
			for (unsigned j = 0; j < movies.at(i).genre.size(); j++)
			{
				file << movies.at(i).genre.at(j) << endl;
			}
			file << movies.at(i).releaseDate << endl;
			file << to_string(movies.at(i).locations.size()) << endl;
			for (unsigned k = 0; k < movies.at(i).locations.size(); k++)
			{
				file << movies.at(i).locations.at(k) << endl;
			}
			file << movies.at(i).language << endl;
			file << to_string(movies.at(i).runtime) << endl;
			file << movies.at(i).keyword << endl;
			file << to_string(movies.at(i).boxOffice) << endl;
		}

		file.close();
	}
	catch (exception ex)
	{

	}
}

void ProjectManager::updateProject()
{
	cout << "Enter the movie title to update" << endl;
	string tempUpdate;
	getline(cin, tempUpdate);
	for (unsigned i = 0; i < movies.size(); i++)
	{
		if (tempUpdate == movies.at(i).title)
		{
			//cout << "This one workds" << endl;
			//movies.erase(movies.begin() + i);

			cout << " +-------------------------------------------------+" << endl;
			cout << " |             1. Status                           |" << endl;
			cout << " |             2. Title                            |" << endl;
			cout << " |             3. Summary                          |" << endl;
			cout << " |             4. Genre                            |" << endl;
			cout << " |             5. Release Date                     |" << endl;
			cout << " |             6. Filming Locations                |" << endl;
			cout << " |             7. Language                         |" << endl;
			cout << " |             8. Runtime                          |" << endl;
			cout << " |             9. Keyword                          |" << endl;
			cout << " |            10. Box Office                       |" << endl;
			cout << " +-------------------------------------------------+" << endl;
			cout << "Which field do you want to change? (1, 2, 3, ...)" << endl;

			int user;
			int num;
			string g;
			cin >> user;
			cin.ignore();

			switch (user)
			{
			case 1:
				cout << "Enter movie status" << endl;
				cout << " 0 - UNRELEASED" << endl;
				cout << " 1 - NOW PLAYING" << endl;
				cout << " 2 - RELEASED" << endl;
				cin >> movies.at(i).status;
				cin.ignore();
				break;
			case 2:
				cout << "Enter movie title" << endl;
				getline(cin, movies.at(i).title);
				break;
			case 3:
				cout << "Enter movie summary" << endl;
				getline(cin, movies.at(i).summary);
				break;
			case 4:
				cout << "How many genres are there in this movie?" << endl;
				cin >> num;
				cin.ignore();
				for (int i = 0; i < num; i++)
				{
					cout << "Enter movie genre number " + to_string(i + 1) << endl;
					getline(cin, g);
					movies.at(i).genre.push_back(g);
				}
				break;
			case 5:
				cout << "Enter release date (DD-MM-YYYY)" << endl;
				getline(cin, movies.at(i).releaseDate);
				break;
			case 6:
				cout << "How many locations was this movie filmed at?" << endl;
				cin >> num;
				cin.ignore();
				for (int i = 0; i < num; i++)
				{
					cout << "Enter movie filming location " + to_string(i + 1) << endl;
					getline(cin, g);
					movies.at(i).locations.push_back(g);
				}
				break;
			case 7:
				cout << "Enter the language of the movie" << endl;
				getline(cin, movies.at(i).language);
				break;
			case 8:
				cout << "Enter movie runtime (mins)" << endl;
				cin >> movies.at(i).runtime;
				cin.ignore();
				break;
			case 9:
				cout << "Enter a keyword for the movie" << endl;
				getline(cin, movies.at(i).keyword);
				break;
			case 10:
				cout << "Enter the weekly box office for the movie" << endl;
				cin >> movies.at(i).boxOffice;
				cin.ignore();
				break;
			default:
				cout << "Invalid input" << endl;
				break;
			}
		}
	}
	showMenu();
}

void ProjectManager::deleteProject()
{
	cout << "Enter the movie title to delete" << endl;
	string tempDelete;
	getline(cin, tempDelete);

	for (unsigned i = 0; i < movies.size(); i++)
	{
		if (tempDelete == movies.at(i).title)
		{
			//cout << "This one workds" << endl;
			movies.erase(movies.begin() + i);
		}
	}
	showMenu();
}