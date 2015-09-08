using System;

namespace VR
{

    public abstract class Event
    {
        protected const byte INFORMATION = 1;
        protected const byte WARNING = 2;
        protected const byte ERROR = 3;


        protected ushort m_nClass;
        protected ushort m_nType;
        protected uint m_tTime;
        protected ushort m_nMsec;
        protected ushort m_nData;          // data (16 bits)
        protected string messageText; // text of message from xml
        protected byte priority; // 1-10
        protected byte messageType; // warning/ error / information


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

        public virtual void setMessageTypePriority()
        {
            if (messageText.Substring(0, 1) == "$")
            {
                switch (messageText.Substring(1,1))
                {
                    case "I":
                        messageType = INFORMATION;
                        break;
                    case "W":
                        messageType = WARNING;
                        break;
                    case "E":
                        messageType = ERROR;
                        break;
                }
                priority = Convert.ToByte(messageText.Substring(2, 1));

                var replaced = messageText.Substring(0, 3);
                messageText = messageText.Replace(replaced, " ");
            }
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
            
            //dword1 = BitConverter.ToUInt32(byte_arr, 8);
            //dword2 = BitConverter.ToUInt32(byte_arr, 8);

            switch (class_id)
            {
                case 0:
                    switch (type_id)
                    {
                        case 1:
                            uint dword1ch = BitConverter.ToUInt32(byte_arr,8);
                            uint dword2ch = BitConverter.ToUInt32(byte_arr,12);
                            EventChan eventChan = new EventChan( milliseconds, data, time, dword1ch, dword2ch);
                            return eventChan;
                            
                        case 2:
                            uint dword1app = BitConverter.ToUInt32(byte_arr,8);
                            uint dword2app = BitConverter.ToUInt32(byte_arr,12);
                            EventApp eventApp = new EventApp( milliseconds, data, time, dword1app, dword2app);
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
