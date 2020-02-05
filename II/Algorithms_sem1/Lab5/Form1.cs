using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Algorytm_5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        class Point
        {
            public double x;
            public double y;
        }
        class Vectorchick
        {
            public static Vectorchick operator *(Vectorchick a, double b)
            {
                Vectorchick c = new Vectorchick();
                c.x = a.x * b;
                c.y = a.y * b;
                return c;
            }
            public static Vectorchick operator -(Vectorchick a, Vectorchick b)
            {
                Vectorchick c = new Vectorchick();
                c.x = a.x - b.x;
                c.y = a.y - b.y;
                return c;
            }
            public static Vectorchick operator +(Vectorchick a, Vectorchick b)
            {
                Vectorchick c = new Vectorchick();
                c.x = a.x + b.x;
                c.y = a.y + b.y;
                return c;
            }
            public double x;
            public double y;
        }
        class Ball
        {
            public Ball ()
            {
                Cordinates = new Point();
                topLeft = new Point();
                speed = new Vectorchick();
            }
            public Point Cordinates;
            public Vectorchick speed;
            public double radius;
            public Point topLeft;
            public void recalculateTopLeftCordinates ()
            {
                topLeft.x = Cordinates.x - radius;
                topLeft.y = Cordinates.y - radius;
            }
            public void verticalBorder ()
            {
                speed.x *= -1;
            }
            public void horizontalBorder()
            {
                speed.y *= -1;
            }
        }

        List<Ball> listBall = new List<Ball>();
        SolidBrush brushBall = new SolidBrush(Color.Blue);
        SolidBrush brushEraser = new SolidBrush(Color.White);
        Graphics graphics;
        int countTouch = 0;
        double time;
        int countTime = 0;

        private double culculateVector (Vectorchick vectorchick1)
        {
            return Math.Sqrt(Math.Pow(vectorchick1.x, 2) + Math.Pow(vectorchick1.y, 2));
        }

        private double cuclulateAngle(Vectorchick vectorchick1, Vectorchick vectorchick2)
        {
            double lengthVector1 = culculateVector(vectorchick1);
            double lengthVector2 = culculateVector(vectorchick2);
            double scalarЬultiplication = vectorchick1.x * vectorchick2.x + vectorchick1.y * vectorchick2.y;
            return Math.Acos(scalarЬultiplication / (lengthVector1 * lengthVector2));
        }

        private void draw ()
        {
            for (int i = 0; i < listBall.Count; i++)
            {
                listBall[i].recalculateTopLeftCordinates();
                graphics.FillEllipse(brushBall, (float)listBall[i].topLeft.x, (float)listBall[i].topLeft.y, (float)listBall[i].radius * 2, (float)listBall[i].radius * 2);
            }
        }

        private void erase()
        {
            for (int i = 0; i < listBall.Count; i++)
            {
                graphics.FillEllipse(brushEraser, (float)listBall[i].topLeft.x, (float)listBall[i].topLeft.y, (float)listBall[i].radius * 2, (float)listBall[i].radius * 2);
            }
        }

        private void changeCordinate()
        {
            for(int i = 0; i < listBall.Count; i++)
            {
                listBall[i].Cordinates.x += listBall[i].speed.x;
                listBall[i].Cordinates.y += listBall[i].speed.y;
            }
        }

        private void checkVerticalTouch()
        {
            for (int i = 0; i < listBall.Count; i++)
            {
                if((listBall[i].Cordinates.x - listBall[i].radius <= 0) || 
                   (listBall[i].Cordinates.x + listBall[i].radius >= pictureBox1.Width))
                {
                    listBall[i].verticalBorder();
                }
            }
        }

        private void checkHorizontalTouch()
        {
            for (int i = 0; i < listBall.Count; i++)
            {
                if ((listBall[i].Cordinates.y - listBall[i].radius <= 0) ||
                    (listBall[i].Cordinates.y + listBall[i].radius >= pictureBox1.Height))
                {
                    listBall[i].horizontalBorder();
                }
            }
        }

        private void checkTouch()
        {
            for (int i = 0; i < listBall.Count; i++)
            {
                for (int j = i + 1; j < listBall.Count; j++)
                { 
                    if (Math.Sqrt(Math.Pow(listBall[i].Cordinates.x - listBall[j].Cordinates.x, 2) + 
                                  Math.Pow(listBall[i].Cordinates.y - listBall[j].Cordinates.y, 2)) <=
                        listBall[i].radius + listBall[j].radius)
                    {
                        ballColision(i, j);
                        countTouch++;
                    }

                }
            }
        }

        private void ballColision(int i, int j)
        {
            Vectorchick centerVector = new Vectorchick();
            centerVector.x = listBall[j].Cordinates.x - listBall[i].Cordinates.x;
            centerVector.y = listBall[j].Cordinates.y - listBall[i].Cordinates.y;

            double AngleI = cuclulateAngle(centerVector, listBall[i].speed);
            double AngleJ = cuclulateAngle(centerVector, listBall[j].speed);
            double lengthCenterVector = culculateVector(centerVector);
            centerVector.x /= lengthCenterVector;
            centerVector.y /= lengthCenterVector;
            Vectorchick swapVectorI = new Vectorchick();
            Vectorchick swapVectorJ = new Vectorchick();
            swapVectorI = centerVector * culculateVector(listBall[i].speed) * Math.Cos(AngleI);
            swapVectorJ = centerVector * culculateVector(listBall[j].speed) * Math.Cos(AngleJ);
            listBall[i].speed = listBall[i].speed - swapVectorI + swapVectorJ;
            listBall[j].speed = listBall[j].speed - swapVectorJ + swapVectorI;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            textBox1.Text = "40";
            textBox2.Text = "2";
            textBox3.Text = "3";
            textBox4.Text = "137";
            textBox5.Text = "217";
            textBox6.Text = "20000";
            graphics = pictureBox1.CreateGraphics();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBall.Add(new Ball());
            listBall[listBall.Count - 1].radius = Convert.ToDouble(textBox1.Text);
            listBall[listBall.Count - 1].speed.y = Convert.ToDouble(textBox2.Text);
            listBall[listBall.Count - 1].speed.x = Convert.ToDouble(textBox3.Text);
            listBall[listBall.Count - 1].Cordinates.y = Convert.ToDouble(textBox4.Text);
            listBall[listBall.Count - 1].Cordinates.x = Convert.ToDouble(textBox5.Text);
            draw();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            countTime++;
            erase();
            changeCordinate();
            checkTouch();
            checkHorizontalTouch();
            checkVerticalTouch();
            draw();
            if (countTime >= time / 15)
            {
                timer1.Stop();
                label15.Text = countTouch.ToString();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            timer1.Start();
            time = Convert.ToInt32(textBox6.Text);
        }
    }
}
