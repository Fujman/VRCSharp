using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VR
{
    public abstract class Event
    {
        protected ushort m_nClass;
        protected ushort m_nType;
        protected uint m_tTime;
        protected ushort m_nMsec;
        protected ushort m_nData;          // data (16 bits)
        

        // Temp method 
        public virtual void Created()
        {
            
        }

        public virtual void Show()
        {
            
        }

        public virtual void Write()
        {
            
        }

        public virtual string GetLine()
        {
            return null;
        }

        public static Event CreateObject(byte[] byte_arr)
        {
            int classId = byte_arr[0] & 0x03;
            ushort class_id = Convert.ToUInt16(classId);

            int typeId = byte_arr[0] & 0x3C;
            typeId = typeId >> 2;
            ushort type_id = Convert.ToUInt16(typeId);

            int imilliseconds = BitConverter.ToUInt16(byte_arr, 0);
            imilliseconds = imilliseconds >> 6;
            ushort milliseconds = Convert.ToUInt16(imilliseconds);

            ushort data = BitConverter.ToUInt16(byte_arr, 2);


            uint time = BitConverter.ToUInt32(byte_arr, 4);
            uint dword1 = BitConverter.ToUInt32(byte_arr,8);
            uint dword2 = BitConverter.ToUInt32(byte_arr,12);
            //dword1 = BitConverter.ToUInt32(byte_arr, 8);
            //dword2 = BitConverter.ToUInt32(byte_arr, 8);

            switch (class_id)
            {
                case 2:
                    switch (type_id)
                    {
                        case 1:
                            EventChan eventChan = new EventChan( milliseconds, data, time, dword1, dword2);
                            return eventChan;
                            
                        case 2:
                            EventApp eventApp = new EventApp( milliseconds, data, time, dword1, dword2);
                            return eventApp;
                            
                        default:
                            //Console.WriteLine("\n Unidentified type!");
                            return null;
                            
                    }
                case 3:
                    switch (type_id)
                    {
                        default:
                            ushort stringSize = Convert.ToUInt16(byte_arr[10]);
                            byte[] stringArr=new byte[stringSize];
                            for (int i = 16, j=0; j < stringSize; i++,j++)
                            {
                                stringArr[j] = byte_arr[i];
                            }
                            
                            EventString eventString= new EventString(milliseconds,data,time,stringSize,stringArr);
                            return eventString;
                    }
                    
                    
                    
                default:
                    //Console.WriteLine("\n Unidentified class!");
                    return null;
                    

            }
        }
        
    }
}
