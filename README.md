Реализация паттерна "Стратегия":
  Перечисляемый тип - enum class GrowthStrategyType
  Абстрактный класс стратегии - GrowthStrategy
  Конкретные стратегии - NaturalGrowthStrategy, FastGrowthStrategy, SlowGrowthStrategy
  Фабричный метод - CreateGrowthStrategy() 
  Инкапсуляция стратегии - в классе Tree есть указатель GrowthStrategy* growthStrategy
  Функция для задания стратегии - SetGrowthStrategy()
  Использование стратегии - метод Grow() использует текущую стратегию через growthStrategy->ExecuteGrowth()
