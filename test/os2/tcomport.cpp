/*
   95.11.19
*/

#include <pub\common.hpp>
#include <net\comport.hpp>

ComPort port;
bool fReceiving;
bool fPortAvail;

void Receiver(void*)
{
   fReceiving = YES;
   forever
   {
      while (fPortAvail && !port.IsByteReadable());
      if (!fPortAvail) break;
      putchar(port.GetByte());
   }
   fReceiving = NO;
}

void Main()
{
   char szInit[] = "ATS11=50\r";

   port.Open(2);
   port.SetBitRate(57600);
   port.SetDataBits(8);
   port.SetParity(ComPort::NoParity);
   port.SetStopBits(ComPort::StopBit1);
   fPortAvail = YES;
   port.Write(szInit, strlen(szInit));

   #if defined __BORLANDC__
      _beginthread (Receiver,16384,NULL);
   #elif defined __WATCOMC__
      _beginthread (Receiver,NULL,16384,NULL);
   #endif

   forever
   {
      char buf[512];
      gets(buf);
      if (strcmp(buf,"quit") == 0) break;
      port.Write(buf,strlen(buf));
      port.PutByte('\r');
   }
   fPortAvail = NO;
   while (fReceiving);
   port.Close();
}
