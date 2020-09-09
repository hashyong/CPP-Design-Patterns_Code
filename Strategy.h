// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/13 9:19 下午
// Description:
//

#pragma once

enum TaxBase {
  CN_Tax,
  US_Tax,
  DE_Tax,
  FR_Tax //更改
};

// old code, 每次新增一个代码都要修改老的Calculate, 违反开闭原则,
// 对修改关闭，对扩展开放 每一个都是一种策略, 使用策略模式
class SalesOrder {
  TaxBase tax;

public:
  double CalculateTax() {
    //...

    if (tax == CN_Tax) {
      // CN***********
    } else if (tax == US_Tax) {
      // US***********
    } else if (tax == DE_Tax) {
      // DE***********
    } else if (tax == FR_Tax) { //更改
      //...
    } else if (tax == FR_Tax) { //更改
      //...
    }

    //....
  }
};

struct Context {};
// base class
class TaxStrategy {
public:
  virtual double Calculate(const Context &context) = 0;
  virtual ~TaxStrategy() {}
};

class CNTax : public TaxStrategy {
public:
  virtual double Calculate(const Context &context) {
    //***********
  }
};

class USTax : public TaxStrategy {
public:
  virtual double Calculate(const Context &context) {
    //***********
  }
};

class DETax : public TaxStrategy {
public:
  virtual double Calculate(const Context &context) {
    //***********
  }
};

//扩展
//*********************************
class FRTax : public TaxStrategy {
public:
  virtual double Calculate(const Context &context) {
    //.........
  }
};

class StrageFactory {
public:
  static TaxStrategy *CreateStraegy(TaxBase item) {
    switch (item) {
    default:
      return new FRTax();
    }
  }
};

class SalesOrderOpt {
private:
  TaxStrategy *strategy;

public:
  SalesOrderOpt(TaxStrategy *strategyFactory) {
    this->strategy = strategyFactory;
  }
  ~SalesOrderOpt() { delete this->strategy; }

public:
  double CalculateTax() {
    //...
    Context context;

    double val = strategy->Calculate(context); //多态调用
    //...
  }
};

void strategy_main() {
  auto obj =
      std::make_shared<SalesOrderOpt>(StrageFactory::CreateStraegy(CN_Tax));
  obj->CalculateTax();
}
