using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Schema;

namespace FarmBot_Software
{
    class FarmBotXml
    {
        private XmlDocument LoadingXML;
        private String XMLFileName;
        private List<Season> Seasons;
        private Season LoadingSeason;
        private String XmlFileName;

        public FarmBotXml(String fileName, bool generateXML)
        {
            XmlFileName = fileName;

            LoadingXML = new XmlDocument();
            Seasons = new List<Season>();

            LoadDocument(XmlFileName, generateXML);
            ParseDocumentToStructData();
        }

        private void ParseDocumentToStructData()
        {
            XmlNodeList xmlSeasons = LoadingXML.DocumentElement.ChildNodes;
            for (int i = 0; i < xmlSeasons.Count; i++)
            {
                Season tempSeason = new Season();
                tempSeason.Name = xmlSeasons[i]["Name"].InnerText;
                tempSeason.Id = i + 1;

                int treeIndex = 0;
                foreach (XmlNode nodeOfSeason in xmlSeasons[i])
                {
                    if (nodeOfSeason.Name == "Tree")
                    {
                        tempSeason.Tree[treeIndex].Name = nodeOfSeason["Name"].InnerText;
                        tempSeason.Tree[treeIndex].MaxTemperature = int.Parse(nodeOfSeason["MaxTemp"].InnerText);
                        tempSeason.Tree[treeIndex].MaxHumidity = int.Parse(nodeOfSeason["MaxHumi"].InnerText);
                        XmlNode timeForWaterNode = nodeOfSeason["TimeForWater"];
                        for (int index = 0; index < timeForWaterNode.ChildNodes.Count; index++)
                        {
                            Time time = new Time();
                            time.Hour = int.Parse(timeForWaterNode.ChildNodes[index]["Hour"].InnerText);
                            time.Minute = int.Parse(timeForWaterNode.ChildNodes[index]["Minute"].InnerText);
                            tempSeason.Tree[treeIndex].TimeForWaterList.Add(time);
                        }

                        treeIndex++;
                    }
                }
                Seasons.Add(tempSeason);
            }
        }
        public XmlDocument LoadDocument(String fileName, bool generateXML)
        {
            XMLFileName = fileName;
            //LoadingXML.PreserveWhitespace = true;
            try
            {
                LoadingXML.Load(XMLFileName);
            }
            catch (System.IO.FileNotFoundException)
            {
                if (generateXML)
                {
                    string xml = generateXMLString();
                    LoadingXML.LoadXml(xml);
                    LoadingXML.Save(fileName);
                }
                else
                {
                    return null;
                }
            }
            return LoadingXML;
        }

        private string generateXMLString()
        {
            string xml =
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
                "<FarmBot>" +
                "  <Season id=\"New Name\">" +
                "    <Name>\"Season 1\"</Name>" +
                "    <Tree id=\"1\">" +
                "      <Name>\"Tree 1\"</Name>" +
                "      <MaxTemp>40</MaxTemp>" +
                "      <MaxHumi>50</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "    <Tree id=\"2\">" +
                "      <Name>\"Tree 2\"</Name>" +
                "      <MaxTemp>50</MaxTemp>" +
                "      <MaxHumi>40</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "    <Tree id=\"3\">" +
                "      <Name>\"Tree 3\"</Name>" +
                "      <MaxTemp>45</MaxTemp>" +
                "      <MaxHumi>60</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "  </Season>" +
                "  <Season id=\"2\">" +
                "    <Name>\"Season 2\"</Name>" +
                "    <Tree id=\"1\">" +
                "      <Name>\"Tree 1\"</Name>" +
                "      <MaxTemp>40</MaxTemp>" +
                "      <MaxHumi>50</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "    <Tree id=\"2\">" +
                "      <Name>\"Tree 2\"</Name>" +
                "      <MaxTemp>50</MaxTemp>" +
                "      <MaxHumi>40</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "    <Tree id=\"3\">" +
                "      <Name>\"Tree 3\"</Name>" +
                "      <MaxTemp>45</MaxTemp>" +
                "      <MaxHumi>60</MaxHumi>" +
                "      <TimeForWater>" +
                "        <Time id=\"1\">" +
                "          <Hour>12</Hour>" +
                "          <Minute>15</Minute>" +
                "        </Time>" +
                "      </TimeForWater>" +
                "    </Tree>" +
                "  </Season>" +
                "</FarmBot>";

            return xml;
        }

        public void FillSeasonName(ComboBox cbSeasonName)
        {
            foreach(Season season in Seasons)
            {
                cbSeasonName.Items.Add(season.Name);
            }
            cbSeasonName.SelectedIndex = 0;
        }

        public Season LoadSeason(string seasonName)
        {
            foreach(Season season in Seasons)
            {
                if (season.Name == seasonName)
                {
                    LoadingSeason = season;
                }
            }
            return LoadingSeason;
        }

        public void UpdateSeason(Season loadingSeason)
        {
            this.LoadingSeason = loadingSeason;

            XmlNode newSeasonNode = LoadingXML.CreateElement("Season");
            XmlNode newSeasonName = LoadingXML.CreateElement("Name");
            XmlAttribute newSeasonId = LoadingXML.CreateAttribute("id");

            newSeasonName.InnerText = LoadingSeason.Name;            
            newSeasonId.InnerText = LoadingSeason.Id.ToString();

            newSeasonNode.AppendChild(newSeasonName);
            newSeasonNode.Attributes.Append(newSeasonId);

            XmlNode[] newTree = new XmlNode[3];
            for(int index = 0; index < 3; index++)
            {
                newTree[index] = LoadingXML.CreateElement("Tree");
                XmlNode newTreeName = LoadingXML.CreateElement("Name");
                XmlNode newMaxTemp = LoadingXML.CreateElement("MaxTemp");
                XmlNode newMaxHumi = LoadingXML.CreateElement("MaxHumi");
                XmlAttribute newTreeId = LoadingXML.CreateAttribute("id");

                newTreeName.InnerText = LoadingSeason.Tree[index].Name;
                newMaxTemp.InnerText = LoadingSeason.Tree[index].MaxTemperature.ToString();
                newMaxHumi.InnerText = LoadingSeason.Tree[index].MaxHumidity.ToString();
                newTreeId.InnerText = (index + 1).ToString();

                newTree[index].AppendChild(newTreeName);
                newTree[index].AppendChild(newMaxTemp);
                newTree[index].AppendChild(newMaxHumi);

                newSeasonNode.AppendChild(newTree[index]);
            }

            XmlNode replaceNode = LoadingXML.DocumentElement.ChildNodes[LoadingSeason.Id - 1];
            LoadingXML.DocumentElement.ReplaceChild(newSeasonNode, replaceNode);

            LoadingXML.Save(XmlFileName);
             
        }
    }
}
