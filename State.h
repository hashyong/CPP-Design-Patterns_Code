// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/17 1:18 下午
// Description:
//

#pragma once

namespace state {

enum NetworkState {
  Network_Open,
  Network_Close,
  Network_Connect,
};

class NetworkProcessor {
private:
  NetworkState state;

public:
  void Operation1() {
    if (state == Network_Open) {
      //**********
      state = Network_Close;
    } else if (state == Network_Close) {
      //..........
      state = Network_Connect;
    } else if (state == Network_Connect) {
      //$$$$$$$$$$
      state = Network_Open;
    }
  }

public:
  void Operation2() {
    if (state == Network_Open) {
      //**********
      state = Network_Connect;
    } else if (state == Network_Close) {
      //.....
      state = Network_Open;
    } else if (state == Network_Connect) {
      //$$$$$$$$$$
      state = Network_Close;
    }
  }

public:
  void Operation3() {}
};

class NetworkStateOpt {

public:
  NetworkStateOpt *pNext;
  virtual void Operation1() = 0;
  virtual void Operation2() = 0;
  virtual void Operation3() = 0;

  virtual ~NetworkStateOpt() {}
};

class CloseState : public NetworkStateOpt {
private:
  static NetworkStateOpt* m_instance;

public:
  static NetworkStateOpt *getInstance() {
    return m_instance;
  }
};

class ConnectState : public NetworkStateOpt {
private:
  static NetworkStateOpt* m_instance;

public:
  static NetworkStateOpt *getInstance() {
    return m_instance;
  }
};

class OpenState : public NetworkStateOpt {
private:
  static NetworkStateOpt *m_instance;

public:
  static NetworkStateOpt *getInstance() {
    if (m_instance == nullptr) {
      m_instance = new OpenState();
    }
    return m_instance;
  }

  void Operation1() {
    //**********
    pNext = CloseState::getInstance();
  }

  void Operation2() {
    //..........
    pNext = ConnectState::getInstance();
  }

  void Operation3() {
    //$$$$$$$$$$
    pNext = OpenState::getInstance();
  }
};

//...

class NetworkProcessorOpt {
private:
  NetworkStateOpt *pState;

public:
  NetworkProcessorOpt(NetworkStateOpt *pState) { this->pState = pState; }

  void Operation1() {
    //...
    pState->Operation1();
    pState = pState->pNext;
    //...
  }

  void Operation2() {
    //...
    pState->Operation2();
    pState = pState->pNext;
    //...
  }

  void Operation3() {
    //...
    pState->Operation3();
    pState = pState->pNext;
    //...
  }
};

void test() {
  auto* state = new NetworkProcessorOpt(new OpenState());
  state->Operation1();
  state->Operation2();
  state->Operation3();
}

} // namespace state