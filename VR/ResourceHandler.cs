using System;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Reflection;

namespace VR
{
    class ResourceHandler
    {
       
        private  int[] messageIDs;
        private  string[] texts;
        private static ResourceHandler _handler;

        public static ResourceHandler GetHandler(int languageId)
        {
            if (_handler == null)
            {
                _handler = new ResourceHandler(languageId);
            }
            return _handler;
        }

        public static ResourceHandler GetHandler()
        {
            if (_handler != null)
            {
                return _handler;
            }
            else
            {
                _handler = new ResourceHandler(0);
                return _handler;
            }
        }
        private ResourceHandler(int languageId)
        {
            List<int> idsList = new List<int>();
            List<string> textsList = new List<string>();

            XmlDocument xDoc = new XmlDocument();

            Assembly _assembly;
            Stream _xmlStream = null;

            _assembly = Assembly.GetExecutingAssembly();
            
            


            switch (languageId)
            {
                case 0:
                    _xmlStream = _assembly.GetManifestResourceStream("VR.bin.Debug.messages_en.xml");
                    break;
                case 1:
                    _xmlStream = _assembly.GetManifestResourceStream("VR.bin.Debug.messages_ru.xml");    
                    break;
                default:
                    _xmlStream = _assembly.GetManifestResourceStream("VR.bin.Debug.messages_en.xml");
                    break;
                //case 2:
                //    xDoc.Load("messages_ua.xml");
                //    break;
                //case 3:
                //    xDoc.Load("messages_am.xml");
                //    break;
                //case 4:
                //    xDoc.Load("");
                //    break;
                //case 5:
                //    xDoc.Load("");
                //    break;
                //case 6:
                //    xDoc.Load("");
                //    break;

            }
            xDoc.Load(_xmlStream);
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

        public  string getText(int messageId)
        {
            int index = Array.IndexOf(messageIDs, messageId);
            string text = texts[index];
            return text;
        }
    }
}
