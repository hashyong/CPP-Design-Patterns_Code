// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/16 1:20 下午
// Description:
//

#pragma once

namespace facade {
class Food1 {
public:
  void operation() {}
};
class Food2 {
public:
  void operation() {}
};

class Food3 {
public:
  void operation() {}
};

class Facade {
public:
  Facade(){
    food1_ = new Food1();
    food2_ = new Food2();
    food3_ = new Food3();

  }
  virtual ~Facade(){
    delete food1_;
    delete food2_;
    delete food3_;
  }

  void wrapOpration(){
    food1_->operation();
    food2_->operation();
    food3_->operation();
  }

private:
  Food1* food1_;
  Food2* food2_;
  Food3* food3_;
};

void test() {
  Facade fa;
  fa.wrapOpration();
}
} // namespace facade
