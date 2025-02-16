using System.Collections.Generic;
using ExamPrep.Model;

namespace ExamPrep.Controller
{
    public interface IOrderController
    {
        void AddOrder(string CustomerID, int ProductID, int Quantity, decimal TotalAmount);
        List<Order> GetOrders();
    }
}
