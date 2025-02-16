using ExamPrep.Controller;
using ExamPrep.DBContext;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ExamPrep.View;

namespace ExamPrep
{
    internal class Program
    {
        static void Main(string[] args)
        {
            MyDbContext context = new MyDbContext(Environment.GetEnvironmentVariable("DB"));
            OrderController orderController = new OrderController(context);
            ProductController productController = new ProductController(context);
            ViewUI view = new ViewUI(productController, orderController);
        }
    }
}
