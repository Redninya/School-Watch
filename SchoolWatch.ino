#include "U8glib.h"
#include "GyverButton.h"
#include <Wire.h>
#include <DS3231.h>

//--------SETINGS----------
#define timeSet 0   //Ставить время с компютера, 1 - да | 0 - нет (если не выключить после прошивки то часы после перезагрузки
//будут всё время вставать на тоже время что и при прошивания



DS3231 clock;
RTCDateTime dt;




GButton sens1(3, LOW_PULL, NORM_OPEN);
GButton sens2(2, LOW_PULL, NORM_OPEN);

unsigned long last_time;


byte page;
boolean mode;
int card;

String tmin;
String thour;
String tdate;
String tmont;
String tyear;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI



void setup() {


  clock.begin();

  if (timeSet) {
    clock.setDateTime(__DATE__, __TIME__);
  }


  sens1.setDebounce(0);        // настройка антидребезга (по умолчанию 80 мс)
  sens1.setTimeout(600);        // настройка таймаута на удержание (по умолчанию 500 мс)
  sens1.setClickTimeout(300);   // настройка таймаута между кликами (по умолчанию 300 мс)

  sens2.setDebounce(0);
  sens2.setTimeout(600);
  sens2.setClickTimeout(300);



}

void loop(void) {
  u8g.firstPage();




  sens1.tick();
  sens2.tick();
  dt = clock.getDateTime();
  tmin = dt.minute;
  thour = dt.hour;
  tdate = dt.day;
  tmont = dt.month;
  tyear = dt.year;


  if (sens1.isPress()) {
    if (mode == 0) {
      page++;
    }
    else if (mode == 1) {
      card++;
    }
  }

  if (sens2.isPress()) {
    if (mode == 0) {
      page--;
    }
    else if (mode == 1) {
      card--;
    }
  }

  if (sens1.isHolded() && sens2.isHolded()) {
    mode = !mode;
  }


  if (page == 0) {
    if (mode == 0) {
      do {
        zerop();
      }
      while (u8g.nextPage());
    }
  }

  if (page == 1) {
    if (mode == 0) {
      do {
        firstp();
      }
      while (u8g.nextPage());
    }
  }

  if (page == 2) {
    if (mode == 0) {
      do {
        secondp();
      }
      while (u8g.nextPage());
    }
  }

  if (page == 3) {
    if (mode == 0) {
      do {
        thirdp();
      }
      while (u8g.nextPage());
    }
  }

  if (page == 4) {
    if (mode == 0) {
      do {
        fourthp();
      }
      while (u8g.nextPage());
    }
  }

  if (page == 5) {
    if (mode == 0) {
      do {
        fifftp();
      }
      while (u8g.nextPage());
    }
  }



  if (mode == 1) {

    if (card == 0) {
      do {
        clockp();
      }
      while (u8g.nextPage());
    }

    if (card == 1) {
      do {
        datep();
      }
      while (u8g.nextPage());
    }

    if (card > 1) {
      card = 0;
    }
    if (card < 0) {
      card = 1;
    }
  }
}


//-----------------------------------------------------------------------
//                      CLOCK PAGES
//-----------------------------------------------------------------------
void clockp(void) {
  u8g.setFont(u8g_font_fub25);
  u8g.setPrintPos(15, 50);
  u8g.print(thour);
  u8g.setPrintPos(75, 50);
  u8g.print(tmin);
  u8g.drawDisc(64, 25, 4);
  u8g.drawDisc(64, 45, 4);
}

void datep(void) {
  u8g.setFont(u8g_font_fub11);
  u8g.setPrintPos(0, 36);
  u8g.print(tdate);
  u8g.drawDisc(30, 35, 2);
  u8g.setPrintPos(40, 36);
  u8g.print(tmont);
  u8g.drawDisc(70, 35, 2);
  u8g.setPrintPos(80, 36);
  u8g.print(tyear);
}

