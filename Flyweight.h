// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/16 1:18 下午
// Description:
//

#pragma once

namespace fly {

class Font {
private:
  // unique object key
  string key;

  // object state
  //....
public:
  Font(const string &key) {
    //...
  }
};

class FontFactory {
private:
  map<string, Font *> fontPool;

public:
  Font *GetFont(const string &key) {

    auto item = fontPool.find(key);
    if (item != fontPool.end()) {
      return fontPool[key];
    } else {
      Font *font = new Font(key);
      fontPool[key] = font;
      return font;
    }
  }

  void clear() {
    //...
  }
};
} // namespace fly
