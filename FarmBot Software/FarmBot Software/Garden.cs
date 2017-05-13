using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FarmBot_Software
{
    class Garden
    {
        public Garden(PictureBox pbGarden, RadioButton rbNone, RadioButton rbTree1, RadioButton rbTree2, RadioButton rbTree3)
        {
            this.PbGarden = pbGarden;
            this.RbNone = rbNone;
            this.RbTree1 = rbTree1;
            this.RbTree2 = rbTree2;
            this.RbTree3 = rbTree3;

            Cells = new GardenCell[24];
            Icons = new PictureBox[24];

            for (int index = 0; index < 24; index++)
            {
                Cells[index] = GardenCell.NONE;

                Icons[index] = new PictureBox();
                Icons[index].Size = new Size(40, 40);
                Icons[index].Location = new Point((index % 3) * 60 + 10, (index / 3) * 60 + 10);
                Icons[index].Click += new System.EventHandler(this.IconClick);
                PbGarden.Controls.Add(Icons[index]);
                Icons[index].Parent = PbGarden;
                Icons[index].Hide();
            }
        }

        public void SetTreeIcon(int index, GardenCell tree)
        {
            switch (tree)
            {
                case GardenCell.NONE:
                    Icons[index].Hide();
                    Cells[index] = GardenCell.NONE;
                    break;
                case GardenCell.TREE1:
                    Icons[index].Show();
                    Icons[index].BackColor = Color.FromArgb(79, 196, 246);
                    Cells[index] = GardenCell.TREE1;
                    break;
                case GardenCell.TREE2:
                    Icons[index].Show();
                    Icons[index].BackColor = Color.FromArgb(230, 76, 101);
                    Cells[index] = GardenCell.TREE2;
                    break;
                case GardenCell.TREE3:
                    Icons[index].Show();
                    Icons[index].BackColor = Color.FromArgb(252, 177, 80);
                    Cells[index] = GardenCell.TREE3;
                    break;
                default:
                    break;
            }
        }

        public void ShowTreeIcon(int index)
        {
            if (RbTree1.Checked == true)
            {
                SetTreeIcon(index, GardenCell.TREE1);
            }
            else if (RbTree2.Checked == true)
            {
                SetTreeIcon(index, GardenCell.TREE2);
            }
            else if (RbTree3.Checked == true)
            {
                SetTreeIcon(index, GardenCell.TREE3);
            }
            else
            {
                SetTreeIcon(index, GardenCell.NONE);
            }
        }

        private void IconClick(object sender, EventArgs e)
        {
            PictureBox pbIcon = ((PictureBox)sender);
            for (int i = 0; i < Icons.Length; i ++)
            {
                if ( Icons[i] == pbIcon)
                {
                    ShowTreeIcon(i);
                }
            }
        }

        public PictureBox PbGarden;
        public RadioButton RbNone;
        public RadioButton RbTree1;
        public RadioButton RbTree2;
        public RadioButton RbTree3;

        public GardenCell[] Cells;
        public PictureBox[] Icons;
    }

    enum GardenCell
    {
        NONE = 0,
        TREE1 = 1,
        TREE2 = 2,
        TREE3 = 3,
    };
}
