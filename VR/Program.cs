using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VR
{
    class Program
    {
        static void Main(string[] args)
        {   
            tagYEventBaseData test = new tagYEventBaseData();
            const int BYTE_SIZE = 1;
            byte[] arr = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
            Buffer.BlockCopy(arr, 3 * BYTE_SIZE, arr, 0 * BYTE_SIZE, 4 * BYTE_SIZE);
            foreach (byte value in arr)
                Console.Write("{0}  ", value);
            
            
            //YEventBaseData asd = new YEventBaseData();
            //asd.SetClass(2);
            //asd.SetType(12);
            //asd.SetTime(345);
            //Console.WriteLine(asd.SizeOf());





        }


    }
}
