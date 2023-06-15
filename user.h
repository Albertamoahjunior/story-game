#ifndef STORY_GAME_USER_H
#define STORY_GAME_USER_H
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
class user{
private:
    string username;
    string password;
    int level;
public:
    user(){
        this->username = "";
        this->password = "";
        this->level = 0;
    }
    user(string username, string password, int level){
        this->username = username;
        this->password = password;
        this->level = level;
    }
    void setUserName(string username){
        this->username = username;
    }
    void setpassword(string password){
        this->password = password;
    }
    void setLevel(int level){
        this->level = level;
    }
    string getUserName(){
        return this->username;
    }
    string getPassword(){
        return this->password;
    }
    int getLevel(){
        return this->level;
    }
    //save player progress in the text file
    void saveUserData(string filepath){
        string loc = filepath +"\\user_data.txt";
        //opening or writing to a file
        ofstream userData;
        userData.open(loc, ios::app);
        userData <<this->username<<" "<<this->password<<" "<<this->level<<endl;

        //closing the file
        userData.close();
        cout<<"User create successfully"<<endl;
    }
    void updateProfile(string filepath, user player){
        string userData;
        string name;
        string templine;
        int level;
        string password;
        string loc = filepath +"\\user_data.txt";
        string temploc = filepath + "\\temp.txt";

        //
        ofstream tempData;
        tempData.open(temploc);
        //reading from files
        ifstream savedData;
        savedData.open(loc);
        if(!savedData){
            //continue with game
        }else {
            //go through the file line by line
            while(getline(savedData, userData)) {
                stringstream dataLine(userData);
                dataLine >> name >> password >> level;

                if(player.getUserName() != name){
                    //do something
                    tempData <<" "<<name <<" "<<password <<" "<<level;
                    break;
                }
            }

            savedData.close();
            tempData.close();
        }
        remove(loc.c_str());
        //writing new dataline
        ofstream newData;

        newData.open(temploc, ios::app);

        newData<<"\n"<<player.getUserName()<<" "<<player.getPassword()<<" "<<player.getLevel();

        newData.close();
        rename(temploc.c_str(), loc.c_str());
        cout<<"Your data has been saved successfully"<<endl;
    }

};
#endif //STORY_GAME_USER_H
