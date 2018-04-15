// Экзамен.
// Реализвать класс Очередь; три метода: 
// * добавить,
// * получить следующего из очереди с удалением его из очереди
// * получить состояние очереди (количество в очереди или что-то вроде того) 
// Внутри очереди список-шаблон List<T>.

using System;
using System.Collections.Generic;

namespace Bsuir.AaDs.Cs.Sample6
{
    public class Queue<T>
    {
        private readonly List<T> items;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="capacity">Initial capacity of the queue.</param>
        public Queue(int capacity = 4)
        {
            items = new List<T>(capacity);
        }

        /// <summary>
        /// Add item to queue.
        /// </summary>
        /// <param name="item">Item to add.</param>
        public void Enqueue(T item)
        {
            items.Add(item);
        }

        /// <summary>
        /// Remove first item from queue.
        /// </summary>
        /// <returns>First item which is removed.</returns>
        /// <exception cref="InvalidOperationException">In case no items in queue.</exception>
        public T Dequeue()
        {
            if (Any())
            {
                var item = items[0];
                items.RemoveAt(0);
                return item;
            }

            throw new InvalidOperationException("Queue is empty");
        }

        /// <summary>
        /// Check queue has items or not.
        /// </summary>
        /// <returns><keyword>true</keyword> if queue has at least one element,
        /// <keyword>false</keyword> otherwise.</returns>
        public bool Any()
        {
            return items.Count > 0;
        }

        /// <summary>
        /// Overridden to get diagnostic info.
        /// </summary>
        /// <returns>Diagnostic info <see cref="string"/></returns>
        public override string ToString()
        {
            var result = $"Queue contains {items.Count} items.";

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
            catch (InvalidOperationException ex)
            {
                Console.WriteLine("Catched exception: {0}", ex.Message);
            }
        }
    }
}
