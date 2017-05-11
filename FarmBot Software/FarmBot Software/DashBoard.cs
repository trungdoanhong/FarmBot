using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace FarmBot_Software
{
    public partial class DashBoard : Form
    {
        private Season LoadingSeason;
        private Garden LoadingGarden;
        private FarmBotXml LoadingDatabaseXml;
        private int LoadingTreeIndex;

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

            LoadingTreeIndex = 0;
        }

        private void DashBoard_Load(object sender, EventArgs e)
        {
            LoadingDatabaseXml.FillSeasonName(cbSeasonName);
        }

        private void btExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
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

                lbX.Text = "X : " + ((pbEndActuator.Left + 20) * 10) / 6 + " mm";
                lbY.Text = "Y : " + ((pbEndActuator.Top + 20) * 10) / 6 + " mm";
            }
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
            TimeControlList[order].Delete();
            TimeControlList.RemoveAt(order);
            for (int i = order; i < TimeControlList.Count; i++)
            {
                TimeControlList[i].SetPosition(15 + (i % 2) * 145, 48 + 40 * (i / 2));
            }
        }        

        private void btLoadSeason_Click(object sender, EventArgs e)
        {
            LoadingSeason = LoadingDatabaseXml.LoadSeason(cbSeasonName.Text);
            LoadTreeData(0);
        }

        public void LoadTreeData(int order)
        {
            tbTreeName.Text = LoadingSeason.Tree[order].Name;
            tbTempForWater.Text = LoadingSeason.Tree[order].MaxTemperature.ToString();
            tbHumiForWater.Text = LoadingSeason.Tree[order].MaxHumidity.ToString();

            LoadingTreeIndex = order;
        }

        private void btTree2_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
            LoadTreeData(1);
        }

        private void btTree3_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
            LoadTreeData(2);
        }

        private void btTree1_Click(object sender, EventArgs e)
        {
            if (LoadingSeason == null)
                return;
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
            LoadingSeason.Tree[LoadingTreeIndex].Name = tbTreeName.Text;
            LoadingSeason.Tree[LoadingTreeIndex].MaxTemperature = int.Parse(tbTempForWater.Text);
            LoadingSeason.Tree[LoadingTreeIndex].MaxHumidity = int.Parse(tbHumiForWater.Text);

            LoadingDatabaseXml.UpdateSeason(LoadingSeason);
        }

        

    }
}
