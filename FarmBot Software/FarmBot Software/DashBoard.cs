using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FarmBot_Software
{
    public partial class DashBoard : Form
    {
        public DashBoard()
        {
            InitializeComponent();
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

        private void DashBoard_Load(object sender, EventArgs e)
        {
            pbEndActuator.BackColor = Color.Transparent;
            pbEndActuator.Parent = pbGarden;
            pbEndActuator.Location = new System.Drawing.Point(60 - pbEndActuator.Size.Width/2, 60 - pbEndActuator.Size.Height/2);
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
            }
        }


    }
}
