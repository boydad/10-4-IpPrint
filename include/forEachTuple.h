#include <tuple>


namespace _detail_
{
    // Главная роль здесь у шаблона класса iterate_tuple.
    
    // Первый параметр шаблона класса iterate_tuple имеет тип int (index).
    // Значение этого параметра используется функцией get, 
    // которая "достает" из кортежа элемент по указанной позиции.
    
    // Мы рекурсивно сдвигаем позицию (уменьшаем index на 1) и таким образом
    // перемещаемся по кортежу.
    
    // Когда значение индекса становится равно 0, рекурсия завершается,
    // благодаря частичной специализации для индекса равного 0.
    
    // При этом есть особый случай, когда индекс равен -1. Он соответствует 
    // ситуации, когда кортеж не содержит ни одного элемента.
    
    template<int index, typename Callback, typename... Args>
    struct iterate_tuple 
    {
        static void next(const std::tuple<Args...>& t, Callback callback) 
        {
            // Уменьшаем позицию и рекурсивно вызываем этот же метод 
            iterate_tuple<index - 1, Callback, Args...>::next(t, callback);
            
            // Вызываем обработчик и передаем ему позицию и значение элемента
            callback(index, std::get<index>(t));
        }
    };
    
    // Частичная специализация для индекса 0 (завершает рекурсию)
    template<typename Callback, typename... Args>
    struct iterate_tuple<0, Callback, Args...> 
    {
        static void next(const std::tuple<Args...>& t, Callback callback) 
        {
            callback(0, std::get<0>(t));
        }
    };

    // Частичная специализация для индекса -1 (пустой кортеж)
    template<typename Callback, typename... Args>
    struct iterate_tuple<-1, Callback, Args...>
    {
        static void next(std::tuple<Args...>& t, Callback callback)
        {
            // ничего не делаем
        }
    };
}


//
// "Волшебный" for_each для обхода элементов кортежа (compile time!):
//
template<typename Callback, typename... Args>
void for_each(const  std::tuple<Args...>& t, Callback& callback) 
{
    // Размер кортежа
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;
    
    // Запускаем рекурсивный обход элементов кортежа во время компиляции
    _detail_::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}