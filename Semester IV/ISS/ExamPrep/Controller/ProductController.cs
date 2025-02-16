using ExamPrep.Model;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExamPrep.Controller
{
    internal class ProductController : IProductController
    {
        private static int DiscountTreshhold = 10;
        private static decimal DiscountAmount= 0.1m;
        private static decimal TaxAmount= 0.05m;

        private DbContext _context;
        private OrderController _orderController;
        public ProductController(DbContext context) {
            this._context = context;

        }

        private decimal ComputeTotalAmount(int quantity, decimal price)
        {
            decimal discount = this.ComputeDiscount(quantity, price);
            decimal tax = this.ComputeTax(quantity, price);

            return (price * quantity) - discount + tax;
        }

        private decimal ComputeDiscount(int quantity, decimal price)
        {
            decimal discount = 0;
            if(quantity > DiscountTreshhold)
            {
                discount = DiscountAmount * price * quantity;
            }
            return discount;
        }

        private decimal ComputeTax(int quantity, decimal price)
        {
            return TaxAmount * quantity * price;
        }

        public void ProcessOrder(string customerID, int productID, int quantity)
        {
            decimal price = GetProductPrice(productID);
            decimal totalAmount = this.ComputeTotalAmount(quantity, price);
            try
            {
                this._orderController.AddOrder(customerID, productID, quantity, totalAmount);
            }
            catch (Exception exception) {
                throw exception;
            }

        }

        private decimal GetProductPrice(int productID)
        {
            try
            {
                var product = this._context.Product.FirstOrDefault(product => product.ID == productID);
                return product.Price;
            }
            catch (Exception exception)
            {
               if(Environment.GetEnvironmentVariable("LOGGING") == "file")
                {
                    File.AppendAllText("log.txt", $"Error:{exception.Message}");
                }
                else
                {
                    throw exception;
                }
            }

        }

    }
}
