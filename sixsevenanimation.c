// Yes, I used AI to help polish the logic and optimize the rendering, but I'm still actively studying the code to understand every line
// made by ruy
// SIX SEVEN NEVER DIEEEEEEEEEEEEE!!!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>


#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

// -----------------------------------------
// ANIMATION SETTINGS
// -----------------------------------------
const int MAX_HEIGHT = 40;
const int SPEED_US = 65000;
const int ART_WIDTH = 40;
const int GAP_WIDTH = 15;
// -----------------------------------------


void handle_sigint(int sig) {
    printf("\033[?25h\n");
    exit(0);
}

int main() {

    signal(SIGINT, handle_sigint);


    char buffer[8192];
    setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));


    printf("\033[?25l");

    char *six[] = {
        "               ####### ",
        "              ##     ##",
        "              ##       ",
        "              ######## ",
        "              ##     ##",
        "              ##     ##",
        "               ######  "
    };

    char *seven[] = {
        "               ########",
        "                    ## ",
        "                   ##  ",
        "                  ##   ",
        "                 ##    ",
        "                ##     ",
        "               ##      "
    };

    char *hand6[] = {
        "            =======                    ",
        "           /XXXXXXX\\ ===               ",
        "         //XXXXXXXX \\XXX\\              ",
        "        /XXXXXXXXXXXXXXX \\             ",
        "    ===XXXX| XXXXXXX| XXXXX\\           ",
        "   XXXXXXXX|XXXXXXXX| XXXXXX\\          ",
        "  /XXXX\\XX |XXXXXXXX| XXXXXX\\          ",
        " /XXXXX \\ /  XXXXXX /  XXXXXX\\         ",
        "  \\XXX /-|   XXXX //   XXXXXX|         ",
        "   \\==/  | XXXXX-/     XXXX--/         ",
        "         | XXXXXXXX----XXX/-/\\ /==/==\\ ",
        "         | XX   XXX      /=== \\ -- -- |",
        "         \\ XX--\\XXX//===\\ |XX| |XX|XX||",
        "          \\     \\X//|XX|| |XX| |XX|XX|/",
        "          \\\\XX /-\\/ |XX|/  --   -- --/ ",
        "           \\\\ / /    --/  -- / --/  /  ",
        "           \\       -- / --- /   / -/   ",
        "            \\    --- /     /   /---    ",
        "             \\      \\     /   /        ",
        "              \\    / \\   /   /         ",
        "               ====   === ===          "
    };

    char *hand7[] = {
        "                 /═════\\           ",
        "              /-/-XXXXX\\\\-         ",
        "           /-/XXXXXXXXXXXX\\        ",
        "          /XXXXXXXXXXXXX/XX\\       ",
        "         / XXXXXXXXXXXX/ XXX\\════  ",
        "        ║ XXXXX XXXXXXXX\\XXX/XXXX\\ ",
        "        ║XXXXXX  XXXXXX  \\  |XXXXX\\",
        "       /║XXXXXXXX XXXXXXX|══\\XXXXX/",
        " /══\\ ══\\═══-XXXX XXXXXX  ║  \\═══/ ",
        "|│XX││XX│\\/══\\ ═══  XXXXX ║        ",
        "|│XX││XX│|│XX│/───\\ XXXXX ║        ",
        "\\ ── \\── |│XX││XXX│\\ --   ║        ",
        " \\|   \\   \\-- │XXX│ \\  \\  ║        ",
        "  \\   \\    \\   ───   \\-  |║        ",
        "   \\   \\   |    \\    | \\ /         ",
        "   \\   \\   \\     \\      /          ",
        "    \\   \\   \\     \\    /           ",
        "     ══\\|   \\     /   /            ",
        "        ════ \\═══/ ═══             "
    };

    
    int num_height = ARRAY_SIZE(six);
    int hand6_height = ARRAY_SIZE(hand6);
    int hand7_height = ARRAY_SIZE(hand7); 
    
    int max_total_height = num_height + 2 + hand6_height; 
    int max_travel_y = MAX_HEIGHT - max_total_height; 
    
    int total_art_width = (ART_WIDTH * 2) + GAP_WIDTH; 

    int master_y = 0; 
    int dir = 1;

    printf("\033[2J");

    while (1) {

        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int cols = w.ws_col; 


        int pad_left = (cols - total_art_width) / 2;
        if (pad_left < 0) pad_left = 0;

        printf("\033[H");

        int y6 = master_y;
        int y7 = max_travel_y - master_y; 

        int yHand6 = y6 + num_height + 2;
        int yHand7 = y7 + num_height + 2;

        for (int i = 0; i < MAX_HEIGHT; i++) {
            char *line6 = "";
            char *line7 = "";

            if (i >= y6 && i < y6 + num_height)
                line6 = six[i - y6];
            else if (i >= yHand6 && i < yHand6 + hand6_height)
                line6 = hand6[i - yHand6];

            if (i >= y7 && i < y7 + num_height)
                line7 = seven[i - y7];
            else if (i >= yHand7 && i < yHand7 + hand7_height)
                line7 = hand7[i - yHand7];

            for(int p = 0; p < pad_left; p++) {
                putchar(' ');
            }
            

            printf("%-*s", ART_WIDTH, line6);
            for(int p = 0; p < GAP_WIDTH; p++) putchar(' ');
            printf("%-*s\n", ART_WIDTH, line7);
        }

        fflush(stdout);

        usleep(SPEED_US);

        master_y += dir;
        if (master_y <= 0 || master_y >= max_travel_y) {
            dir *= -1;
        }
    }

    return 0;
}