//------------------------------------------------------------------------------------------
//                                   PAGES
//------------------------------------------------------------------------------------------
void zerop(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("3.uzd naktis, gramatina,");
  u8g.setPrintPos(0, 15);
  u8g.print("noslepumains.");
  u8g.setPrintPos(0, 24);
  u8g.print("4.uzd 1.upe;p-pp;psp");
  u8g.setPrintPos(0, 33);
  u8g.print("2.zivs;v-u;psp");
  u8g.setPrintPos(0, 42);
  u8g.print("3.mezs;zs-s;psp");
  u8g.setPrintPos(0, 51);
  u8g.print("4.berzs;z-s;psp");
  u8g.setPrintPos(0, 60);
  u8g.print("5.eglu;l-l,;vsm");
}

void firstp(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("6.alna;ln-l,n,;vsm");
  u8g.setPrintPos(0, 15);
  u8g.print("7.laca;c-c^;vsm");
  u8g.setPrintPos(0, 24);
  u8g.print("5.uzd 1.atbraukt(apbraukt),");
  u8g.setPrintPos(0, 33);
  u8g.print("uzsaukt, atgriezties(apgriezties)");
  u8g.setPrintPos(0, 42);
  u8g.print("atbildet, apgerbties(atgerbties)");
  u8g.setPrintPos(0, 51);
  u8g.print("aizsegt, izkaltet, apsveikt");
  u8g.setPrintPos(0, 60);
  u8g.print("Pozicionalas skanu parmainas");
}

void secondp(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("2. saozdams, pluzdams, iemezdams,");
  u8g.setPrintPos(0, 15);
  u8g.print("nokozdams, pazuzdams, ielaizdams,");
  u8g.setPrintPos(0, 24);
  u8g.print("nomests, aizsviests");
  u8g.setPrintPos(0, 33);
  u8g.print("Vesturiskas skanu mijas.");
  u8g.setPrintPos(0, 42);
  u8g.print("6.uzd 1. 2,medicina,;un,;");
  u8g.setPrintPos(0, 51);
  u8g.print("nodarbosanos,;3. nosaukumu,;");
  u8g.setPrintPos(0, 60);
  u8g.print("augi-;loki,;rutki,;vibotnes-");
}

void thirdp(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("4.Zamelis,;augu,;augi,;narbulu,;");
  u8g.setPrintPos(0, 15);
  u8g.print("dzelzszale,;kalmes,;pelaski,;");
  u8g.setPrintPos(0, 24);
  u8g.print("neaizmirstules,;");
  u8g.setPrintPos(0, 33);
  u8g.print("6.paparde,;zalem,;nakti,;speki:;");
  u8g.setPrintPos(0, 42);
  u8g.print("VTL; 7.atrast,;spejas,;laimi,;");
  u8g.setPrintPos(0, 51);
  u8g.print("izdarams,.");
  u8g.setPrintPos(0, 60);
  u8g.print("6.uzd 3.1.savvalas;v-u;psp");
}

void fourthp(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("2.gadsimta;ds-c;psp");
  u8g.setPrintPos(0, 15);
  u8g.print("3.uzskatiija;z-s;psp");
  u8g.setPrintPos(0, 24);
  u8g.print("4.latviesu;t-s^;vsm");
  u8g.setPrintPos(0, 33);
  u8g.print("5.lidzekliem;l-l,;vsm");
  u8g.setPrintPos(0, 42);
  u8g.print("6.sadedzinaja;g-dz;vsm");
  u8g.setPrintPos(0, 51);
  u8g.print("7.atrast;d-s;vsm");
  u8g.setPrintPos(0, 60);
  u8g.print("6.uzd 4. 1.spilgti;g-k;psp");
}

void fifftp(void) {
  u8g.setFont(u8g_font_4x6r);
  u8g.setPrintPos(0, 6);
  u8g.print("2.spriezot;d-z^;vsm");
  u8g.setPrintPos(0, 15);
  u8g.print("3.Jan,a;n-n,;vsm");
  u8g.setPrintPos(0, 24);
  u8g.print("");
  u8g.setPrintPos(0, 33);
  u8g.print("THE END!!!!");
}

void intro(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(0, 32);
  u8g.print("HELLO DAIRIS");
}
