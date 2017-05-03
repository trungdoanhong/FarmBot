using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace FarmBot_Software
{
    public partial class TestControlBoard : Form
    {
        public TestControlBoard()
        {
            InitializeComponent();
        }


        private void refresh_Click(object sender, EventArgs e)
        {
            cb_COM.Items.Clear();
            foreach (string com in SerialPort.GetPortNames())
            {
                cb_COM.Items.Add(com);
            }
            cb_COM.SelectedIndex = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                foreach (string com in SerialPort.GetPortNames())
                {
                    cb_COM.Items.Add(com);
                }
                cb_COM.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show(" Failed !");
            }
        }

        private void bt_connect_Click(object sender, EventArgs e)
        {
            try
            {

                if (lb_ComState.Text != "Connect !")
                {
                    string comselect = cb_COM.Text;
                    Port1.PortName = comselect;
                    Port1.Open();
                    lb_ComState.Text = "Connect !";
                    bt_connect.Text = "Disconnect ...";
                    cb_COM.Enabled = false;

                }
                else
                {
                    Port1.Close();
                    lb_ComState.Text = "Disconnect ...";
                    bt_connect.Text = "Connect !";
                    cb_COM.Enabled = true;
                }
            }
            catch
            {
                MessageBox.Show("Cannot connect to this COM port !");
            }
        }

        private void Process_when_receive_value(object sender, SerialDataReceivedEventArgs e)
        {
            string s = Port1.ReadLine();
            this.BeginInvoke(new LineReceivedEvent(LineReceived), s);
        }

        private delegate void LineReceivedEvent(string POT);
        private void LineReceived(string s)
        {
            ;
        }

        private void X_Click(object sender, EventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            Thread threadSendCmd = new Thread(SendCommandX);
            threadSendCmd.Start();           
            
        }

        private void Y_Click(object sender, EventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            Thread threadSendCmd = new Thread(SendCommandY);
            threadSendCmd.Start();

        }

        private void Z_Click(object sender, EventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            Thread threadSendCmd = new Thread(SendCommandZ);
            threadSendCmd.Start();

        }

        private void XPressEnter(object sender, KeyEventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            if( e.KeyCode == Keys.Enter)
            {
                X_Click(null, null);
            }
        }

        private void YPressEnter(object sender, KeyEventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            if (e.KeyCode == Keys.Enter)
            {
                Y_Click(null, null);
            }
        }

        private void ZPressEnter(object sender, KeyEventArgs e)
        {
            if (!Port1.IsOpen)
                return;
            if (e.KeyCode == Keys.Enter)
            {
                Z_Click(null, null);
            }
        }

        public void SendCommandX()
        {
            Port1.WriteLine("X-" + tbX.Text);
            Thread.Sleep(10);
            Port1.WriteLine("MoveX");
        }

        public void SendCommandY()
        {
            Port1.WriteLine("Y-" + tbY.Text);
            Thread.Sleep(10);
            Port1.WriteLine("MoveY");
        }

        public void SendCommandZ()
        {
            Port1.WriteLine("Z-" + tbZ.Text);
            Thread.Sleep(10);
            Port1.WriteLine("MoveZ");
        }

        private void btCloseForm_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [System.Runtime.InteropServices.DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [System.Runtime.InteropServices.DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        private void TestControlBoard_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }        
    }
}

