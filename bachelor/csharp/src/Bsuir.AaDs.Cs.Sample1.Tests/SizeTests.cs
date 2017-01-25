using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Bsuir.AaDs.Cs.Sample1.Tests
{
    [TestClass]
    public class SizeTests
    {
        [TestMethod]
        public void SizeConstructorPositiveCaseTest()
        {
            const int expectedLength = 1;
            const int expectedWidth = 2;

            var size = new Size(expectedLength, expectedWidth);

            Assert.AreEqual(expectedLength, size.Length, $"{nameof(Size.Length)} is set during {nameof(Size)} construction.");
            Assert.AreEqual(expectedWidth, size.Width, $"{nameof(Size.Width)} is set during {nameof(Size)} construction.");
        }

        [TestMethod]
        public void SizeConstructorIncorrectLengthTest()
        {
            AssertIncorrectLength(-1);
            AssertIncorrectLength(0);
        }

        [TestMethod]
        public void SizeConstructorIncorrectWidthTest()
        {
            AssertIncorrectWidth(-1);
            AssertIncorrectWidth(0);
        }

        [TestMethod]
        public void SizeToStringWorksTest()
        {
            const int expectedLength = 1;
            const int expectedWidth = 2;
            var expectedToString = $"{nameof(Size.Length)}: {expectedLength}, {nameof(Size.Width)}: {expectedWidth}";

            var size = new Size(expectedLength, expectedWidth);

            var actualToString = size.ToString();

            Assert.AreEqual(expectedToString, actualToString, "ToString() is overridden.");
        }

        private static void AssertTryCatch<TException>(Action thrownAction,
            Action<TException> assertAction) where TException : Exception
        {
            try
            {
                thrownAction();
            }
            catch (TException e)
            {
                assertAction(e);
            }
            catch (Exception e)
            {
                Assert.Fail($"Unknown exception {e} was thrown.");
            }
        }

        private static void AssertIncorrectLength(int length)
        {
            AssertTryCatch<ArgumentOutOfRangeException>(() => new Size(length, 1),
                e => Assert.AreEqual("length", e.ParamName,
                        $"{nameof(Size.Length)} is validated during {nameof(Size)} construction."));
        }

        private static void AssertIncorrectWidth(int width)
        {
            AssertTryCatch<ArgumentOutOfRangeException>(() => new Size(1, width),
                e => Assert.AreEqual("width", e.ParamName,
                        $"{nameof(Size.Width)} is validated during {nameof(Size)} construction."));
        }
    }
}
