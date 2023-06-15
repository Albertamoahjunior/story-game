#include <iostream>
#include <fstream>
#include<filesystem>
#include <sstream>
#include "user.h"
#include "story.h"

//basic global variables used
user players[10];
int numberOfRegisteredPlayers = 0;
int success;
int currentLevel = 1;

//find the file directory of this file
filesystem::path cur = filesystem::current_path();
const string cfilepath = cur.string();

//Adventure game to be played
story adventureGame("THE CURSE", 5);


using namespace std;

//retrieve data from the text file
void retrieveData(string filepath){
     //string variable to keep the lines
    string userData;
    string name;
    int level;
    string password;
    string loc = filepath +"\\user_data.txt";

    //reading from files
    ifstream savedData;
    savedData.open(loc);
    if(!savedData){
        //continue with game
    }else {
        //go through the file line by line
        while (getline(savedData, userData)) {
            stringstream dataLine(userData);
            char separator;
            dataLine >> name >> password >> level;

            user player(name, password, level);
            players[numberOfRegisteredPlayers] = player;

            numberOfRegisteredPlayers += 1;
        }

        savedData.close();
    }
}


//let user continue or start the game all over
void playGame(user player){
    if (player.getLevel() > 0){
        adventureGame.currentLevel(player.getLevel());
    }
    else if(player.getLevel() == 0){
        cout<<"Welcome "<<player.getUserName()<<" to this adventure game"<<endl;
        success = adventureGame.startGame();

        if(success == 1){
            currentLevel += 1;
            char choice;
            cout<<"Do you wish to continue or save and exit."<<endl;
            cout<<"Enter k for continue and q for exit."<<endl;
            cin>>choice;
            if(choice == 'q'){
                player.setLevel(currentLevel);
                player.updateProfile(cur.string(), player);
            }else if(choice == 'k'){
                player.setLevel(currentLevel);
                playGame(player);
            }
        }else{
            player.setLevel(0);
            playGame(player);
        }

    }
}

//create account for users
void createAccount(string filepath){
    user player;
    string name;
    string pass;
    string cPass;
    cout<<"There should be no spaces in the username or password"<<endl;
    cout<<"Enter your username"<<endl;
    cin>>name;
    cout<<"Enter your password"<<endl;
    cin>>pass;
    cout<<"Confirm password"<<endl;
    cin>>cPass;

    if(pass == cPass){
        player.setUserName(name);
        player.setpassword(cPass);
        players[numberOfRegisteredPlayers] = player;
        numberOfRegisteredPlayers += 1;
        player.saveUserData(filepath);
        playGame(player);
    }else{
        cout<<"Passwords are not the same"<<endl;
    }
}

//allow users to log in
void logIn() {
    string name;
    string password;
    user player;
    bool logged = false;
    cout << "Please enter your username" << endl;
    cin >> name;
    cout << "Please enter your password" << endl;
    cin >> password;

    for (user profile: players) {
        if (profile.getUserName() == name && profile.getPassword() == password) {
            logged = true;
            player = profile;
            break;
        }
    }
    if(logged){
        playGame(player);
    }else{
        cout<<"Wrong username or password"<<endl;
    }

}

int choice;
string question = "What will you do?";

//main interface for the users
int main() {

    //retrieve data from file
    retrieveData(cur.string());
    //level 1
    string storyLevel_1 = "You are a brave adventurer tasked with finding "
                          "a magical gem that can save your village from a curse.\n"
                          "You set out on a journey to find the gem.\n"
                          "You come across a rickety bridge over a deep ravine.";
    string choice_1_level_1 = "Cross the bridge";
    string choice_2_level_1 = "Find another way around";
    string outcome_1_level_1 = "You fell off. Game Over!";
    string outcome_2_level_1 = "You find another way around the ravine and continue the game";
    int success_level_1 = 2;
    adventureGame.setStoryLevels(storyLevel_1, choice_1_level_1, choice_2_level_1,outcome_1_level_1,outcome_2_level_1, success_level_1);
//level 2
    string storyLevel_2 = "You come across a river.";
    string choice_1_level_2 = "Try to swim across";
    string choice_2_level_2 = "Look for another way to cross the river";
    string outcome_1_level_2 = "You drown trying to swim across the river you drown! Game over!";
    string outcome_2_level_2 = "You look around and find a boat to cross safely. You continue on your journey";
    int success_level_2 = 2;
    adventureGame.setStoryLevels(storyLevel_2, choice_1_level_2, choice_2_level_2, outcome_1_level_2, outcome_1_level_2, success_level_2);
//level 3
    string storyLevel_3 = "As you continue your journey, you hear a loud growling noise.\n"
                          " As you turn around, you see a large ferocious bear.";
    string choice_1_level_3 = "Run as fast as you can";
    string choice_2_level_3 = "Hide from the bear";
    string outcome_1_level_3 = "You run away but get caught up by the bear and eaten. Game over";
    string outcome_2_level_3 = "You hide from the bear and wait till it leaves, and you continue the journey";
    int success_level_3 = 3;
    adventureGame.setStoryLevels(storyLevel_3, choice_1_level_3, choice_2_level_3, outcome_1_level_3, outcome_1_level_3, success_level_3);
//level 4
    string storyLevel_4;
    string choice_1_level_4;
    string choice_2_level_4;
    string outcome_1_level_4;
    string outcome_2_level_4;
    int success_level_4 = 2;
    adventureGame.setStoryLevels(storyLevel_4, choice_1_level_4, choice_2_level_4, outcome_1_level_4, outcome_1_level_4, success_level_4);
//level 5
    string storyLevel_5;
    string choice_1_level_5;
    string choice_2_level_5;
    string outcome_1_level_5;
    string outcome_2_level_5;
    int success_level_5 = 2;
    adventureGame.setStoryLevels(storyLevel_5, choice_1_level_5, choice_2_level_5,outcome_1_level_5, outcome_2_level_5, success_level_5);


    start:
    cout<<"GAME TIME!!"<<endl;
    cout<<"1.New here? Create an account"<<endl;
    cout<<"2.Already have an account, log in"<<endl;
    cout<<"Please enter the according number to make a choice"<<endl;
    cin>>choice;

    //switch among the different options
    switch(choice){
        case 1:
            createAccount(cfilepath);
            break;
        case 2:
            logIn();
            break;
        default:
            cout<<"Enter a valid choice"<<endl;
            goto start;
    }
    return 0;
}
