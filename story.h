#ifndef STORY_GAME_STORY_H
#define STORY_GAME_STORY_H
#include <iostream>


using namespace std;

class story{
private:
    int setLevel = 0;
    int choiceNumber = 0;
    int success = 0;
    string title;
    int numberOfLevels;

    struct storyLevel{
        string story;
        string choice_1;
        string  choice_2;
        string outcome_1;
        string outcome_2;
        int success;
    };

    storyLevel story_levels[5];


public:
    story(string title, int numberOfLevels){
        this->title = title;
        this->numberOfLevels = numberOfLevels;
    }
    void setTitle(string title) {
        this->title = title;
    }
    void setNUmberOfLevels(int levels){
        this->numberOfLevels = levels;
    }
    string getTitle(){
        return title;
    }
    int getNumberOfLevels(){
        return numberOfLevels;
    }
    void setStoryLevels(string story, string choice_1, string choice_2, string outcome_1, string outcome_2, int success){
        storyLevel stage;
        stage.story = story;
        stage.choice_1 = choice_1;
        stage.choice_2 = choice_2;
        stage.outcome_1 = outcome_1;
        stage.outcome_2 = outcome_2;
        stage.success = success;

        story_levels[setLevel] = stage;
        setLevel += 1;
    }
    storyLevel* getStoryLevels(){
        storyLevel *stages = new storyLevel[5];
        for(int i = 0; i<5; i++){
            stages[i] = this->story_levels[i];
        }
        return stages;
    }
    int nextLevel(int glevel){
        if (glevel < 5) {
            glevel += 1;

            //story and choices
            cout<<this->story_levels[glevel].story<<endl;
            cout<<"1."<<this->story_levels[glevel].choice_1<<endl;
            cout<<"2."<<this->story_levels[glevel].choice_2<<endl;

            //take the choice of a user
            cout<<"Choose by entering the according number"<<endl;
            cin>>choiceNumber;

            //outcomes based on choice made
            if(choiceNumber == 1){
                cout<<this->story_levels[glevel].outcome_1<<endl;
            }else if(choiceNumber == 2){
                cout<<this->story_levels[glevel].outcome_2<<endl;
            }else{
                cout<<"Enter a valid option";
                nextLevel(glevel);
            }
            if(choiceNumber == this->story_levels[glevel].success){
                success = 1;
                return success;
            }else{
                success = 0;
            }
        }
    }
    int currentLevel(int glevel) {
        if (glevel > 5) {
            cout<<"You have finished the game. Congratulations"<<endl;
        } else {
            glevel -= 1;

            //play game
            //story and choices
            cout << this->story_levels[glevel].story << endl;
            cout << "1." << this->story_levels[glevel].choice_1 << endl;
            cout << "2." << this->story_levels[glevel].choice_2 << endl;

            //take a choice by a user
            cout << "Choose by entering the according number" << endl;
            cin >> choiceNumber;

            //outcomes based on choice made
            if (choiceNumber == 1) {

                cout << this->story_levels[glevel].outcome_1 << endl;
            } else if (choiceNumber == 2) {
                cout << this->story_levels[glevel].outcome_2 << endl;
            } else {
                cout << "Enter a valid option" << endl;
                currentLevel(glevel);
            }
            if (choiceNumber == this->story_levels[glevel].success) {
                success = 1;
                return success;
            } else {
                success = 0;
            }
        }
    }
    int startGame(){
        cout<<"Game start"<<endl;
        //play game
        //story and choices
        cout<<this->story_levels[0].story<<endl;
        cout<<"1."<<this->story_levels[0].choice_1<<endl;
        cout<<"2."<<this->story_levels[0].choice_2<<endl;

        //take a choice from the user
        cout<<"Choose by entering the according number"<<endl;
        cin>>choiceNumber;
        //outcomes based on choice made
        if(choiceNumber == 1){
            cout<<this->story_levels[0].outcome_1<<endl;
        }else if(choiceNumber == 2){
            cout<<this->story_levels[0].outcome_2<<endl;
        }else{
            cout<<"Enter a valid option"<<endl;
            startGame();
        }

        if(choiceNumber == this->story_levels[0].success){
            success = 1;
            return success;
        }else{
            success = 0;
        }
    }
};

#endif //STORY_GAME_STORY_H
