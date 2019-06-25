// Main.cpp
// CS 4499
// Written By: Katherine Wilsdon
// 1 April 2019
// Dr. Kerby
// Description - Creates a simulation of a population of bunnies, using a collection of Bunny objects.

#include "Bunny.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

// Vector of bunny names
vector<string> bunnyNames = {
  "Hopper", "Thumper", "Whiskers", "Midnight", "Dawn",
  "Twilight", "Pearl", "Ruby", "Diamond", "Misty",
  "Snowflake", "Daisy", "Rose", "Moose", "Bear",
  "Summer", "Autumn", "Mars", "Jupiter", "Venus"
};

// Field variables
vector<Bunny> mutants;
vector<Bunny> nonMutants;
vector<Bunny> maleBreeding;
vector<Bunny> femaleBreeding;
vector<int> countOfNonMutantBunniesAtEachAge(11);
vector<int>countOfMutantBunniesAtEachAge(51);
int maleBunnies = 0;
int femaleBunnies = 0;
int genderQueerBunnies = 0;
int babiesBorn = 0;
int bunniesDied = 0;
ofstream output;
bool bunnyDied = false;

// Random number generator at seed 10
default_random_engine generator(10);

// Member function declaration
void Initialization();
long unsigned int GeneratesRandomNumber(int);
Gender RandomizeGender();
bool RandomizeMutant();
void AgeAndKillBunnies();
void CreateBreedingVectors();
void ClearBreedingVectors();
void Breed();
void CreateABunny();
Color ColorOfBornBunny(Bunny, Bunny);
void ConvertAMutant();
void PopulateAgeVectors();
void ClearVariables();
void Output();

// Initializes 10 bunnies that are not radioactive mutant vampire bunnies
void Initialization(){
  for (int i = 0; i < 10; i++){
    string randomName = bunnyNames.at(GeneratesRandomNumber(bunnyNames.size()));
    Gender randomGender = RandomizeGender();
    Color randomColor = Color(GeneratesRandomNumber(4));
    Bunny baby = Bunny(randomName, randomGender, randomColor, 0, false);
    nonMutants.push_back(baby);
    output << "Bunny " << baby.GetName() << " was born!" << endl;
  }

}

// Generates a random number with a given size
long unsigned int GeneratesRandomNumber(int size){
  uniform_int_distribution<int> distribution(0, size - 1);
  long unsigned int randomNumber = distribution(generator);
  return randomNumber;
}

// Randomizes the bunny gender using the default_random_engine
Gender RandomizeGender(){
  long unsigned int randomNumber = GeneratesRandomNumber(100);
  // The bunny will have a 6/100 probability of being assigned GenderQueer
  if (randomNumber < 6){
    Gender gender = GenderQueer;
    genderQueerBunnies++;
    return gender;
  } // The bunny will have a 47/100 probability of being assigned Male
  else if (randomNumber < 53){
    Gender gender = Male;
    maleBunnies++;
    return gender;
  } // The bunny will have a 47/100 probability of being assigned Female
  else {
    Gender gender = Female;
    femaleBunnies++;
    return gender;
  }
}

// Randomizes whether the bunny is a mutant using the default_random_engine
bool RandomizeMutant(){
  long unsigned int randomNumber = GeneratesRandomNumber(100);
  // The bunny will have a 3/100 probability of being a mutant when born
  if (randomNumber < 3){
    return true;
  } // The bunny will have a 97/100 probability of being a nonmutant when born
  else {
    return false;
  }
}

