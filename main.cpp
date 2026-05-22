// Winter'24
// Instructor: Diba Mirza
// Student name: Katelyn Hamel
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <map>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    std::map<string, double> movies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            
            //cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            movies[movieName] = movieRating;
    }

    movieFile.close();

    if (argc == 2){
        for(auto it = movies.begin(); it != movies.end(); it++){
        cout << it->first << ", " << fixed << setprecision(1) << it->second << endl;
        }
        
            //print all the movies in ascending alphabetical order of movie names
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    
    //adding to best movies vector
    vector<pair<string,double>> bestM;

  for(auto x: prefixes){
    vector<pair<string,double>> prefMovie;
    bool havePref =false;

    for(auto it = movies.lower_bound(x); it != movies.end(); it++){
            if (it->first.substr(0, x.size()) == x){
                prefMovie.push_back(*it);
                havePref = true;
            }
            
        }
        
        //  If no movie with that prefix exists print the following message
        if (!havePref){
            cout << "No movies found with prefix " << x << endl;
        }

        
    
            std::sort(prefMovie.begin(), prefMovie.end(), [](const auto& a, const auto& b) {
                if (a.second != b.second){
                    return a.second>b.second;
                }

                return a.first < b.first;
            });
        //printing prefMovie in order based by ranking
            for (auto x: prefMovie){
                cout << x.first << ": " << x.second << endl;
        
            }
        
        bestM.push_back(prefMovie[0]);
        //gap for aesthetics
        cout << endl;

    }

    //printing best movie
    int i = 0;
    for (auto x: prefixes){
            //printing best
            cout << "Best movie with prefix " << x << " is: "<< bestM[i].first<< " with rating " << std::fixed << std::setprecision(1) << bestM[i].second<< endl;
            i++;
    }

  

      

    

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}





/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}*/