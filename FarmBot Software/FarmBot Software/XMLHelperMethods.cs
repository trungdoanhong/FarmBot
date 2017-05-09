using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Schema;

namespace FarmBot_Software
{
    class XMLHelperMethods
    {
        public XmlDocument LoadDocument(bool generateXML)
        {
            XmlDocument doc = new XmlDocument();
            doc.PreserveWhitespace = true;
            try
            {
                doc.Load(Constants.DatabaseFileName);
            }
            catch (System.IO.FileNotFoundException)
            {
                // If specifies that they want to generate XML when the data file is
                // not found, then generate some XML for them to start with.
                if (generateXML)
                {
                    string xml = generateXMLString();
                    doc.LoadXml(xml);
                }
                else
                {
                    return null;
                }
            }
            return doc;
        }

        private string generateXMLString()
        {
            string xml = "<?xml version=\"1.0\" encoding=\"utf-8\" ?> \n" +
                "<FarmBot> \n" +
                    "<Season name =\"Season 1\"> + \n" +
                        "<Tree id=\"1\"> + \n" + 
                          "<Name>\"Tree 1\"</Name> + \n" +
                          "<MaxTemp>40</MaxTemp> + \n" +
                          "<MaxHumi>50</MaxHumi> + \n" +
                          "<TimeForWater> + \n" +
                            "<ID>1</ID> + \n" +
                            "<Hour>12</Hour> + \n" +
                            "<Minute>15</Minute> + \n" +
                          "</TimeForWater>  + \n" +
                        "</Tree>  + \n" +
                        "<Tree id=\"2\"> + \n" +
                          "<Name>\"Tree 2\"</Name> + \n" +
                          "<MaxTemp>60</MaxTemp> + \n" +
                          "<MaxHumi>50</MaxHumi> + \n" +
                          "<TimeForWater> + \n" +
                            "<ID>1</ID> + \n" +
                            "<Hour>12</Hour> + \n" +
                            "<Minute>15</Minute> + \n" +
                          "</TimeForWater>  + \n" +
                        "</Tree>  + \n" +
                        "<Tree id=\"3\"> + \n" +
                          "<Name>\"Tree 3\"</Name> + \n" +
                          "<MaxTemp>30</MaxTemp> + \n" +
                          "<MaxHumi>50</MaxHumi> + \n" +
                          "<TimeForWater> + \n" +
                            "<ID>1</ID> + \n" +
                            "<Hour>12</Hour> + \n" +
                            "<Minute>15</Minute> + \n" +
                          "</TimeForWater>  + \n" +
                        "</Tree>  + \n" +
                "</FarmBot>";
            return xml;
        }

        public XmlNode GetSeason(string uniqueAttribute, XmlDocument doc)
        {
            XmlNamespaceManager nsmgr = new XmlNamespaceManager(doc.NameTable);
            nsmgr.AddNamespace("bk", "http://www.contoso.com/books");
            string xPathString = "//bk:books/bk:book[@ISBN='" + uniqueAttribute + "']";
            XmlNode xmlNode = doc.DocumentElement.SelectSingleNode(xPathString, nsmgr);
            return xmlNode;
        }
    }
}
