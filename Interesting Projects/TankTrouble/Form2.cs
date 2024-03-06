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
    public partial class MAP1 : Form
    {
        int scorep = 0;
        int scoreq=0;
        Timer Clock;
        const int Interval = 15;
        int AUp = 0;
        int ADown = 0;
        int ARight = 0;
        int ALeft = 0;
        int W = 0;
        int A = 0;
        int S = 0;
        int D = 0;
        int Q = 0;
        int P = 0;
        bool w = false;
        bool a = false;
        bool s = false;
        bool d = false;
        bool aup = false;
        bool adown = false;
        bool aright = false;
        bool aleft = false;
        bool q = false;
        bool p = false;
        bool shotq = false;
        bool shotp = false;
        bool gameOver = false;
        public Form BackToMainForm { get; set; }
        public MAP1()
        {
            InitializeComponent();
            Initialize_Timer();
        }
        void Initialize_Timer()
        {
            Clock = new Timer();
            Clock.Interval = Interval;
            Clock.Tick += new System.EventHandler(this.ClockTick);
            Clock.Start();
        }
        void ClockTick(object sender, EventArgs e)
        {
            Main_Function();
        }
        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);
            if (e.KeyCode == Keys.W)
                w = true;
            if (e.KeyCode == Keys.A)
                a = true;
            if (e.KeyCode == Keys.S)
                s = true;
            if (e.KeyCode == Keys.D)
                d = true;
            if (e.KeyCode == Keys.Up)
                aup = true;
            if (e.KeyCode == Keys.Down)
                adown = true;
            if (e.KeyCode == Keys.Right)
                aright = true;
            if (e.KeyCode == Keys.Left)
                aleft = true;
            if (e.KeyCode == Keys.Q)
                q = true;
            if (e.KeyCode == Keys.P)
                p = true;
        }
        protected override void OnKeyUp(KeyEventArgs e)
        {
            base.OnKeyUp(e);
            if (e.KeyCode == Keys.W)
                w = false;
            if (e.KeyCode == Keys.A)
                a = false;
            if (e.KeyCode == Keys.S)
                s = false;
            if (e.KeyCode == Keys.D)
                d = false;
            if (e.KeyCode == Keys.Up)
                aup = false;
            if (e.KeyCode == Keys.Down)
                adown = false;
            if (e.KeyCode == Keys.Right)
                aright = false;
            if (e.KeyCode == Keys.Left)
                aleft = false;
            if (e.KeyCode == Keys.Q)
                q = false;
            if (e.KeyCode == Keys.P)
                p = false;
            if (shotp == true)
                shotp = false;
            if (shotq == true)
                shotq = false;
            if(e.KeyCode==Keys.Enter && gameOver==true)
            {
                RestartGame();
            }
        }
        void Main_Function()
        {

            int speed = 3;
            if (w && (pictureBox1.Top - 7) > 0)
            {
                W++;
                pictureBox1.Top -= speed;
            }  
            if (a && (pictureBox1.Left - 7) > 0)
            {
                A++;
                pictureBox1.Left -= speed;
            }
            if (s && (pictureBox1.Top + 7) < 190)
            {
                S++;
                pictureBox1.Top += speed;
            }
            if (d && (pictureBox1.Left + 20) < (this.Width - pictureBox1.Width))
            { 
                D++;
                pictureBox1.Left += speed;
            }
            if(aup && (pictureBox2.Top + 7) > 260)
            {
                AUp++;
                pictureBox2.Top -= speed;
            }
            if(adown && (pictureBox2.Top + 15) < 500)
            {
                ADown++;
                pictureBox2.Top += speed;
            }
            if(aright && (pictureBox2.Left + 20) < (this.Width - pictureBox2.Width))
            {
                ARight++;
                pictureBox2.Left += speed;
            }
            if(aleft && (pictureBox2.Left - 7 > 0))
            {
                ALeft++;
                pictureBox2.Left -= speed;
            }
            if(q && shotq==false)
            {
                MakeBulletq();
                shotq = true;
            }
            if(p && shotp == false)
            {
                MakeBulletp();
                shotp = true;
            }
            foreach(Control x in this.Controls)
            {
                if(x is PictureBox && (string)x.Tag== "bulletq")
                {
                    x.Top += 5;
                    if(x.Top<0)
                    {
                        RemoveBulletq(((PictureBox)x));
                    }
                    if(x.Top>600)
                    {
                        RemoveBulletq(((PictureBox)x));
                    }
                    if(pictureBox2.Bounds.IntersectsWith(x.Bounds))
                    {
                        RemoveBulletq(((PictureBox)x));
                        scoreq++;
                        GameOver();
                    }
                }
                if (x is PictureBox && (string)x.Tag == "bulletp")
                {
                    x.Top -= 5;
                    if (x.Top < 0)
                    {
                        RemoveBulletp(((PictureBox)x));
                    }
                    if (x.Top > 800)
                    {
                        RemoveBulletp(((PictureBox)x));
                    }
                    if (pictureBox1.Bounds.IntersectsWith(x.Bounds))
                    {
                        RemoveBulletp(((PictureBox)x));
                        scorep++;
                        GameOver();
                    }
                }
            }
            label1.Text = "" + scoreq;
            label2.Text = "" + scorep;
        }
        private void Form2_Load(object sender, EventArgs e)
        {

        }
        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
        int speed =9;
        private void MAP1_KeyDown(object sender, KeyEventArgs e)
        {

        }
        private void RestartGame()
        {
            foreach (Control x in this.Controls)
            {
                if (x is PictureBox && (string)x.Tag == "bulletq")
                {
                    x.Top = 7878787;
                }
                if (x is PictureBox && (string)x.Tag == "bulletp")
                {
                     x.Top = 7878787;
                }
            }
            shotp = false;
            shotq = false;
            gameOver = false;
            label1.Text = "" + scoreq;
            label2.Text = "" + scorep;
            pictureBox1.Top = 157;
            pictureBox1.Left = 448;
            pictureBox2.Top = 450;
            pictureBox2.Left = 448;

            Clock.Start();
        }
        private void GameOver()
        {
            Clock.Stop();
            label1.Text = "" + scoreq;
            label2.Text = "" + scorep;
            gameOver = true;
        }
        private void RemoveBulletp(PictureBox bulletp)
        {
            this.Controls.Remove(bulletp);
            bulletp.Dispose();
        }
        private void RemoveBulletq(PictureBox bulletq)
        {
            this.Controls.Remove(bulletq);
            bulletq.Dispose();
        }
        private void MakeBulletq()
        {
            PictureBox bulletq = new PictureBox();
            bulletq.BackColor = Color.Maroon;
            bulletq.Height = 10;
            bulletq.Width = 5;
            bulletq.Top = pictureBox1.Top + pictureBox1.Height;
            bulletq.Left = pictureBox1.Left + pictureBox1.Width / 2;
            bulletq.Tag = "bulletq";
            this.Controls.Add(bulletq);
        }
        private void MakeBulletp()
        {
            PictureBox bulletp = new PictureBox();
            bulletp.BackColor = Color.Maroon;
            bulletp.Height = 10;
            bulletp.Width = 5;
            bulletp.Top = pictureBox2.Top - pictureBox2.Height+50;
            bulletp.Left = pictureBox2.Left + pictureBox2.Width / 2;
            bulletp.Tag = "bulletp";
            this.Controls.Add(bulletp);
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

    }
}
