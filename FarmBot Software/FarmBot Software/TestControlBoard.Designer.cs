namespace FarmBot_Software
{
    partial class TestControlBoard
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
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.refresh = new System.Windows.Forms.Label();
            this.lb_ComState = new System.Windows.Forms.Label();
            this.cb_COM = new System.Windows.Forms.ComboBox();
            this.bt_connect = new System.Windows.Forms.Button();
            this.Port1 = new System.IO.Ports.SerialPort(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.tbX = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.tbY = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.tbZ = new System.Windows.Forms.TextBox();
            this.btCloseForm = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.groupBox1.Controls.Add(this.refresh);
            this.groupBox1.Controls.Add(this.lb_ComState);
            this.groupBox1.Controls.Add(this.cb_COM);
            this.groupBox1.Controls.Add(this.bt_connect);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.ForeColor = System.Drawing.Color.White;
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(212, 100);
            this.groupBox1.TabIndex = 27;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Serial Port";
            // 
            // refresh
            // 
            this.refresh.AutoSize = true;
            this.refresh.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.refresh.ForeColor = System.Drawing.Color.White;
            this.refresh.Location = new System.Drawing.Point(14, 21);
            this.refresh.Name = "refresh";
            this.refresh.Size = new System.Drawing.Size(65, 17);
            this.refresh.TabIndex = 25;
            this.refresh.Text = "Refresh";
            this.refresh.Click += new System.EventHandler(this.refresh_Click);
            // 
            // lb_ComState
            // 
            this.lb_ComState.AutoSize = true;
            this.lb_ComState.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_ComState.ForeColor = System.Drawing.Color.White;
            this.lb_ComState.Location = new System.Drawing.Point(28, 67);
            this.lb_ComState.Name = "lb_ComState";
            this.lb_ComState.Size = new System.Drawing.Size(108, 17);
            this.lb_ComState.TabIndex = 24;
            this.lb_ComState.Text = "Disconnect ...";
            // 
            // cb_COM
            // 
            this.cb_COM.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cb_COM.FormattingEnabled = true;
            this.cb_COM.Location = new System.Drawing.Point(17, 42);
            this.cb_COM.Name = "cb_COM";
            this.cb_COM.Size = new System.Drawing.Size(82, 24);
            this.cb_COM.TabIndex = 23;
            // 
            // bt_connect
            // 
            this.bt_connect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(199)))), ((int)(((byte)(124)))));
            this.bt_connect.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.bt_connect.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_connect.ForeColor = System.Drawing.Color.White;
            this.bt_connect.Location = new System.Drawing.Point(115, 38);
            this.bt_connect.Name = "bt_connect";
            this.bt_connect.Size = new System.Drawing.Size(91, 27);
            this.bt_connect.TabIndex = 22;
            this.bt_connect.Text = "Kết nối";
            this.bt_connect.UseVisualStyleBackColor = false;
            this.bt_connect.Click += new System.EventHandler(this.bt_connect_Click);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(199)))), ((int)(((byte)(124)))));
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(106, 141);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(53, 23);
            this.button1.TabIndex = 28;
            this.button1.Text = "X";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.X_Click);
            // 
            // tbX
            // 
            this.tbX.Location = new System.Drawing.Point(29, 144);
            this.tbX.Name = "tbX";
            this.tbX.Size = new System.Drawing.Size(53, 20);
            this.tbX.TabIndex = 29;
            this.tbX.KeyDown += new System.Windows.Forms.KeyEventHandler(this.XPressEnter);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(199)))), ((int)(((byte)(124)))));
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(106, 180);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(53, 23);
            this.button2.TabIndex = 28;
            this.button2.Text = "Y";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.Y_Click);
            // 
            // tbY
            // 
            this.tbY.Location = new System.Drawing.Point(29, 183);
            this.tbY.Name = "tbY";
            this.tbY.Size = new System.Drawing.Size(53, 20);
            this.tbY.TabIndex = 29;
            this.tbY.KeyDown += new System.Windows.Forms.KeyEventHandler(this.YPressEnter);
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(199)))), ((int)(((byte)(124)))));
            this.button3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button3.ForeColor = System.Drawing.Color.White;
            this.button3.Location = new System.Drawing.Point(106, 218);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(53, 23);
            this.button3.TabIndex = 28;
            this.button3.Text = "Z";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += new System.EventHandler(this.Z_Click);
            // 
            // tbZ
            // 
            this.tbZ.Location = new System.Drawing.Point(29, 221);
            this.tbZ.Name = "tbZ";
            this.tbZ.Size = new System.Drawing.Size(53, 20);
            this.tbZ.TabIndex = 29;
            this.tbZ.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ZPressEnter);
            // 
            // btCloseForm
            // 
            this.btCloseForm.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(254)))), ((int)(((byte)(87)))), ((int)(((byte)(71)))));
            this.btCloseForm.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btCloseForm.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btCloseForm.ForeColor = System.Drawing.Color.White;
            this.btCloseForm.Location = new System.Drawing.Point(242, 13);
            this.btCloseForm.Name = "btCloseForm";
            this.btCloseForm.Size = new System.Drawing.Size(30, 23);
            this.btCloseForm.TabIndex = 30;
            this.btCloseForm.Text = "X";
            this.btCloseForm.UseVisualStyleBackColor = false;
            this.btCloseForm.Click += new System.EventHandler(this.btCloseForm_Click);
            // 
            // TestControlBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.btCloseForm);
            this.Controls.Add(this.tbZ);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.tbY);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.tbX);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "TestControlBoard";
            this.Text = "Test Control Board";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TestControlBoard_MouseDown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label refresh;
        private System.Windows.Forms.Label lb_ComState;
        private System.Windows.Forms.ComboBox cb_COM;
        private System.Windows.Forms.Button bt_connect;
        private System.IO.Ports.SerialPort Port1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox tbX;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox tbY;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox tbZ;
        private System.Windows.Forms.Button btCloseForm;
    }
}

