using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//IN PROGRESS
namespace VR
{
    class EventString:Event
    {
        //private ushort m_nClass;
        //private ushort m_nType;
        //private uint m_tTime;
        //private ushort m_nMsec;
        //private ushort m_nData;(Message)          // data (16 bits)
        private string m_str;
        private ushort m_nSize;

        public EventString(ushort nMsec, ushort nData, uint tTime,ushort nSize, byte[] stringMessageArr)
        {
            m_nClass = 3;
            m_nType = 1;// Temp
            m_nMsec = nMsec;
            m_nData = nData;
            m_tTime = tTime;
            m_nSize = nSize;
            m_str = Encoding.Unicode.GetString(stringMessageArr);

        }
        public DateTime GetTimeEx()
        {
            DateTime datetime = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            datetime = datetime.AddSeconds(m_tTime);
            datetime = datetime.AddMilliseconds(m_nMsec);
            return datetime;

        }
        //public override void Write()
        //{

        //    string text = "Class:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + m_nData + " | Time:" + GetTimeEx()+"String message:"+ m_str;
        //    // WriteAllText creates a file, writes the specified string to the file,
        //    // and then closes the file.
        //    using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\Users\Narek\Dump.txt", true))
        //    {
        //        file.WriteLine(text);
        //    }
        //}

        public override string GetLine()
        {
            string text = "Class:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + Convert.ToString(m_nData,16) + " | Time:" + GetTimeEx() + "String message:" + m_str;
            return text;
        }
    }
}
