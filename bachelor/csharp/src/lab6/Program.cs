using System;
using System.Collections.Generic;

// класс очередь; три метода: 
// добавить,
// получить следующего из очереди с удалением его из очереди
// и состояние очереди (количество в очереди или что-то вроде того) 
// внутри очереди список list

namespace lab6
{
    public class Queue<T>
    {
        private readonly List<T> items;

        public Queue()
        {
            items = new List<T>();
        }

        public void Enqueue(T item)
        {
            items.Add(item);
        }

        public T Dequeue()
        {
            if (items.Count > 0)
            {
                var item = items[0];
                items.RemoveAt(0);
                return item;
            }

            throw new InvalidOperationException("Queue is empty");
        }

        public bool Any()
        {
            return items.Count > 0;
        }

        //пока в очереди есть элемент, очередь дай элемент
        public override string ToString()
        {
            string result = string.Format("Queue contains {0} items.", items.Count);

            for (int i = 0; i < items.Count; ++i)
            {
                if (i == 0)
                {
                    result += " Queue:\n";
                }

                result += items[i] + "\n";
            }

            return result;
        }
    }

    class Program
    {
        static void Main()
        {
            var numbersQueue = new Queue<int>();
            Console.WriteLine("Queue after creation: {0}", numbersQueue);

            numbersQueue.Enqueue(1);
            numbersQueue.Enqueue(2);
            numbersQueue.Enqueue(3);

            while (numbersQueue.Any())
            {
                Console.WriteLine("Queue: {0}", numbersQueue);
                Console.WriteLine("Dequeue: {0}", numbersQueue.Dequeue());
            }

            try
            {
                Console.WriteLine("Try to dequeue from empty queue: {0}", numbersQueue);
                Console.WriteLine(numbersQueue.Dequeue());
            }
            catch (Exception ex)
            {
                Console.WriteLine("Catched exception: {0}", ex.Message);
            }
        }
    }
}
