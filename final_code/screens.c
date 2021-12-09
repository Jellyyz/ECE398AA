#include "screens.h"
#include "lcd.h"
#include "keypad.h"
#include "piezzo.h"
#include "seg7.h"
#include "buttons.h"
#include "led.h"
#include <time.h> 
#include "ir.h"
#include "timer32.h"
int32_t k;
int credit_balance = 0;
char c_b[3] = {'0','0'}; 
int bet = 0; 

/*
boot_screen
Boot screen to display
Inputs: None
Outputs: None
Side Effects: Changes the LCD display
*/
void boot_screen(void) {
    LCD_clear(); 
    LCD_show("---------------------", 0);
    LCD_show("Gally & Zhuxuan", 1);
    LCD_show(" Slot Machine", 2);
    LCD_show("---------------------", 3);
    Systick_ms_delay(3000);
    // while(1){
    //     int i = 0;
    //     for(i; i < 100; i++){
    //         set_seg_leds(i);
    //         Systick_ms_delay(500); 
    //     }
    // }
}

/*
menu_main
Main menu
Inputs: None
Outputs: None
Side Effects: Changes the LCD display
*/
void menu_main(void) {
    int flag;
    while (1) {
        flag = 0;
        LCD_clear();
        LCD_show("1- Sounds", 0);
        LCD_show("2- Enter Credits", 1);
        LCD_show("3- Play", 2);
        while(1) {
            int8_t keypress = read_keypad();
            switch(keypress) {
                case 1:
                    menu_sounds();              
                    flag = 1; 
                    break;
                case 2:
                    menu_enter_credits();
                    flag = 1; 
                    break;
                case 3:
                    menu_play();
                    flag = 1; 
                    break;
            } 
            if(flag) {
                break; 
            }
        }
    }
}

/*
menu_sounds
Menu for setting sounds
Inputs: None
Outputs: None
Side Effects: Changes the LCD display, and may play tunes
*/
void menu_sounds(void) {
    LCD_clear(); 
    LCD_show("0 - Tune0", 0);
    LCD_show("1 - Tune1", 1); 
    LCD_show("* - Main Menu", 2); 

    while(1){
        int8_t keypress = read_keypad();
        // printf("%d\n", keypress);
        switch(keypress){
            case KEYPAD_ZERO:
                set_tune(TUNE0);
                break;
            case 1: 
                set_tune(TUNE1);
                break;
            case 3:
                play_tune();
                break; 
            case STAR:
                return; 
            default:
                break; 
        } 
    }

}

/*
menu_enter_credits
Menu for entering credits
Inputs: None
Outputs: None
Side Effects: Changes the number of credits
*/
void menu_enter_credits(void) {
    int flag; 
    //int r; 
    //r = read_ADC();
    while(1){
    flag = 0;
    LCD_clear();
    LCD_show("Enter Credits:", 0);
    LCD_show(c_b, 1); 
        while(1){
            int8_t keypress = read_keypad();
            switch(keypress){
                case STAR:
                    return; 
                default:
                    enter_credits();
                    flag = 1;
                    break;   
            } 
            if(flag){
                break; 
            }
        }
    }

}

/*
enter_credits
Helper function to parse the amount of credits set
Inputs: None
Outputs: None
Side Effects: Sets the 7 segment displays and the current balance
*/
void enter_credits() {
    
    k = credit_balance;
    k = get_keypad(); 
    if(k == -10){                    // 101 is what the get_keypad returns if we press a star 
        menu_main();
    } 
    sprintf(c_b, "%d", k);
    if(k > 99){
        k = 99;
    }
    set_seg_leds(k);
    //testing if function works
    // printf("keypress= %d\n", k);
    // printf("keypress char = %c\n", c_b); 
    credit_balance = k; 
    return; 
}

/*
menu_play
Menu for playing the slot machine
Inputs: None
Outputs: None
Side Effects: Changes the LCD dsiplay
*/
void menu_play(void) {
    while(1){
    on_game_screen = 1; 
    LCD_clear();
    LCD_show("Current Bet: ", 1);
    char betc[2];  
     
    
    while(1){
        Systick_ms_delay(200); 
        // printf("%d\n", bet); 
        sprintf(betc, "%u", bet);
        LCD_show(betc, 2);
        int8_t keypress = read_keypad();
        if(keypress == STAR) {
            on_game_screen = 0; 
            return;  
        }
        if(flag_bet_minus){
            if (bet != 0) bet--; 
            flag_bet_minus = 0;
        }
        if(flag_bet_plus){
            if (bet != 5) bet++; 
            flag_bet_plus = 0;
        }
        if(flag_cash_out){ 
            flag_cash_out = 0; 
            menu_cash_out();
        }
        if(flag_play){
            if (bet == 0) {
                flag_play = 0;
                continue;
            } 
            else{
                flag_play = 0; 
                reel();     
                break;
            }
        }
    } 
    }
}

