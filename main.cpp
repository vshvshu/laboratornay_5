#include <iostream>
#include "trees_pattern.h"

using namespace std;

// Реализация методов стратегий
void NaturalGrowthStrategy::ExecuteGrowth() {
    cout << "Growing naturally..." << endl;
}

void FastGrowthStrategy::ExecuteGrowth() {
    cout << "Growing fast with nutrients..." << endl;
}

void SlowGrowthStrategy::ExecuteGrowth() {
    cout << "Growing slowly conserving resources..." << endl;
}

// Реализация фабричного метода
GrowthStrategy* CreateGrowthStrategy(GrowthStrategyType type) {
    switch(type) {
        case GrowthStrategyType::NaturalGrowth:
            return new NaturalGrowthStrategy();
        case GrowthStrategyType::FastGrowth:
            return new FastGrowthStrategy();
        case GrowthStrategyType::SlowGrowth:
            return new SlowGrowthStrategy();
        default:
            return new NaturalGrowthStrategy();
    }
}

// Реализация методов Tree
Tree::Tree(TreeType type) : Type(type), Height(0.0), Age(0), IsHealthy(true),
                           growthStrategy(new NaturalGrowthStrategy()) {}

Tree::~Tree() {
    delete growthStrategy;
}

void Tree::SetGrowthStrategy(GrowthStrategyType strategyType) {
    delete growthStrategy;
    growthStrategy = CreateGrowthStrategy(strategyType);
}

// Реализация конструкторов конкретных деревьев
Oak::Oak() : Tree(TreeType::Oak) {}
Pine::Pine() : Tree(TreeType::Pine) {}
Birch::Birch() : Tree(TreeType::Birch) {}

int main() {
    // Демонстрация паттернов
    cout << "Strategy Pattern + Template Method Pattern" << endl;

    // Создаем деревья с разными стратегиями
    Oak oak;
    Pine pine;
    Birch birch;

    // Устанавливаем стратегии
    oak.SetGrowthStrategy(GrowthStrategyType::NaturalGrowth);
    pine.SetGrowthStrategy(GrowthStrategyType::FastGrowth);
    birch.SetGrowthStrategy(GrowthStrategyType::SlowGrowth);

    cout << endl;
    // Тестируем рост деревьев
    cout << "First growth:" << endl;
    oak.Grow();
    pine.Grow();
    birch.Grow();

    cout << endl;
    // Динамическая смена поведения объекта
    cout << "Changing oak to fast growth:" << endl;
    oak.SetGrowthStrategy(GrowthStrategyType::FastGrowth);
    oak.Grow();

    cout << endl;
    // Показываем состояние деревьев
    cout << "Tree states:" << endl;
    cout << "Oak - height: " << oak.GetHeight() << ", age: " << oak.GetAge() << endl;
    cout << "Pine - height: " << pine.GetHeight() << ", age: " << pine.GetAge() << endl;
    cout << "Birch - height: " << birch.GetHeight() << ", age: " << birch.GetAge() << endl;

    return 0;
}
