#ifndef PANCITO_CPP
#define PANCITO_CPP
#include "pancito.hpp"

Pancito::Pancito()
{
  this->id = 0;
  this->expiration_date = 0;
  this->price = 0;
  this->name = "";
  this->weight = 0;
}

Pancito::Pancito(int id, float weight, float price, char *name, bool gluten_free, int expiration_date)
{
  this->id = id;
  this->weight = weight;
  this->price = price;
  this->name = name;
  this->gluten_free = gluten_free;
  this->expiration_date = expiration_date;
}

Pancito::Pancito(const Pancito &obj)
{
  this->id = obj.id;
  this->weight = obj.weight;
  this->price = obj.price;
  this->name = obj.name;
  this->gluten_free = obj.gluten_free;
  this->expiration_date = obj.expiration_date;
}

int Pancito::getID()
{
  return this->id;
}

void Pancito::setID(int id)
{
  this->id = id;
}

float Pancito::getWeight()
{
  return this->weight;
}

void Pancito::setWeight(float weight)
{
  this->weight = weight;
}

float Pancito::getPrice()
{
  return this->price;
}

void Pancito::setPrice(float price)
{
  this->price = price;
}

std::string Pancito::getName()
{
  return this->name;
}

void Pancito::setName(char *name)
{
  this->name = name;
}
#endif
