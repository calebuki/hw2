#include "movie.h"
#include "util.h"
#include <iostream>


Movie::Movie(std::string& name, double price, int qty, 
             std::string& genre, std::string& rating)
             : Product("movie", name, price, qty) {
  genre_ = genre;
  rating_ = rating;
}

//keyword overridden for movie
std::set<std::string> Movie::keywords() const {
  std::set<std::string> words;

  //add keywords from the name
  std::set<std::string> nameKeywords = parseStringToWords(name_);
  words.insert(nameKeywords.begin(), nameKeywords.end());

  //add genre
  words.insert(genre_);

  //add rating
  words.insert(rating_);

  return words;
}

std::string Movie::displayString() const {
  return name_ + "\n" 
  + "Genre: " + genre_ + " Rating: " + rating_ + "\n"
  + std::to_string(price_) + " " + std::to_string(qty_)
  + " left." + "\n";
}

void Movie::dump(std::ostream& os) const {
  os << "movie" << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ <<std::endl;
}
