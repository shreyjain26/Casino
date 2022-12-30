#include<iostream>
#include<ctime>
#include<conio.h>
using namespace std;

class blackjack{
    protected:
        int phand[5], dhand[5];
        int p, d, phand_sum, dhand_sum;
        
        void clear_hands();

        void add_phand(int seed);
        void add_dhand(int seed);
        void dealer_display();
        void player_display();
        void display();
        void set_ace();
        int sum_p();
        int sum_d();
};

class roulette{
    protected:
    int random_generator(int n){
        srand(time(0));
        return (rand()%n);
    }
};

class up7down7{
    protected:
        int rand_generator(int n);
};

class acc : public blackjack, public up7down7, public roulette{
    protected:
        int seed;
        string name;
        int age;
        long balance;
        long bet;
        void win();
        void loss();
        void winnings(int odds);

        public:
            acc();
            acc(string nam,int ag,long bal);
            void set_seed();
            void deposit(long amt);
            void withdraw(long amt);
            long check_balance();
            friend ostream & operator <<(ostream &out, acc &account);
            void set_bet();

            void play_blackjack();
            void play_7up_7down();
            void play_slots();
            void play_roulette(bool *exit_cond);
};

void acc :: set_seed(){
    srand(time(0));
    seed = rand() % 10000;
}


int main(){1
    string name;
    int age;
    long balance;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your age: ";
    cin>>age;
    if(age < 18){
        cout<<"You cannot create an account before turning 18";
        exit(0);
    }
    cout<<"Enter your balance: ";
    cin>>balance;
    acc player(name, age, balance);
    bool main_flag = true;
    while(main_flag){
        cout<<"1.deposit    2.withdraw     3.check balance      4.Play a game      5.Exit"<<endl;
        char k;
        cin>>k;
        switch(k){
            case '1':{
                cout<<"How much do you want to deposit?";
                long amt;
                cin>>amt;
                player.deposit(amt);
            }
            break;
            case '2':{
                cout<<"How much do you want to withdraw?";
                long amt;
                cin>>amt;
                player.withdraw(amt);
            }
            break;
            case '3':
                cout<<"Your balance is:"<<player.check_balance();
                cout<<endl;
            break;
            case '4':{
                if(player.check_balance() < 2000){
                    cout<<"Minimum balance required to place a bet in any game is 2000."<<endl;
                    break;
                }
                bool game_flag = true, roulette_flag;
                do{
                    cout<<"Which game do you want to play?\n1.BlackJack      2.Roulette      3.Slots     4.Seven up seven down      5.Go Back"<<endl;
                       char game_var;
                       cin>>game_var;
                       switch(game_var){
                            case '1':
                                cout<<"Do you want to see the rules? Y or N"<<endl;
                                char black;
                                cin>>black;
                                if(black == 'y' || black == 'Y'){
                                    cout<<"----------------------------------------------------------Rules---------------------------------------------------------------"<<endl;
                                    cout<<" o 1: The value of your cards is face value. Jack, Queen and King are 10"<<endl;
                                    cout<<" o 2: Aces can be 1 or 11"<<endl;
                                    cout<<" o 3: One card of the dealer will not be shown until the break case"<<endl;
                                    cout<<" o 4: Dealer wins if the sum total of the cards is 21"<<endl;
                                    cout<<" o 5: You win if the sum total of your cards is 21"<<endl;
                                    cout<<" o 6: If your sum total is greater than 21 you lose"<<endl;
                                    cout<<" o 7: Only if dealer's sum total is less than 15, then the dealer can hit a card"<<endl;
                                    cout<<" o 8: You can hit a card, double down on your bet or simply stand"<<endl;
                                    cout<<"      Hitting a card means to pick another card and stand means to simply pass"<<endl;
                                    cout<<" o 9: Whoever's sum total of card is closer is 21 wins"<<endl;
                                    cout<<" o 10: If you win you get twice the amount, if you tie you get back your bet amount while if you lose, sike you're just bad"<<endl;
                                }
                                cout<<"----------------------------------------=-----Welcome to blackjack!---------------------------------------------------------"<<endl<<endl;
                                player.play_blackjack();
                            break;
                            case '2':
                                cout<<"----------------------------------------------Welcome to Roulette!----------------------------------------------------------"<<endl<<endl;
                                roulette_flag = true;
                                while(roulette_flag){
                                    player.play_roulette(&roulette_flag);
                                }
                                cout<<"\n----------------------------------------------------Thank You-------------------------------------------------------------"<<endl;
                                break;
                            case '3':
                                cout<<"------------------------------------------------Welcome to Slots!-----------------------------------------------------------"<<endl<<endl;
                                player.play_slots();
                                break;
                            case '4':
                                cout<<"-----------------------------------------Welcome to Seven up Seven down!----------------------------------------------------"<<endl<<endl;
                                player.play_7up_7down();
                                break;
                            default:
                                game_flag = false;
                        }
                }
                while(game_flag);
            }
            break;
            default:
                main_flag = false;
        }
    }
    return 0;
}

