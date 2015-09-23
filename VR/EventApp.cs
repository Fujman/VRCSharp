using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VR
{
    class EventApp:Event
    {
        //private ushort m_nClass;
        //private ushort m_nType;
        //private uint m_tTime;
        //private ushort m_nMsec;
        //private ushort m_nData;(Message)         // data (16 bits)
        private uint m_dwData1;          // data (64 bits)
        private uint m_dwData2;
        //protected byte priority; // 1-10
        //protected byte messageType; // warning/ error / information
        

        public EventApp( ushort nMsec, ushort nData, uint tTime, uint dwData1, uint dwData2)
        {
            m_nClass = 0;
            m_nType = 2;
            m_nMsec = nMsec;
            m_nData = nData;
            m_tTime = tTime;
            m_dwData1 = dwData1;
            m_dwData2 = dwData2;
            messageText = ResourceHandler.getText(m_nData);
            setMessageTypePriority();

        }
        // Temp method 
        public override void Created()
        {
            Console.WriteLine("\nEventApp object created!");
        }
        public override void Show()
        {
            Console.Write("\nClass:" + m_nClass);
            Console.Write(" | Type:" + m_nType);
            Console.Write(" | MessageID:" + m_nData);
            Console.Write(" | Time: " + GetTimeEx());

        }
        public DateTime GetTimeEx()
        {
            DateTime datetime = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            datetime = datetime.AddSeconds(m_tTime);
            datetime = datetime.AddMilliseconds(m_nMsec);
            return datetime;

        }

        private void GetText()
        {
            if (messageText.Contains("%lu"))
            {
                // making 64-bit variable from 2 32-bit ones
                ulong finalVariable = (ulong) m_dwData2 << 32 | m_dwData1;

                messageText = messageText.Replace("%lu", finalVariable.ToString());
            }

            if (messageText.Contains("%Z"))
            {
                int nCase = (int)m_dwData1;
                int nData = (int) m_dwData2;


                string szCase = "";
                int iEnd = 0;
                for (int i = 0; i < messageText.Length; ++i)
                {
                    char asd = messageText[i];
                    if (messageText[i] == '\\' && i < messageText.Length - 1 && messageText[i + 1] == 'n')
                    {
                        if (iEnd == (int)nCase)
                        {
                            szCase = messageText.Substring(i + 2);
                            break;
                        }
                        ++iEnd;
                    }
                }

                if (szCase.Length > 0)
                {
                    int iPos = szCase.IndexOf('\\');
                    if (iPos >= 0)
                        szCase = szCase.Remove(iPos, szCase.Length - iPos);
                }

                int z_index = messageText.IndexOf("%Z");
                messageText = messageText.Remove(z_index).Insert(z_index, szCase);
            }


            if (messageText.Contains("%8.8X"))
            {
                messageText = messageText.Replace("%8.8X", m_dwData2.ToString("X8"));
            }

        }

        public override string  GetLine()
        {
            GetText();
            string text = "\nClass:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + Convert.ToString(m_nData, 16) +
                          " | Time:" + GetTimeEx()+" | Ints: "+Convert.ToString(m_dwData1,16)+"  "+Convert.ToString(m_dwData2,16) +"  " + messageText;
            return text;    
        }

    }
}
