// lab2
// Создать класс Книга со свойствами Автор, Название и Цена.
// Ввести список Книг, реализовать поиск Книг по Автору.

using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace Bsuir.AaDs.Cs.Sample2
{
    public static class Contract
    {
        [Pure]
        public static void NotNull<T>([NotNull] this T value, [NotNull] string valueName) where T : class
        {
            if (value == null)
            {
                throw new ArgumentNullException(valueName, $"{valueName} is null");
            }
        }

        [Pure]
        public static void NotEmpty([CanBeNull] this string value, [NotNull] string valueName)
        {
            if (value == string.Empty)
            {
                throw new ArgumentException($"{valueName} is empty", valueName);
            }
        }

        [Pure]
        public static void NotNullOrEmpty([NotNull] this string value, [NotNull] string valueName)
        {
            NotNull(value, valueName);
            NotEmpty(value, valueName);
        }

        [Pure]
        public static void PositiveOrZero(decimal value, string valueName)
        {
            if (value < 0)
            {
                throw new ArgumentException($"{valueName} is {value}, which is less than zero");
            }
        }
    }

    public class Author
    {
        public Author([NotNull] string name, [NotNull] string surname)
        {
            Contract.NotNullOrEmpty(name, nameof(name));
            Contract.NotNullOrEmpty(surname, nameof(surname));

            Name = name;
            Surname = surname;
        }

        [NotNull]
        public string Name { get; }

        [NotNull]
        public string Surname { get; }

        [Pure]
        public override string ToString() =>
            $"{{{nameof(Name)}: {Name}, {nameof(Surname)}: {Surname}}}";
    }

    public class Book
    {
        [NotNull]
        public Author Author { get; }

        [NotNull]
        public string Title { get; }

        public decimal Price { get; }

        public Book([NotNull] Author author, [NotNull] string title, decimal price)
        {
            Contract.NotNull(author, nameof(author));
            Contract.NotNullOrEmpty(title, nameof(title));
            Contract.PositiveOrZero(price, nameof(price));

            Author = author;
            Title = title;
            Price = price;
        }

        [Pure]
        public override string ToString() =>
            $"{{{nameof(Title)}: {Title}, {nameof(Author)}: {Author}, {nameof(Price)}: {Price}}}";
    }

    static class GenericReader
    {
        public static int ReadNumber([NotNull] string prompt)
        {
            Contract.NotNull(prompt, nameof(prompt));

            Console.Write(prompt);

            int number;
            while (!int.TryParse(Console.ReadLine(), out number))
            {
                Console.Error.WriteLine("Failure input.");
            }

            return number;
        }

        public static decimal ReadDecimal([NotNull] string prompt)
        {
            Contract.NotNull(prompt, nameof(prompt));

            Console.Write(prompt);

            decimal number;
            while (!decimal.TryParse(Console.ReadLine(), out number))
            {
                Console.Error.WriteLine("Failure input.");
            }

            return number;
        }

        public static string ReadString([NotNull] string prompt)
        {
            Contract.NotNull(prompt, nameof(prompt));

            Console.Write(prompt);

            string value;
            while ((value = Console.ReadLine()) == string.Empty)
            {
                Console.Error.WriteLine("Failure input.");
            }

            Debug.Assert(value != string.Empty, "value != string.Empty");

            return value;
        }
    }

    public static class BookReader
    {
        [NotNull]
        [ItemNotNull]
        public static List<Book> ReadBooks(int booksCount)
        {
            Contract.PositiveOrZero(booksCount, nameof(booksCount));

            return Enumerable.Range(0, booksCount)
                .Select(bookNo => ReadBook(bookNo))
                .ToList();
        }

        [NotNull]
        private static Book ReadBook(int bookNo)
        {
            Debug.Assert(bookNo >= 0, "BookNo should be >= 0.");

            Console.WriteLine("Add book: {0}", bookNo + 1);

            Console.WriteLine("Author: ");
            string name = GenericReader.ReadString("Name: "),
                surname = GenericReader.ReadString("Surname: ");
            Author author = new Author(name, surname);

            string title = GenericReader.ReadString("Title: ");
            decimal price = GenericReader.ReadDecimal("Price: ");

            return new Book(author, title, price);
        }
    }

    public static class Search
    {
        [Pure]
        public static List<Book> FindByAuthor([NotNull] this List<Book> books,
            [NotNull] string authorName)
        {
            Contract.NotNull(books, nameof(books));
            Contract.NotNullOrEmpty(authorName, nameof(authorName));

            return books.Where(book => IsBookOfSameAuthor(book.Author, authorName))
                .ToList();
        }

        [Pure]
        private static bool IsBookOfSameAuthor([NotNull] Author author, [NotNull] string authorName)
        {
            Debug.Assert(author != null, "author != null");
            Debug.Assert(!string.IsNullOrEmpty(authorName), "!string.IsNullOrEmpty(authorName)");

            return author.Name == authorName;
        }
    }

    class Program
    {
        static void Main()
        {
            int booksCount = GenericReader.ReadNumber("How many books do you want to add? ");
            List<Book> books = BookReader.ReadBooks(booksCount);

            string authorName = GenericReader.ReadString("Enter a author name to find the books: ");
            List<Book> booksByAuthor = books.FindByAuthor(authorName);

            WriteFoundBooks(authorName, booksByAuthor);
        }

        private static void WriteFoundBooks([NotNull] string authorName, [NotNull] List<Book> booksByAuthor)
        {
            Debug.Assert(authorName != null, "authorName != null");
            Debug.Assert(booksByAuthor != null, "booksByAuthor != null");

            if (booksByAuthor.Count == 0)
            {
                Console.WriteLine("No books of author with name {0} are found", authorName);
            }
            else
            {
                booksByAuthor.ForEach(bookByAuthor => Console.WriteLine("Finded {0}'s book: {1}", authorName, bookByAuthor));
            }
        }
    }
}