void acc :: play_blackjack(){
    p = 0, d = 0;
    set_bet();
    clear_hands();
    add_phand(seed--);
    add_phand(seed--);
    add_dhand(seed--);
    add_dhand(seed--);
    display();
    set_ace();
    if(dhand[0] == 11 && dhand[1] == 11){
        dhand[1] = 1;
        display();
    }
    dhand_sum = sum_d();
    phand_sum = sum_p();
    if(phand_sum > 21){
        cout<<"You're busted. ";
        loss();
        cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
        return;
    }
    else if ( dhand_sum > 21 ){
        cout<<"Dealer's cards: "<<dhand[0];
        dealer_display();
        cout<<"The dealer is busted. ";
        win();
        cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
        return;
    }
    else if ( dhand_sum == 21 ){
        cout<<"Dealer's cards: "<<dhand[0];
        dealer_display();
        cout<<"\nThe dealer has blackjack, you lose!"<<endl;
        cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
        return;
    }
    else if ( phand_sum == 21){
        cout<<"You have blackjack!\n";
        win();
        cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
        return;
    }
    else if ( dhand_sum < 15 ){
        add_dhand(seed--);
        dhand_sum = sum_d();
        display();
        if ( dhand_sum > 21 ){
            cout<<"Dealer's cards: "<<dhand[0];
            dealer_display();
            cout<<"The dealer is busted. ";
            win();
            cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
            return;
        }
        else if ( dhand_sum == 21 ){
            cout<<"Dealer's cards: "<<dhand[0];
            dealer_display();
            cout<<"\nThe dealer has blackjack, you lose!"<<endl;
            cout<<"\n----------------------------------------------------Thank You---------------------------------------------------------------"<<endl;
            return;
        }
    }
    bool options_flag = true, first_case = true;
    while(options_flag){
        cout<<"1. Hit       2.Double Down       3.Stand"<<endl;
        int option;
        cin>>option;
        switch(option){
            case 1:{
                if ( first_case ){
                    add_phand(seed--);
                    phand_sum = sum_p();
                    display();
                    if(phand_sum > 21){
                        cout<<"You're busted. ";
                        loss();
                        cout<<"\n----------------------------------------------------Thank You-------------------------------------------------------------"<<endl;
                        return;
                    }
                    else if ( phand_sum == 21){
                        cout<<"You have blackjack!\n";
                        win();
                        cout<<"\n----------------------------------------------------Thank You-------------------------------------------------------------"<<endl;
                        return;
                    }
                    first_case = false;
                }
                else{
                    cout<<"You can only hit once"<<endl;
                }
            }
            break;
            case 2:{
                if ( ( balance - bet ) < 0 ){
                    cout<<"Not possible"<<endl;
                }
                else{
                    balance -= bet;
                    bet = bet * 2;
                }
            }
            break;
            default:
                options_flag = false;
        }
    }
    if( dhand_sum > phand_sum ){
         cout<<"Dealer's cards: "<<dhand[0];
        dealer_display();
        player_display();
        cout<<"The dealer is closer. ";
        loss();
    }
    else if( phand_sum > dhand_sum ){
         cout<<"Dealer's cards: "<<dhand[0];
        dealer_display();
        player_display();
        cout<<"You are closer. ";
        win();
    }
    else if( dhand_sum = phand_sum ){
         cout<<"Dealer's cards: "<<dhand[0];
        dealer_display();
        player_display();
        cout<<"It is a tie. You get your bet amount back."<<endl;
        balance += bet;
    }
    cout<<"\n-----------------------------------------------------Thank You-------------------------------------------------------------"<<endl;
}

