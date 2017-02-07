
#include <stdio.h>
#include <wiringPi.h>
#include <mcp3004.h>

#include <mapper/mapper.h>
#include <lo/lo.h>

#define BASE 100 //mcp3004/8
#define SPI_CH 0

#define NUM_CH 8

mapper_device source = 0;
mapper_signal sendsigs[NUM_CH];

int main(int argc, char *argv[])
{
   int dev;
   if (wiringPiSetup() == -1) {
      printf("wiringPi init failed\n");
      return -1;
   }

   mcp3004Setup(BASE,SPI_CH);


   //set up mapper device
   source = mdev_new("PiShield",0,0);
   if (!source) {
      printf("mapper error!\n");
      return -1;
   }
   printf("mapper source created!\n");
   int min = 0;
   int max = 1023;
   int i;
   for (i=0; i<NUM_CH; i++)
   {
      char sig_name[32];
      sprintf(sig_name, "PiShield%i",i);
      sendsigs[i] = mdev_add_output(source, sig_name, 1, 'i',"raw", &min, &max);  
   }

   printf("Number of outputs created = %i\n", mdev_num_outputs(source));

   printf("Waiting for device");
   while(!mdev_ready(source))
   {
      mdev_poll(source, 0);
      printf(".");
      delay(100);
   }
   printf("\n   Done!\n");

   int counter = 0;
   while (1)
   {
      counter++;
      int i;
      for (i=0; i<8; i++)
      {

          int sval = analogRead(BASE + i);
          msig_update_int(sendsigs[i], sval);
          if (counter>50) printf("%4i ", sval);
      }
      if (counter>50) printf("\n");
      if (counter>50) counter = 0;

      mdev_poll(source,10);
      delay(10); //max 100hz
   }
   return 0;
}
