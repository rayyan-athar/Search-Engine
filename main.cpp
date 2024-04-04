/// File Name: main.cpp
/// Name: Rayyan Athar 
/// UIN 657986463 
/// netID: ratha3
/// Course: CS 251 
/// Assignement: PROJECT 2
/// Description: User creates their own search engine, by loading in a file and creating an inverted index matching search terms to their URLs...
/// ...then the user is alllowed to use their search engine by entering sentence queries and viewing which URLs match query

#include "search.h"
using namespace std;

// Below are all functions that are test cases for the first four milestones

bool testCleanToken() {
    string ans1 = "hello", ans2 = "he.l.l.o", ans3 = "";
    int pass = 0, fail = 0;

    ans1 == cleanToken(".Hello") ? ++pass : ++fail;
    ans1 == cleanToken("HELLO") ? ++pass : ++fail;
    ans1 == cleanToken("...heLLo....") ? ++pass : ++fail;

    ans2 == cleanToken("+He.l.l.O.!") ? ++pass : ++fail;
    ans2 == cleanToken("--!.he.l.l.o?+.") ? ++pass : ++fail;
    ans2 == cleanToken("+'HE.L.L.O..-!.") ? ++pass : ++fail;
    
    ans3 == cleanToken("...123....") ? ++pass : ++fail;
    ans3 == cleanToken("1+2+3") ? ++pass : ++fail;
    ans3 == cleanToken("..3-2-1..") ? ++pass : ++fail;

    return 0 == fail;
}

bool testGatherTokens() {
    set<string> ans1 = {"eggs", "milk", "bread", "fish", "cheese"};
    set<string> ans2 = {"red", "green", "orange", "yellow", "blue", "indigo", "violet"};
    set<string> ans3 = {"i'm", "not", "trying", "to", "eat", "you"};
    int pass = 0, fail = 0;


    ans1 == gatherTokens("EGGS! milk, fish,      @  bread cheese") ? ++pass : ++fail;
    ans2 == gatherTokens("red ~green~ orange yellow blue indigo violet") ? ++pass : ++fail;
    ans3 == gatherTokens("I'm not trying to eat you") ? ++pass : ++fail;

    return 0 == fail;
}

bool testBuildIndex() {
    map<string, set<string> > index;
    int pass = 0, fail = 0;

    4 == buildIndex("tiny.txt",index) ? ++pass : ++fail;
    86 == buildIndex("cplusplus.txt",index) ? ++pass : ++fail;
    13 == buildIndex("stackoverflow.txt",index) ? ++pass : ++fail;
    148 == buildIndex("wiki-uni.txt",index) ? ++pass : ++fail;

    return 0 == fail;
}

bool testFindQueryMatches() {
    map<string, set<string> > index;
    set<string> ans1 = {};
    set<string> ans2 = {"www.dr.seuss.net"};
    set<string> ans3 = {"www.rainbow.org"};
    set<string> ans4 = {"www.rainbow.org", "www.dr.seuss.net"};
    set<string> ans5 = {"www.shoppinglist.com", "www.rainbow.org", "www.dr.seuss.net", "www.bigbadwolf.com"};


    int pass = 0, fail = 0;

    buildIndex("tiny.txt",index);
    ans1 == findQueryMatches(index,"eggs +red +Fish +trying") ? ++pass : ++fail;
    ans2 == findQueryMatches(index,"blue +fish") ? ++pass : ++fail;
    ans3 == findQueryMatches(index,"red -one") ? ++pass : ++fail;
    ans4 == findQueryMatches(index,"fish -cheese +red violet") ? ++pass : ++fail;
    ans5 == findQueryMatches(index,"bread fish not green") ? ++pass : ++fail;


    return 0 == fail;
}

int main() {
    
    
    string filename;
    getline(cin, filename);
    searchEngine(filename);  
     
    // int pass = 0, fail = 0;
    // (testCleanToken()) ? ++pass : ++fail;
    // (testGatherTokens()) ? ++pass : ++fail;
    // (testBuildIndex()) ? ++pass : ++fail;
    // (testFindQueryMatches()) ? ++pass : ++fail;

    // cout << "Passes: " <<  pass << endl;
    // cout << "Fails: " << fail << endl;

    return 0;
}

