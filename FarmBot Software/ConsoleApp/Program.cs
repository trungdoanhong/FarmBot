using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<book ISBN='1-861001-57-5'>" +
                        "<title><main>You</main><sub>me</sub></title>" +
                        "<price>19.95</price>" +
                        "</book>");

            XmlNode root = doc.FirstChild;

            //Display the contents of the child nodes.
            if (root.HasChildNodes)
            {
                for (int i = 0; i < root.ChildNodes.Count; i++)
                {
                    if (root.ChildNodes[i].Name == "title")
                        for (int j = 0; j < root.ChildNodes[i].ChildNodes.Count; j++)
                        {
                            Console.WriteLine(root.ChildNodes[i].ChildNodes[j].InnerText);
                        }
                }
            }
            Console.ReadKey();
        }
    }
}
