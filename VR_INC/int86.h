#ifndef __INT86_H
#define __INT86_H

#define SWAP2(b)   ( (((b)>>1)&0x01) | (((b)&0x01)<<1) )
#define SWAP4(b)   ( (((b)>>2)&0x03) | (((b)&0x03)<<2) )
#define SWAP8(b)   ( (((b)>>4)&0x0F) | (((b)&0x0F)<<4) )
#define SWAP16(b)  ( (((b)>>8)&0xFF) | (((b)&0xFF)<<8) )
#define SWAP32(b)  ( (((b)>>16)&0x0000FFFF) | (((b)&0x0000FFFF)<<16) )
#define SWAP64(b)  ( (((b)>>32)&0xFFFFFFFF) | (((b)&0xFFFFFFFF)<<32) )

#define REVB2(b)   ( (((b)>>1)&0x01) | (((b)&0x01)<<1) )
#define REVB4(b)   ( (REVB2((b)>>2)) | ((REVB2(b))<<2) )
#define REVB8(b)   ( (REVB4((b)>>4)) | ((REVB4(b))<<4) )
#define REVB16(b)  ( (REVB8((b)>>8)) | ((REVB8(b))<<8) )
#define REVB32(b)  ((REVB16((b)>>16))| ((REVB16(b))<<16))
#define REVB64(b)  ((REVB32((b)>>32))| ((REVB32(b))<<32))


#define ROR8(b)    ((b)&1?((b)>>=1,(b)|=0x80,1):((b)>>=1,0))  //CF returned
#define ROL8(b)    ((b)&0x80?((b)<<=1,(b)|=1,1):((b)<<=1,0))  //CF returned

#define RCR8(b,cf) ((b)&1?((b)>>=1,(b)|=((cf)<<7),1):((b)>>=1,(b)|=((cf)<<7),0))  //CF returned, cf=0,1
#define RCL8(b,cf) ((b)&0x80?((b)<<=1,(b)|=(cf),1):((b)<<=1,(b)|=(cf),0))         //CF returned, cf=0,1


#define ROR16(b)   ((b)&1?((b)>>=1,(b)|=0x8000,1):((b)>>=1,0))  //CF returned
#define ROL16(b)   ((b)&0x8000?((b)<<=1,(b)|=1,1):((b)<<=1,0))  //CF returned

#define RCR16(b,cf) ((b)&1?((b)>>=1,(b)|=((cf)<<15),1):((b)>>=1,(b)|=((cf)<<15),0))  //CF returned, cf=0,1
#define RCL16(b,cf) ((b)&0x8000?((b)<<=1,(b)|=(cf),1):((b)<<=1,(b)|=(cf),0))         //CF returned, cf=0,1


//efine ROR32(b)   ((b)&1?((b)>>=1,(b)|=0x80000000,1):((b)>>=1,0))  //CF returned
//efine ROL32(b)   ((b)&0x80000000?((b)<<=1,(b)|=1,1):((b)<<=1,0))  //CF returned

#define RCR32(b,cf) ((b)&1?((b)>>=1,(b)|=((cf)<<31),1):((b)>>=1,(b)|=((cf)<<31),0))  //CF returned, cf=0,1
#define RCL32(b,cf) ((b)&0x80000000?((b)<<=1,(b)|=(cf),1):((b)<<=1,(b)|=(cf),0))     //CF returned, cf=0,1


//efine ROR64(b)   ((b)&1?((b)>>=1,(b)|=0x8000000000000000i64,1):((b)>>=1,0))  //CF returned
//efine ROL64(b)   ((b)&0x8000000000000000i64?((b)<<=1,(b)|=1,1):((b)<<=1,0))  //CF returned

#define RCR64(b,cf) ((b)&1?((b)>>=1,(b)|=((cf)<<63),1):((b)>>=1,(b)|=((cf)<<63),0))  //CF returned, cf=0,1
#define RCL64(b,cf) ((b)&0x8000000000000000i64?((b)<<=1,(b)|=(cf),1):((b)<<=1,(b)|=(cf),0))     //CF returned, cf=0,1

//low byte first
#define LBF32(i)   ( \
   (( (((DWORD)(i))>>24)&0x000000FF  )    )| \
   (( (((DWORD)(i))>>16)&0x000000FF  )<<8 )| \
   (( (((DWORD)(i))>> 8)&0x000000FF  )<<16)| \
   (( (((DWORD)(i))    )&0x000000FF  )<<24))

#endif//__INT86_H
#pragma once