/*
reel
Helper function to handle the slot machine reels
Inputs: None
Outputs: None
Side Effects: Changes the credit balance, may play tunes
*/
void reel() {   
    P2->OUT &= ~(BIT0 | BIT1);                     // Clear all the bits on the register (set them to off)
    LCD_clear(); 
    t32_int_flag = 0;
    int flag; 
    int stop = 0; 
    char l0[4] = "   "; 
    char l1[4] = "   "; 
    char l2[4] = "   "; 
    char l3[4] = "   "; 
    char * lines[4] = {l0, l1, l2, l3};
    // 157 heart
    // 22 circle
    

    
        srand(time(NULL)); 
        rand();  
        int i, j;
        int a = rand() % 999; 
        /*
        mod 20: 5% to get a rly easy roll 
        mod 50: 2% to winner guarenteed, can also use for testing
        */ 
        if(a % 20 == 0){
            flag = 5; // 5% 
        }
        if(a % 50 == 0){
            flag = 2; // 2% also use for testing win 
        }
        flag = a % 2 ? 0 : 1;  // else choose from 2 of generated sets
        
        flag = 0;

        switch(flag){ 
            case 5: 
            strcpy(l0, "122"); 
            strcpy(l1,  "233"); 
            strcpy(l2,  "334"); 
            strcpy(l3,  "441"); 
            break; 
        
            case 1:
            strcpy(l0,  "123"); 
            strcpy(l1,  "234"); 
            strcpy(l2,  "341"); 
            strcpy(l3,  "412"); 
            break; 
             
            case 0:
            strcpy(l0,  "243"); 
            strcpy(l1,  "312"); 
            strcpy(l2,  "431"); 
            strcpy(l3,  "124"); 
            break; 
            
            default:
            strcpy(l0,  "111"); 
            strcpy(l1,  "111"); 
            strcpy(l2,  "111"); 
            strcpy(l3,  "111"); 
            break; 
        }
    
        /* what we want
            i0 1 4 
            i1 2 1
            i2 3 2
            i3 4 3
        */
        //buffer to help scroll 
        char ll0[3] = ""; 
        char ll1[3] = ""; 
        char ll2[3] = "";
        char ll3[3] = ""; 
        // scrolling section

        t32_delay_30s();
        while(stop < 3){
            // scroll down for the first and last col 
            LCD_show(l0, 0);
            LCD_show(l1, 1);
            LCD_show(l2, 2);
            LCD_show(l3, 3);
            Systick_ms_delay(250);
            if(flag_play) {
                flag_play = 0;
                stop++; 
            }
            if (t32_int_flag) {
                break;
            }
            for(j = stop; j < 3; j++) {
                ll0[j] = l3[j]; 
                ll1[j] = l0[j]; 
                ll2[j] = l1[j];
                ll3[j] = l2[j]; 
                l0[j] = ll0[j]; 
                l1[j] = ll1[j]; 
                l2[j] = ll2[j]; 
                l3[j] = ll3[j]; 
            }
        }
        t32_int_flag = 0;
                
        int win = 0; 
        // checker to see if any win cons we checking line 1
        // if match on all roll then win = 2; 
        for (i = 0; i < 3; i++) {
            if(
                ( (lines[i])[0] == (lines[i])[1] ) &&
                ( (lines[i])[0] == (lines[i])[2] ) ) {
                win++;
            }
        }
        if(win != 0){
            // turn on green led
            P2 -> OUT ^= BIT1; 
        }   
        else{
            P2 -> OUT ^= BIT0; 
        }
        // credits calculated :
        // switch 
        switch(win){
            // case 1;  credits += bet 
            // case 2; credits +=  bet + bet 
            // default: credits -= bet 

            case 0:
                    credit_balance -= bet; 
                    break;
            case 1: 
                    play_tune();
                    credit_balance += bet;
                    break;  
            default:
                    play_tune();
                    credit_balance += bet + bet;
                    break;
        }
        if(credit_balance > 99){
            credit_balance = 99; 
        }
        set_seg_leds(credit_balance);
        // bet should = 0; 
        Systick_ms_delay(3000);
        bet = 0; 
        return; 

}

/*
menu_cash_out
Menu for cash out
Inputs: None
Outputs: None
Side Effects: Changes the credit balance, plays tune
*/
void menu_cash_out(){
    LCD_clear();
    char str0[] = "Cash Out: ";
    char str1[3];
    char buf[16];
    memset(buf, 0, 16);
    convert_credit_str(str1, credit_balance);
    strcpy(buf, str0);
    strcpy(buf + strlen(str0), str1);

    LCD_show(buf, 1);
    LCD_show("Thanks 4 Playing", 2); 
    LCD_show("      Goodbye", 3);
    play_tune(); 
    Systick_ms_delay(3000);
    Systick_ms_delay(3000);
    k = 0;
    credit_balance = 0; 
    set_seg_leds(credit_balance); 
    menu_main();
}

/*
convert_credit_str
converts an integer for the number of credits into string.
Inputs: pointer to string, integer value
Outputs: None
Side Effects: Changes the string
*/
void convert_credit_str(uint8_t *str1, uint32_t credit_balance) {
    str1[0] = '0' + credit_balance / 10;
    str1[1] = '0' + credit_balance % 10;
    str1[2] = '\0';
}
