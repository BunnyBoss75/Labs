using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int n, i, j, Start, Finish, flag_1, flag_2 = 0;
        int[,] A;
        int[,] B;
        float[,] C;
        double angle;
        Random r = new Random();
        Label[] L;
        private void Rand_n(object sender, EventArgs e)
        {
            textBox_n.Text = Convert.ToString(r.Next(2, 16));
        }
        private void Rand_Start(object sender, EventArgs e)
        {
            if (textBox_n.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter the number of vertices";
                return;
            }
            n = Convert.ToInt32(textBox_n.Text);
            textBox_Start.Text = Convert.ToString(r.Next(1, n + 1));
        }
        private void Rand_Finish(object sender, EventArgs e)
        {
            if (textBox_n.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter the number of vertices";
                return;
            }
            n = Convert.ToInt32(textBox_n.Text);
            if (textBox_Start.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter Start";
                return;
            }
            Start = Convert.ToInt32(textBox_Start.Text) - 1;
            while (true)
            {
                i = r.Next(0, n);
                if (i != Start)
                {
                    break;
                }
            }
            textBox_Finish.Text = Convert.ToString(i + 1);
        }
        private void draw()
        {
            pictureBox1.Controls.Clear();
            Graphics g = pictureBox1.CreateGraphics();
            g.Clear(Color.White);
            Pen p = new Pen(Color.Black, 0.1F);
            SolidBrush q = new SolidBrush(Color.Gray);
            SolidBrush t = new SolidBrush(Color.Black);
            Font f = new Font("Arial", 11.0F);
            Label[] L = new Label[n*n];
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    if (j > i & A[i, j] > 0)
                    {
                        g.DrawLine(p, C[0, i], C[1, i], C[0, j], C[1, j]);
                    }
                }
            }
            if (flag_1 == 1)
            {
                p.Color = Color.Green;
                p.Width = 5;
                int now = Finish, next;
                while (now != Start)
                {
                    next = B[2, now];
                    g.DrawLine(p, C[0, now], C[1, now], C[0, next], C[1, next]);
                    now = next;
                }
            }
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    if (A[i, j] > 0)
                    {
                        L[i] = new Label();
                        L[i].Location = new Point(Convert.ToInt32(((C[0, i] + C[0, j]) / 2) - 8), Convert.ToInt32(((C[1, i] + C[1, j]) / 2) - 8));
                        L[i].Text = Convert.ToString(A[i, j]);
                        L[i].Height = 15;
                        L[i].Width = 15;
                        pictureBox1.Controls.Add(L[i]);
                    }
                }
            }
            for (i = 0; i < n; i++)
            {
                if (i == Start)
                {
                    q.Color = Color.DarkBlue;
                }
                if (i == Finish)
                {
                    q.Color = Color.Red;
                }
                g.FillEllipse(q, C[0, i] - 10, C[1, i] - 10, 20, 20);
                q.Color = Color.Gray;
            }
            for (i = 0; i < n; i++)
            {
                if (B[0, i] == Int32.MaxValue)
                {
                    g.DrawString("inf", f, t, C[0, i] - 9, C[1, i] - 8);
                }
                else
                {
                    if (B[0, i] < 10)
                    {
                        g.DrawString(Convert.ToString(B[0, i]), f, t, C[0, i] - 7, C[1, i] - 8);
                    }
                    else
                    {
                        g.DrawString(Convert.ToString(B[0, i]), f, t, C[0, i] - 10, C[1, i] - 8);
                    }
                }
            }
        }
        private void B_Generation ()
        {
            for (i = 0; i < n; i++)
            {
                B[0, i] = Int32.MaxValue;
                B[1, i] = 1;
                B[2, i] = -1;
            }
        }
        private void Generation_ckick(object sender, EventArgs e)
        {
            if (textBox_n.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter the number of vertices";
                return;
            }
            n = Convert.ToInt32(textBox_n.Text);
            if (n < 2)
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter correct n";
                return;
            }
            flag_1 = 0;
            Start = -1;
            Finish = -1;
            angle = 360.0 / n;
            A = new int[n, n];
            B = new int[3, n];
            C = new float[2, n];
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    A[i, j] = -1;
                    if ((r.Next(0, 3) % 4) == 0 & j > i)
                    {
                        A[i, j] = r.Next(1, 10);
                    }
                }
            }
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    if (i > j)
                    {
                        A[i, j] = A[j, i];
                    }
                }
            }
            for (i = 0; i < n; i++)
            {
                C[0, i] = (float)(250 + 240 * Math.Sin(( i * angle * 3.14 / 180)));
                C[1, i] = (float)(250 + 240 * Math.Sin(((i * angle) - 90) * 3.14 / 180));
            }
            B_Generation();
            draw();
            label_Write.ForeColor = Color.Green;
            label_Write.Text = "Graph is ready";
            flag_2 = 1;
        }
        private void WIN_click(object sender, EventArgs e)
        {
            if (textBox_Start.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter Start";
                return;
            }
            if (textBox_Finish.Text == "")
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter Finish";
                return;
            }
            Start = Convert.ToInt32(textBox_Start.Text) - 1;
            Finish = Convert.ToInt32(textBox_Finish.Text) - 1;
            if (flag_2 == 0 | n != Convert.ToInt32(textBox_n.Text))
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Please generate";
                return;
            }
            if (Start > n - 1 | Start < 0)
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter correct Start";
                return;
            }
            if (Finish > n - 1 | Finish < 0)
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Enter correct Finish";
                return;
            }
            if (Finish == Start)
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "Finish can not be equal to the Start";
                return;
            }
            B_Generation();
            while (true)
            {
                B[0, Start] = 0;
                int min = Int32.MaxValue, num_min = 0;
                for (i = 0; i < n; i++)
                {
                    if (B[0, i] < min & B[1, i] == 1)
                    {
                        min = B[0, i];
                        num_min = i;
                    }
                }
                if (min == Int32.MaxValue)
                {
                    break;
                }
                for (i = 0; i < n; i++)
                {
                    if (A[num_min, i] > 0 & B[0, i] > B[0, num_min] + A[num_min, i])
                    {
                        B[0, i] = B[0, num_min] + A[num_min, i];
                        B[2, i] = num_min;
                    }
                }
                B[1, num_min] = 0;
            }
            if (B[0, Finish] == Int32.MaxValue)
            {
                label_Write.ForeColor = Color.Red;
                label_Write.Text = "The path is not found";
                return;
            }
            flag_1 = 1;
            draw();
            label_Write.ForeColor = Color.Green;
            label_Write.Text = "The path is found perfectly";
        }
    }
}