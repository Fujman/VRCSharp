#include "event.cpp"
#include "evntport.cpp"
//#include "events.cpp"
extern "C" { // BC
main();
}

void func(YEvent& ev) {
  char sz[80];
  printf("%s\n",ev.GetText(sz,80));
}

main(){
  char sz[80];
  YEvent16 ev(9,0xF123);
  YEvent20 ev2((DWORD)0xF1234L);
  ev.SetTime();
  ev2.SetTime();
  printf("\n16 bit:\n\t");
  printf("%s\n",ev.GetText(sz,80));
  printf("20 bit:\n\t");
  printf("%s\n",ev2.GetText(sz,80));

  YEvent64 ev64(15,0xF1234567L,0xF7654321L);
  ev64.SetTime();
  ev64.SetData16(0xF321);
  printf("64 bit:\n\t");
  printf("%s\n",ev64.GetText(sz,80));


  YEventPort evp, evp2;
  evp.in(0x337,0xFF);   evp.SetTime();
  evp2.out(0x338,0xAA); evp2.SetTime();
  printf("%s\n\t",(evp.isIn()?"IN:":"OUT:"));
  printf("%s\n",evp.GetText(sz,80));
  printf("%s\n\t",(evp2.isOut()?"OUT:":"IN:"));
  printf("%s\n",evp2.GetText(sz,80));

  printf("\n\t%s\n",evp.GetText(sz,80));
  evp.SetPort(evp.GetPort()+0x100);
  evp.SetByte(evp.GetByte()+0x01);
  printf("\t%s\n",evp.GetText(sz,80));

  //evp.SetClass(1);
  //evp.SetType(1);
  //evp.SetData16(1);
  //YEvent(1,1);
  //ev = ev2;
  //  func(ev2);
  //  func(evp);
  //  func(ev64);

  printf("\nSize of YEventBaseData = %d\n",sizeof(YEventBaseData));
  printf("\nSize of YEvent = %d\n",sizeof(YEvent));
  printf("Size of YEvent16 = %d\n",sizeof(YEvent16));
  printf("Size of YEvent20 = %d\n",sizeof(YEvent20));
  printf("Size of YEvent64 = %d\n",sizeof(YEvent64));
  return 0;
}

