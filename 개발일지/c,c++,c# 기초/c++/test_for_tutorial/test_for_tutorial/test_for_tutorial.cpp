/*
#include <iostream>
using namespace std;

void Test() {
    int a = 100;

    cout << a << endl;
}


int main()
{
    int hp = 10;
    Test();

    int mp = 200;
    
}
*/

//textRPG
#include <iostream>
using namespace std;


enum Player_type
{
    pt_none = 0,
    pt_worrior =1, pt_thief =2, pt_mage =3 
};
enum Monster_type
{
    mt_none =0,
    mt_Slime =1, mt_Orc =2, mt_Skeleton = 3
};

// 전역인것은 똑같으니 이렇게 관리하면 좋다.
struct State_info
{
    int hp;
    int attack;
    int defence;
};

Player_type player_type; //c++에선 enum은 int정수랑 같다. 근데 c#은 아니다...
State_info player_state;

Monster_type monter_type;
State_info monter_state;

void EnterLobby();
void SelectPlayer();
void EnterField();
void CreateRandomMonster();
void EnterBattle();
void WaitForNextKey();

int main()
{
    srand((unsigned int)time(0)); // 가상의 랜덤이기때문에 첫번째 값만 이렇게 씨드값을 설정해야함.
    EnterLobby();
}

void EnterLobby() {
    while (true)
    {
        cout << "------------------" << endl;
        cout << "로비에 입장하였습니다~~!" << endl;
        cout << "------------------" << endl;

        //플레이어 직업 선택
        SelectPlayer();

        cout << "------------------" << endl;
        cout << "1. 필드 입장 2. 게임 종료" << endl;
        cout << "------------------" << endl;

        int input;
        cin >> input;

        if (input == 1)
        {
            EnterField();
        }
        else
        {
            return;
        }
    }
}

void SelectPlayer() {

    while (true)
    {
        cout << "------------------" << endl;
        cout << "직업을 골라주세요~~!" << endl;
        cout << "1.전사 2.마법사 3. 도적" << endl;
        cout << "> ";

        int choice;
        cin >> choice;

        if (choice == pt_worrior)
        {
            cout << "전사 생성중..." << endl;
            player_state.hp = 150;
            player_state.attack = 10;
            player_state.defence = 5;
            player_type = pt_worrior;
            break;
        }
        else if (choice == pt_thief)
        {
            cout << "도적 생성중..." << endl;
            player_state.hp = 100;
            player_state.attack = 15;
            player_state.defence = 3;
            player_type = pt_thief;
            break;
        }
        else if (choice == pt_mage)
        {
            cout << "마법사 생성중..." << endl;
            player_state.hp = 80;
            player_state.attack = 25;
            player_state.defence = 0;
            player_type = pt_mage;
            break;
        }
    }
}

void EnterField()
{
    while (true)
    {
        cout << "------------------" << endl;
        cout << "필드에 입장 했습니다!" << endl;
        cout << "------------------" << endl;

        cout << "[PLAYER] HP : " << player_state.hp << " / ATT : " << player_state.attack << " / DEF : " << player_state.defence << endl;

        //몬스터 스폰
        CreateRandomMonster();

        cout << "------------------" << endl;
        cout << "1. 전투 2. 도주" << endl;
        cout << "> ";

        int input;
        cin >> input;
        if (input == 1)
        {
            EnterBattle();
            if (player_state.hp == 0)
                return;
        }
        else
        {
            return;
        }
    }
}

void CreateRandomMonster()
{
    //rand() 랜덤한숫자를 내보내는 함수
    //c++에선 랜덤함수가 c#과 다르다. 씨드(초기화)가 필요함
    int Random_choice = 1 + (rand() % 3);

    switch (Random_choice)
    {
    case mt_Slime:
        cout << "슬라임 생성중 ...! (HP:30 / ATT:2 / DEF:0)" << endl;
        monter_state.hp = 30;
        monter_state.attack = 2;
        monter_state.defence = 0;
        monter_type = mt_Slime;
        break;

    case mt_Orc:
        cout << "오크 생성중 ...! (HP:40 / ATT:10 / DEF:3)" << endl;
        monter_state.hp = 40;
        monter_state.attack = 10;
        monter_state.defence = 3;
        monter_type = mt_Orc;
        break;

    case mt_Skeleton:
        cout << "해골 생성중 ...! (HP:80 / ATT:15 / DEF:5)" << endl;
        monter_state.hp = 80;
        monter_state.attack = 15;
        monter_state.defence = 5;
        monter_type = mt_Skeleton;
        break;
    }
}

void EnterBattle()
{
    while (true)
    {
        int damage = player_state.attack - monter_state.defence;
        if (damage < 0)
            damage = 0;

        //선빵 처리
        monter_state.hp -= damage;
        if (monter_state.hp < 0)
            monter_state.hp = 0;

        cout << "몬스터의 남은 체력 : " << monter_state.hp << endl;

        if (monter_state.hp == 0)
        {
            cout << "몬스터 처치" << endl;
            WaitForNextKey();
            return;
        }

        //반격
        damage = monter_state.attack - player_state.defence;
        if (damage < 0)
            damage = 0;

        player_state.hp -= damage;
        if (player_state.hp < 0)
            player_state.hp = 0;
        cout << "플레이어 남은 체력 : " << player_state.hp << endl;

        if (player_state.hp == 0)
        {
            cout << "당신은 사망했습니다..." << endl;
            WaitForNextKey();
            return;
        }
    }
}

void WaitForNextKey()
{
    cout << "계속 하려면 1 을 눌러주세요..." << endl;
    cout << "> ";

    int input;
    cin >> input;

    system("cls"); //콘솔창 깨끗하게만들어줌
}
