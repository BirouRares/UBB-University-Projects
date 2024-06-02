using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace A1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daNeighborhoods, daSmartHomes;
        DataSet dset;
        BindingSource bsNeighborhoods, bsSmartHomes;

        SqlCommandBuilder cmdBuilder;

        string queryNeighborhood;
        string queryHome;

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            try
            {
                daSmartHomes.Update(dset, "SmartHome");
                MessageBox.Show("Changes saved to the database");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }

        void FillData()
        {
            try
            {
                conn = new SqlConnection(getConString());

                queryNeighborhood = "SELECT * FROM Neighborhood";
                queryHome = "SELECT * FROM SmartHome";

                daNeighborhoods = new SqlDataAdapter(queryNeighborhood, conn);
                daSmartHomes = new SqlDataAdapter(queryHome, conn);
                dset = new DataSet();

                daNeighborhoods.Fill(dset, "Neighborhood");
                daSmartHomes.Fill(dset, "SmartHome");

                cmdBuilder = new SqlCommandBuilder(daSmartHomes);

                dset.Relations.Add(
                    "FK_Neighborhood_SmartHome",
                    dset.Tables["Neighborhood"].Columns["NID"],
                    dset.Tables["SmartHome"].Columns["NID"]
                );

                bsNeighborhoods = new BindingSource();
                bsSmartHomes = new BindingSource();

                bsNeighborhoods.DataSource = dset.Tables["Neighborhood"];
                bsSmartHomes.DataSource = bsNeighborhoods;
                bsSmartHomes.DataMember = "FK_Neighborhood_SmartHome";

                this.dgvNeighborhoods.DataSource = bsNeighborhoods;
                this.dgvSmartHomes.DataSource = bsSmartHomes;

                cmdBuilder.GetUpdateCommand();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        string getConString()
        {
            return "Data Source = Birou; Initial Catalog = Practic; Integrated Security = True";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
