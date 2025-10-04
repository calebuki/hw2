#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>
#include <set>
#include "product.h"

class Clothing : public Product {

  public:

  //Constructor
  Clothing(std::string& name, double price, int qty, std::string& size, std::string& brand);

  //override virtual functions
  std::set<std::string> keywords() const override;
  std::string displayString() const override;
  void dump(std::ostream& os) const override;

  private:

  std::string size_;
  std::string brand_;

};

#endif
