/***********************************************************************
Matr.-Nr:                     3104154
Nachname/Surname:             Alsabbagh
Vorname/Given name:           Ibrahim
Uni-Email:                    ibrahim.alsabbagh@stud.uni-due.de
Studiengang/Course of studis: software Engineering ISE
***********************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct  City{
    string name;
    string addition;
    City *nextCity;
};

ostream& operator<<(ostream& o,City* City){
    while(City != nullptr){
        if(City->addition.find(",") != 0){
            o << City->name << " " << City->addition;
        }else{
            o<< City->name << City->addition;
        }
        City = City->nextCity;
        if(City != nullptr){
            o<<"|";
        }
    }
    return o;
}


int getNumberFromArray(int myNumbers[5]) {
    int result = 0;

    for (int i = 0; i < 5; i++) {

        result *= 10;
        result += myNumbers[i];

    }

    return result;
}

void print(City *arr[],int length, int from, int to){
    for(int i=from; i<=to; i++){
        if(arr[i] != nullptr){
            cout<<i<<" ";
            cout<<arr[i]<<endl;
        }
    }
}

void read_file(string fileName, struct City* cities[], int legnth) {
    ifstream nFile;
    string line;
    string trash;
    nFile.open(fileName);
    if (nFile.is_open()) {
        getline(nFile, trash); // ignoring the first line
        while (getline(nFile, line)) {
            if (line == "")
                continue;
            string plz;
            City* readCity = new City();
            int i = 0;
            for (i = 0; i < line.length(); i++) {
                if (line.at(i) == ';')
                    break;
                readCity->name += line.at(i);
            }
            i++;
            for (i; i < line.length(); i++) {
                if (line.at(i) == ';')
                    break;
                readCity->addition += line.at(i);
            }
            i++;
            for (i; i < line.length(); i++) {
                plz += line.at(i);
                if (line.at(i) == ';')
                    break;
            }
            int postalCity = stoi(plz);

            if (cities[postalCity] == nullptr)
                cities[postalCity] = readCity;
            else {
                readCity->nextCity = cities[postalCity];
                cities[postalCity] = readCity;
            }


        }
        nFile.close();
    }
    else {
        cout << "Unable to open file";
    }
}
int main(){
    City *Citys[100000];
    char n;
    string plz;
    string fileName;
    string postCity1;
    string postCity2;
    int fromArray[5] = { 0,0,0,0,0 };
    int toArray[5] = { 9,9,9,9,9 };

    cout<<"please input zip City: ";
    cin>>fileName;
    read_file("plz.csv", Citys, 100000);
    cout << "read file " << fileName << " ... done" << endl;
    while(true){
        cout << "q quit" <<endl<< "c City" <<endl<< "f from to" <<endl;
        cin >> n;
        if(n == 'c'){
            cout << "please n zip City: ";
            cin >> plz;
             for (int i = 0; i < plz.length() && i < 5; i++) {
                fromArray[i] = (int)plz.at(i) - '0';
                toArray[i] = (int)plz.at(i) - '0';
            }
            print(Citys, 100000, getNumberFromArray(fromArray), getNumberFromArray(toArray));

        }else if(n == 'f'){
            cout<<"from which zip City: ";
            cin>>postCity1;
            cout<<"up to which zip City: ";
            cin>>postCity2;
            print(Citys, 100000, stoi(postCity1), stoi(postCity2));

        }else if(n == 'q'){
            return 0;
        }
    }
    return 0;
}