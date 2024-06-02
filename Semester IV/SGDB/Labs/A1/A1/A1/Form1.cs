using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace A1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daManufacturers, daProducts;
        DataSet dset;
        BindingSource bsManufacturers, bsProducts;

        SqlCommandBuilder cmdBuilder;

        string queryMan;
        string queryProd;

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            try
            {
                daProducts.Update(dset, "Products");
                MessageBox.Show("Changes saved to the database");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        void FillData()
        {
            try
            {
                conn = new SqlConnection(getConStirng());

                queryMan = "SELECT * FROM Manufacturers";
                queryProd = "SELECT * FROM Products";

                daManufacturers = new SqlDataAdapter(queryMan, conn);
                daProducts = new SqlDataAdapter(queryProd, conn);
                dset = new DataSet();
                daManufacturers.Fill(dset, "Manufacturers");
                daProducts.Fill(dset, "Products");

                cmdBuilder = new SqlCommandBuilder(daProducts);
            
                dset.Relations.Add
                (
                    "FK_Manufacturers_Products",
                    dset.Tables["Manufacturers"].Columns["ManufacturerID"],
                    dset.Tables["Products"].Columns["ManufacturerID"]
                );

                this.ManufacturersTable.DataSource = dset.Tables["Manufacturers"];
                this.ProductsTable.DataSource = this.ManufacturersTable.DataSource;
                this.ProductsTable.DataMember = "FK_Manufacturers_Products";

                cmdBuilder.GetUpdateCommand();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }
        string getConStirng()
        {
            return "Data Source = Birou; Initial Catalog = A1; Integrated Security = True";
        }
    }
}