void acc :: play_roulette(bool *exit_cond){
    int choice,selection, random, i;
    cout<<"\n1.Odd/Even       2.Black/Red         3.High/Low      4.Column        5.Dozen         6.Straight Up       7.Exit"<<endl;
    cin>>choice;
    int R[18]={1,3,5,7,9,12,14,16,18,21,23,25,27,28,30,32,34,36},B[18]={2,4,6,8,10,11,13,15,19,20,22,24,26,29,31,33,35};
    switch(choice){
        case 1:
            Retry1:
                cout<<"1.Odd    2.Even?"<<endl;
                cin>>selection;
                if(selection < 1 || selection > 2){
                    cout<<"Try Again"<<endl;
                    goto Retry1;
                }
                set_bet();
                random = random_generator(38);
                if(random == 37 || random==0){
                    cout<<"The ball lands on 00"<<endl;
                    loss();
                    break;
                }
                else{
                    cout<<"\nThe ball lands on "<<random<<" .";
                    if((((random)%2==0)&&(selection==2))||(((random)%2==1)&&(selection==1)))
                        winnings(1);
                    else
                        loss();
                }
        break;
        case 2:
            Retry2:
                cout<<"\n1)Red or 2)Black?:";
                cin>>selection;
                if(selection>2||selection<1){
                    cout<<"Try Again"<<endl;
                    goto Retry2;
                }
                set_bet();
                random=random_generator(38);
                if(random==37||random==0){
                    cout<<"\nThe ball lands on 00";
                    loss();
                    break;
                }
                else
                    cout<<"\nThe ball lands on "<<random<<" .";
                    if(selection==1){
                        for(i=0;i<18;i++){
                            if(random==R[i]){
                                winnings(1);
                                break;
                            }
                            if(i==17)
                                loss();
                        }
                    }
                    else if(selection==2){
                        for(i=0;i<18;i++){
                            if(random==B[i]){
                                winnings(1);
                                break;
                            }
                            if(i==17)
                            loss();
                        }
                    }
        break;
        case 3:
            Retry3:
                cout<<"\n1)High or 2)Low?:";
                cin>>selection;
                if(selection>2||selection<1){
                    cout<<"Try again"<<endl;
                    goto Retry3;
                }
                set_bet();
                random=random_generator(38);
                if(random==37||random==0){
                    cout<<"\nThe ball lands on 00";
                    loss();
                    break;
                }
                else
                    cout<<"\nThe ball lands on "<<random<<" .";
                if(((random>18&&random<=36)&&(selection==1))||((random>0&&random<=18)&&(selection==2)))
                    winnings(1);
                else
                    loss();
        break;
        case 4:
            Retry4:
                cout<<"\nColumn 1,2 or 3?:";
                cin>>selection;
                if(selection>3||selection<1){
                    cout<<"Try again"<<endl;
                    goto Retry4;
                }
                set_bet();
                random=random_generator(38);
                if(random==37||random==0){
                    cout<<"\nThe ball lands on 00";
                    loss();
                    break;
                }
                else
                    cout<<"\nThe ball lands on "<<random<<" .";
                switch(selection)
                {
                case 1:
                    if(random%3==1)
                        winnings(2);
                    else
                        loss();
                break;
                case 2:
                    if(random%3==2)
                        winnings(2);
                    else
                        loss();
                break;
                case 3:
                    if(random%3==0)
                        winnings(2);
                    else
                        loss();
                break;
                }
        break;
        case 5:
            Retry5:
                cout<<"\nDozen 1,2 or 3?:";
                cin>>selection;
                if(selection>3||selection<1){
                    cout<<"Try again"<<endl;
                    goto Retry5;
                }
                set_bet();
                random=random_generator(38);
                if(random==37||random==0){
                    cout<<"\nThe ball lands on 00";
                    loss();
                    break;
                }
                else
                    cout<<"\nThe ball lands on "<<random<<" .";
                switch(selection){
                    case 1:
                        if(1<=random<=12)
                            winnings(2);
                        else
                            loss();
                    break;
                    case 2:
                        if(13<=random<=24)
                            winnings(2);
                        else
                            loss();
                    break;
                    case 3:
                        if(25<=random<=36)
                            winnings(2);
                        else
                            loss();
                    break;
                }
        break;
        case 6:
            Retry6:
                cout<<"\nSelect the number to bet on: ";
                cin>>selection;
                if(selection>37||selection<0){
                    cout<<"Try again"<<endl;
                    goto Retry6;
                }
                set_bet();
                random=random_generator(38);
                cout<<"\nThe ball lands on "<<random<<" .";
                if(random==selection)
                    winnings(35);
                else
                    loss();
        break;
        case 7:
            *exit_cond = false;
            break;
        default:
            cout<<"\nTry again"<<endl;
            break;
    }
}

