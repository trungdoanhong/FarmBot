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
                tempSeason.N = xmlSeasons[i]["Name"].InnerText;
                tempSeason.I = i + 1;

                String[] treeStrings = xmlSeasons[i]["Garden"].InnerText.Split(',');

                for (int index = 0; index < 24; index++)
                {
                    tempSeason.G[index] = int.Parse(treeStrings[index]);
                }

                int treeIndex = 0;
                foreach (XmlNode nodeOfSeason in xmlSeasons[i])
                {
                    if (nodeOfSeason.Name == "Tree")
                    {
                        tempSeason.T[treeIndex].N = nodeOfSeason["Name"].InnerText;
                        tempSeason.T[treeIndex].MaxT = int.Parse(nodeOfSeason["MaxTemp"].InnerText);
                        tempSeason.T[treeIndex].MaxH = int.Parse(nodeOfSeason["MaxHumi"].InnerText);
                        tempSeason.T[treeIndex].MinH = int.Parse(nodeOfSeason["MinHumi"].InnerText);
                        XmlNode timeForWaterNode = nodeOfSeason["TimeForWater"];
                        for (int index = 0; index < timeForWaterNode.ChildNodes.Count; index++)
                        {
                            Time time = new Time();
                            time.H = int.Parse(timeForWaterNode.ChildNodes[index]["Hour"].InnerText);
                            time.M = int.Parse(timeForWaterNode.ChildNodes[index]["Minute"].InnerText);
                            tempSeason.T[treeIndex].Times.Add(time);
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
                "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" +
                "<FarmBot>\n" +              
                "</FarmBot>";

            return xml;
        }

        public void FillSeasonName(ComboBox cbSeasonName)
        {
            foreach(Season season in Seasons)
            {
                cbSeasonName.Items.Add(season.N);
            }
            if (cbSeasonName.Items.Count > 0)
                cbSeasonName.SelectedIndex = 0;
        }

        public Season LoadSeason(string seasonName)
        {
            foreach(Season season in Seasons)
            {
                if (season.N == seasonName)
                {
                    LoadingSeason = season;
                }
            }
            return LoadingSeason;
        }

        public void UpdateSeason(Season loadingSeason)
        {
            this.LoadingSeason = loadingSeason;

            XmlNode newSeasonNode = CreateSeasonNode(loadingSeason);

            XmlNode replaceNode = LoadingXML.DocumentElement.ChildNodes[LoadingSeason.I - 1];
            LoadingXML.DocumentElement.ReplaceChild(newSeasonNode, replaceNode);

            LoadingXML.Save(XmlFileName);
             
        }

        private XmlNode CreateSeasonNode(Season seasonForCreateNode)
        {
            XmlNode newSeasonNode = LoadingXML.CreateElement("Season");
            XmlNode newSeasonName = LoadingXML.CreateElement("Name");
            XmlNode newGarden = LoadingXML.CreateElement("Garden");
            XmlAttribute newSeasonId = LoadingXML.CreateAttribute("id");

            newSeasonName.InnerText = seasonForCreateNode.N;
            newSeasonId.InnerText = seasonForCreateNode.I.ToString();

            String gardenString = "";

            for (int i = 0; i < 24; i++)
            {
                gardenString += seasonForCreateNode.G[i];
                if (i < 23)
                {
                    gardenString += ",";
                }
            }
            newGarden.InnerText = gardenString;

            newSeasonNode.AppendChild(newSeasonName);
            newSeasonNode.AppendChild(newGarden);
            newSeasonNode.Attributes.Append(newSeasonId);

            XmlNode[] newTree = new XmlNode[3];
            for (int index = 0; index < 3; index++)
            {
                newTree[index] = LoadingXML.CreateElement("Tree");
                XmlNode newTreeName = LoadingXML.CreateElement("Name");
                XmlNode newMaxTemp = LoadingXML.CreateElement("MaxTemp");
                XmlNode newMaxHumi = LoadingXML.CreateElement("MaxHumi");
                XmlNode newMinHumi = LoadingXML.CreateElement("MinHumi");
                XmlNode newTimeForWater = LoadingXML.CreateElement("TimeForWater");
                XmlAttribute newTreeId = LoadingXML.CreateAttribute("id");

                newTreeName.InnerText = seasonForCreateNode.T[index].N;
                newMaxTemp.InnerText = seasonForCreateNode.T[index].MaxT.ToString();
                newMaxHumi.InnerText = seasonForCreateNode.T[index].MaxH.ToString();
                newMinHumi.InnerText = seasonForCreateNode.T[index].MinH.ToString();
                newTreeId.InnerText = (index + 1).ToString();

                // Add parameter into Tree

                newTree[index].AppendChild(newTreeName);
                newTree[index].AppendChild(newMaxTemp);
                newTree[index].AppendChild(newMaxHumi);
                newTree[index].AppendChild(newMinHumi);
                newTree[index].AppendChild(newTimeForWater);
                newTree[index].Attributes.Append(newTreeId);

                // Add time into TimeForWater
                for (int i = 0; i < seasonForCreateNode.T[index].Times.Count; i++)
                {
                    XmlNode newTime = LoadingXML.CreateElement("Time");
                    XmlNode newHour = LoadingXML.CreateElement("Hour");
                    XmlNode newMinute = LoadingXML.CreateElement("Minute");
                    XmlAttribute newTimeId = LoadingXML.CreateAttribute("id");

                    newHour.InnerText = seasonForCreateNode.T[index].Times[i].H.ToString();
                    newMinute.InnerText = seasonForCreateNode.T[index].Times[i].M.ToString();
                    newTimeId.InnerText = (i + 1).ToString();

                    newTime.AppendChild(newHour);
                    newTime.AppendChild(newMinute);
                    newTime.Attributes.Append(newTimeId);

                    newTimeForWater.AppendChild(newTime);

                }

                // Add Tree into Season
                newSeasonNode.AppendChild(newTree[index]);
            }
            return newSeasonNode;
        }

        public Season CreateSeason(String SeasonName)
        {
            Season creatingSeason = new Season();
            creatingSeason.N = SeasonName;
            creatingSeason.I = Seasons.Count + 1;

            Seasons.Add(creatingSeason);

            XmlNode creatingSeasonNode = CreateSeasonNode(creatingSeason);
            LoadingXML.DocumentElement.AppendChild(creatingSeasonNode);

            LoadingXML.Save(XmlFileName);

            return creatingSeason;
        }

        public bool DeleteSeason(String seasonName)
        {
            int deleteSeasonOrder = -1;
            for (int index = 0; index < Seasons.Count; index++ )
            {
                if (Seasons[index].N == seasonName)
                {
                    deleteSeasonOrder = index;
                    break;
                }
            }            

            if (deleteSeasonOrder == -1)
                return false;

            for (int index = 0; index < Seasons.Count; index++)
            {
                Seasons[index].I = index + 1;
            }

            Seasons.RemoveAt(deleteSeasonOrder);
            DeleteSeasonNode(seasonName);

            return true;
        }

        public bool DeleteSeasonNode(String seasonName)
        {
            XmlNode deleteSeasonNode = null;
            XmlNodeList seasonNodes = LoadingXML.DocumentElement.ChildNodes;

            for (int i = 0; i < seasonNodes.Count; i++ )
            {
                if (seasonNodes[i]["Name"].InnerText == seasonName)
                {
                    deleteSeasonNode = seasonNodes[i];
                }
            }

            if (deleteSeasonNode == null)
                return false;
            
            LoadingXML.DocumentElement.RemoveChild(deleteSeasonNode);

            seasonNodes = LoadingXML.DocumentElement.ChildNodes;

            for (int i = 0; i < seasonNodes.Count; i++)
            {
                seasonNodes[i].Attributes["id"].InnerText = (i + 1).ToString();                
            }

            LoadingXML.Save(XmlFileName);

            return true;
        }
    }
}
