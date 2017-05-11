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
            Tree[0] = new Tree();
            Tree[1] = new Tree();
            Tree[2] = new Tree();
        }
        public String Name { get; set; }
        public int Id {get; set;}
        public Tree[] Tree;
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
        public List<Time> TimeForWaterList;
    }

    public class Time
    {
        public int Hour { get; set; }
        public int Minute { get; set; }
    }
}
