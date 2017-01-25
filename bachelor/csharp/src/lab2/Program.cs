using System;

namespace lab2
{
    public class book
    {
        public string Author { get; set; }
        public string Name { get; set; }
        public int Price { get; set; }
        public book()
        {
            Author = "";
            Name = "";
            Price = 0;
        }
        public book(string author, string name, int price)
        {
            Author = author;
            Name = name;
            Price = price;
        }
    }
    static class InputHelp
    {
        public static int InputNumber(string prompt)
        {
            Console.WriteLine(prompt);
            int number;
            while (!int.TryParse(Console.ReadLine(), out number))
                Console.Error.WriteLine("Failure input.");
            return number;
        }
    }
    public class Inputbook
    {
        public void InputBook(book[] books)
        {
            for (int i = 0; i < books.Length; i++)
            {
                books[i] = new book();

                Console.WriteLine("\nAdd book: {0}", i + 1);

                Console.Write("Author: ");
                books[i].Author = Console.ReadLine();

                Console.Write("Name: ");
                books[i].Name = Console.ReadLine();

                Console.Write("Price: ");
                books[i].Price = InputHelp.InputNumber("");
            }
        }
    }
    public class Program
    {
        //public static class Search
        //{
        //    public static void SearchGoods(book[] goods, int lowerPrice)
        //    {
        //        Console.WriteLine($"\nSearch book by price from {lowerPrice}rub.");

        //        foreach (var good in goods)
        //            if (good.Price > lowerPrice)
        //                Console.WriteLine("Finded book: {0}, {1}, price {2}", good.Author, good.Name, good.Price);
        //    }
    }
    public static class SearchByName
    {
        public static void SearchAuthor(book[] authors)
        {
            Console.WriteLine("Enter a author name to find a book");
            string author = Console.ReadLine();
            foreach (var good in authors)
                if (good.Name == author)
                    Console.WriteLine("Finded book: {0}, {1}, price {2}", good.Author, good.Name, good.Price);
        }
    }
    class Book
    {
        static void Main(string[] args)
        {
            int booksCount = InputHelp.InputNumber("How many books do you want to add: ");

            var books = new book[booksCount];
            var book = new Inputbook();
            book.InputBook(books);
            int lowerPrice = InputHelp.InputNumber("Lowest price to search: ");
            SearchByName.SearchAuthor(books);
            Console.ReadLine();
        }
    }
}

