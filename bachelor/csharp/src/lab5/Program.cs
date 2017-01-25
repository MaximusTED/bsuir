using System;
using System.Collections.Generic;

namespace lab5
{
    public class Letter
    {
        private string from;
        public string From
        {
            get { return from; }
            set { Validate("From", value); from = value; }
        }

        private string to;
        public string To
        {
            get { return to; }
            set { Validate("To", value); to = value; }
        }

        private string forward;
        public string Forward
        {
            get { return forward; }
            set { Validate("Forward", value); forward = value; }
        }

        private string subject;
        public string Subject
        {
            get { return subject; }
            set { Validate("Subject", value); subject = value; }
        }

        private string body;
        public string Body
        {
            get { return body; }
            set { Validate("Body", value); body = value;  }
        }

        public Letter(string from, string to, string forward, string subject, string body)
        {
            From = from;
            To = to;
            Forward = forward;
            Subject = subject;
            Body = body;
        }

        private static void Validate(string name, string value)
        {
            if (string.IsNullOrEmpty(value))
            {
                throw new ArgumentException($"Letter '{name}' is null or empty.");
            }
        }

        public override string ToString() => 
            $"From: {From}\nTo: {To}\nForward: {Forward}\nSubject: {Subject}\nBody: {Body}";
    }

    class Program
    {
        static int Main(string[] args)
        {
            var letters = new List<Letter>();

            try
            {
                RunMenu(letters);
                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Problem found: {0}", ex.Message);
            }

            return 1;
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
                Console.WriteLine(" 4 - Close                 ");
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

                        string from = Read();
                        int deletedCount = DeleteAllLetters(from, letters);

                        Console.WriteLine("Deleted {0} letter(s) from \"{1}\".", deletedCount, from);

                        break;
                    case 4:
                        break;
                    default:
                        Console.WriteLine("{0} option is not supported.", choice);
                        break;
                }
            } while (choice != 4);
        }

        public static void AddLetter(List<Letter> letters)
        {
            Console.WriteLine("> Creating letter...");

            Console.Write("  From: ");
            string from = Read();

            Console.Write("  To: ");
            string to = Read();

            Console.Write("  Forward: ");
            string forward = Read();

            Console.Write("  Subject: ");
            string subject = Read();

            Console.Write("  Body: ");
            string body = Read();

            letters.Add(new Letter(from, to, forward, subject, body));
        }

        public static string Read()
        {
            return Console.ReadLine().Trim();
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
    }
}
