#include "book.h"
#include "util.h"
#include <iostream>

Book::Book(std::string& name, double price, int qty, 
           std::string& author, std::string& isbn) 
           : Product("book", name, price, qty) {
  author_ = author;
  isbn_ = isbn;
}

//keyword overridden for book
std::set<std::string> Book::keywords() const {
  std::set<std::string> words;

  //add keywords from the name
  std::set<std::string> nameKeywords = parseStringToWords(name_);
  words.insert(nameKeywords.begin(), nameKeywords.end());

  //add keywords from the author's name
  std::set<std::string> authorKeywords = parseStringToWords(author_);
  words.insert(authorKeywords.begin(), authorKeywords.end());

  //add isbn
  words.insert(isbn_);

  return words;
}

std::string Book::displayString() const {
  return name_ + "\n" 
  + "Author: " + author_ + " ISBN: " + isbn_ + "\n"
  + std::to_string(price_) + " " + std::to_string(qty_)
  + " left." + "\n";
}

void Book::dump(std::ostream& os) const {
  os << "book" << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << isbn_ << std::endl;
  os << author_ <<std::endl;
  
  
}
