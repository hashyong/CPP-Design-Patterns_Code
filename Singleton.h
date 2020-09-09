// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 9:38 下午
// Description:
//

#pragma once

namespace sin {

class Singleton {
private:
  Singleton()= default;
  Singleton(const Singleton &other) = delete;

public:
  static Singleton *getInstance();
  static std::atomic<Singleton *>  m_instance;
  static std::mutex m_mutex;
};

//Singleton *Singleton::m_instance = nullptr;

//线程非安全版本
Singleton *Singleton::getInstance() {
  if (m_instance == nullptr) {
    m_instance = new Singleton();
  }
  return m_instance;
}

//线程安全版本，但锁的代价过高
Singleton *Singleton::getInstance() {
  // 获取这个方法的人都要先锁住，成串行访问了
  lock lock;
  if (m_instance == nullptr) {
    m_instance = new Singleton();
  }
  return m_instance;
}

//非线程安全版本，但锁的代价过高
Singleton *Singleton::getInstance() {
  if (m_instance == nullptr) {
    // 这里可能同时有多个请求进来
    lock lock;
    m_instance = new Singleton();
  }
  return m_instance;
}

//双检查锁，但由于内存读写reorder不安全
Singleton *Singleton::getInstance() {

  if (m_instance == nullptr) {
    Lock lock;
    // 就算有多个请求进来，再判断一次即可，避免线程不安全
    if (m_instance == nullptr) {
      m_instance = new Singleton();
    }
  }
  return m_instance;
}

// C++ 11版本之后的跨平台实现 (volatile)
std::atomic<Singleton *> Singleton::m_instance;
std::mutex Singleton::m_mutex;

// 对于Acquire来说，保证Acquire后的读写操作不会发生在Acquire动作之前
// 对于Release来说，保证Release前的读写操作不会发生在Release动作之后, 当前线程中的读或写不能被重排到此存储后
// 上边的解释真的是闹心，我来用白话解释下
// 因为现在多核cpu，cache 导致reorder，即某些操作不按我们的想法来走
// x=3; acquire; x=2;
// 假如不加acquire，x的结果最终有可能等于3，加上acquire之后保证，x=2不会在x=3之前执行，x=2在x=3之后执行，符合预期，最终x是=2的
// x=2； release; x=4
// 假如不加release，x最终可能为2，因为x=4先执行，其次x=2，加上release之后保证，x=2肯定在x=4之前执行，符合我们的预期
// relaxed 只保证原子性, 不保证最终的顺序

Singleton *Singleton::getInstance() {
  Singleton *tmp = m_instance.load(std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_acquire); //获取内存fence
  if (tmp == nullptr) {
    std::lock_guard<std::mutex> lock(m_mutex);
    tmp = m_instance.load(std::memory_order_relaxed);
    if (tmp == nullptr) {
      tmp = new Singleton;
      std::atomic_thread_fence(std::memory_order_release); //释放内存fence
      m_instance.store(tmp, std::memory_order_relaxed);
    }
  }
  return tmp;
}

} // namespace sin
