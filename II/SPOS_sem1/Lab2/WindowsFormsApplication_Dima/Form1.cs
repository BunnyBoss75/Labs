using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication_Dima
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            timer1.Interval = 30;
            timer1.Start();
            Thread Thread1 = new Thread(Method);
            Thread Thread2 = new Thread(Method1);
            Thread1.Start();
            Thread2.Start();        }
        void Method()
        {
            int thousand = 1000;
            int[,] Matrix = new int[thousand, thousand];
            int[] Vector = new int[thousand];
            int[] Result = new int[thousand];
            Random rand = new Random();
            for (int i = 0; i < thousand; i++)
            {
                Vector[i] = rand.Next(-1, 2);
                for (int j = 0; j < thousand; j++)
                {
                   Matrix[i, j] = rand.Next(-1,2);
                }
            }
            TimeSpan TimeSpan1 = new TimeSpan();
            Stopwatch Stopwatch1 = new Stopwatch();
            for (int x = 0; x < 200; x++)
            {
                Stopwatch1.Start();
                for (int i = 0; i < thousand; i++)
                {
                    Result[i] = 0;
                    for (int j = 0; j < thousand; j++)
                    {
                        Result[i] += Matrix[i, j] * Vector[j];
                    }
                }
                Stopwatch1.Stop();
                TimeSpan1 = Stopwatch1.Elapsed;
                Action Action1 = () => richTextBox1.Text += ("M * V = " + TimeSpan1.Milliseconds + "ms   ");
                Invoke(Action1);
                Stopwatch1.Reset();
                Stopwatch1.Start();
                for (int i = 0; i < thousand; i++)
                {
                    Result[i] = 0;
                    for (int j = 0; j < thousand; j++)
                    {
                        Result[i] += Vector[j] * Matrix[j, i];
                    }
                }
                Stopwatch1.Stop();
                TimeSpan1 = Stopwatch1.Elapsed;
                Action1 = () => richTextBox1.Text += ("V * M = " + TimeSpan1.Milliseconds + "ms" + Environment.NewLine);
                Invoke(Action1);
            }
        }

        void Method1()
        {
            int thousand = 1000;
            int[,] Matrix = new int[thousand, thousand];
            int[] Vector = new int[thousand];
            int[] Result = new int[thousand];
            Random rand = new Random();
            for (int i = 0; i < thousand; i++)
            {
                Vector[i] = rand.Next(-1, 2);
                for (int j = 0; j < thousand; j++)
                {
                    Matrix[i, j] = rand.Next(-1, 2);
                }
            }
            TimeSpan TimeSpan1 = new TimeSpan();
            Stopwatch Stopwatch1 = new Stopwatch();
            for (int x = 0; x < 200; x++)
            {
                Stopwatch1.Start();
                for (int i = 0; i < thousand; i++)
                {
                    Result[i] = 0;
                    for (int j = 0; j < thousand; j++)
                    {
                        Result[i] += Matrix[i, j] * Vector[j];
                    }
                }
                Stopwatch1.Stop();
                TimeSpan1 = Stopwatch1.Elapsed;
                Action Action1 = () => richTextBox2.Text += ("M * V = " + TimeSpan1.Milliseconds + "ms   ");
                Invoke(Action1);
                Stopwatch1.Reset();
                Stopwatch1.Start();
                for (int i = 0; i < thousand; i++)
                {
                    Result[i] = 0;
                    for (int j = 0; j < thousand; j++)
                    {
                        Result[i] += Vector[j] * Matrix[j, i];
                    }
                }
                Stopwatch1.Stop();
                TimeSpan1 = Stopwatch1.Elapsed;
                Action1 = () => richTextBox2.Text += ("V * M = " + TimeSpan1.Milliseconds + "ms" + Environment.NewLine);
                Invoke(Action1);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        int ii = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            ii++;
            label2.Text = ii.ToString();
        }
    }
}
