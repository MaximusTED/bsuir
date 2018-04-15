// lab3
// Создать класс Елка и наследник Новогодняя Елка.
// Реализовать метод Зима Началась, переопределить в наследнике.
// Захардкодить список елок различного типа и показать полиморфизм на этапе
// выполнения, вызвав метод Зима Началась и отобразив разные результаты для
// разных типов елок.

using System;
using System.Collections.Generic;

namespace Bsuir.AaDs.Cs.Sample3
{
    public class Spruce
    {
        public string Placement { get; }
        public int Height { get; set; }

        public Spruce(string placement, int height)
        {
            Placement = placement;
            Height = height;
        }

        public virtual void WinterStarted()
        {
            Write("I'm spruce. My height: {0}m. My placement: {1}.", Height, Placement);
        }

        protected virtual void Write(string format, params object[] args) => Console.WriteLine(format, args);
    }

    public class NewYearSpruce : Spruce
    {
        public int DecorationsCount { get; }

        public NewYearSpruce(string placement, int height, int numdecor) : base(placement, height)
        {
            DecorationsCount = numdecor;
        }

        public override void WinterStarted()
        {
            base.WinterStarted();
            Write(" Decorations count: {0}.\n", DecorationsCount);
        }

        protected override void Write(string format, params object[] args) => Console.Write(format, args);
    }

    class Program
    {
        public static void SearchTree(List<Spruce> placements)
        {
            Console.WriteLine("Enter a tree placement to find information about it height, and number of decorations if it possible");

            string placement = Console.ReadLine();

            foreach (var tree in placements)
            {
                if (tree.Placement == placement)
                {
                    Console.WriteLine("Finded spruce: My height: {0}m. My placement: {1}.\n", tree.Height, tree.Placement);
                }
            }
        }

        static void Main()
        {
            var forest = new List<Spruce>
            {
                new Spruce("Zion", 1488),
                new Spruce("Strathol'm", 228),
                new NewYearSpruce("Izengard", 7788, 69)
            };

            foreach (var tree in forest)
            {
                tree.WinterStarted();
            }

            SearchTree(forest);
        }
    }
}
