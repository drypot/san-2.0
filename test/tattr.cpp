         /*
         {
            crt.clear();
            tty.gotoxy(1,1);
            tty.output("Bold AB ab", fnt_attr::BOLD);
            tty.output("Underline AB ab", fnt_attr::UNDERLINE);
            tty.output("Shadow AB ab", fnt_attr::SHADOW);
            tty.output("Inverse AB ab", fnt_attr::INVERSE);

            tty.gotoxy(1,4);
            tty.output("Bold AB ab",fnt_attr::ENLARGE_H | fnt_attr::BOLD);
            tty.output("Underline AB ab",fnt_attr::ENLARGE_H | fnt_attr::UNDERLINE);
            tty.output("Shadow AB ab",fnt_attr::ENLARGE_H | fnt_attr::SHADOW);
            tty.output("Inverse AB ab",fnt_attr::ENLARGE_H | fnt_attr::INVERSE);

            tty.gotoxy(1,7);
            tty.output("Bold AB ab",fnt_attr::ENLARGE_V | fnt_attr::BOLD);
            tty.output("Underline AB ab",fnt_attr::ENLARGE_V | fnt_attr::UNDERLINE);
            tty.output("Shadow AB ab",fnt_attr::ENLARGE_V | fnt_attr::SHADOW);
            tty.output("Inverse AB ab",fnt_attr::ENLARGE_V | fnt_attr::INVERSE);

            tty.gotoxy(1,10);
            tty.output("Bold AB ab",fnt_attr::ENLARGE | fnt_attr::BOLD);
            tty.output("Underline AB ab",fnt_attr::ENLARGE | fnt_attr::UNDERLINE);
            tty.output("Shadow AB ab",fnt_attr::ENLARGE | fnt_attr::SHADOW);
            tty.output("Inverse AB ab",fnt_attr::ENLARGE | fnt_attr::INVERSE);

            getch();
         }
         */

         /*
         void test_han_attr()
         {
               tty.gotoxy(5,5); tty.output('e´');
               tty.gotoxy(10,10); tty.output('e´',fnt_attr::ENLARGE_H);
               tty.gotoxy(14,14); tty.output('e´',fnt_attr::ENLARGE_V);
               tty.gotoxy(18,18); tty.output('e´',fnt_attr::ENLARGE);
               getch();

               int i;

               tty.gotoxy(-4,3);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::BOLD);

               tty.gotoxy(-3,6);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::UNDERLINE);

               tty.gotoxy(-2,9);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::SHADOW);

               tty.gotoxy(-1,12);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::INVERSE);
               getch();


               tty.gotoxy(-1,1);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::SHADOW);

               tty.gotoxy(-1,29);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::SHADOW);
               getch();


               tty.gotoxy(-1,0);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::INVERSE);

               tty.gotoxy(-1,30);
               forcnt(i,22) tty.output('e´',fnt_attr::ENLARGE | fnt_attr::INVERSE);
               getch();


               tty.gotoxy(-4,5);
               forcnt(i,22) tty.output('e´',fnt_attr::BOLD);

               tty.gotoxy(-3,8);
               forcnt(i,22) tty.output('e´',fnt_attr::UNDERLINE);

               tty.gotoxy(-2,11);
               forcnt(i,22) tty.output('e´',fnt_attr::SHADOW);

               tty.gotoxy(-1,13);
               forcnt(i,22) tty.output('e´',fnt_attr::INVERSE);
               getch();
         }
         */
