using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace FarmBot_Software
{
    class TimeControl
    {
        public TimeControl(Panel panel, int x = 0, int y = 0)
        {
            pnParent = panel;
            lbTimeForWater = new Label();
            btDeleteTime = new Button();

            lbTimeForWater.AutoSize = true;
            lbTimeForWater.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            lbTimeForWater.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            lbTimeForWater.Size = new System.Drawing.Size(49, 20);
            lbTimeForWater.Text = "00:00";

            btDeleteTime.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(89)))), ((int)(((byte)(123)))));
            btDeleteTime.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            btDeleteTime.ForeColor = System.Drawing.Color.White;
            btDeleteTime.Size = new System.Drawing.Size(20, 20);
            btDeleteTime.Text = "x";
            btDeleteTime.UseVisualStyleBackColor = false;

            pnParent.Controls.Add(lbTimeForWater);
            pnParent.Controls.Add(btDeleteTime);
            SetPosition(x, y);
            IsActive = true;
        }        
        public void SetTime(String timeString)
        {
            lbTimeForWater.Text = timeString;
        }

        public void SetTime(int hour, int min)
        {
            String hh = "";
            String mm = "";

            if (hour < 10)
            {
                hh = "0" + hour;
            }
            else
            {
                hh = "" + hour;
            }

            if (min < 10)
            {
                mm = "0" + min;
            }
            else
            {
                mm = "" + min;
            }

            lbTimeForWater.Text = hh + ":" + mm;
        }
        public void SetPosition(int x, int y)
        {
            lbTimeForWater.Location = new Point(x, y);
            btDeleteTime.Location = new Point(x + 55, y);

        }

        public void Delete()
        {
            pnParent.Controls.Remove(lbTimeForWater);
            pnParent.Controls.Remove(btDeleteTime);
        }

        public void Hide()
        {
            lbTimeForWater.Hide();
            btDeleteTime.Hide();
            IsActive = false;
        }

        public void Show()
        {
            lbTimeForWater.Show();
            btDeleteTime.Show();
            IsActive = true;
        }

        public Label lbTimeForWater;
        public Button btDeleteTime;
        public Panel pnParent;
        public bool IsActive = false;
    }
}
