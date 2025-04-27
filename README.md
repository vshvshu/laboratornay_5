Реализация паттерна "Стратегия":
  Перечисляемый тип - enum class GrowthStrategyType
  Абстрактный класс стратегии - GrowthStrategy
  Конкретные стратегии - NaturalGrowthStrategy, FastGrowthStrategy, SlowGrowthStrategy
  Фабричный метод - CreateGrowthStrategy() 
  Инкапсуляция стратегии - в классе Tree есть указатель GrowthStrategy* growthStrategy
  Функция для задания стратегии - SetGrowthStrategy()
  Использование стратегии - метод Grow() использует текущую стратегию через growthStrategy->ExecuteGrowth()

Реализация паттерна "Шаблонный метод"
  В базовом классе Tree определен шаблонный метод Grow(), который фиксирует общую структуру алгоритма роста
  Метод разделен на этапы (BeforeGrowth, ExecuteGrowth, SpecificGrowthBehavior, AfterGrowth)
  Общие части алгоритма (проверка здоровья, увеличение возраста и высоты) реализованы в базовом классе
