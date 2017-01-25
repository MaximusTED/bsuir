using System;
using System.Collections.Generic;

namespace lab4
{
    public class Letter
    {
        public int Year { get; set; }
        public string From { get; set; }
        public string To { get; set; }
        public string Forward { get; set; }
        public string Subject { get; set; }
        public string Body { get; set; }

        public Letter(int year, string from, string to, string forward, string subject, string body)
        {
            Year = year;
            From = from;
            To = to;
            Forward = forward;
            Subject = subject;
            Body = body;
        }

        public override string ToString() => 
            $"Year: {Year}\nFrom: {From}\nTo: {To}\nForward: {Forward}\nSubject: {Subject}\nBody: {Body}\n";
    }

    class Program
    {
        static void Main(string[] args)
        {
            List<Letter> letters = new List<Letter>();

            RunMenu(letters);
        }

        public static void RunMenu(List<Letter> letters)
        {
            int choice;
            do
            {
                Console.WriteLine("---------------------------");
                Console.WriteLine(" 1 - Add new letter        ");
                Console.WriteLine(" 2 - Show all letters      ");
                Console.WriteLine(" 3 - Delete all for sender ");
                Console.WriteLine(" 4 - Delete all with word ");
                Console.WriteLine(" 5 - Close                 ");
                Console.WriteLine("---------------------------");
                Console.Write("> ");

                choice = int.Parse(Console.ReadLine());

                switch (choice)
                {
                    case 1:
                        AddLetter(letters);
                        break;
                    case 2:
                        ViewAllLetters(letters);
                        break;
                    case 3:
                        Console.Write("Whose letter(s) will be deleted? ");

                        string from = Read(string.Empty);
                        int deletedCount = DeleteAllLetters(from, letters);

                        Console.WriteLine("Deleted {0} letter(s) from \"{1}\".", deletedCount, from);

                        break;
                    case 4:
                        Console.Write("Input the word from body to delete letter(s) with it: ");

                        string body = Read(string.Empty);
                        deletedCount = DeleteLettersWithWord(body, letters);

                        Console.WriteLine("Deleted {0} letter(s) with \"{1}\".", deletedCount, body);

                        break;
                    case 5:
                        break;
                    default:
                        Console.WriteLine("{0} option is not supported.", choice);
                        break;
                }
            } while (choice != 5);
        }

        public static void AddLetter(List<Letter> letters)
        {
            Console.WriteLine("> Creating letter...");
            Console.Write("  Year: ");
            int year = Int32.Parse(Read("Year"));

            Console.Write("  From: ");
            string from = Read("From");

            Console.Write("  To: ");
            string to = Read("To");

            Console.Write("  Forward: ");
            string forward = Read("Forward");

            Console.Write("  Subject: ");
            string subject = Read("Subject");

            Console.Write("  Body: ");
            string body = Read("Body");

            letters.Add(new Letter(year, from, to, forward, subject, body));
        }

        public static string Read(string prefix)
        {
            string value;

            while (string.IsNullOrEmpty(value = Console.ReadLine().Trim()))
            {
                Console.WriteLine("Please, enter correct data.");
                Console.Write("  {0}: ", prefix);
            }

            return value;
        }

        public static void ViewAllLetters(List<Letter> letters)
        {
            if (letters.Count == 0)
            {
                Console.WriteLine("No letters found.");
                return;
            }

            for (int i = 0; i < letters.Count; ++i)
            {
                Console.WriteLine("Letter #{0}", i + 1);
                Console.WriteLine(letters[i]);
                Console.WriteLine();
            }
        }

        private static int DeleteAllLetters(string from, List<Letter> letters)
        {
            int deletedCount = 0;

            for (int i = letters.Count - 1; i >= 0; --i)
            {
                Letter letter = letters[i];

                if (letter.From == from)
                {
                    letters.RemoveAt(i);
                    ++deletedCount;
                }
            }

            return deletedCount;
        }
        private static int DeleteLettersWithWord(string body, List<Letter> letters)
        {
            int deletedCount = 0;

            for (int i = letters.Count - 1; i >= 0; --i)
            {
                Letter letter = letters[i];

                if (letter.Body.Contains(body))
                {
                    letters.RemoveAt(i);
                    ++deletedCount;
                }
            }

            return deletedCount;
        }
    }
}