/// File Name: search.h
/// Name: Rayyan Athar 
/// UIN 657986463 
/// netID: ratha3
/// Course: CS 251 
/// Assignement: PROJECT 2
/// Description: User creates their own search engine, by loading in a file and creating an inverted index matching search terms to their URLs...
/// ...then the user is alllowed to use their search engine by entering sentence queries and viewing which URLs match query


#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

// Function takes in a string that isn't "clean", and retuns a clean string without any leading or ending punctuation and all letters lowercased
string cleanToken(string s) {
    string clean = "";
    int ind1 = 0, ind2 = 0;
    bool empty = true;
    
    // First loop loops through string from start until a non punct character is reached and stores the (starting) index breaking the loop
    // Second loop loops through string from end until a non punct charcter is reached and stores the (ending) index breaking the loop
    // A clean string stores the substring of the dirty string, from the starting index to the ending index
    for(int i = 0; i < s.size(); i++) {
        if(!ispunct(s.at(i))){
            ind1 = i;
            break; 
        }
    }
    for(int j = (s.size()-1); j >= 0; j--){
        if(!ispunct(s.at(j))){
            ind2 = j+1;
            break;
        }
    }
    clean = s.substr(ind1,ind2-ind1);


    // Loops through the clean string converting characters to lowercase, then checks to see if there are any alphabets using a boolean value,
    // If alphabets are found the clean string is returned, if there are no alphabets an empty string is returned instead
    for(int i =0; i<clean.size();i++){
        clean.at(i) = tolower(clean.at(i));
    }

    for(int i = 0; i < clean.size(); i++) {
        if(isalpha(clean.at(i))) {
            empty = false;
            break;
        }
    }

    if(empty) {
        clean = "";
    }

    return clean;  
}

// Function takes in a string which is a body of text that contains words seperated by spaces, and returns all those individual unique clean tokens in text within a set
set<string> gatherTokens(string text) {
    set<string> tokens;
    string token, clean = "";
    stringstream line(text);
    
    // Using a stringstream and while loop, the token stores every word from the text string
    // The word is then cleaned and if it is not empty it is inserted into the tokens set that is returned
    while(line >> token)
    {
        clean = cleanToken(token);

        if(clean.size() > 0) {
            tokens.insert(clean);    
        }    
    }
    
    return tokens; 
}

// Function takes in filename to be opened, and a map index passed by reference which is an inverted index that maps a term to a set of all URLS that contain the word
// Function returns an integer that represents the number of URLs
int buildIndex(string filename, map<string, set<string> >& index) {
    int count = 0;
    string URL, text;
    set<string> tokens, URLs;

    
    // File is opened and if it can't be opened function terminates by returning 0
    ifstream infile(filename);
    if(!infile.is_open()) {
        return 0;
    }
    
    // While loop gets two lines from the file, the first one which is the URL, and the second which is the body of text (search terms)
    // For each text, it is seperated into clean tokens and stored in a set, then a for loop loops through the set of clean tokens and maps a set of URLs to each token
    // Then for every token in the map, the specific URL is inserted into its set of URLs, after the loop the URLs set is cleared, and the count is updated and finally returned
    while(getline(infile,URL) && getline(infile,text)){
        tokens = gatherTokens(text);
        
        for(auto a: tokens){ 
            index.emplace(a,URLs);
            index.at(a).insert(URL);  
        }

        URLs.clear();
        count++;
    }

    return count;
}

// Function takes in a map index passed by reference which is an inverted index that maps a term to a set of all URLs that contain the word, and a string which will be a sentence specifying all queries to be included or excluded
// Function returns a set that contains all the URLs obtained from the sentence query specification 
set<string> findQueryMatches(map<string, set<string> >& index, string sentence) {
    set<string> result, URLs, temp;
    stringstream ss (sentence);
    string query;

    // Using a while loop and stringstream, a query is obtained from the sentence
    // Then a set will hold all the URLs pertaining to the cleaned token, and based on the first character of the query, that set will either be unioned, intersected, or 'differenced'...
    // with a result set that holds all current URLs from all previous search queries. This is due to operations inserting into a temporary set, which is then assigned to the result set, while temp set is cleared
    // After the loop, the result set is returned containing all URLs that matched the entire sentence of queries
    while(ss >> query) {

        URLs = index.at(cleanToken(query));

        if(query.at(0) == '+') {
            set_intersection(URLs.begin(),URLs.end(),result.begin(),result.end(),inserter(temp,temp.begin()));
        }
        else if(query.at(0) == '-') {
            set_difference(result.begin(),result.end(),URLs.begin(),URLs.end(),inserter(temp,temp.begin()));
        }
        else {
            set_union(URLs.begin(),URLs.end(),result.begin(),result.end(),inserter(temp,temp.begin()));
        }

        result = temp;
        temp.clear();
    }

    return result;  
}

// Function takes in a filename, and uses all previous functions to run the search engine by building an inverted index and searching through it by prompting user to enter search terms
void searchEngine(string filename) {
    int pages = 0, terms = 0;
    string query = "";
    set<string> URLs;
    map<string, set <string> >index;

    // Inverted index is creatd from filename and relevant information is displayed
    cout << "Stand by while building index..." << endl;
    pages = buildIndex(filename,index);
    terms  = index.size();
    cout << "Indexed " << pages << " pages containing " << terms << " unique terms\n" << endl;


    // User is prompted to enter a search query sentence, and while the user enters nothing, a set 'queries' will hold all relevant URLs found from the complete search query...
    // ... and output the number of and all URLs 
    cout << "Enter query sentence (press enter to quit): " ;
    getline(cin, query);
    while(query != "") {
        
        URLs = findQueryMatches(index, query);
        cout << "Found " << URLs.size() << " matching pages" << endl; 
        for(auto a : URLs) {
            cout << a << endl;
        }

        cout << "Enter query sentence (press enter to quit): " ;
        getline(cin, query);
    }

    cout<< "Thank you for searching!" << endl;
    
    return;
    
}