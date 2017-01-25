using System;
using System.Collections.Generic;

namespace lab3
{
    public class Spruce
    {
        public string placement { get; set; }
        public int height { get; set; }
        public Spruce(string placement, int height)
        {
            this.placement = placement;
            this.height = height;
        }
        public virtual void WinterStarted()
        {
            Write("I'm spruce. My height: {0}m. My placement: {1}.", height, placement);
        }
        protected virtual void Write(string format, params object[] args) => Console.WriteLine(format, args);
    }

    public class NewYearSpruce : Spruce
    {
        public int numdecor { get; set; }
        public NewYearSpruce(string placement, int height, int numdecor) : base(placement, height)
        {
            this.numdecor = numdecor;
        }
        public override void WinterStarted()
        {
            base.WinterStarted();
            Write(" Number of decorations: {0}.\n", numdecor);
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
                if (tree.placement == placement)
                {
                    Console.WriteLine("Finded spruce: My height: {0}m. My placement: {1}.\n", tree.height, tree.placement);
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
