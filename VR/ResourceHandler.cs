using System;
using System.Collections.Generic;
using System.Xml;

namespace VR
{
    static class ResourceHandler
    {
        private static int[] messageIDs;
        private static string[] texts;

        static  ResourceHandler()
        {
            List<int> idsList = new List<int>();
            List<string> textsList = new List<string>();

            XmlDocument xDoc = new XmlDocument();
            xDoc.Load("messages_en.xml");
            // получим корневой элемент
            XmlElement xRoot = xDoc.DocumentElement;
            // обход всех узлов в корневом элементе
            foreach (XmlNode xnode in xRoot)
            {

                // обходим все дочерние узлы элемента user
                foreach (XmlNode childnode in xnode.ChildNodes)
                {
                    
                    // если узел - messageID
                    if (childnode.Name == "messageID")
                    {
                        idsList.Add(Convert.ToInt32(childnode.InnerText, 16)); 
                    }
                   
                    if (childnode.Name == "text")
                    {
                        textsList.Add(childnode.InnerText);
                    }
                }
               
            }
            texts = textsList.ToArray();
            messageIDs = idsList.ToArray();
        }

        public static string getText(int messageId)
        {
            int index = Array.IndexOf(messageIDs, messageId);
            string text = texts[index];
            return text;
        }
    }
}
