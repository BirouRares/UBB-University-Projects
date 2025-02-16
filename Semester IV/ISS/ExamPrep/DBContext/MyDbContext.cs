using ExamPrep.Model;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace ExamPrep.DBContext
{
    internal class MyDbContext : DbContext
    {
        public MyDbContext(DbContextOptions<MyDbContext> options) : base(options)
        {
        }

        public DbSet<Order> Orders { get; set; }

        public DbSet <Product> Products { get; set; }

        
    }
}
