// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 7:36 下午
// Description:
//

#pragma once

// 框架和应用的协作关系，组件协作模式
#include "dessignPattern/TemplateMethod.h"
#include "dessignPattern/Strategy.h"
#include "dessignPattern/Observer.h"

// 划清楚每个类的职责，避免滥用继承导致的类的膨胀，单一职责模式
#include "dessignPattern/Decorator.h"
#include "dessignPattern/Bridge.h"

// 对象创建模式, 绕过new 具体类型绑定，从而不依赖具体类, 支持对象创建的稳定
#include "dessignPattern/FactoryMethod.h"
#include "dessignPattern/AbstractFactory.h"
#include "dessignPattern/Prorotype.h"
#include "dessignPattern/Build.h"

// 对象性能模式，避免大量对象导致的性能问题
// #include "dessignPattern/Singleton.h"
#include "dessignPattern/Flyweight.h"

//接口隔离模式，在组件构建过程中，某些接口直接的依赖会带来很多问题，
// 或者不能实现，采用一组间接口来隔离本来互相紧密关联的接口是一个常见的解决方案
#include "dessignPattern/Facade.h"
#include "dessignPattern/Proxy.h"
#include "dessignPattern/Adapter.h"
#include "dessignPattern/Mediator.h"

// 状态变化模式，某些对象的状态经常发生变化
// 如何对这些变化进行有效的管理，同时又维护高层模块的稳定，状态变化模式为这种问题提出了解决方案h
#include "dessignPattern/State.h"
#include "dessignPattern/Memento.h"

// 数据结构模式，如果让客户依赖这些复杂的数据结构，将极大的破坏组件的的复用
// 此时，将这些特定数据结构封装在内部，在外部提供统一的接口，来实现与特定结构无关的访问
#include "dessignPattern/Composite.h"
#include "dessignPattern/Iterator.h"
