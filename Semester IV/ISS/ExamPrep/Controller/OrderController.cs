using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.Migrations.Model;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ExamPrep.DBContext;
using ExamPrep.Model;

namespace ExamPrep.Controller
{
    internal class OrderController : IOrderController
    {
        private MyDbContext Context;
        public OrderController(MyDbContext Context)
        {
            this.Context = Context;
        }

        public void AddOrder(string CustomerID, int ProductID, int Quantity, decimal TotalAmount)
        {
            try
            {
                var Order = new Order()
                {
                    CustomerId = CustomerID,
                    ProductId = ProductID,
                    Quantity = Quantity,
                    TotalAmount = TotalAmount
                };
                this.Context.Orders.add(Order);
                this.Context.SaveChanges();
                
            }
            catch (Exception exception)
            {
                throw exception;
            }
        }

        public List<Order> GetOrders()
        {
            return this.Context.Orders.ToList();
        }

    }


}
