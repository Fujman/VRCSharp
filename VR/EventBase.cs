using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;




namespace VR
{
    public class Constatns
    {
        public const byte EVN_64BIT_CLASS = 0;
        public const byte EVN_16BIT_CLASS = 1;
        public const byte EVN_20BIT_CLASS = 2;
        public const byte EVN_xxBIT_CLASS = 3;
    }
    public class tagYEventBaseData            // 64 bits (8 bytes)   // data: 16 bits (2 bytes)
    {                                   // = EVN_16BIT_CLASS (1)
        protected ushort m_nClass;
        protected ushort m_nType;
        protected ushort m_nMsec;
        protected ushort m_nData;         // data (16 bits)
        protected uint   m_tTime;
        
    }

    public class tagYEventBaseData64 :tagYEventBaseData          // 128 bits (16 bytes) // data: 80 bits (10 bytes)
    {
        //private ushort m_nClass;
        //private ushort m_nType;
        //private ushort m_nMsec;
        //private ushort m_nData;          // data (16 bits)
        //private uint m_tTime;
        protected uint m_dwData1;          // data (64 bits)
        protected uint m_dwdata2;          // --||--||--
    }

    public class tagYEventBaseDataEx:tagYEventBaseData  // 128 bits (16 bytes) // data: 80 bits (10 bytes)
    {
        //private ushort m_nClass;
        //private ushort m_nType;
        //private ushort m_nMsec;
        //private ushort m_nData;         // message ID
        //private uint m_tTime;
        private ushort m_nYeranSec;     // time_t extension to YTime - in 100ns units(14 bits)// time_t extension to YTime - must be zero (2 bits)
        private ushort m_nSize;         // data size, bytes
        private uint   m_nSignature;      // data type
    }

    /// /////////////////////////////////////////////////////////////////////////////
    public class YEventBaseData : tagYEventBaseData
    {
        public ushort GetClass()
        {
            return m_nClass;
        }

        public ushort GetType()
        {
            return m_nClass == Constatns.EVN_20BIT_CLASS ? (ushort)0 : m_nType;
        }

        public ushort GetMessageID()
        {
            return m_nData;
        }

        

        public void SetClass(ushort nClass)
        {
            if(nClass<=3)
            m_nClass = nClass;
        }

        public void SetType(ushort nType)
        {
            if(nType<=15)
            m_nType = nType;
        }

        public void SetmessageID(ushort nMessageID)
        {
            m_nData = nMessageID;
        }

        public uint GetTime(ushort pn_Msec)
        {
            if (pn_Msec != 0)
                pn_Msec = m_nMsec;
            return m_tTime;
        }

        public void SetTime(uint tTime, ushort nMsec = 0)
        {
            m_tTime = tTime;
            m_nMsec = nMsec;

        }
        public void Invalidate()
        {
            
        }

        public DateTime GetTimeEx()
        {
            DateTime datetime = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            datetime.AddSeconds(m_tTime);
            datetime.AddMilliseconds(m_nMsec);
            return datetime;

        }

        public void SetTimeEx(DateTime tTime)
        {
            var delta = tTime - new DateTime(1970, 1, 1);
            m_tTime = Convert.ToUInt32(delta.TotalSeconds);
            m_nMsec = Convert.ToUInt16(delta.Milliseconds);

        }

        public void SetTimeEx()
        {
            SetTimeEx(DateTime.Now);
        }

        public uint GetSignature()
        {
            return 0;
        }

        public unsafe  void memcpy(void* dst, void* src, int count)
        {
            const int blockSize = 4096;
            byte[] block = new byte[blockSize];
            byte* d = (byte*)dst, s = (byte*)src;
            for (int i = 0, step; i < count; i += step, d += step, s += step)
            {
                step = count - i;
                if (step > blockSize)
                {
                    step = blockSize;
                }
                Marshal.Copy(new IntPtr(s), block, 0, step);
                Marshal.Copy(block, 0, new IntPtr(d), step);
            }
        }
        public unsafe uint GetSize()
        {
            return 0;
        }
        public unsafe void* GetData(void *pRawData, int nMaxSize, uint nOffset) 
        {
        uint nNeed = GetSize();
        if (nOffset>nNeed)
        return null;
        if (nMaxSize != 0 && (uint) nMaxSize<nNeed - nOffset)
        return null;
        void* pData = GetData();
        if (nNeed - nOffset == 0 || pData == null)
        return pRawData;
        if (pData != null)
        pData = (void*) ((( byte*) pData) + nOffset);
        memcpy(pRawData,  pData,   Convert.ToInt32(nNeed - nOffset));
        return pRawData;
        }

        public unsafe void* GetData()
        {
        bool bxx = (m_nClass == 3);
        bool b64 = (m_nClass == 0);
        bool b20 = (m_nClass == 2);
        bool b16 = (m_nClass == 1);
        //if (bxx) return (void*) (((struct tagYEventBaseDataEx*)this) + 1);
        //if (b64) return (void*) (((struct tagYEventBaseData*)this) + 1);
        //if (b20) return (void*) &m_nData;
        //if (b16) return (void*) &m_nData;
        return null;//never reached
        }

        public unsafe void* SetData(void* pRawData, int nRawSize, uint nOffset)
        {
            uint nNeed = GetSize();
            if (nRawSize != 0 && (uint)nRawSize + nOffset > nNeed)
                return null;
            if (nRawSize != 0 && (uint)nRawSize + nOffset < nNeed)
                nNeed = (uint)nRawSize + nOffset;
            void* pData = GetData();
            if (nNeed - nOffset == 0 || pData == null)
                return pData;
            if (pData != null)
                pData = (void*)(((byte*)pData) + nOffset);
            memcpy(pData, pRawData, Convert.ToInt32(nNeed - nOffset));
            return pData;
        }

        //public unsafe int SizeOf()
        //{
        //    return (Marshal.SizeOf(this));
        //}
       

        public unsafe void* SetData()
        {
            return null;
        }
         zfjdsakljdfljksdkljfjksdf 


             sdf
             sd
             f
             s
             df
    }

}   

