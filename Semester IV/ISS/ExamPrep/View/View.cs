using ExamPrep.Controller;
using ExamPrep.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace ExamPrep.View
{
    public class ViewUI
    {
        private IProductController _productController;
        private IOrderController _orderController;

        private static string _optionAdd = "1";
        private static string _optionGetAll = "2";
        private static string _optionExit = "0";

        private static string _regexIncorrectFormat = "[a-z]{4}[0-9]{4}";

        public ViewUI(IProductController productController, IOrderController orderController)
        {
            _productController = productController;
            _orderController = orderController;
        }

        private void ShowMenu()
        {
            Console.WriteLine("1.Add.");
            Console.WriteLine("2.Get all.");
            Console.WriteLine("0.Exit.");
            Console.WriteLine("Chose: ");
        }

        private void HandleAdd()
        {
            Console.WriteLine("Enter customer ID:");
            string customerID = Console.ReadLine();
            if(!Regex.IsMatch(customerID, _regexIncorrectFormat)) {
                Console.Write("Invalid product ID");
                return;
            }
            Console.WriteLine("Enter product ID:");
            int productID = int.Parse(Console.ReadLine());
            Console.WriteLine("Enter quantity ID:");
            int quantity = int.Parse(Console.ReadLine());
            this._productController.ProcessOrder(customerID, productID, quantity);
        }

        private void HandleGetAllOrders()
        {
            List<Order> orders = this._orderController.GetOrders();
            this.PrintAllOrders(orders);
        }

        private void PrintAllOrders(List<Order> orders)
        {
            foreach (var order in orders)
            {
                Console.WriteLine(order.ToString());
            }
        }

        private void RunMenu()
        {
            while(true) {
                this.ShowMenu();
                string choice = Console.ReadLine();

                if(choice == _optionAdd)
                {
                    this.HandleAdd();
                }
                else if(choice == _optionGetAll) {
                    this.HandleGetAllOrders();
                }else if(choice == _optionExit)
                {
                    return;
                }
            }
        }


    }
}
