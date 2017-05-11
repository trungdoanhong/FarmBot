using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace ConsoleApp
{
    class A
    {
        public A()
        {
            value = 1;
        }

        public int value;
    }


    class Program
    {
        
        public static void Main()
        {

            XmlDocument doc = new XmlDocument();
            doc.Load("books.xml");

            const String seasonName = "Season 1";

            XmlNodeList seasons = doc.DocumentElement.ChildNodes;
            for (int i = 0; i < seasons.Count; i++)
            {
                if (seasons[i].Attributes["id"].InnerText == "1")
                {
                    Console.WriteLine(seasons[i].Attributes["id"].InnerText);
                    seasons[i].Attributes["id"].Value = "New Name";
                    foreach (XmlNode nodeOfSeason in seasons[i])
                    {
                        if (nodeOfSeason.Name == "Tree")
                        {
                            XmlNode timeForWater = nodeOfSeason["TimeForWater"];
                            XmlNodeList times = timeForWater.ChildNodes;
                            //XmlNode id = doc.CreateElement("ID");
                            //XmlNode time = doc.CreateElement("Time");
                            //time.AppendChild(id);
                            //timeForWater.AppendChild(time);
                            XmlNode deleteTime = times[1];
                            timeForWater.RemoveChild(deleteTime);
                        }
                    }
                }
            }

            doc.Save("books.xml");

            Console.ReadKey();

        }

        
    }
}
