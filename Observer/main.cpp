#include <iostream>
#include <memory>
#include <vector>

class ISubscriber {
 public:
  virtual void update() = 0;
};

class IPublisher {
 public:
  virtual void noticeAll() = 0;
  virtual void addSubscriber(ISubscriber *item) = 0;
  virtual void remSubscriber(ISubscriber *item) = 0;
};

class Suplier : public IPublisher {
  std::vector<ISubscriber *> subscribers;
  int beverage_price = 0;
  int food_price = 0;

 public:
  void noticeAll() {
    for (auto item : subscribers) {
      item->update();
    }
  }

  void addSubscriber(ISubscriber *item) { this->subscribers.push_back(item); }

  void remSubscriber(ISubscriber *item) {
    subscribers.erase(
        std::remove(this->subscribers.begin(), this->subscribers.end(), item));
  }

  void setBeverage_price(int price) { this->beverage_price = price; }

  void setFood_price(int price) { this->food_price = price; }

  int getBeverate_price() { return this->beverage_price; }

  int getFood_price() { return this->food_price; }
};

class Supermarket : public ISubscriber {
  std::shared_ptr<Suplier> supermarket_suplier;

 public:
  explicit Supermarket(std::shared_ptr<Suplier> item)
      : supermarket_suplier(item) {
    supermarket_suplier->addSubscriber(this);
  };

  void update() {
    std::cout << "Price of food: " << supermarket_suplier->getFood_price()
              << "€" << std::endl;
  }
};

class Bar : public ISubscriber {
  std::shared_ptr<Suplier> bar_suplier;

 public:
  explicit Bar(std::shared_ptr<Suplier> item) : bar_suplier(item) {
    bar_suplier->addSubscriber(this);
  };

  void update() {
    std::cout << "Price of beverage: " << bar_suplier->getBeverate_price()
              << "€" << std::endl;
  }
};

int main(void) {
  // Initialize the suplier with price changing
  std::shared_ptr<Suplier> suplier(new Suplier());
  suplier->setBeverage_price(2000);
  suplier->setFood_price(2300);

  // Create clients
  Supermarket supermarket(suplier);
  Bar bar(suplier);

  // Notify changes
  suplier->noticeAll();

  // Remove one subscriber
  suplier->remSubscriber(&bar);

  suplier->noticeAll();

  return 0;
}
