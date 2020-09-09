// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/17 1:51 下午
// Description:
//

#pragma once

namespace itera {

template <typename T> class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual T &current() = 0;
};

template <typename T> class CollectionIterator : public Iterator<T> {
public:
  CollectionIterator() = default;

  void first() override {}
  void next() override {}
  bool isDone() const override {}
  T &current() override {}
};

template <typename T> class MyCollection {
public:
  Iterator<T> &GetIterator() {
    //...
    return *new CollectionIterator<T>();
  }
};

void MyAlgorithm() {
  MyCollection<int> mc;
  for (mc.GetIterator().first(); !mc.GetIterator().isDone();
       mc.GetIterator().next()) {
    cout << mc.GetIterator().current() << endl;
  }
}

} // namespace itera
