using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VR
{
    class EventChan:Event
    {
        //private ushort m_nClass;
        //private ushort m_nType;
        //private uint m_tTime;
        //private ushort m_nMsec;
        //private ushort m_nData;(Message)         // data (16 bits)
        private uint m_dwData1;//(Channel)          // data (64 bits)
        private uint m_dwData2;
        //protected byte priority; // 1-10
        //protected byte messageType; // warning/ error / information

        public EventChan( ushort nMsec, ushort nData, uint tTime, uint dwData1, uint dwData2)
        {
            m_nClass = 0;
            m_nType = 1;
            m_tTime = tTime;
            m_nMsec = nMsec;
            m_nData = nData;
            m_dwData1 = dwData1;
            m_dwData2 = dwData2;
            messageText = ResourceHandler.getText(m_nData);
            setMessageTypePriority();

        }
        
        // Temp method 
        public override void Created()
        {
            Console.Write("\nEventChan object created!");
        }
        // Temp method
        public override void Show()
        {
            Console.WriteLine("Class:" + m_nClass);
            Console.Write(" | Type:" + m_nType);
            Console.Write(" | MessageID:" + m_nData);
            Console.Write(" | Time:"+ GetTimeEx());

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
                ulong finalVariable = (ulong)m_dwData2 << 32 | m_dwData1;

                messageText = messageText.Replace("%lu", finalVariable.ToString());
            }



            //IN PROGRESS

            if (messageText.Contains("%d"))
            {
                var m_dwData1_2 = m_dwData1 >>16; // taking last 2 bytes
                Int16 put = (Int16) m_dwData1_2;
                messageText = messageText.Replace("%d", put.ToString());
            }
            if (messageText.Contains("%.0d"))
            {
                var m_dwData1_1 = m_dwData1 & 0xFFFF;
                var put = m_dwData1_1;
                messageText = messageText.Replace("%.0d", put.ToString());
            }

        }

        //public override void Write()
        //{

        //    string text = "Class:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + m_nData + " | Time:" + GetTimeEx();
        //    // WriteAllText creates a file, writes the specified string to the file,
        //    // and then closes the file.
        //    using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\Users\Narek\Dump.txt", true))
        //    {
        //        file.WriteLine(text);
        //    }
        //}
        public override string GetLine()
        {   
            GetText();
            // to add variables
            string text = "Class:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + Convert.ToString(m_nData, 16) + " | Time:" + GetTimeEx() +"  "+ messageText;
            return text;
        }
    }
}
