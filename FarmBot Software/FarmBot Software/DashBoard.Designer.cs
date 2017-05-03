namespace FarmBot_Software
{
    partial class DashBoard
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
            this.btTestControlBoard = new System.Windows.Forms.Button();
            this.btExit = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.pbGarden = new System.Windows.Forms.PictureBox();
            this.pbEndActuator = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pbGarden)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbEndActuator)).BeginInit();
            this.SuspendLayout();
            // 
            // btTestControlBoard
            // 
            this.btTestControlBoard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(168)))), ((int)(((byte)(171)))));
            this.btTestControlBoard.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btTestControlBoard.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btTestControlBoard.ForeColor = System.Drawing.Color.White;
            this.btTestControlBoard.Location = new System.Drawing.Point(12, 21);
            this.btTestControlBoard.Name = "btTestControlBoard";
            this.btTestControlBoard.Size = new System.Drawing.Size(140, 30);
            this.btTestControlBoard.TabIndex = 0;
            this.btTestControlBoard.Text = "Test Control Board";
            this.btTestControlBoard.UseVisualStyleBackColor = false;
            this.btTestControlBoard.Click += new System.EventHandler(this.btTestControlBoard_Click);
            // 
            // btExit
            // 
            this.btExit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(76)))), ((int)(((byte)(101)))));
            this.btExit.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btExit.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btExit.ForeColor = System.Drawing.Color.White;
            this.btExit.Location = new System.Drawing.Point(700, 12);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(34, 26);
            this.btExit.TabIndex = 1;
            this.btExit.Text = "X";
            this.btExit.UseVisualStyleBackColor = false;
            this.btExit.Click += new System.EventHandler(this.btExit_Click);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(52)))), ((int)(((byte)(104)))), ((int)(((byte)(175)))));
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(77, 66);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 48);
            this.button1.TabIndex = 2;
            this.button1.Text = "Connect";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(12, 68);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 45);
            this.label1.TabIndex = 3;
            this.label1.Text = "FarmBot\r\n Is not \r\nAvailable !";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(12, 170);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(140, 21);
            this.comboBox1.TabIndex = 4;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 132);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(140, 20);
            this.textBox1.TabIndex = 5;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(168, 132);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(52, 20);
            this.button2.TabIndex = 6;
            this.button2.Text = "Add";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button3.ForeColor = System.Drawing.Color.White;
            this.button3.Location = new System.Drawing.Point(168, 169);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(52, 20);
            this.button3.TabIndex = 6;
            this.button3.Text = "Load";
            this.button3.UseVisualStyleBackColor = false;
            // 
            // pbGarden
            // 
            this.pbGarden.BackColor = System.Drawing.Color.Transparent;
            this.pbGarden.ErrorImage = null;
            this.pbGarden.Image = global::FarmBot_Software.Properties.Resources.farmsize1;
            this.pbGarden.InitialImage = null;
            this.pbGarden.Location = new System.Drawing.Point(12, 208);
            this.pbGarden.Name = "pbGarden";
            this.pbGarden.Size = new System.Drawing.Size(180, 480);
            this.pbGarden.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbGarden.TabIndex = 7;
            this.pbGarden.TabStop = false;
            // 
            // pbEndActuator
            // 
            this.pbEndActuator.BackColor = System.Drawing.Color.Transparent;
            this.pbEndActuator.Image = global::FarmBot_Software.Properties.Resources.endDevice;
            this.pbEndActuator.Location = new System.Drawing.Point(53, 247);
            this.pbEndActuator.Name = "pbEndActuator";
            this.pbEndActuator.Size = new System.Drawing.Size(40, 40);
            this.pbEndActuator.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbEndActuator.TabIndex = 8;
            this.pbEndActuator.TabStop = false;
            this.pbEndActuator.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseDown);
            this.pbEndActuator.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseMove);
            // 
            // DashBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(31)))), ((int)(((byte)(37)))), ((int)(((byte)(61)))));
            this.ClientSize = new System.Drawing.Size(746, 704);
            this.Controls.Add(this.pbEndActuator);
            this.Controls.Add(this.pbGarden);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btExit);
            this.Controls.Add(this.btTestControlBoard);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "DashBoard";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DashBoard";
            this.Load += new System.EventHandler(this.DashBoard_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.DashBoard_MouseDown);
            ((System.ComponentModel.ISupportInitialize)(this.pbGarden)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbEndActuator)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btTestControlBoard;
        private System.Windows.Forms.Button btExit;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.PictureBox pbGarden;
        private System.Windows.Forms.PictureBox pbEndActuator;
    }
}

