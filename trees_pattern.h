#ifndef TREES_PATTERN_H
#define TREES_PATTERN_H

#include <iostream>
#include <cstdlib>

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

// Базовый класс дерева
class Tree {
protected:
    TreeType Type;
    double Height;
    int Age;
    bool IsHealthy;
    GrowthStrategy* growthStrategy;

public:
    Tree(TreeType type);
    virtual ~Tree();

    void SetGrowthStrategy(GrowthStrategyType strategyType);
    virtual void Grow();

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

// Конкретные типы деревьев
class Oak : public Tree {
public:
    Oak();
    void Grow() override;
};

class Pine : public Tree {
public:
    Pine();
    void Grow() override;
};

class Birch : public Tree {
public:
    Birch();
    void Grow() override;
};

#endif // TREES_PATTERN_H
