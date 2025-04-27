#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "trees_pattern.h"

using namespace std;

// Типы деревьев
enum class TreeType : int {
    Oak,
    Pine,
    Birch,
    Unknown
};

class Tree // Родительский (базовый) класс "Дерево"
{
private:
    TreeType Type;
    double Height;
    int Age;

protected:
    bool IsHealthy;

public:
    Tree(TreeType type) : Type(type), Height(0.0), Age(0), IsHealthy(false)
    {
        IsHealthy = static_cast<bool>(rand()%2);
    }

    virtual ~Tree() {}

    bool Healthy() const { return IsHealthy; }
    TreeType GetType() const { return Type; }
    double GetHeight() const { return Height; }
    int GetAge() const { return Age; }

    virtual void Grow()
    {
        if(Healthy())
        {
            cout << "Growing a HEALTHY tree... ";
        }
        else
        {
            cout << "Growing a SICK tree... ";
        }
    }
};

class Oak : public Tree
{
public:
    Oak();
    ~Oak() {}

    void Grow() override;
};

Oak::Oak() : Tree(TreeType::Oak) { }

void Oak::Grow()
{
    Tree::Grow();
    cout << "Growing oak..." << endl;
}

class Pine : public Tree
{
public:
    Pine() : Tree(TreeType::Pine) { }
    ~Pine() {}

    void Grow() override;
};

void Pine::Grow()
{
    Tree::Grow();
    cout << "Growing pine..." << endl;
}

class Birch : public Tree
{
public:
    Birch() : Tree(TreeType::Birch) { }
    ~Birch() {}

    void Grow();
};

void Birch::Grow()
{
    Tree::Grow();
    cout << "Growing birch..." << endl;
}

enum class TreeSpecies : int {
    Oak = 1,
    Pine = 2,
    Birch = 3,
    Undefined = 0
};

Tree *CreateTree(TreeSpecies type)
{
    Tree *newTree = nullptr;

    if(type == TreeSpecies::Oak)
    {
        newTree = new Oak;
    }
    else if(type == TreeSpecies::Pine)
    {
        newTree = new Pine;
    }
    else if(type == TreeSpecies::Birch)
    {
        newTree = new Birch;
    }

    return newTree;
}

class TreeSpeciesDecorator : public IteratorDecorator<class Tree*>
{
private:
    TreeSpecies TargetSpecies;
public:
    TreeSpeciesDecorator(Iterator<Tree*> *it, TreeSpecies species)
    : IteratorDecorator<Tree*>(it), TargetSpecies(species) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetType() != static_cast<TreeType>(TargetSpecies))
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->GetType() != static_cast<TreeType>(TargetSpecies));
    }
};

class TreeHealthDecorator : public IteratorDecorator<class Tree*>
{
private:
    bool TargetHealth;
public:
    TreeHealthDecorator(Iterator<Tree*> *it, bool isHealthy)
    : IteratorDecorator<Tree*>(it), TargetHealth(isHealthy) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->Healthy() != TargetHealth)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->Healthy() != TargetHealth);
    }
};

void GrowAll(Iterator<Tree*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Tree *currentTree = it->GetCurrent();
        currentTree->Grow();
    }
}

void GrowAllHealthy(Iterator<Tree*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Tree *currentTree = it->GetCurrent();
        if(!currentTree->Healthy()) continue;

        currentTree->Grow();
    }
}

void GrowAllPines(Iterator<Tree*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Tree *currentTree = it->GetCurrent();
        if(currentTree->GetType() != TreeType::Pine) continue;

        currentTree->Grow();
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");

    size_t N = 30;

    ArrayClass<Tree*> treeArray;
    for(size_t i=0; i<N; i++)
    {
        int tree_num = rand()%3+1;
        TreeSpecies tree_type = static_cast<TreeSpecies>(tree_num);
        Tree *newTree = CreateTree(tree_type);
        treeArray.Add(newTree);
    }

    wcout << L"Размер массива деревьев: " << treeArray.Size() << endl;

    list<Tree*> treeList;
    for(size_t i=0; i<N; i++)
    {
        int tree_num = rand()%3+1;
        TreeSpecies tree_type = static_cast<TreeSpecies>(tree_num);
        Tree *newTree = CreateTree(tree_type);
        treeList.push_back(newTree);
    }

    wcout << L"Размер списка деревьев: " << treeList.size() << endl;

    cout << endl << "Growing all in a simple loop:" << endl;
    for(size_t i=0; i<treeArray.Size(); i++)
    {
        Tree *currentTree = treeArray[i];
        currentTree->Grow();
    }

    cout << endl << "Growing all using iterator:" << endl;
    Iterator<Tree*> *allIt = treeArray.GetIterator();
    GrowAll(allIt);
    delete allIt;

    cout << endl << "Growing all healthy using iterator:" << endl;
    Iterator<Tree*> *healthyIt = new TreeHealthDecorator(treeArray.GetIterator(), true);
    GrowAll(healthyIt);
    delete healthyIt;

    cout << endl << "Growing all pines using iterator:" << endl;
    Iterator<Tree*> *pineIt = new TreeSpeciesDecorator(treeArray.GetIterator(), TreeSpecies::Pine);
    GrowAll(pineIt);
    delete pineIt;

    cout << endl << "Growing all healthy pines using iterator:" << endl;
    Iterator<Tree*> *healthyPineIt =
        new TreeHealthDecorator(new TreeSpeciesDecorator(treeArray.GetIterator(), TreeSpecies::Pine), true);
    GrowAll(healthyPineIt);
    delete healthyPineIt;

    cout << endl << "Growing all healthy pines using adapted iterator (another container):" << endl;
    Iterator<Tree*> *adaptedIt = new ConstIteratorAdapter<std::list<Tree*>, Tree*>(&treeList);
    Iterator<Tree*> *adaptedPineIt = new TreeHealthDecorator(new TreeSpeciesDecorator(adaptedIt, TreeSpecies::Pine), true);
    GrowAll(adaptedPineIt);
    delete adaptedPineIt;

    return 0;
}
