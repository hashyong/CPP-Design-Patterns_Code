// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/16 1:36 下午
// Description:
//

#pragma once

namespace adapter {
//目标接口（新接口）
class ITarget {
public:
  virtual void process() = 0;
};

//遗留接口（老接口）
class IAdaptee {
public:
  virtual void foo(int data) = 0;
  virtual int bar() = 0;
};

//遗留类型
class OldClass : public IAdaptee {
  //....
  void foo(int data) override {}
  int bar() override{};
};

//对象适配器
class Adapter : public ITarget { //继承新接口
protected:
  IAdaptee *pAdaptee; //组合老接口

public:
  Adapter(IAdaptee *pAdaptee) { this->pAdaptee = pAdaptee; }

  virtual void process() {
    int data = pAdaptee->bar();
    pAdaptee->foo(data);
  }
};

//类适配器
class AdapterClass : public ITarget,
                     protected OldClass { //多继承
};

void test() {
  IAdaptee *pAdaptee = new OldClass();
  ITarget *pTarget = new Adapter(pAdaptee);
  pTarget->process();
}

// stack and queue is deque adapter
} // namespace adapter
