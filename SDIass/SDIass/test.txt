#include "ProjectManager.h"
#include "Project.h"
#include "Material.h"
#include <iostream>
#include <string>
using namespace std;

ProjectManager::ProjectManager()
{
	loadProject();
	loadMaterial();
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
	cout << " |             5. Search Project                   |" << endl;
	cout << " |             6. View Materials                   |" << endl;
	cout << " |             7. Add Material                     |" << endl;
	cout << " |             8. Delete Material                  |" << endl;
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
	case 5:
		searchProject();
		break;
	case 6:
		displayMaterial();
		break;
	case 7:
		addMaterial();
		break;
	case 8:
		deleteMaterial();
		break;
	default:
		postProject();
		postMaterial();
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
		
		// ASK TITLE
		cout << "Enter movie title" << endl;
		getline(cin, project.title);

		// ASK SUMMARY
		cout << "Enter movie summary" << endl;
		getline(cin, project.summary);
		
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
		
		// ASK RUNTIME
		cout << "Enter movie runtime (mins)" << endl;
		cin >> project.runtime;
		cin.ignore();
		
		// ASK KEYWORD
		cout << "Enter a keyword for the movie" << endl;
		getline(cin, project.keyword);
		
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
		movies.push_back(project);
		
		showMenu();
	}
	catch (exception ex)
	{
		
	}

	
}

void ProjectManager::displayProject()
{	
	system("cls");
	cout << "Total movies: " << movies.size() << endl << endl;
	for (unsigned i = 0; i < movies.size(); i++)
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
		searchMaterial(movies.at(i).title);
		//cout << endl;
	}
	showMenu();
}

void ProjectManager::loadProject()
{
	cout << "Loading file..." << endl;
	try
	{
		infile.open("ProjectDatabase.txt");
		
		string g;
		while (!infile.eof())
		{	
			Project p;

			int num;

			// READ STATUS
			getline(infile, g);
			p.status = stoi(g);

			// READ TITLE
			getline(infile, p.title);
			
			// READ SUMMARY
			getline(infile, p.summary);

			// READ GENRE
			getline(infile, g);
			num = stoi(g);
			for (int i = 0; i < num; i++)
			{
				getline(infile, g);
				p.genre.push_back(g);
			}
			getline(infile, p.releaseDate);
			
			getline(infile, g);
			num = stoi(g);
			for (int i = 0; i < num; i++)
			{
				getline(infile, g);
				p.locations.push_back(g);
			}
			getline(infile, p.language);

			getline(infile, g);
			p.runtime = stoi(g);
			getline(infile, p.keyword);
			getline(infile, g);
			
			p.boxOffice = stod(g);

			movies.push_back(p);
			
		}
	}
	catch(exception ex)
	{
		
	}
	infile.close();
}

