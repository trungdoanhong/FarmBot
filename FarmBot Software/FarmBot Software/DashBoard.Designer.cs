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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DashBoard));
            this.btTestControlBoard = new System.Windows.Forms.Button();
            this.btExit = new System.Windows.Forms.Button();
            this.btConnect = new System.Windows.Forms.Button();
            this.lbConnectState = new System.Windows.Forms.Label();
            this.cbSeasonName = new System.Windows.Forms.ComboBox();
            this.tbSeasonName = new System.Windows.Forms.TextBox();
            this.btAddSeason = new System.Windows.Forms.Button();
            this.btLoadSeason = new System.Windows.Forms.Button();
            this.pbGarden = new System.Windows.Forms.PictureBox();
            this.pbEndActuator = new System.Windows.Forms.PictureBox();
            this.lbX = new System.Windows.Forms.Label();
            this.lbY = new System.Windows.Forms.Label();
            this.btHome = new System.Windows.Forms.Button();
            this.btX = new System.Windows.Forms.Button();
            this.btY = new System.Windows.Forms.Button();
            this.btTree1 = new System.Windows.Forms.Button();
            this.btTree2 = new System.Windows.Forms.Button();
            this.btTree3 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tbTreeName = new System.Windows.Forms.TextBox();
            this.lbTreeName = new System.Windows.Forms.Label();
            this.pnTimeForWater = new System.Windows.Forms.Panel();
            this.tbMinuteWater = new System.Windows.Forms.TextBox();
            this.tbHourWater = new System.Windows.Forms.TextBox();
            this.lbTimeForWater1 = new System.Windows.Forms.Label();
            this.lbColon = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btAddTimeForWater = new System.Windows.Forms.Button();
            this.btDeleteTimeForWater1 = new System.Windows.Forms.Button();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tbTempForWater = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.tbHumiForFan = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.button9 = new System.Windows.Forms.Button();
            this.btUpload = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.lbDebug = new System.Windows.Forms.Label();
            this.btMinimize = new System.Windows.Forms.Button();
            this.panel6 = new System.Windows.Forms.Panel();
            this.label11 = new System.Windows.Forms.Label();
            this.rbNone = new System.Windows.Forms.RadioButton();
            this.rbTree1 = new System.Windows.Forms.RadioButton();
            this.rbTree2 = new System.Windows.Forms.RadioButton();
            this.rbTree3 = new System.Windows.Forms.RadioButton();
            this.btSave = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btDelete = new System.Windows.Forms.Button();
            this.FarmBotSerialPort = new System.IO.Ports.SerialPort(this.components);
            this.btZ = new System.Windows.Forms.Button();
            this.tbX = new System.Windows.Forms.TextBox();
            this.lbZ = new System.Windows.Forms.Label();
            this.tbY = new System.Windows.Forms.TextBox();
            this.tbZ = new System.Windows.Forms.TextBox();
            this.btPump = new System.Windows.Forms.Button();
            this.tbWaterSpendTime = new System.Windows.Forms.TextBox();
            this.cbFan = new System.Windows.Forms.CheckBox();
            this.cbLamp = new System.Windows.Forms.CheckBox();
            this.cbVaccum = new System.Windows.Forms.CheckBox();
            this.cbSoilSensor = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.panel8 = new System.Windows.Forms.Panel();
            this.tbHumiForMist = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pbGarden)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbEndActuator)).BeginInit();
            this.panel1.SuspendLayout();
            this.pnTimeForWater.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panel2.SuspendLayout();
            this.panel7.SuspendLayout();
            this.panel8.SuspendLayout();
            this.SuspendLayout();
            // 
            // btTestControlBoard
            // 
            this.btTestControlBoard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(168)))), ((int)(((byte)(171)))));
            this.btTestControlBoard.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btTestControlBoard.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btTestControlBoard.ForeColor = System.Drawing.Color.White;
            this.btTestControlBoard.Location = new System.Drawing.Point(27, 57);
            this.btTestControlBoard.Name = "btTestControlBoard";
            this.btTestControlBoard.Size = new System.Drawing.Size(152, 30);
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
            this.btExit.Location = new System.Drawing.Point(726, 4);
            this.btExit.Name = "btExit";
            this.btExit.Size = new System.Drawing.Size(34, 26);
            this.btExit.TabIndex = 1;
            this.btExit.Text = "X";
            this.btExit.UseVisualStyleBackColor = false;
            this.btExit.Click += new System.EventHandler(this.btExit_Click);
            // 
            // btConnect
            // 
            this.btConnect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(52)))), ((int)(((byte)(104)))), ((int)(((byte)(175)))));
            this.btConnect.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btConnect.ForeColor = System.Drawing.Color.White;
            this.btConnect.Location = new System.Drawing.Point(195, 57);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(86, 61);
            this.btConnect.TabIndex = 2;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = false;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // lbConnectState
            // 
            this.lbConnectState.AutoSize = true;
            this.lbConnectState.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.lbConnectState.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbConnectState.ForeColor = System.Drawing.Color.White;
            this.lbConnectState.Location = new System.Drawing.Point(28, 100);
            this.lbConnectState.Name = "lbConnectState";
            this.lbConnectState.Size = new System.Drawing.Size(144, 15);
            this.lbConnectState.TabIndex = 3;
            this.lbConnectState.Text = "FarmBot is not Available !";
            // 
            // cbSeasonName
            // 
            this.cbSeasonName.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbSeasonName.FormattingEnabled = true;
            this.cbSeasonName.Location = new System.Drawing.Point(27, 170);
            this.cbSeasonName.Name = "cbSeasonName";
            this.cbSeasonName.Size = new System.Drawing.Size(180, 32);
            this.cbSeasonName.TabIndex = 4;
            this.cbSeasonName.SelectedIndexChanged += new System.EventHandler(this.btLoadSeason_Click);
            // 
            // tbSeasonName
            // 
            this.tbSeasonName.Location = new System.Drawing.Point(96, 137);
            this.tbSeasonName.Name = "tbSeasonName";
            this.tbSeasonName.Size = new System.Drawing.Size(111, 20);
            this.tbSeasonName.TabIndex = 5;
            // 
            // btAddSeason
            // 
            this.btAddSeason.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btAddSeason.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btAddSeason.ForeColor = System.Drawing.Color.White;
            this.btAddSeason.Location = new System.Drawing.Point(221, 136);
            this.btAddSeason.Name = "btAddSeason";
            this.btAddSeason.Size = new System.Drawing.Size(60, 20);
            this.btAddSeason.TabIndex = 6;
            this.btAddSeason.Text = "Add";
            this.btAddSeason.UseVisualStyleBackColor = false;
            this.btAddSeason.Click += new System.EventHandler(this.btAddSeason_Click);
            // 
            // btLoadSeason
            // 
            this.btLoadSeason.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btLoadSeason.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btLoadSeason.ForeColor = System.Drawing.Color.White;
            this.btLoadSeason.Location = new System.Drawing.Point(221, 162);
            this.btLoadSeason.Name = "btLoadSeason";
            this.btLoadSeason.Size = new System.Drawing.Size(60, 21);
            this.btLoadSeason.TabIndex = 6;
            this.btLoadSeason.Text = "Load";
            this.btLoadSeason.UseVisualStyleBackColor = false;
            this.btLoadSeason.Click += new System.EventHandler(this.btLoadSeason_Click);
            // 
            // pbGarden
            // 
            this.pbGarden.BackColor = System.Drawing.Color.Transparent;
            this.pbGarden.ErrorImage = null;
            this.pbGarden.Image = global::FarmBot_Software.Properties.Resources.farmsize1;
            this.pbGarden.InitialImage = null;
            this.pbGarden.Location = new System.Drawing.Point(27, 213);
            this.pbGarden.Name = "pbGarden";
            this.pbGarden.Size = new System.Drawing.Size(180, 480);
            this.pbGarden.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbGarden.TabIndex = 7;
            this.pbGarden.TabStop = false;
            this.pbGarden.Click += new System.EventHandler(this.pbGarden_Click);
            // 
            // pbEndActuator
            // 
            this.pbEndActuator.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.pbEndActuator.Image = global::FarmBot_Software.Properties.Resources.endDevice;
            this.pbEndActuator.Location = new System.Drawing.Point(68, 252);
            this.pbEndActuator.Name = "pbEndActuator";
            this.pbEndActuator.Size = new System.Drawing.Size(40, 40);
            this.pbEndActuator.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbEndActuator.TabIndex = 8;
            this.pbEndActuator.TabStop = false;
            this.pbEndActuator.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseDown);
            this.pbEndActuator.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseMove);
            this.pbEndActuator.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseUp);
            // 
            // lbX
            // 
            this.lbX.AutoSize = true;
            this.lbX.ForeColor = System.Drawing.Color.White;
            this.lbX.Location = new System.Drawing.Point(221, 217);
            this.lbX.Name = "lbX";
            this.lbX.Size = new System.Drawing.Size(60, 13);
            this.lbX.TabIndex = 9;
            this.lbX.Text = "X : 100 mm";
            // 
            // lbY
            // 
            this.lbY.AutoSize = true;
            this.lbY.ForeColor = System.Drawing.Color.White;
            this.lbY.Location = new System.Drawing.Point(221, 234);
            this.lbY.Name = "lbY";
            this.lbY.Size = new System.Drawing.Size(60, 13);
            this.lbY.TabIndex = 9;
            this.lbY.Text = "Y : 100 mm";
            // 
            // btHome
            // 
            this.btHome.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btHome.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btHome.ForeColor = System.Drawing.Color.White;
            this.btHome.Location = new System.Drawing.Point(221, 272);
            this.btHome.Name = "btHome";
            this.btHome.Size = new System.Drawing.Size(60, 20);
            this.btHome.TabIndex = 6;
            this.btHome.Text = "Home";
            this.btHome.UseVisualStyleBackColor = false;
            this.btHome.Click += new System.EventHandler(this.btHome_Click);
            // 
            // btX
            // 
            this.btX.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btX.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btX.ForeColor = System.Drawing.Color.White;
            this.btX.Location = new System.Drawing.Point(256, 297);
            this.btX.Name = "btX";
            this.btX.Size = new System.Drawing.Size(25, 20);
            this.btX.TabIndex = 6;
            this.btX.Text = "X";
            this.btX.UseVisualStyleBackColor = false;
            this.btX.Click += new System.EventHandler(this.btX_Click);
            // 
            // btY
            // 
            this.btY.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btY.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btY.ForeColor = System.Drawing.Color.White;
            this.btY.Location = new System.Drawing.Point(256, 323);
            this.btY.Name = "btY";
            this.btY.Size = new System.Drawing.Size(25, 20);
            this.btY.TabIndex = 6;
            this.btY.Text = "Y";
            this.btY.UseVisualStyleBackColor = false;
            this.btY.Click += new System.EventHandler(this.btY_Click);
            // 
            // btTree1
            // 
            this.btTree1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(196)))), ((int)(((byte)(246)))));
            this.btTree1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btTree1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btTree1.ForeColor = System.Drawing.Color.White;
            this.btTree1.Location = new System.Drawing.Point(319, 57);
            this.btTree1.Name = "btTree1";
            this.btTree1.Size = new System.Drawing.Size(89, 79);
            this.btTree1.TabIndex = 2;
            this.btTree1.Text = "Tree 1";
            this.btTree1.UseVisualStyleBackColor = false;
            this.btTree1.Click += new System.EventHandler(this.btTree1_Click);
            // 
            // btTree2
            // 
            this.btTree2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(76)))), ((int)(((byte)(101)))));
            this.btTree2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btTree2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btTree2.ForeColor = System.Drawing.Color.White;
            this.btTree2.Location = new System.Drawing.Point(319, 175);
            this.btTree2.Name = "btTree2";
            this.btTree2.Size = new System.Drawing.Size(89, 79);
            this.btTree2.TabIndex = 2;
            this.btTree2.Text = "Tree 2";
            this.btTree2.UseVisualStyleBackColor = false;
            this.btTree2.Click += new System.EventHandler(this.btTree2_Click);
            // 
            // btTree3
            // 
            this.btTree3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(252)))), ((int)(((byte)(177)))), ((int)(((byte)(80)))));
            this.btTree3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btTree3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btTree3.ForeColor = System.Drawing.Color.White;
            this.btTree3.Location = new System.Drawing.Point(319, 296);
            this.btTree3.Name = "btTree3";
            this.btTree3.Size = new System.Drawing.Size(89, 79);
            this.btTree3.TabIndex = 2;
            this.btTree3.Text = "Tree 3";
            this.btTree3.UseVisualStyleBackColor = false;
            this.btTree3.Click += new System.EventHandler(this.btTree3_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel1.Controls.Add(this.tbTreeName);
            this.panel1.Controls.Add(this.lbTreeName);
            this.panel1.Location = new System.Drawing.Point(465, 56);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(269, 56);
            this.panel1.TabIndex = 10;
            // 
            // tbTreeName
            // 
            this.tbTreeName.Location = new System.Drawing.Point(98, 20);
            this.tbTreeName.Name = "tbTreeName";
            this.tbTreeName.Size = new System.Drawing.Size(157, 20);
            this.tbTreeName.TabIndex = 1;
            this.tbTreeName.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbTreeName_KeyDown);
            // 
            // lbTreeName
            // 
            this.lbTreeName.AutoSize = true;
            this.lbTreeName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbTreeName.ForeColor = System.Drawing.Color.White;
            this.lbTreeName.Location = new System.Drawing.Point(13, 20);
            this.lbTreeName.Name = "lbTreeName";
            this.lbTreeName.Size = new System.Drawing.Size(79, 17);
            this.lbTreeName.TabIndex = 0;
            this.lbTreeName.Text = "Tree Name";
            // 
            // pnTimeForWater
            // 
            this.pnTimeForWater.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.pnTimeForWater.Controls.Add(this.tbMinuteWater);
            this.pnTimeForWater.Controls.Add(this.tbHourWater);
            this.pnTimeForWater.Controls.Add(this.lbTimeForWater1);
            this.pnTimeForWater.Controls.Add(this.lbColon);
            this.pnTimeForWater.Controls.Add(this.label3);
            this.pnTimeForWater.Controls.Add(this.btAddTimeForWater);
            this.pnTimeForWater.Controls.Add(this.btDeleteTimeForWater1);
            this.pnTimeForWater.Location = new System.Drawing.Point(465, 131);
            this.pnTimeForWater.Name = "pnTimeForWater";
            this.pnTimeForWater.Size = new System.Drawing.Size(269, 161);
            this.pnTimeForWater.TabIndex = 11;
            // 
            // tbMinuteWater
            // 
            this.tbMinuteWater.Location = new System.Drawing.Point(167, 11);
            this.tbMinuteWater.Name = "tbMinuteWater";
            this.tbMinuteWater.Size = new System.Drawing.Size(20, 20);
            this.tbMinuteWater.TabIndex = 7;
            // 
            // tbHourWater
            // 
            this.tbHourWater.Location = new System.Drawing.Point(129, 11);
            this.tbHourWater.Name = "tbHourWater";
            this.tbHourWater.Size = new System.Drawing.Size(20, 20);
            this.tbHourWater.TabIndex = 7;
            // 
            // lbTimeForWater1
            // 
            this.lbTimeForWater1.AutoSize = true;
            this.lbTimeForWater1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbTimeForWater1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lbTimeForWater1.Location = new System.Drawing.Point(15, 48);
            this.lbTimeForWater1.Name = "lbTimeForWater1";
            this.lbTimeForWater1.Size = new System.Drawing.Size(49, 20);
            this.lbTimeForWater1.TabIndex = 0;
            this.lbTimeForWater1.Text = "12:15";
            this.lbTimeForWater1.Visible = false;
            // 
            // lbColon
            // 
            this.lbColon.AutoSize = true;
            this.lbColon.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbColon.ForeColor = System.Drawing.Color.White;
            this.lbColon.Location = new System.Drawing.Point(153, 11);
            this.lbColon.Name = "lbColon";
            this.lbColon.Size = new System.Drawing.Size(12, 17);
            this.lbColon.TabIndex = 0;
            this.lbColon.Text = ":";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(13, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(98, 17);
            this.label3.TabIndex = 0;
            this.label3.Text = "Time for water";
            // 
            // btAddTimeForWater
            // 
            this.btAddTimeForWater.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btAddTimeForWater.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btAddTimeForWater.ForeColor = System.Drawing.Color.White;
            this.btAddTimeForWater.Location = new System.Drawing.Point(203, 12);
            this.btAddTimeForWater.Name = "btAddTimeForWater";
            this.btAddTimeForWater.Size = new System.Drawing.Size(52, 20);
            this.btAddTimeForWater.TabIndex = 6;
            this.btAddTimeForWater.Text = "Add";
            this.btAddTimeForWater.UseVisualStyleBackColor = false;
            this.btAddTimeForWater.Click += new System.EventHandler(this.btAddTimeForWater_Click);
            // 
            // btDeleteTimeForWater1
            // 
            this.btDeleteTimeForWater1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btDeleteTimeForWater1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDeleteTimeForWater1.ForeColor = System.Drawing.Color.White;
            this.btDeleteTimeForWater1.Location = new System.Drawing.Point(70, 48);
            this.btDeleteTimeForWater1.Name = "btDeleteTimeForWater1";
            this.btDeleteTimeForWater1.Size = new System.Drawing.Size(20, 20);
            this.btDeleteTimeForWater1.TabIndex = 6;
            this.btDeleteTimeForWater1.Text = "x";
            this.btDeleteTimeForWater1.UseVisualStyleBackColor = false;
            this.btDeleteTimeForWater1.Visible = false;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel3.Controls.Add(this.tbTempForWater);
            this.panel3.Controls.Add(this.label7);
            this.panel3.Controls.Add(this.label5);
            this.panel3.Location = new System.Drawing.Point(465, 309);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(269, 51);
            this.panel3.TabIndex = 12;
            // 
            // tbTempForWater
            // 
            this.tbTempForWater.Location = new System.Drawing.Point(171, 16);
            this.tbTempForWater.Name = "tbTempForWater";
            this.tbTempForWater.Size = new System.Drawing.Size(54, 20);
            this.tbTempForWater.TabIndex = 1;
            this.tbTempForWater.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbTempForWater_KeyDown);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.White;
            this.label7.Location = new System.Drawing.Point(231, 18);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(23, 17);
            this.label7.TabIndex = 0;
            this.label7.Text = "°C";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(12, 17);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(157, 17);
            this.label5.TabIndex = 0;
            this.label5.Text = "Temperature For Water";
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel4.Controls.Add(this.tbHumiForFan);
            this.panel4.Controls.Add(this.label8);
            this.panel4.Controls.Add(this.label9);
            this.panel4.Location = new System.Drawing.Point(465, 377);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(269, 51);
            this.panel4.TabIndex = 12;
            // 
            // tbHumiForFan
            // 
            this.tbHumiForFan.Location = new System.Drawing.Point(171, 16);
            this.tbHumiForFan.Name = "tbHumiForFan";
            this.tbHumiForFan.Size = new System.Drawing.Size(54, 20);
            this.tbHumiForFan.TabIndex = 1;
            this.tbHumiForFan.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbHumiForFan_KeyDown);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.White;
            this.label8.Location = new System.Drawing.Point(234, 18);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(20, 17);
            this.label8.TabIndex = 0;
            this.label8.Text = "%";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.Color.White;
            this.label9.Location = new System.Drawing.Point(12, 17);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(115, 17);
            this.label9.TabIndex = 0;
            this.label9.Text = "Humidity For Fan";
            // 
            // button9
            // 
            this.button9.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(199)))), ((int)(((byte)(124)))));
            this.button9.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button9.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button9.ForeColor = System.Drawing.Color.White;
            this.button9.Location = new System.Drawing.Point(473, 634);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(123, 43);
            this.button9.TabIndex = 2;
            this.button9.Text = "Load";
            this.button9.UseVisualStyleBackColor = false;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // btUpload
            // 
            this.btUpload.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(128)))), ((int)(((byte)(255)))));
            this.btUpload.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btUpload.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btUpload.ForeColor = System.Drawing.Color.White;
            this.btUpload.Location = new System.Drawing.Point(618, 634);
            this.btUpload.Name = "btUpload";
            this.btUpload.Size = new System.Drawing.Size(123, 43);
            this.btUpload.TabIndex = 2;
            this.btUpload.Text = "Upload";
            this.btUpload.UseVisualStyleBackColor = false;
            this.btUpload.Click += new System.EventHandler(this.btUpload_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.BackColor = System.Drawing.Color.Transparent;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.ForeColor = System.Drawing.Color.White;
            this.label10.Location = new System.Drawing.Point(281, 6);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(231, 20);
            this.label10.TabIndex = 9;
            this.label10.Text = "Dashboard - FarmBot Software";
            this.label10.MouseDown += new System.Windows.Forms.MouseEventHandler(this.DashBoard_MouseDown);
            // 
            // panel5
            // 
            this.panel5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(28)))), ((int)(((byte)(47)))));
            this.panel5.Controls.Add(this.lbDebug);
            this.panel5.Controls.Add(this.label10);
            this.panel5.Controls.Add(this.btMinimize);
            this.panel5.Controls.Add(this.btExit);
            this.panel5.Location = new System.Drawing.Point(-1, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(775, 35);
            this.panel5.TabIndex = 13;
            this.panel5.MouseDown += new System.Windows.Forms.MouseEventHandler(this.DashBoard_MouseDown);
            // 
            // lbDebug
            // 
            this.lbDebug.AutoSize = true;
            this.lbDebug.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(76)))), ((int)(((byte)(101)))));
            this.lbDebug.Location = new System.Drawing.Point(14, 10);
            this.lbDebug.Name = "lbDebug";
            this.lbDebug.Size = new System.Drawing.Size(0, 13);
            this.lbDebug.TabIndex = 10;
            // 
            // btMinimize
            // 
            this.btMinimize.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(168)))), ((int)(((byte)(171)))));
            this.btMinimize.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btMinimize.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btMinimize.ForeColor = System.Drawing.Color.White;
            this.btMinimize.Location = new System.Drawing.Point(686, 4);
            this.btMinimize.Name = "btMinimize";
            this.btMinimize.Size = new System.Drawing.Size(34, 26);
            this.btMinimize.TabIndex = 1;
            this.btMinimize.Text = "_";
            this.btMinimize.UseVisualStyleBackColor = false;
            this.btMinimize.Click += new System.EventHandler(this.btMinimize_Click);
            // 
            // panel6
            // 
            this.panel6.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel6.Controls.Add(this.label11);
            this.panel6.Location = new System.Drawing.Point(27, 137);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(63, 20);
            this.panel6.TabIndex = 14;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.BackColor = System.Drawing.Color.Transparent;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.ForeColor = System.Drawing.Color.White;
            this.label11.Location = new System.Drawing.Point(5, 1);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(56, 17);
            this.label11.TabIndex = 9;
            this.label11.Text = "Season";
            // 
            // rbNone
            // 
            this.rbNone.AutoSize = true;
            this.rbNone.Checked = true;
            this.rbNone.ForeColor = System.Drawing.Color.White;
            this.rbNone.Location = new System.Drawing.Point(224, 377);
            this.rbNone.Name = "rbNone";
            this.rbNone.Size = new System.Drawing.Size(51, 17);
            this.rbNone.TabIndex = 15;
            this.rbNone.TabStop = true;
            this.rbNone.Text = "None";
            this.rbNone.UseVisualStyleBackColor = true;
            // 
            // rbTree1
            // 
            this.rbTree1.AutoSize = true;
            this.rbTree1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(196)))), ((int)(((byte)(246)))));
            this.rbTree1.Location = new System.Drawing.Point(224, 400);
            this.rbTree1.Name = "rbTree1";
            this.rbTree1.Size = new System.Drawing.Size(56, 17);
            this.rbTree1.TabIndex = 15;
            this.rbTree1.Text = "Tree 1";
            this.rbTree1.UseVisualStyleBackColor = true;
            // 
            // rbTree2
            // 
            this.rbTree2.AutoSize = true;
            this.rbTree2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(76)))), ((int)(((byte)(101)))));
            this.rbTree2.Location = new System.Drawing.Point(224, 423);
            this.rbTree2.Name = "rbTree2";
            this.rbTree2.Size = new System.Drawing.Size(56, 17);
            this.rbTree2.TabIndex = 15;
            this.rbTree2.Text = "Tree 2";
            this.rbTree2.UseVisualStyleBackColor = true;
            // 
            // rbTree3
            // 
            this.rbTree3.AutoSize = true;
            this.rbTree3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(252)))), ((int)(((byte)(177)))), ((int)(((byte)(80)))));
            this.rbTree3.Location = new System.Drawing.Point(224, 446);
            this.rbTree3.Name = "rbTree3";
            this.rbTree3.Size = new System.Drawing.Size(56, 17);
            this.rbTree3.TabIndex = 15;
            this.rbTree3.Text = "Tree 3";
            this.rbTree3.UseVisualStyleBackColor = true;
            // 
            // btSave
            // 
            this.btSave.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(76)))), ((int)(((byte)(101)))));
            this.btSave.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btSave.ForeColor = System.Drawing.Color.White;
            this.btSave.Location = new System.Drawing.Point(325, 634);
            this.btSave.Name = "btSave";
            this.btSave.Size = new System.Drawing.Size(123, 43);
            this.btSave.TabIndex = 2;
            this.btSave.Text = "Save";
            this.btSave.UseVisualStyleBackColor = false;
            this.btSave.Click += new System.EventHandler(this.btSave_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.pictureBox1.Image = global::FarmBot_Software.Properties.Resources.endDevice;
            this.pictureBox1.Location = new System.Drawing.Point(-75, 252);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(40, 40);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 8;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseDown);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbEndActuator_MouseMove);
            // 
            // btDelete
            // 
            this.btDelete.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btDelete.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDelete.ForeColor = System.Drawing.Color.White;
            this.btDelete.Location = new System.Drawing.Point(221, 189);
            this.btDelete.Name = "btDelete";
            this.btDelete.Size = new System.Drawing.Size(60, 20);
            this.btDelete.TabIndex = 6;
            this.btDelete.Text = "Delete";
            this.btDelete.UseVisualStyleBackColor = false;
            this.btDelete.Click += new System.EventHandler(this.btDelet_Click);
            // 
            // FarmBotSerialPort
            // 
            this.FarmBotSerialPort.PortName = "COM50";
            this.FarmBotSerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.ReceiveDataFromSerialPort);
            // 
            // btZ
            // 
            this.btZ.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btZ.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btZ.ForeColor = System.Drawing.Color.White;
            this.btZ.Location = new System.Drawing.Point(256, 349);
            this.btZ.Name = "btZ";
            this.btZ.Size = new System.Drawing.Size(25, 20);
            this.btZ.TabIndex = 6;
            this.btZ.Text = "Z";
            this.btZ.UseVisualStyleBackColor = false;
            this.btZ.Click += new System.EventHandler(this.btZ_Click);
            // 
            // tbX
            // 
            this.tbX.Location = new System.Drawing.Point(221, 297);
            this.tbX.Name = "tbX";
            this.tbX.Size = new System.Drawing.Size(30, 20);
            this.tbX.TabIndex = 16;
            this.tbX.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbX_KeyDown);
            // 
            // lbZ
            // 
            this.lbZ.AutoSize = true;
            this.lbZ.ForeColor = System.Drawing.Color.White;
            this.lbZ.Location = new System.Drawing.Point(221, 252);
            this.lbZ.Name = "lbZ";
            this.lbZ.Size = new System.Drawing.Size(48, 13);
            this.lbZ.TabIndex = 9;
            this.lbZ.Text = "Z : 0 mm";
            // 
            // tbY
            // 
            this.tbY.Location = new System.Drawing.Point(221, 323);
            this.tbY.Name = "tbY";
            this.tbY.Size = new System.Drawing.Size(30, 20);
            this.tbY.TabIndex = 16;
            this.tbY.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbY_KeyDown);
            // 
            // tbZ
            // 
            this.tbZ.Location = new System.Drawing.Point(221, 349);
            this.tbZ.Name = "tbZ";
            this.tbZ.Size = new System.Drawing.Size(30, 20);
            this.tbZ.TabIndex = 16;
            this.tbZ.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbZ_KeyDown);
            // 
            // btPump
            // 
            this.btPump.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            this.btPump.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btPump.ForeColor = System.Drawing.Color.White;
            this.btPump.Location = new System.Drawing.Point(9, 36);
            this.btPump.Name = "btPump";
            this.btPump.Size = new System.Drawing.Size(60, 20);
            this.btPump.TabIndex = 6;
            this.btPump.Text = "Pump";
            this.btPump.UseVisualStyleBackColor = false;
            this.btPump.Click += new System.EventHandler(this.btPump_Click);
            // 
            // tbWaterSpendTime
            // 
            this.tbWaterSpendTime.Location = new System.Drawing.Point(9, 10);
            this.tbWaterSpendTime.Name = "tbWaterSpendTime";
            this.tbWaterSpendTime.Size = new System.Drawing.Size(35, 20);
            this.tbWaterSpendTime.TabIndex = 16;
            this.tbWaterSpendTime.Text = "1000";
            // 
            // cbFan
            // 
            this.cbFan.AutoSize = true;
            this.cbFan.ForeColor = System.Drawing.Color.White;
            this.cbFan.Location = new System.Drawing.Point(6, 12);
            this.cbFan.Name = "cbFan";
            this.cbFan.Size = new System.Drawing.Size(44, 17);
            this.cbFan.TabIndex = 17;
            this.cbFan.Text = "Fan";
            this.cbFan.UseVisualStyleBackColor = true;
            this.cbFan.CheckedChanged += new System.EventHandler(this.cbFan_CheckedChanged);
            // 
            // cbLamp
            // 
            this.cbLamp.AutoSize = true;
            this.cbLamp.ForeColor = System.Drawing.Color.White;
            this.cbLamp.Location = new System.Drawing.Point(6, 35);
            this.cbLamp.Name = "cbLamp";
            this.cbLamp.Size = new System.Drawing.Size(52, 17);
            this.cbLamp.TabIndex = 17;
            this.cbLamp.Text = "Lamp";
            this.cbLamp.UseVisualStyleBackColor = true;
            this.cbLamp.CheckedChanged += new System.EventHandler(this.cbLamp_CheckedChanged);
            // 
            // cbVaccum
            // 
            this.cbVaccum.AutoSize = true;
            this.cbVaccum.ForeColor = System.Drawing.Color.White;
            this.cbVaccum.Location = new System.Drawing.Point(6, 58);
            this.cbVaccum.Name = "cbVaccum";
            this.cbVaccum.Size = new System.Drawing.Size(65, 17);
            this.cbVaccum.TabIndex = 17;
            this.cbVaccum.Text = "Vaccum";
            this.cbVaccum.UseVisualStyleBackColor = true;
            this.cbVaccum.CheckedChanged += new System.EventHandler(this.cbVaccum_CheckedChanged);
            // 
            // cbSoilSensor
            // 
            this.cbSoilSensor.AutoSize = true;
            this.cbSoilSensor.ForeColor = System.Drawing.Color.White;
            this.cbSoilSensor.Location = new System.Drawing.Point(6, 81);
            this.cbSoilSensor.Name = "cbSoilSensor";
            this.cbSoilSensor.Size = new System.Drawing.Size(79, 17);
            this.cbSoilSensor.TabIndex = 17;
            this.cbSoilSensor.Text = "Soil Sensor";
            this.cbSoilSensor.UseVisualStyleBackColor = true;
            this.cbSoilSensor.CheckedChanged += new System.EventHandler(this.cbSoilSensor_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(50, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 13);
            this.label1.TabIndex = 18;
            this.label1.Text = "Ms";
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel2.Controls.Add(this.tbWaterSpendTime);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.btPump);
            this.panel2.Location = new System.Drawing.Point(221, 486);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(86, 65);
            this.panel2.TabIndex = 19;
            // 
            // panel7
            // 
            this.panel7.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel7.Controls.Add(this.cbFan);
            this.panel7.Controls.Add(this.cbLamp);
            this.panel7.Controls.Add(this.cbSoilSensor);
            this.panel7.Controls.Add(this.cbVaccum);
            this.panel7.Location = new System.Drawing.Point(221, 569);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(86, 108);
            this.panel7.TabIndex = 20;
            // 
            // panel8
            // 
            this.panel8.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(57)))), ((int)(((byte)(66)))), ((int)(((byte)(100)))));
            this.panel8.Controls.Add(this.tbHumiForMist);
            this.panel8.Controls.Add(this.label2);
            this.panel8.Controls.Add(this.label4);
            this.panel8.Location = new System.Drawing.Point(465, 446);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(269, 51);
            this.panel8.TabIndex = 12;
            // 
            // tbHumiForMist
            // 
            this.tbHumiForMist.Location = new System.Drawing.Point(171, 16);
            this.tbHumiForMist.Name = "tbHumiForMist";
            this.tbHumiForMist.Size = new System.Drawing.Size(54, 20);
            this.tbHumiForMist.TabIndex = 1;
            this.tbHumiForMist.KeyDown += new System.Windows.Forms.KeyEventHandler(this.tbHumiForMist_KeyDown);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(234, 18);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(20, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "%";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(12, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(116, 17);
            this.label4.TabIndex = 0;
            this.label4.Text = "Humidity For Mist";
            // 
            // DashBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(31)))), ((int)(((byte)(37)))), ((int)(((byte)(61)))));
            this.ClientSize = new System.Drawing.Size(771, 703);
            this.Controls.Add(this.panel7);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.tbZ);
            this.Controls.Add(this.tbY);
            this.Controls.Add(this.tbX);
            this.Controls.Add(this.rbTree3);
            this.Controls.Add(this.rbTree2);
            this.Controls.Add(this.rbTree1);
            this.Controls.Add(this.rbNone);
            this.Controls.Add(this.panel6);
            this.Controls.Add(this.panel5);
            this.Controls.Add(this.panel8);
            this.Controls.Add(this.panel4);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.pnTimeForWater);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.lbZ);
            this.Controls.Add(this.lbY);
            this.Controls.Add(this.lbX);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.pbEndActuator);
            this.Controls.Add(this.pbGarden);
            this.Controls.Add(this.btLoadSeason);
            this.Controls.Add(this.btZ);
            this.Controls.Add(this.btY);
            this.Controls.Add(this.btX);
            this.Controls.Add(this.btHome);
            this.Controls.Add(this.btDelete);
            this.Controls.Add(this.btAddSeason);
            this.Controls.Add(this.tbSeasonName);
            this.Controls.Add(this.cbSeasonName);
            this.Controls.Add(this.lbConnectState);
            this.Controls.Add(this.btSave);
            this.Controls.Add(this.btUpload);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.btTree3);
            this.Controls.Add(this.btTree2);
            this.Controls.Add(this.btTree1);
            this.Controls.Add(this.btConnect);
            this.Controls.Add(this.btTestControlBoard);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "DashBoard";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "DashBoard";
            this.Load += new System.EventHandler(this.DashBoard_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.DashBoard_MouseDown);
            ((System.ComponentModel.ISupportInitialize)(this.pbGarden)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbEndActuator)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.pnTimeForWater.ResumeLayout(false);
            this.pnTimeForWater.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.panel6.ResumeLayout(false);
            this.panel6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel7.ResumeLayout(false);
            this.panel7.PerformLayout();
            this.panel8.ResumeLayout(false);
            this.panel8.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btTestControlBoard;
        private System.Windows.Forms.Button btExit;
        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Label lbConnectState;
        private System.Windows.Forms.ComboBox cbSeasonName;
        private System.Windows.Forms.TextBox tbSeasonName;
        private System.Windows.Forms.Button btAddSeason;
        private System.Windows.Forms.Button btLoadSeason;
        private System.Windows.Forms.PictureBox pbGarden;
        private System.Windows.Forms.PictureBox pbEndActuator;
        private System.Windows.Forms.Label lbX;
        private System.Windows.Forms.Label lbY;
        private System.Windows.Forms.Button btHome;
        private System.Windows.Forms.Button btX;
        private System.Windows.Forms.Button btY;
        private System.Windows.Forms.Button btTree1;
        private System.Windows.Forms.Button btTree2;
        private System.Windows.Forms.Button btTree3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label lbTreeName;
        private System.Windows.Forms.TextBox tbTreeName;
        private System.Windows.Forms.Panel pnTimeForWater;
        private System.Windows.Forms.TextBox tbMinuteWater;
        private System.Windows.Forms.TextBox tbHourWater;
        private System.Windows.Forms.Label lbTimeForWater1;
        private System.Windows.Forms.Label lbColon;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btAddTimeForWater;
        private System.Windows.Forms.Button btDeleteTimeForWater1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.TextBox tbTempForWater;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.TextBox tbHumiForFan;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button btUpload;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Button btMinimize;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.RadioButton rbNone;
        private System.Windows.Forms.RadioButton rbTree1;
        private System.Windows.Forms.RadioButton rbTree2;
        private System.Windows.Forms.RadioButton rbTree3;
        private System.Windows.Forms.Button btSave;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btDelete;
        private System.IO.Ports.SerialPort FarmBotSerialPort;
        private System.Windows.Forms.Label lbDebug;
        private System.Windows.Forms.Button btZ;
        private System.Windows.Forms.TextBox tbX;
        private System.Windows.Forms.Label lbZ;
        private System.Windows.Forms.TextBox tbY;
        private System.Windows.Forms.TextBox tbZ;
        private System.Windows.Forms.Button btPump;
        private System.Windows.Forms.TextBox tbWaterSpendTime;
        private System.Windows.Forms.CheckBox cbFan;
        private System.Windows.Forms.CheckBox cbLamp;
        private System.Windows.Forms.CheckBox cbVaccum;
        private System.Windows.Forms.CheckBox cbSoilSensor;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.TextBox tbHumiForMist;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
    }
}

