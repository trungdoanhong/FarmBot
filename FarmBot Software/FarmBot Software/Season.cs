using System;
using System.Collections.Generic;
using System.Text;

namespace FarmBot_Software
{
    public class Season
    {
        public Season()
        {
            T = new Tree[3];
            
            for(int i = 0; i < T.Length; i++)
            {
                T[i] = new Tree();
                T[i].N = "Tree " + (i + 1).ToString();
                T[i].MaxH = 40;
                T[i].MaxT = 40;

            }
            G = new int[24];
            for( int i = 0; i < 24; i++)
            {
                G[i] = 0;
            }

        }
        public String N { get; set; }
        public int I {get; set;}
        public Tree[] T;
        public int[] G;
    }
    public class Tree
    {
        public Tree()
        {
            Times = new List<Time>();

        }
        public String N { get; set; }
        public int MaxT { get; set; }
        public int MaxH { get; set; }
        public int MinH { get; set; }
        public List<Time> Times;
    }

    public class Time
    {
        public int H { get; set; }
        public int M { get; set; }
    }
}
