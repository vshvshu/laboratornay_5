#ifndef TREES_PATTERN_H
#define TREES_PATTERN_H

#include <iostream>
#include <cstdlib>
using namespace std;
// Тип стратегии роста
enum class GrowthStrategyType {
    NaturalGrowth,
    FastGrowth,
    SlowGrowth
};

// Абстрактная стратегия
class GrowthStrategy {
public:
    virtual ~GrowthStrategy() {}
    virtual void ExecuteGrowth() = 0;
};

// Типы деревьев
enum class TreeType {
    Oak,
    Pine,
    Birch
};

// Базовый класс дерева с шаблонным методом
class Tree {
protected:
    TreeType Type;
    double Height;
    int Age;
    bool IsHealthy;
    GrowthStrategy* growthStrategy;

    // Шаги алгоритма роста (методы-заготовки)
    virtual void BeforeGrowth() = 0;
    virtual void AfterGrowth() = 0;
    virtual void SpecificGrowthBehavior() = 0;

public:
    Tree(TreeType type);
    virtual ~Tree();

    void SetGrowthStrategy(GrowthStrategyType strategyType);

    // Шаблонный метод, определяющий структуру алгоритма роста
    void Grow() {
        if(!Healthy()) {
            cout << "Cannot grow - tree is sick!" << endl;
            return;
        }

        BeforeGrowth();
        growthStrategy->ExecuteGrowth();
        SpecificGrowthBehavior();
        Height += 0.5;
        Age++;
        AfterGrowth();
    }

    bool Healthy() const { return IsHealthy; }
    TreeType GetType() const { return Type; }
    double GetHeight() const { return Height; }
    int GetAge() const { return Age; }
};

// Конкретные стратегии
class NaturalGrowthStrategy : public GrowthStrategy {
public:
    void ExecuteGrowth() override;
};

class FastGrowthStrategy : public GrowthStrategy {
public:
    void ExecuteGrowth() override;
};

class SlowGrowthStrategy : public GrowthStrategy {
public:
    void ExecuteGrowth() override;
};

// Фабрика стратегий
GrowthStrategy* CreateGrowthStrategy(GrowthStrategyType type);

// Конкретные типы деревьев с реализацией шагов шаблонного метода
class Oak : public Tree {
protected:
    void BeforeGrowth() override {
        cout << "Oak tree starts growing..." << endl;
    }

    void AfterGrowth() override {
        cout << "Oak tree finished growing. Current height: " << Height << endl;
    }

    void SpecificGrowthBehavior() override {
        cout << "Oak is growing strong and wide." << endl;
    }

public:
    Oak();
};

class Pine : public Tree {
protected:
    void BeforeGrowth() override {
        cout << "Pine tree starts growing..." << endl;
    }

    void AfterGrowth() override {
        cout << "Pine tree finished growing. Current height: " << Height << endl;
    }

    void SpecificGrowthBehavior() override {
        cout << "Pine is growing tall and narrow." << endl;
    }

public:
    Pine();
};

class Birch : public Tree {
protected:
    void BeforeGrowth() override {
        cout << "Birch tree starts growing..." << endl;
    }

    void AfterGrowth() override {
        cout << "Birch tree finished growing. Current height: " << Height << endl;
    }

    void SpecificGrowthBehavior() override {
        cout << "Birch is growing with white bark." << endl;
    }

public:
    Birch();
};

#endif // TREES_PATTERN_H
