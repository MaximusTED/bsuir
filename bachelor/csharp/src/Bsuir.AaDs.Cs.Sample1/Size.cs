using JetBrains.Annotations;
using System;

namespace Bsuir.AaDs.Cs.Sample1
{
    public class Size
    {
        public Size(int length, int width)
        {
            ValidateDimension(nameof(length), length);
            ValidateDimension(nameof(width), width);

            Length = length;
            Width = width;
        }

        public int Length { get; }
        public int Width { get; }

        public override string ToString() =>
            $"{nameof(Length)}: {Length}, {nameof(Width)}: {Width}"; 

        private static void ValidateDimension([NotNull] string dimensionName, int dimensionSize)
        {
            if (dimensionSize <= 0)
            {
                throw new ArgumentOutOfRangeException(dimensionName, 
                    dimensionSize,
                    "Dimension size is out of range (0, int.MaxValue].");
            }
        }
    }
}
