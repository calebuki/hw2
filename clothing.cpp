#include "clothing.h"
#include "util.h"
#include <iostream>


Clothing::Clothing(std::string& name, double price, int qty, 
                   std::string& size, std::string& brand)
                   : Product("clothing", name, price, qty){
  brand_ = brand;
  size_ = size;
}

//keyword overridden for clothing
std::set<std::string> Clothing::keywords() const {
  std::set<std::string> words;

  //add keywords from the name
  std::set<std::string> nameKeywords = parseStringToWords(name_);
  words.insert(nameKeywords.begin(), nameKeywords.end());

  //add keywords from the brand's name
  std::set<std::string> brandKeywords = parseStringToWords(brand_);
  words.insert(brandKeywords.begin(), brandKeywords.end());

  //include size
  words.insert(size_);

  return words;
}

std::string Clothing::displayString() const {
  return name_ + "\n" 
  + "Size: " + size_ + " Brand: " + brand_ + "\n"
  + std::to_string(price_) + " " + std::to_string(qty_)
  + " left." + "\n";
}

void Clothing::dump(std::ostream& os) const {
  os << "clothing" << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ <<std::endl;
}
