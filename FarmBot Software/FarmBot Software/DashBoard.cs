using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO.Ports;
using System.Threading;
using System.Web.Script.Serialization;

namespace FarmBot_Software
{
    public partial class DashBoard : Form
    {
        Season LoadingSeason;
        Garden LoadingGarden;
        FarmBotXml LoadingDatabaseXml;
        int LoadingTreeIndex;
        bool IsFarmBotConnected = false;
        List<SerialPort> SerialPortList;

        int X_EndActuator;
        int Y_EndActuator;
        int Z_EndActuator;

        public DashBoard()
        {
            InitializeComponent();
            InitVariable();
        }

        private void InitVariable()
        {
            // Init EndActuator Icon
            pbEndActuator.Parent = pbGarden;
            pbEndActuator.Location = new System.Drawing.Point(60 - pbEndActuator.Size.Width / 2, 60 - pbEndActuator.Size.Height / 2);

            //Init Garden
            LoadingGarden = new Garden(pbGarden, rbNone, rbTree1, rbTree2, rbTree3);
            LoadingDatabaseXml = new FarmBotXml(Constants.DatabaseFileName, true);

            LoadingTreeIndex = -1;

            // Init Serial Port
            SerialPortList = new List<SerialPort>();
        }

        private void DashBoard_Load(object sender, EventArgs e)
        {
            LoadingDatabaseXml.FillSeasonName(cbSeasonName);
        }

        private void btExit_Click(object sender, EventArgs e)
        {
            Environment.Exit(Environment.ExitCode);
        }

        private void btTestControlBoard_Click(object sender, EventArgs e)
        {
            TestControlBoard testControlBoard = new TestControlBoard();
            testControlBoard.Show();
        }

        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [System.Runtime.InteropServices.DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [System.Runtime.InteropServices.DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        private void DashBoard_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }

        }

        private Point MouseDownLocation;

