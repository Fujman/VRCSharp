using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
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
            var handler = ResourceHandler.GetHandler();
            messageText = handler.getText(nData);
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
            if (messageText.Contains("%Y"))
            {
                uint uData1 = m_dwData1;
                uint uData2 = m_dwData2;
                uint uMask = 1;
                bool Continue = false;

                string szBits = "";

                for (int i = 0; i < 32; i++, uMask <<= 1)
                {
                    // checking first variable
                    uint conj = uData1 & uMask;
                    if (conj != 0)
                    {
                        if (Continue)
                        {
                            szBits += ",";
                        }
                        else
                        {
                            Continue = true;
                            // checking second variable

                        }
                        uint conj2;
                        conj2 = uData2 & uMask;
                        szBits += i.ToString() + (conj2 == 0 ? " -off" : " -on");
                    }
                }

                //Console.WriteLine(szBits);
                //Console.ReadKey();
                messageText = messageText.Replace("%Y", szBits);

                if (messageText.Contains("%.0d"))
                {
                    //messageText = messageText.Replace("%.0d", m_dwData2.ToString("d"));
                    messageText = messageText.Replace("%.0d", " ");
                    if (messageText.Contains("%8.8x"))
                    {
                        messageText = messageText.Replace("%8.8x", m_dwData1.ToString("X"));
                    }
                }
            }
            if (messageText.Contains("%lu"))
            {

                //temp
                if (m_nData == 32856)
                {
                    int firstIndex;
                    firstIndex = messageText.IndexOf("%lu");
                    messageText = messageText.Remove(firstIndex, 3).Insert(firstIndex, m_dwData1.ToString());

                    int lastIndex;
                    lastIndex = messageText.LastIndexOf("%lu");
                    messageText = messageText.Remove(lastIndex, 3).Insert(lastIndex, m_dwData2.ToString());
                }
                else
                {
                    // making 64-bit variable from 2 32-bit ones
                    ulong finalVariable = (ulong)m_dwData2 << 32 | m_dwData1;

                    messageText = messageText.Replace("%lu", finalVariable.ToString());
                }
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

            if (messageText.Contains("%ld"))
            {
                messageText = messageText.Replace("%ld", m_dwData1.ToString("d"));
            }

            if (messageText.Contains("%s"))
            {
                messageText = messageText.Replace("%s", s_handler());
            }

            
        }

        // %s placeholder handler
        public unsafe string s_handler()
        {

            tagDW2STR dw1Str,dw2Str = new tagDW2STR();
            

            char[] sz = new char[9];
            dw1Str.ui = m_dwData1;
            dw2Str.ui = m_dwData2;
            dw1Str.ui ^= 0xAEAEAEAE;
            dw2Str.ui ^= 0xEAEAEAEA;

            for (int i = 0; i < 4; i++)
            {
                sz[i] =(char) dw1Str.ab[i];
            }
            for (int i = 0; i < 4; i++)
            {
                sz[i + 4] = (char) dw2Str.ab[i];
            }
            sz[8] = '\0';
            
            string s = new string(sz);
            return s;
        }

        public override string  GetLine()
        {
            GetText();
            string text = "\nClass:" + m_nClass + " | Type:" + m_nType + " | MessageID:" + Convert.ToString(m_nData, 16) +
                          " | Time:" + GetTimeEx()+
                          //" | Ints: "+Convert.ToString(m_dwData1,16)+"  "+Convert.ToString(m_dwData2,16) +
                          "  " + messageText;
            return text;    
        }


        //Structs for %s placeholder handling

        [StructLayout(LayoutKind.Explicit, Pack = 1)]
        public struct DataStruct
        {
            [FieldOffset(0)]
            public ushort sh;
            [FieldOffset(2)]
            public uint ui;
            [FieldOffset(6)]
            public byte ab;

        }

        [StructLayout(LayoutKind.Explicit, Pack = 1)]
        unsafe public struct tagSTR
        {
            [FieldOffset(0)]
            public DataStruct dataStruct;
            [FieldOffset(0)]
            public fixed byte ab[6];

        }

        [StructLayout(LayoutKind.Explicit, Pack =1)]
        unsafe public struct tagDW2STR
        {
            [FieldOffset(0)] 
            public uint ui;

            [FieldOffset(0)] 
            public fixed byte ab [4];
        }


    }
}
