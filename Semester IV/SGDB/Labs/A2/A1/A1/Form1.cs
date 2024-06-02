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
using System.Configuration;

namespace A1
{
    public partial class Form1 : Form
    {
        SqlConnection connection;
        SqlDataAdapter dataAdapterManufacturers;
        SqlDataAdapter dataAdapterTeams;
        DataSet dataSet;
        SqlCommandBuilder commandBuilder;

        string parentQuery;
        string childQuery;
        string parentTableName;
        string childTableName;
        string parentPrimaryKey;
        string childForeignKey;

        public Form1()
        {
            InitializeComponent();
            LoadSettings();
            FillData();
        }
        void LoadSettings()
        {
            parentQuery = ConfigurationManager.AppSettings["ParentQuery"];
            childQuery = ConfigurationManager.AppSettings["ChildQuery"];
            parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
            childTableName = ConfigurationManager.AppSettings["ChildTableName"];
            parentPrimaryKey = ConfigurationManager.AppSettings["ParentPrimaryKey"];
            childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            try
            {
                dataAdapterTeams.Update(dataSet, childTableName);
                MessageBox.Show("Changes were saved successfully.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        void FillData()
        {
            try
            {
                connection = new SqlConnection(getConStirng());

                dataAdapterManufacturers = new SqlDataAdapter(parentQuery, connection);
                dataAdapterTeams = new SqlDataAdapter(childQuery, connection);

                dataSet = new DataSet();
                dataAdapterManufacturers.Fill(dataSet, parentTableName);
                dataAdapterTeams.Fill(dataSet, childTableName);

                commandBuilder = new SqlCommandBuilder(dataAdapterTeams);

                dataSet.Relations.Add(
                    new DataRelation(
                        "ParentChildRelation",
                        dataSet.Tables[parentTableName].Columns[parentPrimaryKey],
                        dataSet.Tables[childTableName].Columns[childForeignKey]
                    )
                );

                ManufacturersTable.DataSource = dataSet.Tables[parentTableName];
                ProductsTable.DataSource = dataSet.Tables[parentTableName];
                ProductsTable.DataMember = "ParentChildRelation";

                commandBuilder.GetUpdateCommand();
                commandBuilder.GetDeleteCommand();
                commandBuilder.GetInsertCommand();
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        //get connection string from app.config
        string getConStirng()
        {
            return "Data Source = Birou; Initial Catalog = Practic; Integrated Security = True";
        }
    }
}