        private void pbEndActuator_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocation = e.Location;
            }
        }

        private void pbEndActuator_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                pbEndActuator.Left = e.X + pbEndActuator.Left - MouseDownLocation.X;
                pbEndActuator.Top = e.Y + pbEndActuator.Top - MouseDownLocation.Y;

                if (pbEndActuator.Left < -20)
                    pbEndActuator.Left = -20;
                if (pbEndActuator.Left > 160)
                    pbEndActuator.Left = 160;
                if (pbEndActuator.Top < -20)
                    pbEndActuator.Top = -20;
                if (pbEndActuator.Top > 460)
                    pbEndActuator.Top = 460;

                X_EndActuator = ((pbEndActuator.Left + 20) * 10) / 6;
                Y_EndActuator = ((pbEndActuator.Top + 20) * 10) / 6;

                UpdatePositionDisplay();
            }
        }

        void UpdatePositionDisplay()
        {
            lbX.Text = "X : " + X_EndActuator + " mm";
            lbY.Text = "Y : " + Y_EndActuator + " mm";
            lbZ.Text = "Z : " + Z_EndActuator + " mm";
        }

        void UpdatePbEndActuator()
        {
            pbEndActuator.Left = (X_EndActuator * 6) / 10 - 20;
            pbEndActuator.Top = (Y_EndActuator * 6) / 10 - 20;
        }

        private void btMinimize_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void panel5_MouseDown(object sender, MouseEventArgs e)
        {

        }

        List<TimeControl> TimeControlList = new List<TimeControl>();

        private void btAddTimeForWater_Click(object sender, EventArgs e)
        {
            if (TimeControlList.Count == 6)
                return;

            int hour = 0;
            int minute = 0;

            Int16 n;

            if (Int16.TryParse(tbHourWater.Text,out n))
            {
                if (!(n < 0 || n > 23))
                    hour = Int16.Parse(tbHourWater.Text);
            }

            if (Int16.TryParse(tbMinuteWater.Text, out n))
            {
                if (!(n < 0 || n > 59))
                    minute = Int16.Parse(tbMinuteWater.Text);
            }

            AddTimeControlToPanel(hour, minute);
            Time addingTime = new Time();
            addingTime.Hour = hour;
            addingTime.Minute = minute;
            LoadingSeason.Tree[LoadingTreeIndex].TimeForWaterList.Add(addingTime);
        }

        public void AddTimeControlToPanel(int hour, int minute)
        {
            TimeControl timeControl = new TimeControl(pnTimeForWater);
            TimeControlList.Add(timeControl);
            timeControl.SetPosition(15 + ((TimeControlList.Count - 1) % 2) * 145, 48 + 40 * ((TimeControlList.Count - 1) / 2));
            timeControl.SetTime(hour, minute);
            timeControl.btDeleteTime.Click += new System.EventHandler(this.DeleteTimeToWater);
        }

        public void DeleteTimeToWater(object sender, EventArgs e)
        {
            int order = -1;
            foreach( TimeControl timeControl in TimeControlList)
            {
                if (timeControl.btDeleteTime == (Button)sender)
                    order = TimeControlList.IndexOf(timeControl);
            }
            TimeControlList[order].DeleteControls();
            TimeControlList.RemoveAt(order);
            LoadingSeason.Tree[LoadingTreeIndex].TimeForWaterList.RemoveAt(order);

            for (int i = order; i < TimeControlList.Count; i++)
            {
                TimeControlList[i].SetPosition(15 + (i % 2) * 145, 48 + 40 * (i / 2));
            }
        }        

        private void btLoadSeason_Click(object sender, EventArgs e)
        {
            if (cbSeasonName.Text == "")
                return;
            LoadingTreeIndex = -1;
            LoadingSeason = LoadingDatabaseXml.LoadSeason(cbSeasonName.Text);

            UpdateDisplay();
        }

        private void UpdateDisplay()
        {
            LoadingTreeIndex = -1;
            UpdateGardenDisplay();            
            btTree1_Click(null, null);
        }

        private void UpdateGardenDisplay()
        {
            for (int i = 0; i < 24; i++)
            {
                LoadingGarden.SetTreeIcon(i, (GardenCell)LoadingSeason.Garden[i]);
            }
        }

        public void LoadTreeData(int order)
        {
            if (LoadingTreeIndex != -1)
            {
                LoadingSeason.Tree[LoadingTreeIndex].Name = tbTreeName.Text;
                LoadingSeason.Tree[LoadingTreeIndex].MaxTemperature = int.Parse(tbTempForWater.Text);
                LoadingSeason.Tree[LoadingTreeIndex].MaxHumidity = int.Parse(tbHumiForFan.Text);
            }

            RemoveAllTimeControls();

            tbTreeName.Text = LoadingSeason.Tree[order].Name;
            tbTempForWater.Text = LoadingSeason.Tree[order].MaxTemperature.ToString();
            tbHumiForFan.Text = LoadingSeason.Tree[order].MaxHumidity.ToString();
            tbHumiForMist.Text = LoadingSeason.Tree[order].MinHumidity.ToString();

            for( int i = 0; i < LoadingSeason.Tree[order].TimeForWaterList.Count; i++ )
            {
                int hour = LoadingSeason.Tree[order].TimeForWaterList[i].Hour;
                int minute = LoadingSeason.Tree[order].TimeForWaterList[i].Minute;
                AddTimeControlToPanel(hour, minute);
            }

            LoadingTreeIndex = order;
        }


        public void RemoveAllTimeControls()
        {
            foreach( TimeControl deleteTimeControl in TimeControlList)
            {
                deleteTimeControl.DeleteControls();
            }
            TimeControlList.Clear();
        }

        private void btTree3_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
            lbTreeName.ForeColor = Color.FromArgb(252, 177, 80);
            LoadTreeData(2);
        }


        private void btTree2_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
            lbTreeName.ForeColor = Color.FromArgb(230, 76, 101);
            LoadTreeData(1);
        }

        private void btTree1_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
            lbTreeName.ForeColor = Color.FromArgb(79, 196, 246);
            LoadTreeData(0);
        }

        private void pbGarden_Click(object sender, EventArgs e)
        {
            if (rbNone.Checked == true)
                return;
            Point mousePosition = ((PictureBox)sender).PointToClient(Control.MousePosition);
            int cellIndex = mousePosition.X / 60 + (mousePosition.Y / 60) * 3;

            LoadingGarden.ShowTreeIcon(cellIndex);
        }

        private void btSave_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;

            LoadingSeason.Tree[LoadingTreeIndex].Name = tbTreeName.Text;
            LoadingSeason.Tree[LoadingTreeIndex].MaxTemperature = int.Parse(tbTempForWater.Text);
            LoadingSeason.Tree[LoadingTreeIndex].MaxHumidity = int.Parse(tbHumiForFan.Text);
            LoadingSeason.Tree[LoadingTreeIndex].MinHumidity = int.Parse(tbHumiForMist.Text);

            for (int i = 0; i < 24; i++ )
            {
                LoadingSeason.Garden[i] = (int)LoadingGarden.Cells[i];
            }
            LoadingDatabaseXml.UpdateSeason(LoadingSeason);
            ShowMessage("Saved", 3000);
        }

        private void btAddSeason_Click(object sender, EventArgs e)
        {
            if (tbSeasonName.Text == "")
                return;
            LoadingSeason = LoadingDatabaseXml.CreateSeason(tbSeasonName.Text);
            cbSeasonName.SelectedIndex = cbSeasonName.Items.Add(LoadingSeason.Name);
            btLoadSeason_Click(null, null);

            tbSeasonName.Text = "";
        }

        private void btDelet_Click(object sender, EventArgs e)
        {
            if (cbSeasonName.Text == "" || cbSeasonName.Items.Count == 0)
                return;

            LoadingDatabaseXml.DeleteSeason(cbSeasonName.Text);
            cbSeasonName.Items.RemoveAt(cbSeasonName.SelectedIndex);

            if (cbSeasonName.Items.Count > 0)
            {
                cbSeasonName.SelectedIndex = 0;
            }
            else
            {
                cbSeasonName.Text = "";
                tbTreeName.Text = "";
                tbTempForWater.Text = "";
                tbHumiForFan.Text = "";
                RemoveAllTimeControls();
                LoadingSeason = null;
            }
        }
        public void FindFamrBotPort()
        {
            foreach (String connectPortName in SerialPort.GetPortNames())
            {
                SerialPort serialPort = new SerialPort(this.components);                
                serialPort.PortName = connectPortName;
                serialPort.BaudRate = 9600;

                try
                {
                    serialPort.Open();
                }
                catch
                {
                    continue;
                }

                SerialPortList.Add(serialPort);
                serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.ReceiveDataFromSerialPort);
                serialPort.WriteLine("IsFarmBot");
            }

            Thread closePortsThread = new Thread(ClosePorts);
            closePortsThread.Start();
        }

        public void ClosePorts()
        {
            this.Invoke((MethodInvoker)delegate()
            {
                lbConnectState.Text = "";
            });

            for (int i = 0; i < 10; i++ )
            {
                this.Invoke((MethodInvoker)delegate()
                {
                    lbConnectState.Text += ".";
                });
                
                Thread.Sleep(100);
                if (IsFarmBotConnected == true)
                {
                    break;
                }
            }

            this.Invoke((MethodInvoker)delegate()
            {
                if (IsFarmBotConnected == false)
                {
                    lbConnectState.Text = "FarmBot is not Availabel !";
                }

                foreach (SerialPort serialPort in SerialPortList)
                {   
                    serialPort.Close();
                    serialPort.Dispose();
                }
                SerialPortList.Clear();

                if (IsFarmBotConnected == true)
                {
                    FarmBotSerialPort.Open();
                    ShowMessage("FarmBot on " + FarmBotSerialPort.PortName, 3000);
                }
                
            });
            

        }

        private void ReceiveDataFromSerialPort(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort portReceived = ((SerialPort)sender);
            String receiveString;
            try
            {
                receiveString = portReceived.ReadLine();
            }
            catch
            {
                return;
            }

            if (receiveString.Length >= "YesFarmBot".Length)
            {
                if (receiveString.Substring(0, "YesFarmBot".Length) == "YesFarmBot")
                {
                    FarmBotSerialPort.PortName = portReceived.PortName;
                    this.Invoke((MethodInvoker)delegate()
                    {
                        lbConnectState.Text = "FarmBot is Connected !";
                        btConnect.Text = "Disconnect";
                    });
                    
                    IsFarmBotConnected = true;
                }
            }

            if (receiveString.Length > "Json".Length)
            {
                if (receiveString.Substring(0, "Json".Length) == "Json")
                {
                    receiveString = receiveString.Substring("Json".Length + 1);
                    var serializeObject = new JavaScriptSerializer();
                    LoadingSeason = serializeObject.Deserialize<Season>(receiveString);
                    this.Invoke((MethodInvoker)delegate()
                    {
                        UpdateDisplay();
                    }); 
                    ShowMessage("Load Done", 3000);
                }
            }

            
        }

        private void btConnect_Click(object sender, EventArgs e)
        {
            if (btConnect.Text == "Connect")
            {
                FindFamrBotPort();                
            }
            else
            {
                ShowMessage("FarmBot closed " + FarmBotSerialPort.PortName, 2000);
                try
                {
                    FarmBotSerialPort.Close();
                }
                catch
                {

                }
                IsFarmBotConnected = false;
                btConnect.Text = "Connect";
                lbConnectState.Text = "FarmBot is disconnected !";
                
            }
        }

        public void ShowMessage(String msg, int time)
        {
            Thread messageThread = new Thread(() => ProcessMessageThread(msg, time));
            messageThread.Start();
        }

        public void ProcessMessageThread(String msg, int time)
        {
            this.Invoke((MethodInvoker)delegate()
            {
                lbDebug.Text = msg;
            });

            Thread.Sleep(time);

            this.Invoke((MethodInvoker)delegate()
            {
                lbDebug.Text = "";
            });      
        }

        private void btUpload_Click(object sender, EventArgs e)
        {
            if (FarmBotSerialPort.IsOpen == false)
                return;
            ShowMessage("Uploading ...", 5000);
            String jsonString = ""; // We will send this tring to Farmbot Control Box

            var serializeObject = new JavaScriptSerializer();
            jsonString = serializeObject.Serialize(LoadingSeason);
            Season seasonFromJson = serializeObject.Deserialize<Season>(jsonString);
            FarmBotSerialPort.WriteLine(jsonString);
            ShowMessage("Done", 1000);
        }

        private void pbEndActuator_MouseUp(object sender, MouseEventArgs e)
        {
            String gcode = "G00 X" + X_EndActuator.ToString() + " Y" + Y_EndActuator.ToString();
            SendGCode(gcode);
        }

        private void btHome_Click(object sender, EventArgs e)
        {
            String gcode = "G28 X Y Z";
            X_EndActuator = 0;
            Y_EndActuator = 0;
            Z_EndActuator = 0;
            //SendGCode(gcode);
            SendGCode("G28 Z");
            Thread.Sleep(100);
            SendGCode("G28 X Y");
            UpdatePbEndActuator();
            UpdatePositionDisplay();
        }

        private void btX_Click(object sender, EventArgs e)
        {
            String gcode = "G28 X";
            X_EndActuator = 0;
            SendGCode(gcode);
            UpdatePbEndActuator();
            UpdatePositionDisplay();
        }

        public void SendGCode(string gcode)
        {
            if (IsFarmBotConnected == false)
                return;

            ShowMessage(gcode, 1000);
            FarmBotSerialPort.WriteLine(gcode);
        }

        private void btY_Click(object sender, EventArgs e)
        {
            String gcode = "G28 Y";
            Y_EndActuator = 0;
            SendGCode(gcode);
            UpdatePbEndActuator();
            UpdatePositionDisplay();
        }

        private void btZ_Click(object sender, EventArgs e)
        {
            String gcode = "G28 Z";
            Z_EndActuator = 0;
            SendGCode(gcode);
            UpdatePbEndActuator();
            UpdatePositionDisplay();
        }

        private void tbZ_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                int.TryParse(tbZ.Text, out Z_EndActuator);
                SendGCode("G00 Z" + Z_EndActuator.ToString());

                UpdatePositionDisplay();
            }
        }

        private void tbY_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                int.TryParse(tbY.Text, out Y_EndActuator);
                SendGCode("G00 Y" + Y_EndActuator.ToString());

                UpdatePositionDisplay();
                UpdatePbEndActuator();
            }
        }

        private void tbX_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                int.TryParse(tbX.Text, out X_EndActuator);
                SendGCode("G00 X" + X_EndActuator.ToString());

                UpdatePositionDisplay();
                UpdatePbEndActuator();
            }
        }

        private void btPump_Click(object sender, EventArgs e)
        {
            string gcode = "G41 P" + tbWaterSpendTime.Text;
            SendGCode(gcode);
        }

        private void cbFan_CheckedChanged(object sender, EventArgs e)
        {
            string gcode = "G43 F";
            if (cbFan.Checked == true)
            {
                gcode += "1";
            }
            else
            {
                gcode += "0";
            }
            SendGCode(gcode);
        }

        private void cbLamp_CheckedChanged(object sender, EventArgs e)
        {
            string gcode = "G44 L";
            if (cbLamp.Checked == true)
            {
                gcode += "1";
            }
            else
            {
                gcode += "0";
            }
            SendGCode(gcode);
        }

        private void cbVaccum_CheckedChanged(object sender, EventArgs e)
        {
            string gcode = "G42 V";
            if (cbVaccum.Checked == true)
            {
                gcode += "1";
            }
            else
            {
                gcode += "0";
            }
            SendGCode(gcode);
        }

        private void cbSoilSensor_CheckedChanged(object sender, EventArgs e)
        {
            string gcode = "G40 S";
            if (cbSoilSensor.Checked == true)
            {
                gcode += "90";
            }
            else
            {
                gcode += "0";
            }
            SendGCode(gcode);
        }

        private void tbTreeName_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData != Keys.Enter)
                return;

            LoadingSeason.Tree[LoadingTreeIndex].Name = tbTreeName.Text;
            ShowMessage("Edit", 1000);
        }

        private void tbTempForWater_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData != Keys.Enter)
                return;

            LoadingSeason.Tree[LoadingTreeIndex].MaxTemperature = int.Parse(tbTempForWater.Text);
            ShowMessage("Edit", 1000);
        }

        private void tbHumiForFan_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData != Keys.Enter)
                return;

            LoadingSeason.Tree[LoadingTreeIndex].MaxHumidity = int.Parse(tbHumiForFan.Text);
            ShowMessage("Edit", 1000);
        }

        private void tbHumiForMist_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData != Keys.Enter)
                return;

            LoadingSeason.Tree[LoadingTreeIndex].MinHumidity = int.Parse(tbHumiForMist.Text);
            ShowMessage("Edit", 1000);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (FarmBotSerialPort.IsOpen == false)
                return;
            FarmBotSerialPort.WriteLine("Load");
            ShowMessage("Loading ...", 1000);
        }

    }
}
