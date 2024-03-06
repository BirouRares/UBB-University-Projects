using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TankTrouble
{
    public partial class Menu : Form
    {
        public Form BackToMainForm { get; set; }
        public Menu()
        {
            InitializeComponent();
        }

        private void START_Click(object sender, EventArgs e)
        {
            MAP1 frmGame = new MAP1();
            frmGame.BackToMainForm = this;
            frmGame.Show();
            this.Visible = false;
        }

        private void EXIT_Click(object sender, EventArgs e)
        {
            string message = "Are you sure you want to quit the game?";
            string title = "Quit Message Box";
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show(message, title, buttons);
            if (result == DialogResult.Yes)
                Application.Exit();
        }

        private void CONTROLES_Click(object sender, EventArgs e)
        {
            CONTROLS frmGame = new CONTROLS();
            frmGame.BackToMainForm = this;
            frmGame.Show();
            this.Visible = false;
        }

        private void Menu_Load(object sender, EventArgs e)
        {

        }

        private void Menu_KeyDown(object sender, KeyEventArgs e)
        {
            
        }
    }
}
