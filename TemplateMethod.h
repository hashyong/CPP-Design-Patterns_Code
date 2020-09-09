// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/13 8:26 下午
// Description:
//

#pragma once

// old code
//程序库开发人员
class Library {

public:
  void Step1() {
    //...
  }

  void Step3() {
    //...
  }

  void Step5() {
    //...
  }
};

//应用程序开发人员1
class Application {
public:
  bool Step2() {
    //...
  }

  void Step4() {
    //...
  }
};

// 分析，这里框架代码变化频率小，应用程序变化可能性大
// 此时, 假如再来一个应用程序，还得把上边代码copy下，很是重复
// 先有 框架，后有应用程序，application依赖lib，早早就绑定了
//应用程序开发人员1
class Application2 {
public:
  bool Step2() {
    //...
  }

  void Step4() {
    //...
  }
};
// 可以看到，框架代码基本是不变的，不同的是2 和
// 4接口的实现方式而已，可以通过晚绑定，lib依赖application，早的依赖晚的，晚绑定

// opt code
//程序库开发人员
class LibraryOpt {
public:
  void Run() {
    Step1();
    if (Step2()) {
      Step3();
    }
    for (int i = 0; i < 4; i++) {
      Step4();
    }
    Step5();
  }

protected:
  //
  void Step1() {
    //...
  }

  void Step3() {
    //...
  }

  void Step5() {
    //...
  }

  virtual bool Step2() = 0; // changed
  virtual bool Step4() = 0; // changed
};

//应用程序开发人员 final
class ApplicationOpt: public LibraryOpt {
public:
  bool Step2() {
    //...
  }

  bool Step4() {
    //...
  }
};

class TMTest {
  void tm_main() {
    Library lib;
    Application app;

    lib.Step1();
    if (app.Step2()) {
      lib.Step3();
    }
    for (int i = 0; i < 4; i++) {
      app.Step4();
    }
    lib.Step5();
  }

  void tm1_main() {
    Library lib;
    Application2 app;

    lib.Step1();
    if (app.Step2()) {
      lib.Step3();
    }
    for (int i = 0; i < 4; i++) {
      app.Step4();
    }
    lib.Step5();
  }

  // 优雅, 看着舒服, 美滋滋，其实模版方法 在框架里边用的还很多，像是taf，trpc等等，rpc
  void tm_opt() {
    auto lib = std::make_shared<ApplicationOpt>();
    lib->Run();
  }
};
