#ifndef PANCITO_H
#define PANCITO_H
#include <string>

class Pancito
{
private:
  int id;
  float weight, price;
  std::string name;
  bool gluten_free;
  int expiration_date;

public:
  Pancito();
  Pancito(int id, float weight, float price, char *name, bool gluten_free, int expiration_date);
  Pancito(const Pancito &obj);
  int getID();
  void setID(int id);
  float getWeight();
  void setWeight(float weight);
  float getPrice();
  void setPrice(float price);
  std::string getName();
  void setName(char *name);
  bool isGlutenFree();
  void setGlutenFree(bool gluten_free);
};

#endif
