#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
ifstream fin(filename);
    string line;

    while(getline(fin, line)){
        string namePart, scorePart;
        int s1, s2, s3;

        int pos = line.find(':');
        namePart = line.substr(0, pos);
        scorePart = line.substr(pos + 1);

        stringstream ss(scorePart);
        ss >> s1 >> s2 >> s3;

        int total = s1 + s2 + s3;
        char grade = score2grade(total);

        names.push_back(namePart);
        scores.push_back(total);
        grades.push_back(grade);
}
fin.close();
}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command:" << endl;
    getline(cin, line);
    
    stringstream ss(line);
    ss >> command;
    getline(ss, key);
    
    if(key.size() > 0 && key[0] == ' ')
    key = key.substr(1);

}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;

    for(size_t i = 0; i < names.size(); i++){
        string temp = toUpperStr(names[i]);

        if(temp == key){
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            found = true;
            return;
        }
    }

    if(!found){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    char g = key[0];

    cout << "---------------------------------" << endl;

    for(size_t i = 0; i < grades.size(); i++){
        if(grades[i] == g){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }

    if(!found){
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
