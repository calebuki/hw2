#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include "product.h"

class Book : public Product {

  public:

  //Constructor
  Book(std::string& name, double price, int qty, std::string& author, std::string& isbn);

  //override virtual functions
  std::set<std::string> keywords() const override;
  std::string displayString() const override;
  void dump(std::ostream& os) const override;

  private:

  std::string author_;
  std::string isbn_;

};

#endif