void ProjectManager::postProject()
{
	try
	{
		file.open("ProjectDatabase.txt");

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

void ProjectManager::searchProject()
{
	string tempSearch;
	cout << "Enter the movie title to search" << endl;
	getline(cin, tempSearch);

	for (unsigned i = 0; i < movies.size(); i++)
	{
		if (tempSearch == movies.at(i).title)
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
	}
	showMenu();
}

void ProjectManager::addMaterial()
{
	try
	{
		string tempSearch;
		cout << "Enter movie title to add material" << endl;
		getline(cin, tempSearch);

		for (unsigned i = 0; i < movies.size(); i++)
		{
			if (movies.at(i).status != 0)
			{
				Material m;

				// ASK MATERIAL TYPE
				cout << "Enter material type" << endl;
				cout << " 0 - Single-sided DVD" << endl;
				cout << " 1 - Double-sided DVD" << endl;
				cout << " 2 - Combo box set" << endl;
				cout << " 3 - VHS" << endl;
				cout << " 4 - Blu-ray" << endl;
				cin >> m.type;
				cin.ignore();

				// ASK MATERIAL ID
				cout << "Enter material ID (DVD XXX)" << endl;
				getline(cin, m.id);

				// ASK FILM TITLE
				//cout << "Enter material film title" << endl;
				//getline(cin, m.filmTitle);
				m.filmTitle = movies.at(i).title;

				// ASK VIDEO FORMAT
				cout << "Enter material video format" << endl;
				getline(cin, m.format);

				// ASK AUDIO FORMAT
				cout << "Enter material audio format" << endl;
				getline(cin, m.audioFormat);

				// ASK RUNTIME
				//cout << "Enter material film runtime" << endl;
				//cin >> m.runtime;
				//cin.ignore();
				m.runtime = movies.at(i).runtime;

				// ASK LANGUAGE
				//cout << "Enter material film language" << endl;
				//getline(cin, m.language);
				m.language = movies.at(i).language;

				// ASK RETAIL PRICE
				cout << "Enter material retail price" << endl;
				cin >> m.retailPrice;
				cin.ignore();

				materials.push_back(m);
				showMenu();
			}
			else
			{
				cout << "Movie status is UNRELEASED. Unable to add material..." << endl;
			}
		}
	}
	catch (exception ex)
	{

	}
}

void ProjectManager::loadMaterial()
{
	cout << "Loading Material file..." << endl;
	try
	{
		infile.open("MaterialDatabase.txt");

		string g;
		while (!infile.eof())
		{
			Material m;
			int num;

			// READ TYPE
			getline(infile, g);
			m.type = stoi(g);

			// READ MATERIAL ID
			getline(infile, g);
			m.id = g;

			// READ FILM TITLE;
			getline(infile, g);
			m.filmTitle = g;

			// READ VIDEO FORMAT
			getline(infile, g);
			m.format = g;

			// READ AUDIO FORMAT
			getline(infile, g);
			m.audioFormat = g;

			// READ RUNTIME
			getline(infile, g);
			m.runtime = stoi(g);

			// READ LANGUAGE
			getline(infile, g);
			m.language = g;

			// READ RETAIL PRICE
			getline(infile, g);
			m.retailPrice = stod(g);

			materials.push_back(m);
		}
	}
	catch (exception ex)
	{

	}
	infile.close();
}

void ProjectManager::postMaterial()
{
	try
	{
		file.open("MaterialDatabase.txt");

		for (unsigned i = 0; i < materials.size(); i++)
		{
			// POST TYPE
			file << to_string(materials.at(i).type) << endl;

			// POST MATERIAL ID
			file << materials.at(i).id << endl;

			// POST FILM TITLE
			file << materials.at(i).filmTitle << endl;

			// POST VIDEO FORMAT
			file << materials.at(i).format << endl;

			// POST AUDIO FORMAT
			file << materials.at(i).audioFormat << endl;

			// POST RUNTIME
			file << to_string(materials.at(i).runtime) << endl;

			// POST LANGUAGE
			file << materials.at(i).language << endl;

			// POST RETAIL PRICE
			file << to_string(materials.at(i).retailPrice) << endl;
		}
		file.close();
	}
	catch (exception ex)
	{

	}
}

void ProjectManager::displayMaterial()
{
	system("cls");
	cout << "Total materials: " << materials.size() << endl << endl;
	for (unsigned i = 0; i < materials.size(); i++)
	{
		string tempType;
		if (materials.at(i).type == 0)
			tempType = "Single-sided DVD";
		else if (materials.at(i).type == 1)
			tempType = "Double-sided DVD";
		else if (materials.at(i).type == 2)
			tempType = "Combo box set";
		else if (materials.at(i).type == 3)
			tempType = "VHS";
		else if (materials.at(i).type == 4)
			tempType = "Bly-ray";
		else
			tempType = "Single-sided DVD";
		cout << "Type              : " << tempType << endl;
		cout << "ID                : " << materials.at(i).id << endl;
		cout << "Movie title       : " << materials.at(i).filmTitle << endl;
		cout << "Video format      : " << materials.at(i).format << endl;
		cout << "Audio format      : " << materials.at(i).audioFormat << endl;
		cout << "Runtime           : " << materials.at(i).runtime << endl;
		cout << "Language          : " << materials.at(i).language << endl;
		cout << "Retail price      : " << materials.at(i).retailPrice << endl;
		cout << endl;
	}
	showMenu();
}

void ProjectManager::deleteMaterial()
{
	cout << "Enter the material ID to delete" << endl;
	string tempDelete;
	getline(cin, tempDelete);

	for (unsigned i = 0; i < materials.size(); i++)
	{
		if (tempDelete == materials.at(i).id)
		{
			materials.erase(materials.begin() + i);
			cout << "Material deleted successfully" << endl << endl;
		}
	}
	showMenu();
}

void ProjectManager::searchMaterial(string title)
{
	for (unsigned i = 0; i < materials.size(); i++)
	{
		if (title == materials.at(i).filmTitle)
		{
			string tempType;
			if (materials.at(i).type == 0)
				tempType = "Single-sided DVD";
			else if (materials.at(i).type == 1)
				tempType = "Double-sided DVD";
			else if (materials.at(i).type == 2)
				tempType = "Combo box set";
			else if (materials.at(i).type == 3)
				tempType = "VHS";
			else if (materials.at(i).type == 4)
				tempType = "Bly-ray";
			else
				tempType = "Single-sided DVD";
			cout << "Type              : " << tempType << endl;
			cout << "ID                : " << materials.at(i).id << endl;
			cout << "Movie title       : " << materials.at(i).filmTitle << endl;
			cout << "Video format      : " << materials.at(i).format << endl;
			cout << "Audio format      : " << materials.at(i).audioFormat << endl;
			cout << "Runtime           : " << materials.at(i).runtime << endl;
			cout << "Language          : " << materials.at(i).language << endl;
			cout << "Retail price      : " << materials.at(i).retailPrice << endl;
			cout << endl;
		}
	}
}