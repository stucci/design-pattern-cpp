#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Hand {
private:
  int hand_value_;
  Hand(int hand_value) : hand_value_(hand_value) {}
  ~Hand() = default;
  int fight(Hand *h) {
    if (hand_value_ == h->hand_value_) {
      return 0;
    } else if ((hand_value_ + 1) % 3 == h->hand_value_) {
      return 1;
    } else {
      return -1;
    }
  }

public:
  Hand(const Hand &) = delete;            // copy constructor
  Hand &operator=(const Hand &) = delete; // copy assignment operator
  Hand(Hand &&) = delete;                 // move constructor
  Hand &operator=(Hand &) = delete;       // move assignment operator

  static const int ROCK = 0;
  static const int SCISSORS = 1;
  static const int PAPER = 2;

  static Hand *getHand(int hand_value) {
    static vector<Hand *> hands = {new Hand(0), new Hand(1), new Hand(2)};
    return hands[hand_value];
  }
  //   int getHandValue() { return hand_value_; }
  bool isStrongerThan(Hand *h) { return fight(h) == 1; }
  bool isWeakerThan(Hand *h) { return fight(h) == -1; }
};

class Strategy {
public:
  virtual Hand *nextHand() = 0;
  virtual void study(bool win) = 0;
};

class WinningStrategy : public Strategy {
private:
  bool won_ = false;
  Hand *prevHand_;
  random_device rand_device_;

public:
  Hand *nextHand() {
    if (!won_) {
      prevHand_ = Hand::getHand(rand_device_() % 3);
    }
    return prevHand_;
  }
  void study(bool win) { won_ = win; }
};

class RandomStrategy : public Strategy {
private:
  random_device rand_device_;

public:
  //   Hand *nextHand() { return Hand::getHand(rand_device_() % 3); }
  Hand *nextHand() { return Hand::getHand(2); }
  void study(bool win) {}
};

class Player {
private:
  string name_;
  Strategy *strategy_;
  int win_count_;
  int lose_count_;
  int game_count_;

public:
  Player(string name, Strategy *strategy) : name_(name), strategy_(strategy) {}
  Hand *nextHand() { return strategy_->nextHand(); }
  void win() {
    strategy_->study(true);
    win_count_++;
    game_count_++;
  }
  void lose() {
    strategy_->study(false);
    lose_count_++;
    game_count_++;
  }
  void even() { game_count_++; }
  void printResult() {
    cout << "[" << name_ << ": " << game_count_ << " games, " << win_count_
         << "win, " << lose_count_ << "lose]" << endl;
  }
};

int main() {
  Player *player1 = new Player("Joen", new WinningStrategy());
  Player *player2 = new Player("Doe", new RandomStrategy());
  for (int i = 0; i < 10000; i++) {
    Hand *nextHand1 = player1->nextHand();
    Hand *nextHand2 = player2->nextHand();
    if (nextHand1->isStrongerThan(nextHand2)) {
      player1->win();
      player2->lose();
    } else if (nextHand1->isWeakerThan(nextHand2)) {
      player1->lose();
      player2->win();
    } else {
      player1->even();
      player2->even();
    }
  }
  player1->printResult();
  player2->printResult();
  return 0;
}