// Ages bunnies and remove bunnies when they die
void AgeAndKillBunnies(){
  int size = nonMutants.size();
  for (int i = 0; i < size; i++){
    // Increase the bunny's age by 1
    nonMutants.at(i).SetAge(nonMutants.at(i).GetAge() + 1);
  }
  size = mutants.size();
  for (int i = 0; i < size; i++){
    // Increase the bunny's age by 1
    mutants.at(i).SetAge(mutants.at(i).GetAge() + 1);
  }
  int i = 0;
  for (Bunny bunny : nonMutants){
    // If the bunny should be killed, delete the bunny from the nonMutants vector
    if (nonMutants.at(i).GetAge() == -1){
      nonMutants.erase(nonMutants.begin()+i);
      output << "Bunny " << bunny.GetName() << " died!" << endl;
      bunniesDied++;
      bunnyDied = true;
      i--;
    }
    i++;
  }
  i = 0;
  for (Bunny bunny : mutants){
    // If the bunny should be killed, delete the bunny from the mutants vector
    if (mutants.at(i).GetAge() == -1){
      mutants.erase(mutants.begin()+i);
      output << "Radioactive Mutant Vampire Bunny " << bunny.GetName() << " died!" << endl;
      bunniesDied++;
      bunnyDied = true;
      i--;
    }
    i++;
  }
  if (bunnyDied == true){
    output << endl;
  }
}

// Populates the maleBreeding and femaleBreeding vectors
void CreateBreedingVectors(){
  // Populates the maleBreeding vector with bunnies that are male and between the ages 2 and 8
  for (Bunny bunny : nonMutants){
    if (bunny.GetGender() == (Gender)Male && bunny.GetAge() >= 2 && bunny.GetAge() <= 8){
      maleBreeding.push_back(bunny);
    }
  }
  // Populates the femaleBreeding vector with bunnies that are female and between the ages 2 and 8
  for (Bunny bunny : nonMutants){
    if (bunny.GetGender() == (Gender)Female && bunny.GetAge() >= 2 && bunny.GetAge() <= 8){
      femaleBreeding.push_back(bunny);
    }
  }
}

// Clears the breeding female and male vectors
void ClearBreedingVectors(){
  maleBreeding.clear();
  femaleBreeding.clear();
}

// Create new bunnies and add them to the mutants or nonMutants vectors
void Breed(){
  bool isMaleVectorSmaller = false;
  if (maleBreeding.size() < femaleBreeding.size()){
    isMaleVectorSmaller = true;
  }

  // which ever maleBreeding or femaleBreeding vector has the least amount of bunnies, create an equal amount of new bunnies
  if (isMaleVectorSmaller == true){
    int size = maleBreeding.size();
    babiesBorn = size;
    for (int i = 0; i < size; i++){
      CreateABunny();
    }
  } else {
    int size = femaleBreeding.size();
    babiesBorn = size;
    for (int i = 0; i < size; i++){
      CreateABunny();
    }
  }
  output << endl;
}

// Creates a bunny and deletes the parents from the maleBreeding and femaleBreeding vectors
void CreateABunny(){
  // Finds a father and a mother bunny from the breeding vectors
  int fatherIndex = GeneratesRandomNumber(maleBreeding.size());
  int motherIndex = GeneratesRandomNumber(femaleBreeding.size());
  Bunny father = maleBreeding.at(fatherIndex);
  Bunny mother = femaleBreeding.at(motherIndex);

  // Creates a bunny with a random name, random gender, and random color from either the mother or father
  string randomName = bunnyNames.at(GeneratesRandomNumber(bunnyNames.size()));
  Gender randomGender = RandomizeGender();
  Color randomColor = Color(ColorOfBornBunny(father, mother));
  bool randomMutantType = RandomizeMutant();
  Bunny baby = Bunny(randomName, randomGender, randomColor, 0, randomMutantType);

  // Adds the baby to the mutants or nonMutants vector depending on their radioactive_mutant_vampire_bunny type
  if (baby.GetRadioactiveMutantVampireBunny() == false){
    nonMutants.push_back(baby);
    output << "Bunny " << baby.GetName() << " was born!" << endl;
  } else {
    mutants.push_back(baby);
    output << "Radioactive Mutant Vampire Bunny " << baby.GetName() << " was born!" << endl;
  }

  // Deletes the mother and father from the breeding vectors
  maleBreeding.erase(maleBreeding.begin()+fatherIndex);
  femaleBreeding.erase(femaleBreeding.begin()+motherIndex);
}

