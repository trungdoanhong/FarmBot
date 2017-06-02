using System;
using System.Collections.Generic;
using System.Text;

namespace FarmBot_Software
{
    public class Season
    {
        public Season()
        {
            Tree = new Tree[3];
            
            for(int i = 0; i < Tree.Length; i++)
            {
                Tree[i] = new Tree();
                Tree[i].Name = "Tree " + (i + 1).ToString();
                Tree[i].MaxHumidity = 40;
                Tree[i].MaxTemperature = 40;

            }
            Garden = new int[24];
            for( int i = 0; i < 24; i++)
            {
                Garden[i] = 0;
            }

        }
        public String Name { get; set; }
        public int Id {get; set;}
        public Tree[] Tree;
        public int[] Garden;
    }
    public class Tree
    {
        public Tree()
        {
            TimeForWaterList = new List<Time>();

        }
        public String Name { get; set; }
        public int MaxTemperature { get; set; }
        public int MaxHumidity { get; set; }
        public int MinHumidity { get; set; }
        public List<Time> TimeForWaterList;
    }

    public class Time
    {
        public int Hour { get; set; }
        public int Minute { get; set; }
    }
}
