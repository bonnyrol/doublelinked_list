#include <stdio.h>
#include <ncurses.h>


WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

int main() {

    int scale = 1;
    int x = 0, y = 0;
    initscr();

    start_color();
    curs_set(0);
    noecho();
    // timeout(600);

    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    getmaxyx(stdscr, y, x);

    int offset = 2;
    int ch = 0;

    

    while ((ch = getch()) != 'q') {

        
        int h = 8 * scale + 1, w = 8 * scale * 2 + 1;
        WINDOW *field = newwin(h, w, offset, 0);
        wborder(field, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(field);
        // for (int row = 0; row < 8; row++) {
        //     for (int col = 0; col < 8; col++) {

        //         if ((row + col) % 2 == 0) {
        //             attron(COLOR_PAIR(1));
        //         } else {
        //             attroff(COLOR_PAIR(1));
        //         }
                
        //         for (int i = 0; i < scale; i++) {
        //             for (int j = 0; j < scale * 2; j++) {
        //                 mvaddch(offset + i + row * scale, j + col * scale * 2, ' ');
        //             }
        //         }

        //     }
        // }


        // wrefresh(field);
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "scale: %d", scale);
        attroff(COLOR_PAIR(1));

        // int ch = getch();


        if (ch == 'a' && scale > 1) {
            scale--;
        } else if (ch == 'd' && scale < 7) {
            scale++;
        }
        erase();
        wborder(field, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(field);

        delwin(field);
        // doupdate();


    }


    // getch();
    endwin();
    return 0;
}