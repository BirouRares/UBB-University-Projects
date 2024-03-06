
namespace TankTrouble
{
    partial class Menu
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Menu));
            this.START = new System.Windows.Forms.Label();
            this.EXIT = new System.Windows.Forms.Label();
            this.CONTROLES = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // START
            // 
            this.START.AutoSize = true;
            this.START.BackColor = System.Drawing.Color.Transparent;
            this.START.Font = new System.Drawing.Font("Mongolian Baiti", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.START.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.START.Location = new System.Drawing.Point(527, 143);
            this.START.MinimumSize = new System.Drawing.Size(171, 50);
            this.START.Name = "START";
            this.START.Size = new System.Drawing.Size(171, 50);
            this.START.TabIndex = 0;
            this.START.Text = "START";
            this.START.Click += new System.EventHandler(this.START_Click);
            // 
            // EXIT
            // 
            this.EXIT.AutoSize = true;
            this.EXIT.BackColor = System.Drawing.Color.Transparent;
            this.EXIT.Font = new System.Drawing.Font("Mongolian Baiti", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EXIT.Location = new System.Drawing.Point(933, 143);
            this.EXIT.MinimumSize = new System.Drawing.Size(171, 70);
            this.EXIT.Name = "EXIT";
            this.EXIT.Size = new System.Drawing.Size(171, 70);
            this.EXIT.TabIndex = 1;
            this.EXIT.Text = "EXIT";
            this.EXIT.Click += new System.EventHandler(this.EXIT_Click);
            // 
            // CONTROLES
            // 
            this.CONTROLES.BackColor = System.Drawing.Color.Transparent;
            this.CONTROLES.Font = new System.Drawing.Font("Mongolian Baiti", 25.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CONTROLES.Location = new System.Drawing.Point(69, 143);
            this.CONTROLES.MinimumSize = new System.Drawing.Size(171, 70);
            this.CONTROLES.Name = "CONTROLES";
            this.CONTROLES.Size = new System.Drawing.Size(293, 70);
            this.CONTROLES.TabIndex = 0;
            this.CONTROLES.Text = "CONTROLS";
            this.CONTROLES.Click += new System.EventHandler(this.CONTROLES_Click);
            // 
            // Menu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1176, 668);
            this.Controls.Add(this.CONTROLES);
            this.Controls.Add(this.EXIT);
            this.Controls.Add(this.START);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1194, 715);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(1194, 715);
            this.Name = "Menu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Menu";
            this.Load += new System.EventHandler(this.Menu_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Menu_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label START;
        private System.Windows.Forms.Label EXIT;
        private System.Windows.Forms.Label CONTROLES;
    }
}

