using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VR
{
    class FsRead
    {
        private readonly byte[] _byteArray;
        private int i=16;

        public FsRead(string path="c:\\mrec.log")
        {
            //Create a file stream from an existing file.
            FileInfo fi = new FileInfo(path);
            FileStream fs = fi.OpenRead();
            
            //Read 4096 bytes into an array from the specified file.

            
           // const int nBytes = 4096;
            byte[] byteArray = new byte[fs.Length];
            int nBytesRead = fs.Read(byteArray, 0,(int) fs.Length);
            Console.WriteLine("{0} bytes have been read from the specified file.", nBytesRead);
            _byteArray = byteArray;
        }

        public byte[] GetArrayFromFile()
        {
            if (_byteArray.Length < i + 30)
                return null;

            //presumably skips title
            if (_byteArray[i]==0x3c)
            {
                i += 16;
            }

            switch (getClass(i))
            {
                case 0:
                    byte [] shortArr0 =new byte[16];
                    for (int j = 0; j < 16; j++,i++)
                        shortArr0[j] = _byteArray[i];
                    
                    return shortArr0;

                case 1:
                    byte [] shortArr1 =new byte[8];
                    for (int j = 0; j < 8; j++,i++)
                        shortArr1[j] = _byteArray[i];
                    
                    return shortArr1;

                case 2:
                    
                    byte [] shortArr2 =new byte[16];
                    for (int j = 0; j < 16; j++,i++)
                        shortArr2[j] = _byteArray[i];
                    
                    return shortArr2;
                case 3:
                    // calculating EVN_xxBIT_CLASS data size 
                    int dataSize = BitConverter.ToUInt16(_byteArray,i+10);
                    byte [] shortArr3= new byte[16+dataSize];
                   
                    
                    for (int j = 0; j < 16 + dataSize && i<_byteArray.Length; j++, i++)
                    {
                        shortArr3[j] = _byteArray[i];
                    }
                    return shortArr3;
                default:
                    return null;

            }


            //Console.ReadKey();
            //int i = 0;

            //while (i + 16 < 1000000)
            //{
            //    for (int j = i; j - i < 16; j++)
            //    {
            //        string b = Convert.ToString(Convert.ToInt32(byteArray[j]), 16);
            //        // formatting
            //        if (b.Length % 2 != 0)
            //        {
            //            b = "0" + b;
            //        }
            //        Console.Write(b + "  ");
            //    }
            //    Console.WriteLine();
            //    i += 16;
            //}
            

        }

        private int getClass(int p)
        {
            int classId = _byteArray[p]& 0x03;
            return classId;
        }
    }
}
