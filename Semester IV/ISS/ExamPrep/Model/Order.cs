using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExamPrep.Model
{
    internal class Order
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int OrderId { get; set; }
        
        public string CustomerId { get; set; }

        public int ProductId { get; set; }
        [ForeignKey(nameof(ProductId))]
         public Product Product {  get; set; }

        public int Quantity {  get; set; }

        public decimal TotalAmount {  get; set; }
    }
}
