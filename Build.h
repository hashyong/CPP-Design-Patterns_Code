// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 9:33 下午
// Description:
//

#pragma once

namespace build {

class House {
  //....
};

class HouseBuilder {
public:
  House *GetResult() { return pHouse; }
  virtual ~HouseBuilder() {}

  virtual void BuildPart1() = 0;
  virtual void BuildPart2() = 0;
  virtual bool BuildPart3() = 0;
  virtual void BuildPart4() = 0;
  virtual void BuildPart5() = 0;
protected:
  House *pHouse;
};

class StoneHouse : public House {};

class StoneHouseBuilder : public HouseBuilder {
protected:
  virtual void BuildPart1() {
    // pHouse->Part1 = ...;
  }
  virtual void BuildPart2() {}
  virtual bool BuildPart3() {}
  virtual void BuildPart4() {}
  virtual void BuildPart5() {}
};

class HouseDirector {
public:
  HouseBuilder *pHouseBuilder;
  HouseDirector(HouseBuilder *pHouseBuilder) {
    this->pHouseBuilder = pHouseBuilder;
  }

  House *Construct() {
    pHouseBuilder->BuildPart1();
    for (int i = 0; i < 4; i++) {
      pHouseBuilder->BuildPart2();
    }

    bool flag = pHouseBuilder->BuildPart3();
    if (flag) {
      pHouseBuilder->BuildPart4();
    }
    pHouseBuilder->BuildPart5();

    return pHouseBuilder->GetResult();
  }
};

} // namespace build
