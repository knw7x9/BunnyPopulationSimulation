#include "Bunny.h"
#include <iostream>
#include <string>

// Create a bunny with a name, gender, color, and whether a mutant
Bunny::Bunny(std::string name, Gender gender, Color color, int age, bool radioactive_mutant_vampire_bunny) {
  SetName(name);
  SetGender(gender);
  SetColor(color);
  SetRadioactiveMutantVampireBunny(radioactive_mutant_vampire_bunny);
  SetAge(age);
}
