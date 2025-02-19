////////////////////////////////////////////////////////////////////////////////
//
// Small 7 Segment Test Program
//
// Drives a test pattern to the 15 digit 7 segment display
//
////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"


////////////////////////////////////////////////////////////////////////////////
//
// Main Loop
//
// Two itmes are serviced here, the menu for the OLED and the serial USB
// interface
//
////////////////////////////////////////////////////////////////////////////////

#define BLANK 11
#define H1    12
#define H2    13
#define H3    14

int pat[20][8] =
    {
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},   // 10
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
    };

int ch[][8] =
  {
    {1,1,1,1,1,1,0,0},   //0
    {0,1,1,0,0,0,0,0},
    {1,1,0,1,1,0,1,0},   //2
    {1,1,1,1,0,0,1,0},
    {0,1,1,0,0,1,1,0},   //4
    {1,0,1,1,0,1,1,0},
    {1,0,1,1,1,1,1,0},   //6
    {1,1,1,0,0,0,0,0},
    {1,1,1,1,1,1,1,0},   //8
    {1,1,1,1,0,1,1,0},

    {1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0},   // BLANK
    {1,0,0,0,0,0,0,0},   // H1
    {0,0,0,1,0,0,0,0},   // H2
    {0,0,0,0,0,0,1,0},   // H3
    {0,0,0,0,0,0,0,0},
  };

int c = 0;
int num = 0;

int seg[8] =
  {
    16, 17, 18, 19, 20, 21, 22, 26
  };

void copy_char(int c, int d)
{
  for(int i=0; i<8; i++)
    {
      pat[d][i] = ch[c][i];
    }
}

void blank_digits(void)
{
  for(int d=0; d<15; d++)
    {
      copy_char(BLANK, d);
    }
}

void disp_int(int s, int dp, int n)
{
  int ten = 1;
  int invd;
  int dn;
    
  for(int d=s; d<s+dp; d++)
    {
      invd = 14-d;

      dn = (n / ten) % 10;
      copy_char(dn, invd);
      ten *=10;
    }
}


int main()
{
  char line[80];

  stdio_init_all();
  sleep_us(1000);
  
  printf("\n\nSeven segment test program\n\n");
  printf("\nInitialising...");
  
  printf("\nSetting GPIOs...");
  
  // Init gpios

  for(int g=0; g<=14; g++)
    {
      gpio_init(g);
      gpio_set_dir(g, GPIO_OUT);
      gpio_put(g, 1);
    }

  for(int g=0; g<8; g++)
    {
      gpio_init(seg[g]);
      gpio_set_dir(seg[g], GPIO_OUT);
      gpio_put(seg[g], 0);
    }

  int k = 0;
  int k2 = 0;
  int k3 = 0;
  int k4 = 0;
  int k30 = 0;
  int k40 = 0;
  
  int num2 = 0;
  
  // test scan
  while(1)
    {
      k++;

      if( (k % 5) == 0 )
	{
	  c = c + 1;
	  c %= 10;

	  blank_digits();
	  disp_int(0, 10, num++);
	  disp_int(12, 3, num2);

	  k2++;
	  k3++;
	  k4++;
	  
	  if( (k2 % 100)==0 )
	    {
	      num2 *= 17;
	      num2 += 19;
	    }

	  if( (k3 % 30)==0 )
	    {
	      k30++;
	      k30 %= 3;
	    }

	  if( (k4 % 70)==0 )
	    {
	      k40++;
	      k40 %= 3;
	    }

	  copy_char(H1+k30, 14-11);
	  copy_char(H1+k40, 14-10);
	  pat[9][7] = 1;
	  
	}
      
      for(int g=0; g<=14; g++)
	{
	  for(int i=0; i<8;i++)
	    {
	      gpio_put(seg[i], pat[g][i]);
	    }
	  
	  gpio_put(g, 0);
	  sleep_us(100);
	  gpio_put(g, 1);
	}
    }
}
