#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {

  public:

  MyDataStore();
  virtual ~MyDataStore();

  void addProduct(Product* prod) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;

  //amazon stuff

  void addToCart(std::string &username, Product *p);
  void viewCart(std::string &username, std::ostream& os);
  void buyCart(std::string &username);

  private:

  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*>> keywords_;

  std::map<std::string, std::vector<Product*>> carts_;
  std::map<std::string, User*> lowerUsers_;
};

#endif