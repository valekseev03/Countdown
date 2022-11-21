#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


//Countdown Numbers Sections
vector<int>::iterator getIteratorAtValue(vector<int> &inputVector, int value){
    vector<int>::iterator vectorIterator = inputVector.begin();

    while(*vectorIterator != value && vectorIterator != inputVector.end()){
        vectorIterator++;
    }

    return vectorIterator;
}

void shuffleVector(vector<int> &inputVector, int endRandomization){
    int indexOne, indexTwo = 0;

    for(int i = 0; i < endRandomization; i++){
        //get random indexes
        indexOne = rand() % inputVector.size();
        indexTwo = rand() % inputVector.size();

        if(indexOne == indexTwo){
            if(indexTwo == inputVector.size() - 1){
                indexTwo -= 1;
            }else{
                indexTwo += 1;
            }
        }

        //swap values
        inputVector.at(indexOne) += inputVector.at(indexTwo);
        inputVector.at(indexTwo) = inputVector.at(indexOne) - inputVector.at(indexTwo);
        inputVector.at(indexOne) -= inputVector.at(indexTwo);
    }
}

void randomizeValues(vector<int> &inputVector, int numLargeValues, int endRandomization){
    int smallValues[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int largeValues[4] = {25, 50, 75, 100};


    for(int i = 0; i < endRandomization; i++){
        for(int j = 0; j < numLargeValues; j++){
            inputVector.at(j) = largeValues[(rand() % 4)];
        }

        for(int j = numLargeValues; j < inputVector.size(); j++){
            inputVector.at(j) = smallValues[(rand() % 10)];
        }
    }
}

vector<string> getEquation(vector<int> inputVector, int endRandomization){
    vector<string> possibleSolution;
    int endLoop = (rand() % (inputVector.size() / 2)) + (inputVector.size() / 2);
    int finalNumber = inputVector.at(0);

    possibleSolution.emplace_back(to_string(finalNumber));
    for(int i = 1; i < endLoop; i++){
        int randomAction = rand() % 4;
        for(int j = 1; j < endRandomization; j++){
            randomAction = rand() % 4;
        }

        if(randomAction == 0){
            possibleSolution.emplace_back(" + " + to_string(inputVector.at(i)));
            finalNumber += inputVector.at(i);
        }else if (randomAction == 1){
            if(finalNumber <= inputVector.at(i)){
                possibleSolution.emplace_back(" + " + to_string(inputVector.at(i)));
                finalNumber += inputVector.at(i);
            }else{
                possibleSolution.emplace_back(" - " + to_string(inputVector.at(i)));
                finalNumber -= inputVector.at(i);
            }   
        }else if (randomAction == 2){
            if(finalNumber < inputVector.at(i) || finalNumber % inputVector.at(i) != 0){
                possibleSolution.emplace_back(" * " + to_string(inputVector.at(i)));
                finalNumber *= inputVector.at(i);
            }else{
                possibleSolution.emplace_back(" / " + to_string(inputVector.at(i)));
                finalNumber /= inputVector.at(i);
            }
        }else{
            possibleSolution.emplace_back(" * " + to_string(inputVector.at(i)));
            finalNumber *= inputVector.at(i);
        }
    }
    possibleSolution.emplace_back(" = " + to_string(finalNumber));

    return possibleSolution;
}

int stringEquationToAnswer(string inputEquation, vector<int> possibleNumbers){
    int finalAnswer = 0;
    vector<string> inputBySpaces;

    //Seperate Equation By Spaces
    while(inputEquation.find(" ") != string::npos){
        inputBySpaces.emplace_back(inputEquation.substr(0, inputEquation.find(" ")));
        inputEquation = inputEquation.substr(inputEquation.find(" ") + 1, inputEquation.size());
    }
    inputBySpaces.emplace_back(inputEquation);

    //Input Validation
    if(inputBySpaces.size() % 2 != 1){
        return -1;
    }

    //Solve Equation
    finalAnswer = stoi(inputBySpaces.at(0));

    //Check If Valid Number
    vector<int>::iterator vectorIterator = getIteratorAtValue(possibleNumbers, stoi(inputBySpaces.at(0)));
    if(vectorIterator == possibleNumbers.end()){
        return -1;
    }else{
        possibleNumbers.erase(vectorIterator);
    }

    for(int i = 1; i < inputBySpaces.size(); i += 2){
        //Get Operation and Number
        string currentOperation = inputBySpaces.at(i);
        int currentNumber = stoi(inputBySpaces.at(i + 1));

        //Check If Valid Number
        vectorIterator = getIteratorAtValue(possibleNumbers, currentNumber);
        if(vectorIterator == possibleNumbers.end()){
            return -1;
        }else{
            possibleNumbers.erase(vectorIterator);
        }

        //Perform Operation With Number
        if(currentOperation == "*"){
             finalAnswer *= currentNumber;
        }else if (currentOperation == "/"){
            if(currentNumber == 0){
                return -1;
            }else{
                finalAnswer /= currentNumber;
            }
        }else if (currentOperation == "+"){
            finalAnswer += currentNumber;
        }else if (currentOperation == "-"){
            finalAnswer -= currentNumber;
        }else{
            return -1;
        }
    }

    return finalAnswer;
}

void playRound(){
    //Set Up Randomizations (rand() function is predictable, and not truly random every execution)
    int randomOne = 53; //controls numbers
    int randomTwo = 14; //controls order of shuffle
    int randomThree = 24; //controls operations done on numbers
    int numLargeValues = 2;

    cout << "Randomization Time! Enter Three Numbers" << endl;
    cin >> randomOne;
    cin >> randomTwo;
    cin >> randomThree;

    cout << "Number of Large Numbers" << endl;
    cin >> numLargeValues; 

    //Set Up Vectors
    vector<int> allNumbers = {0,0,0,0,0,0};
    randomizeValues(allNumbers, numLargeValues, randomOne);

    for(int i = 0; i < 100; i++){
        cout << endl;
    }

    //Print All Numbers
    cout << "Countdown" << endl;
    for(int i = 0; i < allNumbers.size(); i++){
        cout << allNumbers.at(i) << " ";
    }
    cout << endl;

    //Get Answer
    shuffleVector(allNumbers, randomTwo);
    vector<string> solution = getEquation(allNumbers, randomThree);
    
    //Print Answer
    string actualSolution = solution.at(solution.size() - 1);
    int actualAnswer = stoi(actualSolution.replace(actualSolution.find(" = "), 3, ""));
    cout << actualAnswer << endl;

    //Possibly Solve
    string possibleSolution = "";
    cout << endl << "Enter Possible Solution! (Spaces Between Numbers and Operations)" << endl;
    getline(cin, possibleSolution);
    getline(cin, possibleSolution);
    int possibleAnswer = stringEquationToAnswer(possibleSolution, allNumbers);

    for(int i = 0; i < 100; i++){
        cout << endl;
    }

    if(possibleAnswer == -1){
        cout << "+0 Points: Invalid Solution!" << endl;
    }else if (possibleAnswer == actualAnswer){
        cout << possibleSolution << " = " << possibleAnswer << endl;
        cout << "+10 Points: Valid Solution!" << endl;
    }else if (abs(actualAnswer - possibleAnswer) <= actualAnswer / 10){
        cout << possibleSolution << " = " << possibleAnswer << endl;
        cout << "+7 Points: Close Solution!" << endl;
    }else{
        cout << possibleSolution << " = " << possibleAnswer << endl;
        cout << "+0 Points: Incorrect Solution!" << endl;  
    }

    //Print Solution
    cout << endl;
    for(int i = 0; i < solution.size(); i++){
        if(i == 0){
            for(int j = 0; j < solution.size() - 2; j++){
                cout << "(";
            }        
        }

        cout << solution.at(i);

        if (i != 0 && i != solution.size() - 1){
            cout << ")";
        }
    }
    cout << endl;
}

int main() 
{   
    int numRounds = 0;
    cin >> numRounds;

    for(int i = 0; i < numRounds; i++){
        playRound();
    }
    
} 
 
 
