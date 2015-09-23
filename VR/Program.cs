using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.IO;
using System.Xml;

namespace VR
{
    class Program
    {
        private static void Main(string[] args)
        {
            // TEST
            //
            //
                //XmlDocument xDoc = new XmlDocument();
                //xDoc.Load("messages_en.xml");
                //// получим корневой элемент
                //XmlElement xRoot = xDoc.DocumentElement;
                //// обход всех узлов в корневом элементе
                //foreach (XmlNode xnode in xRoot)
                //{
                    
                //    // обходим все дочерние узлы элемента user
                //    foreach (XmlNode childnode in xnode.ChildNodes)
                //    {
                //        // если узел - company
                //        if (childnode.Name == "messageID")
                //        {
                //            Console.WriteLine("MessageID: {0}", childnode.InnerText);
                //        }
                //        // если узел age
                //        if (childnode.Name == "symbolicName")
                //        {
                //            Console.WriteLine("Symbolic name: {0}", childnode.InnerText);
                //        }
                //        if (childnode.Name == "text")
                //        {
                //            Console.WriteLine("Text: {0}", childnode.InnerText);
                //        }
                //    }
                //    Console.WriteLine();
                //}
                //Console.Read();
            



            //
            // Test\

            
            Console.WriteLine("Введите путь к файлу для чтения:");
            var readPath = Console.ReadLine();
            if (readPath=="")
            {
                readPath = args[1];
            }
            Console.WriteLine("Введите путь к файлу для записи:");
            var writePath = Console.ReadLine();
            
            if (writePath == "")
                writePath = args[0];
            using (var fileWriter = new StreamWriter(writePath, true))
            {

                FsRead reader = new FsRead(readPath);
                

                for (int count = 0; count + 16 <= 800000; count ++)
                {

                    byte[] testBytes = reader.GetArrayFromFile();
                    if (testBytes == null)
                        break;

                    //for (int i = 0; i < 16; i++)
                    //{
                    //    testBytes[i] = wholeArray[i + count];

                    //}



                    Event newEvent = Event.CreateObject(testBytes);

                    if (newEvent != null)
                    {
                        //newEvent.Created();
                        //newEvent.Show();
                        fileWriter.WriteLine(newEvent.GetLine());
                    }

                    else
                    {
                        //Console.WriteLine("\n Object wasn't created!");
                    }
                }



                //testBytes[2] = 0xAF;
                //testBytes[3] = 0xF0;
                //testBytes[4] = 0xAA;
                //testBytes[5] = 0xFF;
                //testBytes[6] = 0x0A;
                //testBytes[7] = 0xAF;

                // Creating object




                //int testClass = testBytes[0]& 0x03;
                //YEventBaseData TestEvent = new YEventBaseData();
                //TestEvent.SetClass(Convert.ToUInt16(testClass));
                //Console.Write("\nClass:"+TestEvent.GetClass());

                //int testType = testBytes[0] & 0x3C;
                //testType = testType >> 2;
                //TestEvent.SetType(Convert.ToUInt16(testType));
                //Console.Write(" | Type:"+ TestEvent.GetType());// Вне зависимости от значения должно выдать 0 для EVN_16BIT_CLASS

                //int testMilliseconds = BitConverter.ToInt16(testBytes,0);
                //testMilliseconds >>= 6;
                //// Console.WriteLine("\n Milliseconds "+testMilliseconds);
                //ushort testData = BitConverter.ToUInt16(testBytes, 2); 
                //TestEvent.SetmessageID(testData);
                //Console.Write(" | MessageID:" + TestEvent.GetMessageID());

                //uint testTime = BitConverter.ToUInt32(testBytes, 4);
                //TestEvent.SetTime(testTime, Convert.ToUInt16(testMilliseconds));
                //Console.Write(" | TimeEx: " +TestEvent.GetTimeEx()+" |");

                Console.ReadLine();


            }


        }

    }
}