void acc :: play_slots(){
    set_bet();
    int roll[3], count = 0;
    for(int i = 0; i < 3; i++){
        srand(seed--);
        roll[i] = rand()%10;
        cout<<roll[i]<<" ";
        _sleep(1000);
    }
    cout<<endl;
    int temp = roll[0];
    for(int i = 1; i < 3; i++){
        if(roll[i] == temp)
            count++;
    }
    if(count == 2)
        win();
    else if(count == 1){
        cout<<"You win half the amount"<<endl;
        balance += bet + bet/2;
    }
    else
        loss();
    cout<<"\n--------------------------------------------------Thank You----------------------------------------------------------------"<<endl;
}

void acc :: play_7up_7down(){
    cout<<"1. 7 down     2. 7 up     3. 7       4.Exit\n"<<endl;
    int choice,random;
    cin>>choice;
    random = rand_generator(seed--);
    set_bet();
    cout<<"The dice rolled a "<<random<<"\n";
    switch(choice){
        case 1:
            if(random > 0 && random < 7)
                win();
            else
                loss();
        break;
        case 2:
            if(random > 7 && random < 14)
                win();
            else
                loss();
        break;
        case 3:
            if(random == 7)
                win();
            else
                loss();
        break;
        default:
            break;
    }
    cout<<"\n-----------------------------------------------------Thank You-------------------------------------------------------------"<<endl;
}

void acc :: win(){
    cout<<"Congratulations, you won!"<<endl;
    balance += 2*bet;
}

void acc :: loss(){
    cout<<"The computer wins!"<<endl;
}

void acc :: set_bet(){
    char ch;
    bool flag_set_bet = true;
    while(flag_set_bet){
        cout<<"Enter the amount you want to bet : ";
        cin>>bet;
        if( ( balance - bet ) < 0){
            cout<<"\nThe amount to be bet should not be greater than your balance."<<endl;
            cout<<"Do you want to check your balance? y or n : ";
            cin>>ch;
            if(ch == 'y' || ch == 'Y'){
                cout<<endl<<check_balance()<<endl;
            }
        }
        else{
            balance -= bet;
            cout<<"Your balance : "<<check_balance()<<endl;
            flag_set_bet = false;
        }
    }
}

acc::acc(string nam,int ag,long bal){
    name=nam;
    age=ag;
    balance=bal;
}

acc :: acc(){}

void acc::deposit(long amt){
    balance+=amt;
}
void acc::withdraw(long amt){
    if((balance-amt)<0){
        cout<<"You cannot withdraw more than what you have."<<endl;
    }
    else
        balance-=amt;
}
long acc::check_balance(){
    return balance;
}

ostream & operator <<(ostream &out, acc &account){
    out<<account.check_balance();
}

void acc :: winnings(int odds){
    cout<<"\nCongratulations! You won "<<bet*odds<<" dollars.";
    balance += bet + bet*odds;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

int up7down7 :: rand_generator(int n){
    srand(n--);
    return rand()%12 + 1;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------

void blackjack :: clear_hands(){
    for(int i = 0; i < 5 ; i++){
        dhand[i] = 0;
        phand[i] = 0;
    }
}

void blackjack :: add_phand(int seed){
    srand(seed);
    phand[p] = 2 + (rand() % 10);
    p++;
}

void blackjack :: add_dhand(int seed){
    srand(seed);
    dhand[d] = 2 + (rand() % 10);
    d++;
}

void blackjack :: dealer_display(){
    for(int i = 1; dhand[i] != 0; i++){
        cout<<" "<<dhand[i];
    }
}

void blackjack :: player_display(){
    cout<<"\nPlayer's cards : ";
    for(int i = 0; phand[i] != 0; i++){
        cout<<phand[i]<<" ";        
    }
    cout<<endl;
}

void blackjack :: display(){
    // dealer_display();
    cout<<"Dealer's cards : *";
    dealer_display();
    player_display();
}

void blackjack :: set_ace(){
    bool set_ace_flag = true;
    for(int i = 0; i < 5; i++){
        if(phand[i] == 11){
            while(set_ace_flag){
            cout<<"Set your Ace : 11 or 1";
            cin>>phand[i];
            if(phand[i] == 1 || phand[i] == 11){
                set_ace_flag = false;
            }
            else
                cout<<"\nAce can on3ly be 1 or 11. Select again."<<endl;
            }
        }
    }
}

int blackjack :: sum_d(){
    int sum_dhand = 0;
    for(int i = 0; dhand[i] != 0; i++){
        sum_dhand += dhand[i];
    }
    return sum_dhand;
}

int blackjack :: sum_p(){
    int sum_phand = 0;
    for(int i = 0; phand[i] != 0; i++){
        sum_phand += phand[i];
    }
    return sum_phand;
}