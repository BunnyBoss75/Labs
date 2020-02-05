namespace WindowsFormsApp2
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.Generation = new System.Windows.Forms.Button();
            this.textBox_n = new System.Windows.Forms.TextBox();
            this.WIN = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label_title = new System.Windows.Forms.Label();
            this.textBox_Start = new System.Windows.Forms.TextBox();
            this.textBox_Finish = new System.Windows.Forms.TextBox();
            this.label_n = new System.Windows.Forms.Label();
            this.label_Start = new System.Windows.Forms.Label();
            this.label_Finish = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label_Write = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // Generation
            // 
            this.Generation.Location = new System.Drawing.Point(6, 107);
            this.Generation.Name = "Generation";
            this.Generation.Size = new System.Drawing.Size(100, 23);
            this.Generation.TabIndex = 0;
            this.Generation.Text = "Generation";
            this.Generation.UseVisualStyleBackColor = true;
            this.Generation.Click += new System.EventHandler(this.Generation_ckick);
            // 
            // textBox_n
            // 
            this.textBox_n.Location = new System.Drawing.Point(99, 19);
            this.textBox_n.Name = "textBox_n";
            this.textBox_n.Size = new System.Drawing.Size(78, 20);
            this.textBox_n.TabIndex = 1;
            // 
            // WIN
            // 
            this.WIN.Location = new System.Drawing.Point(112, 107);
            this.WIN.Name = "WIN";
            this.WIN.Size = new System.Drawing.Size(100, 23);
            this.WIN.TabIndex = 2;
            this.WIN.Text = "WIN";
            this.WIN.UseVisualStyleBackColor = true;
            this.WIN.Click += new System.EventHandler(this.WIN_click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 23);
            this.label1.TabIndex = 0;
            // 
            // label_title
            // 
            this.label_title.AutoSize = true;
            this.label_title.Location = new System.Drawing.Point(377, 9);
            this.label_title.Name = "label_title";
            this.label_title.Size = new System.Drawing.Size(35, 13);
            this.label_title.TabIndex = 3;
            this.label_title.Text = "label2";
            // 
            // textBox_Start
            // 
            this.textBox_Start.Location = new System.Drawing.Point(99, 45);
            this.textBox_Start.Name = "textBox_Start";
            this.textBox_Start.Size = new System.Drawing.Size(78, 20);
            this.textBox_Start.TabIndex = 4;
            // 
            // textBox_Finish
            // 
            this.textBox_Finish.Location = new System.Drawing.Point(99, 71);
            this.textBox_Finish.Name = "textBox_Finish";
            this.textBox_Finish.Size = new System.Drawing.Size(78, 20);
            this.textBox_Finish.TabIndex = 5;
            // 
            // label_n
            // 
            this.label_n.AutoSize = true;
            this.label_n.Location = new System.Drawing.Point(6, 26);
            this.label_n.Name = "label_n";
            this.label_n.Size = new System.Drawing.Size(41, 13);
            this.label_n.TabIndex = 6;
            this.label_n.Text = "Enter n";
            // 
            // label_Start
            // 
            this.label_Start.AutoSize = true;
            this.label_Start.Location = new System.Drawing.Point(6, 52);
            this.label_Start.Name = "label_Start";
            this.label_Start.Size = new System.Drawing.Size(57, 13);
            this.label_Start.TabIndex = 7;
            this.label_Start.Text = "Enter Start";
            // 
            // label_Finish
            // 
            this.label_Finish.AutoSize = true;
            this.label_Finish.Location = new System.Drawing.Point(6, 78);
            this.label_Finish.Name = "label_Finish";
            this.label_Finish.Size = new System.Drawing.Size(62, 13);
            this.label_Finish.TabIndex = 8;
            this.label_Finish.Text = "Enter Finish";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.label_n);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.textBox_Finish);
            this.groupBox1.Controls.Add(this.label_Finish);
            this.groupBox1.Controls.Add(this.WIN);
            this.groupBox1.Controls.Add(this.textBox_Start);
            this.groupBox1.Controls.Add(this.Generation);
            this.groupBox1.Controls.Add(this.textBox_n);
            this.groupBox1.Controls.Add(this.label_Start);
            this.groupBox1.Location = new System.Drawing.Point(12, 30);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(232, 167);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(183, 71);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(43, 23);
            this.button3.TabIndex = 13;
            this.button3.Text = "Rand";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Rand_Finish);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(183, 45);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(43, 23);
            this.button2.TabIndex = 12;
            this.button2.Text = "Rand";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Rand_Start);
            // 
            // label_Write
            // 
            this.label_Write.AutoSize = true;
            this.label_Write.Location = new System.Drawing.Point(15, 228);
            this.label_Write.Name = "label_Write";
            this.label_Write.Size = new System.Drawing.Size(38, 13);
            this.label_Write.TabIndex = 10;
            this.label_Write.Text = "Ready";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(195, 49);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(43, 23);
            this.button1.TabIndex = 11;
            this.button1.Text = "Rand";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Rand_n);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(250, 30);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(517, 509);
            this.pictureBox1.TabIndex = 12;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(779, 551);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label_Write);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label_title);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Generation;
        private System.Windows.Forms.TextBox textBox_n;
        private System.Windows.Forms.Button WIN;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_title;
        private System.Windows.Forms.TextBox textBox_Start;
        private System.Windows.Forms.TextBox textBox_Finish;
        private System.Windows.Forms.Label label_n;
        private System.Windows.Forms.Label label_Start;
        private System.Windows.Forms.Label label_Finish;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label_Write;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

