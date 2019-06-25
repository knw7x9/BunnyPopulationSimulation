#pragma once
#include <string>

enum Gender {Male, Female, GenderQueer};
enum Color {white, brown, black, spotted};

class Bunny {

private:
  std::string _Name;
  Gender _Gender;
  Color _Color;
  int _Age;
  bool _Radioactive_mutant_vampire_bunny;
public:
  // Get and set the name of the bunny
  std::string  GetName() const { return _Name; };
  void SetName(std::string name) {_Name = name; };

  // Get and set the gender of the bunny
  Gender GetGender() const { return _Gender; };
  void SetGender(Gender gender) { _Gender = gender; };

 // Get and set the color of the bunny
 Color GetColor() const { return _Color; };
 void SetColor(Color color) {_Color = color; };

 // Get and set the age of the bunny
 int GetAge() const { return _Age; };
 void SetAge(int age) {
   if (_Radioactive_mutant_vampire_bunny == false) {
     // if the bunny is not a mutant and between the age 0 and 10, set the age
     if (age >= 0 && age <= 10){
       _Age = age;
     } // if the bunny's age is greater than 10, set the age to -1 to be killed
     else {
       _Age = -1;
     }
   } else if (_Radioactive_mutant_vampire_bunny == true) {
     // if the bunny is not a mutant and between the age 0 and 50, set the age
     if (age >= 0 && age <= 50){
       _Age = age;
     } // if the bunny's age is greater than 50, set the age to -1 to be killed
     else {
       _Age = -2;
     }
   }
 };
 // Get and set whether the bunny is a mutant
 bool GetRadioactiveMutantVampireBunny() const { return _Radioactive_mutant_vampire_bunny; };
 void SetRadioactiveMutantVampireBunny(bool isRadioactiveMutantVampireBunny) { _Radioactive_mutant_vampire_bunny = isRadioactiveMutantVampireBunny; };

// Create a bunny with a name, gender, color, age, and whether a mutant
Bunny(std::string name, Gender gender, Color color, int age, bool radioactive_mutant_vampire_bunny);

};