// Chooses a color randomly from the mother and father bunnies
Color ColorOfBornBunny(Bunny father, Bunny mother){
  long unsigned int randomNumber = GeneratesRandomNumber(2);
  // returns the randomly selected color between the parents
  if (randomNumber == 0){
    return father.GetColor();
  } else {
    return mother.GetColor();
  }
}

// Converts one non-radioactive bunny for every radioactive bunny
void ConvertAMutant(){
  int size = mutants.size();
  for (int i = 0; i < size; i++) {
    // Mutants cannot convert a nonMutant when born
    if(mutants.at(i).GetAge() > 0){
      int randomNumber = GeneratesRandomNumber(nonMutants.size());
      // Sets a random nonMutant bunny to be radioactive, adds the bunny to mutants vector, and deletes the bunny from nonMutants vector
      nonMutants.at(randomNumber).SetRadioactiveMutantVampireBunny(true);
      mutants.push_back(nonMutants.at(randomNumber));
      nonMutants.erase(nonMutants.begin()+randomNumber);
      // if last nonMutant is deleted, break out of for loop
      if (nonMutants.empty()){
        break;
      }
    }
  }
}

// Populates the age vectors with the index representing each age
void PopulateAgeVectors(){
  // Populates the nonMutants Age vector
  for (int i = 0; i < nonMutants.size(); i++){
    countOfNonMutantBunniesAtEachAge.at(nonMutants.at(i).GetAge())++;
  }

  // Populates the mutants Age vector
  for (int i = 0; i < mutants.size(); i++) {
    countOfMutantBunniesAtEachAge.at(mutants.at(i).GetAge())++;
  }
}

// Clears field variables for next turn
void ClearVariables(){
  babiesBorn = 0;
  bunniesDied = 0;
  countOfNonMutantBunniesAtEachAge.clear();
  countOfNonMutantBunniesAtEachAge.resize(11);
  countOfMutantBunniesAtEachAge.clear();
  countOfMutantBunniesAtEachAge.resize(51);
  bunnyDied = false;
}

// Adds the statistics to an output file
void Output(){
  output << "Total bunnies: " << nonMutants.size() + mutants.size() << endl;
  output << "Mutant bunnies: " << mutants.size() << endl;
  output << "Nonmutant bunnies: " << nonMutants.size() << endl;
  output << "Male: " << maleBunnies << endl;
  output << "Female: " << femaleBunnies << endl;
  output << "GenderQueer: " << genderQueerBunnies << endl;
  output << "Total bunnies born: " << babiesBorn << endl;
  output << "Total bunnies died: " << bunniesDied << endl;
  output << endl << "Nonmutant Ages" << endl;
  for (int i = 0; i < 11; i++){
    if (countOfNonMutantBunniesAtEachAge.at(i) != 0){
      output << "Age " << i << ": " << countOfNonMutantBunniesAtEachAge.at(i) << endl;
    }
  }
  output << endl << "Mutant Ages" << endl;
  for (int i = 0; i < 51; i++){
    if (countOfMutantBunniesAtEachAge.at(i) != 0){
      output << "Age " << i << ": " << countOfMutantBunniesAtEachAge.at(i) << endl;
    }
  }
}

int main(){
  output.open("output.txt", fstream::out);
  int count = 0;
  output << "Turn" << count << ":"<< endl;
  Initialization();
  output << endl;
  Output();
  count++;
  do {
    ClearVariables();
    ClearBreedingVectors();
    output << endl << "Turn" << count << ":"<< endl;
    AgeAndKillBunnies();
    if (nonMutants.size() != 0){
      CreateBreedingVectors();
      Breed();
      ConvertAMutant();
      PopulateAgeVectors();
    }
    Output();
    count++;
  }
  while (nonMutants.size() != 0);
  output.close();

return 0;
}
