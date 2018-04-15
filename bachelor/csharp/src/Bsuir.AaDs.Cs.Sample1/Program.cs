// lab 1
// Разработать класс Размер со свойствами Длина и Ширина, конструктором инициализации. 
// Разработать консольное приложение, в котором создать массив из элементов и 
// заполнить их экземплярами класса Размер с хардкоженными данными.

using System;

namespace Bsuir.AaDs.Cs.Sample1
{
    class Program
    {
        public static void Main(string[] args)
        {
            var sizes = new[]
            {
                new Size(1, 2),
                new Size(2, 3)
            };

            foreach (var size in sizes)
            {
                Console.WriteLine(size);
            }
        }
    }
}
