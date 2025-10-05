#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){

  for (size_t i = 0; i < products_.size(); ++i) {
    delete products_[i];
  }

  for (size_t i = 0; i < users_.size(); ++i) {
    delete users_[i];
  }

}

void MyDataStore::addProduct(Product *prod) {
  products_.push_back(prod);

  //get all the keywords from the product and put them in per product
  std::set<std::string> rawString = prod->keywords();
  for (std::set<std::string>::iterator it = rawString.begin(); it != rawString.end(); ++it) {
    std::string k = convToLower(*it);
    keywords_[k].insert(prod);
  }
}

void MyDataStore::addUser(User *u) {
  users_.push_back(u);

  //for the lowerUsers_
  lowerUsers_[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  
  std::vector<Product*> temp;

  //incase there's 0 terms, immediately return
  if (terms.empty()) {
    return temp;
  }

  //AND search 
  //returns all the products that contain ALL the search terms entered
  //so essentially an intersection set, we have to match everything
  //to the first term
  
  if (type == 0) {
    std::set<Product*> intersection;
    
    bool firstInit = false;

    for (size_t i = 0; i < terms.size(); ++i) {
      std::string zerb = convToLower(terms[i]);

      //get hits for the first term
      std::set<Product*> hits;
      std::map<std::string, std::set<Product*>>::iterator it = keywords_.find(zerb);
      if (it != keywords_.end()) {
        hits = it->second;
      }

      //check the first term is initialized ?
      if (!firstInit) {
        intersection = hits;
        firstInit = true;
      } else {
        intersection = setIntersection(intersection, hits);
      }
    } 

    //put items from the set into the vector to return
    for (std::set<Product*>::iterator blah = intersection.begin(); blah != intersection.end(); ++blah) {
      temp.push_back(*blah);
    }
  }

  //OR search
  //basically just a union set
  else {
    std::set<Product*> myUnion;

    for (size_t i = 0; i < terms.size(); ++i){
      std::string xiao = convToLower(terms[i]);

      std::map<std::string, std::set<Product*>>::iterator it = keywords_.find(xiao);
      if (it != keywords_.end()) {
        myUnion = setUnion(myUnion, it->second);
      }

      //else: theres nothingn to union
    }

    //put items from the set into the vector to return
    for (std::set<Product*>::iterator blah = myUnion.begin(); blah != myUnion.end(); ++blah) {
      temp.push_back(*blah);
    }

  }

  return temp;
}


//dump
void MyDataStore::dump(std::ostream &ofile){

  //products
  ofile << "<products>" << std::endl;;
  for (size_t i = 0; i < products_.size(); ++i){
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << std::endl;

  //users
  ofile << "<users>" << std::endl;;
  for (size_t i = 0; i < users_.size(); ++i){
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << std::endl;;
}

//amazon.cpp call functions

//ADD
void MyDataStore::addToCart(std::string &username, Product *p){

  std::string user = convToLower(username);
  if (lowerUsers_.find(user) == lowerUsers_.end()) {
    //invlaid user!
    std::cout << "Invalid request" << std::endl;
    return;
  }

  carts_[user].push_back(p);

}

//VIEWCART
void MyDataStore::viewCart(std::string &username, std::ostream& os){

  std::string user = convToLower(username);
  if (lowerUsers_.find(user) == lowerUsers_.end()) {
    //invlaid user!
    os << "Invalid username" << std::endl;
    return;
  }

  //find the user's cart
  std::map<std::string, std::vector<Product*>>::iterator cart_it = carts_.find(user);
  
  //make sure the cart exists?
  if (cart_it == carts_.end()) {
    return;
    //there's an empty cart so nothing to output
  }

  //print 
  std::vector<Product*>& cart = cart_it->second;
  for (size_t i = 0; i < cart.size(); ++i){
    os << "Item " << (i+1) << std::endl;
    os << cart[i]->displayString() << std::endl;
  }
}

//BUYCART
void MyDataStore::buyCart(std::string &username) {

  //user check
  std::string user = convToLower(username);
  if (lowerUsers_.find(user) == lowerUsers_.end()) {
    //invlaid user!
    std::cout << "Invalid username" << std::endl;
    return;
  }


  std::map<std::string, User*>::iterator user_it = lowerUsers_.find(user);
  User *u = user_it->second;

  //we need to go thru the whole cart of the user
  std::vector<Product*>& cart = carts_[user];
  
  for (std::vector<Product*>::iterator it = cart.begin(); it!= cart.end(); ) {

    Product *p = *it;

    //if the product exists
    if (p != nullptr){

      //check if user has enough money AND there's enough to buy
      if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
        p->subtractQty(1);
        u->deductAmount(p->getPrice());
        it = cart.erase(it);
      } else {
      //otherwise, we can't buy it and it just stays in the cart
        ++it;
      }
    }
  }
}
 