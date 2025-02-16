using System;

namespace ExamPrep.Controller
{
    public interface IProductController
    {
        void ProcessOrder(string customerID, int productID, int quantity);

        // Private methods cannot be included in an interface, but here are the method signatures for reference:
        // decimal ComputeTotalAmount(int quantity, decimal price);
        // decimal ComputeDiscount(int quantity, decimal price);
        // decimal ComputeTax(int quantity, decimal price);
        // decimal GetProductPrice(int productID);
    }
}
