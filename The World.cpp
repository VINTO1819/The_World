#include<stdio.h>
#include<windows.h>

#define Sleep(X); //이 옵션을 사용시 디버그 모드 실행. 모든 지연 제거. 

/*함수 선언부*/



int City();//마을 

int Dungeon(int Grade);//던전 

int Dungeon_Start(int Grade);//던전 플래이어 위치설정 

int Dungeon_Main(int Grade);//던전 메인화면 

int Dungeon_Fight(int Grade);//던전 전튜 

int Fight_Attek(int Grade);//공격 

int CheckMobDied(int Grade);//몹 사망 여부 

int MobAttek(int Grade);//몹공격 

int CheckPlayerDied();//플레이어 사망 여부 

int Shop();//상점 

int ShopExpend();//상점 소모품

int ShopPotion();//상점 물약 

int CheckLvUp();//레벨업 체크 

int LevelUp();//레벨업 

int BuyItem(int ItemNum);//아이템 구메 

int playerRegenTick();//플래이어 채력/마나리젠

int ShowStat();//스텟 보여주기 

int ShowArmor();//장비창 

int ShowInventory();//인벤토리 

int SelectItem();//아이템선택 

int Useitem(int Num);

int HpPotion(int Hp, int Potion);

int PpPotion(int Pp, int Potion);

int ColorString(int Color,char String[]);//색깔 코드 바꾸기 함수 

int Line()
{
	
	ColorString(8,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	
}


/*색깔 코드표 정리

00 검정색	08 회색 
01 파란색	09 연한 파란색	 
02 초록색	10 연한 초록색 
03 옥색	    11 연한 옥색 
04 빨간색	12 연한 빨간색 
05 자주색	13 연한 자주색 
06 노란색	14 연한 노란색 
07 흰색 	15 진한 흰색 
*/


/*-----변수 선언부-----*/ 

struct stat
{
	
		/*-----변수 선언부-----*/ 
	
	//스텟 
	int Lv,Exp,MaxExp;//레벨,경험치 관련 
	int Hp,MaxHp,HpGen;//hp관련 
	int Pp,MaxPp,PpGen;//pp관련 
	int Atk;//공격관련 
	int Def;//방어 
	int Speed;//속도
	int Power;//힘 
	char Name[50];
	
	int x,y;//좌표 
	
	//분배스텟
	
	int STR;//힘(공격, 힘에 영향)	 
	int INT;//지능(마나,마나재생력,속도에 영향) 
	int SPD;//속도(속도에 크게 영향) 
	int REG;//재생성(채력 재생력, 마나 재생력, 마나에 영향)
	int BOD;//탱커(채력,방어력,힘에 영향) 
	
	//장비
	
	int Hat = 19;
	int Body = 19;
	int Leggings = 19;
	int Shose = 19;
	int Wepon = 19;
	int Shiled = 19;
	
	//아이템 소지
		
	int Item[32][2];//1차는 아이템코드, 2차는 보유 갯수 
	
		
}; 

struct stat p;

struct stat Mob[2];

//아이템 

/*
1:귀환석
2~5:채력물약
6~9:마나물약
10~18:(초보자의)검,활,지팡이,방패,투구,갑옷,바지,신발,로브 
19:없음 
*/

int HpPotionHeal[4] = {50,750,5000,30000};

int Item[19] = {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ItemPrize[19] = {10,50,1000,10000,100000,50,1000,10000,100000,50,50,50,70,30,100,70,20,150,0};

char ItemName[19][50] = {"귀환석\n기절시 마을로 귀환시켜줍니다.",
"채력 물약(소)\nHp를 50 회복합니다.",
"채력 물약(중)\nHp를 750 회복합니다.",
"채력 물약(대)\nHp를 5,000 회복합니다.",
"채력 물약(특대)\nHp를 30,000 회복합니다.",
"마나 물약(소)\nPp를 50 회복합니다.",
"마나 물약(중)\nPp를 750 회복합니다.",
"마나 물약(대)\nPp를 5,000 회복합니다.",
"마나 물약(특대)\nPp를 30,000 회복합니다.",
"초보자의 목검",
"초보자의 나무 활",
"참나무 지팡이",
"초보자의 방패",
"토끼 가죽 투구",
"토끼 가죽 갑옷",
"토끼 가죽 바지",
"토끼 가죽 신발",
"토끼 가죽 로브",
"없음",
};

int Money = 100;//돈 

char MAPINF[10][1000] =
{
	{"1층부터 10층의 던전에는 약한 마물들이 살고 있다.\n그 중 1층은 마을과도 연결되어 있는 곳.\저 멀리 슬라임이 보인다.\n"},
	{"저 멀리 슬라임 덩어리가 보인다.\n"},
	{"저 멀리 해골 병사가 보인다.\n"},
	{"저 멀리 스켈레톤이 보인다.\n"},
	{"저 멀리 썩은 스켈레톤이 보인다.\n"},
	{"저 멀리 고블린이 보인다.\n"},
	{"저 멀리 홉 고블린이 보인다.\n"},
	{"저 멀리 트롤이 보인다.\n"},
	{"저 멀리 오크가 보인다.\n"},
	{"보스가 있는 최상층이다.\n저 멀리 골렘이 보인다.\n"}
	
};
char MobName[10][100] = 
{
	{"슬라임"},
	{"슬라임 덩어리"},
	{"해골 병사"},
	{"스켈레톤"},
	{"썩은 스켈레톤"},
	{"고블린"},
	{"홉 고블린"},
	{"트롤"},
	{"오크"},
	{"골렘"}
};

int main()//메인함수 
{
	
	/*-----변수 초기화-----*/
	
	//플레이어 스텟	
	p.Lv = 1, p.Exp = 0, p.MaxExp = 10;//레벨 
	p.MaxHp = 100, p.Hp = p.MaxHp, p.HpGen = 0;//채력 
	p.MaxPp = 50, p.Pp = p.MaxPp, p.PpGen = 1;//마나 
	p.Atk = 5, p.Def = 0;//공격력, 방어력 
	p.Speed = 100, p.Power = 10;//속도, 힘 

	//플래이어 분배스텟
	p.STR = 0, p.INT = 0, p.SPD = 0, p.REG = 0, p.BOD = 0;//분배스텟

	City();

}

int City()//마을 
{
	
	//몹 스텟 초기화 
	
	//1층  
	Mob[0].Exp = 10,Mob[0].MaxExp = 10;
	Mob[0].MaxHp = 30, Mob[0].Hp = Mob[0].MaxHp, Mob[0].HpGen = 0;//채력 
	Mob[0].MaxPp = 0, Mob[0].Pp = Mob[0].MaxPp, Mob[0].PpGen = 0;//마나 
	Mob[0].Atk = 3, Mob[0].Def = 0;//공격력, 방어력 
	Mob[0].Speed = 40, Mob[0].Power = 3;//속도, 힘
	
	//2층
	Mob[1].Exp = 20,Mob[1].MaxExp = 20;
	Mob[1].MaxHp = 40, Mob[1].Hp = Mob[1].MaxHp, Mob[1].HpGen = 0;//채력 
	Mob[1].MaxPp = 0, Mob[1].Pp = Mob[1].MaxPp, Mob[1].PpGen = 0;//마나 
	Mob[1].Atk = 4, Mob[1].Def = 0;//공격력, 방어력 
	Mob[1].Speed = 100, Mob[1].Power = 6;//속도, 힘 
	
	//3층
	Mob[2].Exp = 40,Mob[2].MaxExp = 40;
	Mob[2].MaxHp = 60, Mob[2].Hp = Mob[2].MaxHp, Mob[2].HpGen = 0;//채력 
	Mob[2].MaxPp = 0, Mob[2].Pp = Mob[2].MaxPp, Mob[2].PpGen = 0;//마나 
	Mob[2].Atk = 6, Mob[2].Def = 0;//공격력, 방어력 
	Mob[2].Speed = 100, Mob[2].Power = 9;//속도, 힘 
	
	//4층
	Mob[3].Exp = 70,Mob[3].MaxExp = 70;
	Mob[3].MaxHp = 90, Mob[3].Hp = Mob[3].MaxHp, Mob[3].HpGen = 1;//채력 
	Mob[3].MaxPp = 0, Mob[3].Pp = Mob[3].MaxPp, Mob[3].PpGen = 0;//마나 
	Mob[3].Atk = 9, Mob[3].Def = 0;//공격력, 방어력 
	Mob[3].Speed = 100, Mob[3].Power = 12;//속도, 힘 
	
	//5층
	Mob[4].Exp = 110,Mob[4].MaxExp = 120;
	Mob[4].MaxHp = 150, Mob[4].Hp = Mob[4].MaxHp, Mob[4].HpGen = 1;//채력 
	Mob[4].MaxPp = 0, Mob[4].Pp = Mob[4].MaxPp, Mob[4].PpGen = 0;//마나 
	Mob[4].Atk = 13, Mob[4].Def = 0;//공격력, 방어력 
	Mob[4].Speed = 100, Mob[4].Power = 15;//속도, 힘 
	
	//6층
	Mob[5].Exp = 160,Mob[5].MaxExp = 190;
	Mob[5].MaxHp = 230, Mob[5].Hp = Mob[5].MaxHp, Mob[5].HpGen = 2;//채력 
	Mob[5].MaxPp = 0, Mob[5].Pp = Mob[5].MaxPp, Mob[5].PpGen = 0;//마나 
	Mob[5].Atk = 18, Mob[5].Def = 2;//공격력, 방어력 
	Mob[5].Speed = 100, Mob[5].Power = 18;//속도, 힘 
	
	//7층
	Mob[6].Exp = 220,Mob[6].MaxExp = 280;
	Mob[6].MaxHp = 480, Mob[6].Hp = Mob[6].MaxHp, Mob[6].HpGen = 4;//채력 
	Mob[6].MaxPp = 0, Mob[6].Pp = Mob[6].MaxPp, Mob[6].PpGen = 0;//마나 
	Mob[6].Atk = 24, Mob[6].Def = 3;//공격력, 방어력 
	Mob[6].Speed = 100, Mob[6].Power = 21;//속도, 힘 
	
	//8층
	Mob[7].Exp = 290,Mob[7].MaxExp = 450;
	Mob[7].MaxHp = 750, Mob[7].Hp = Mob[7].MaxHp, Mob[7].HpGen = 7;//채력 
	Mob[7].MaxPp = 0, Mob[7].Pp = Mob[7].MaxPp, Mob[7].PpGen = 0;//마나 
	Mob[7].Atk = 31, Mob[7].Def = 4;//공격력, 방어력 
	Mob[7].Speed = 100, Mob[7].Power = 24;//속도, 힘 
	
	//9층
	Mob[8].Exp = 370,Mob[8].MaxExp = 600;
	Mob[8].MaxHp = 1000, Mob[8].Hp = Mob[8].MaxHp, Mob[8].HpGen = 10;//채력 
	Mob[8].MaxPp = 0, Mob[8].Pp = Mob[8].MaxPp, Mob[8].PpGen = 0;//마나 
	Mob[8].Atk = 39, Mob[8].Def = 5;//공격력, 방어력 
	Mob[8].Speed = 100, Mob[8].Power = 27;//속도, 힘 
	
	//10층
	Mob[9].Exp = 1500,Mob[9].MaxExp = 2000;
	Mob[9].MaxHp = 5000, Mob[9].Hp = Mob[9].MaxHp, Mob[9].HpGen = 50;//채력 
	Mob[9].MaxPp = 10, Mob[9].Pp = Mob[9].MaxPp, Mob[9].PpGen = 0;//마나 
	Mob[9].Atk = 50, Mob[9].Def = 10;//공격력, 방어력 
	Mob[9].Speed = 100, Mob[9].Power = 50;//속도, 힘 
	
	//힐 
	
	p.Hp = p.MaxHp;
	
	p.Pp = p.MaxPp;
	
	playerRegenTick();
	
	int Select = 0;
	
	
	
	Line();
	ColorString(9,"-던전의 마을-\n");
	
	Line();
	ColorString(15,"유명한 던전이 있는 마을이다.\n");
	
	B1://B1
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:던전 입장\n");
	ColorString(7,"2:잡화상점 입장\n");
	ColorString(7,"3:스테이더스 확인\n");
	ColorString(7,"4:정비\n");
	
	scanf("%d",&Select);
	
	switch(Select)
	{
		
		case 1:
			Dungeon(0);
			break;
		
		case 2:
			Shop();
			break;
			
		case 3:
			ShowStat();
			goto B1;
			break;
			
		case 4:
			ShowArmor();
			ShowInventory();
			SelectItem();
			goto B1;
			break;
			
		default:
			goto B1;//B1
		
	}
	
	
}

int Dungeon(int Grade)//던전 
{	

	Dungeon_Start(Grade);
	
	Dungeon_Main(Grade);

}

int Dungeon_Start(int Grade)//던전 입장 
{
	
	
	
	playerRegenTick();
	Line();
	ColorString(3, "-던전에 입장하였습니다!-\n");
	Sleep(2000);
	Line();
	ColorString(4, "-기절시 귀환석이 없으면 사망하니 주의해주세요.\n");
	Sleep(2000);
	
}

int Dungeon_Main(int Grade)//던전 선택창 
{
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"");
	printf("-던전 %d층-\n", Grade+1);
	
	Line();
	ColorString(9,"");
	printf("%s", MAPINF[Grade]);
	
	A1://A1
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:전투\n");
	ColorString(7,"2:스탯 확인\n");
	ColorString(7,"3:정비\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			Dungeon_Fight(Grade);
			break;
			
		case 2:
			ShowStat();
			Dungeon_Main(Grade);
			break;
			
		case 3:
			ShowArmor();
			ShowInventory();
			SelectItem();
			break;
			
		default:
			goto A1; //A1
		
	}
	
}

int Dungeon_Fight(int Grade)//전투 
{
	
	playerRegenTick();
	
	Line();
	ColorString(4,"");
	printf("[%s이(가) 튀어나왔다!]\n", MobName[Grade]);
	Sleep(1000);	
	
	int Select = 0;
	
	E1:
	
	Line();
	ColorString(2,"[무엇을 하시겠습니까?]\n");	
	
	C1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	ColorString(7,"1:공격\n");
	//ColorString(7,"2:방어\n");
	ColorString(7,"3:아이템 사용\n");
	//ColorString(7,"4:스킬\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			Fight_Attek(Grade);
			break;
			
		case 3:
			ShowInventory();
			SelectItem();
			break;
			
		default:
			goto C1;//C1
			break;
		
	}
	
	CheckMobDied(Grade);
	
	MobAttek(Grade);
	
	CheckPlayerDied();	
	
	goto E1;
	
}

int Fight_Attek(int Grade)//공격 
{
	
	if(p.Atk - Mob[Grade].Def < 0){
		
		Line();
		ColorString(15,"");
		printf("%s에게 0의 피해를 입혔습니다!\n",MobName[Grade]);
		Sleep(800);
		
	}
	else{
		
		Line();
		ColorString(15,"");
		printf("%s에게 %d의 피해를 입혔습니다!\n",MobName[Grade], p.Atk - Mob[Grade].Def);
		Sleep(800);
		
		Mob[Grade].Hp -= p.Atk - Mob[Grade].Def;	
		
	}
	
	if(Mob[Grade].Hp < 0){
		
		Mob[Grade].Hp = 0;
		
	}
	
	Line();
	ColorString(15,"");
	printf("%s 남은 채력:%d/%d\n",MobName[Grade], Mob[Grade].MaxHp, Mob[Grade].Hp);
	Sleep(800);
	
}

int CheckMobDied(int Grade)//몹 사망여부 
{
	
	if(Mob[Grade].Hp<1)
	{
		
		Line();
		ColorString(1,"");
		printf("%s이(가) 죽었습니다!\n", MobName[Grade]);
		Sleep(800);
		
		p.Exp += Mob[Grade].Exp;
		Line();
		ColorString(2,"");
		printf("경험치를 %d 획득하였습니다!\n",Mob[Grade].Exp);
		Sleep(800);
		
		Money += Mob[Grade].MaxExp;
		Line();
		ColorString(6,"");
		printf("%d골드를 획득하였습니다!\n",Mob[Grade].MaxExp);
		Sleep(800);
		
		CheckLvUp();
		
		Dungeon(Grade+1);
		
	}
	
}

int MobAttek(int Grade)//몹 공격 
{
	
	Line();
	ColorString(5,"");
	printf("%s의 공격!\n",MobName[Grade]);
	Sleep(800);
	
	if(Mob[Grade].Atk - p.Def < 0){
		
		Line();
		ColorString(4,"");
		printf("0의 피해를 입었습니다!\n");
		Sleep(800);
		
	} 
	else{
		
		p.Hp -= Mob[Grade].Atk - p.Def;
	
		Line();
		ColorString(4,"");
		printf("%d의 피해를 입었습니다!\n", Mob[Grade].Atk - p.Def);
		Sleep(800);
		
	}
	
	if(p.Hp < 0){
		
		p.Hp = 0;
		
	}
	
	Line();
	ColorString(2,"");
	printf("남은 채력 %d/%d\n",p.MaxHp,p.Hp);
	Sleep(800);

	
}

int CheckPlayerDied()//플래이어 사망여부 
{
	
	if(p.Hp < 1){
		
		Line();
		ColorString(4,"기절하셨습니다.\n");
		Sleep(800);
		
		if(Item[0] > 0){
			
			Line();
			ColorString(4,"귀환석이 남아 있어 사망하지 않고 마을로 귀환합니다.\n");
			Sleep(800);
			Line();
			ColorString(4,"기절하여 경험치가 0으로 초기화되며, 요구되는 경험치량이 2배 증가합니다..\n");
			Sleep(800);
			p.Exp = 0;
			p.MaxExp *= 2;
			p.Hp = 1;
			Item[0] -= 1;
			City();
			
		}
		else{
			
			Line();
			ColorString(4,"귀환석이 남아 있지 않습니다.\n당신은 사망하였습니다.\n");
			Sleep(800);
			Line();
			ColorString(4,"게임을 처음부터 다시 시작합니다.\n");
			Sleep(800);
			main();
			
		}
		
	}
	
}

int Shop()//상점 
{
	
	
	
	playerRegenTick();
	
	int Select = 0;
	
	Line();
	ColorString(3,"-잡화상점-\n");
	Line();
	ColorString(9,"-여러 가지 물품을 판매하고 있다.\n");
	
	F1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:소모품\n");
	//ColorString(7,"2:장비\n");
	//ColorString(7,"3:판매\n");
	ColorString(7,"4:탈주\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			ShopExpend();
			break;
			
		//case 2:
			break;
			
		//case 3:
			break;
			
		case 4:
			City();
			break;
			
		default:
			goto F1;
		
	}
	
	
}

int ShopExpend()//소모품 
{
	
	
	
	int Select;
	
	Line();
	ColorString(3,"-소모품-\n");
	
	G1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:물약\n");
	ColorString(7,"2:[10골드]귀환석\n");
	ColorString(7,"3:탈주\n");
	
	scanf("%d", &Select);
	
	switch(Select)
	{
		
		case 1:
			ShopPotion();
			break;
			
		case 2:
			BuyItem(0);
			break;
			
		case 3:
			City();
			break;
			
		default:
			goto G1;
		
	}
	
}

int ShopPotion()//물약 
{
	
	
	
	int Select = 0; 
	
	Line();
	ColorString(3,"-물약-\n");
	
	H1:
	
	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]");
	printf("소지금 %dG\n",Money);
	ColorString(7,"1:[50골드]채력 물약(소)[Hp 50 회복]\n");
	ColorString(7,"2:[1,000골드]채력 물약(중)[Hp 750 회복]\n");
	ColorString(7,"3:[10,000골드]채력 물약(대)[Hp 5,000 회복]\n");
	ColorString(7,"4:[100,000골드]채력 물약(특대)[Hp 30,000 회복]\n");
	ColorString(7,"5:[50골드]마나 물약(소)[Pp 50 회복]\n");
	ColorString(7,"6:[1,000골드]마나 물약(중)[Pp 750 회복]\n");
	ColorString(7,"7:[10,000골드]마나 물약(대)[Pp 5,000 회복]\n");
	ColorString(7,"8:[100,000골드]마나 물약(특대)[Pp 30,000 회복]\n");
	ColorString(7,"9:탈주\n");
	
	scanf("%d", &Select);
	
	if(0 < Select){
		
		if(Select<9){
			
			BuyItem(Select);
			
		}
		else if(Select = 9){
			
			City();
			
		}
		
	}
	
		goto H1;
	
}

int CheckLvUp()//레벨업 확인 
{
	
	if(p.Exp > p.MaxExp-1){
		
		LevelUp();
		
	}
	
}

int LevelUp()//레벨업 
{
	
	Line();
	ColorString(6,"레벨이 올랐습니다!\n");
	
	p.Lv += 1; 
	p.Exp -= p.MaxExp;
	p.Hp = p.MaxHp;
	p.Pp = p.MaxPp;
	p.MaxExp *= 1.1;
	p.MaxHp *= 1.04;
	p.MaxPp *= 1.041;
	p.HpGen += p.Lv/5;
	p.PpGen += p.Lv/3;
	p.Atk += p.Lv/10;
	p.Def += p.Lv/35;
	p.Speed += p.Lv/100;
	p.Power += p.Lv/20;
	
	CheckLvUp();
	
}

int BuyItem(int ItemNum)//아이템 구매 
{
	
	if(Money > ItemPrize[ItemNum]-1){
		
		Item[ItemNum] += 1;
		Money -= ItemPrize[ItemNum];
		
		Line();
		ColorString(6,"");
		printf("%s을(를)구매하였습니다!\n",ItemName[ItemNum]);
		
	}
	else{
		
		Line();
		ColorString(4,"");
		printf("골드가 모자랍니다!\n");
		
	}
	
	Shop();
	
}  

int playerRegenTick()//회복 
{
	
	p.Hp += p.HpGen;
	p.Pp += p.PpGen;
	if(p.Hp > p.MaxHp){
		
		p.Hp = p.MaxHp;
		
	}
	if(p.Pp > p.MaxPp){
		
		p.Pp = p.MaxPp;
		
	}
	
}

int ShowStat()//스텟창 
{
	
	Line();
	ColorString(1,"-스테이더스-\n");
	Line();
	ColorString(15,"");
	printf("LV:%-20d Exp:%-10d/%-10d\n",p.Lv,p.MaxExp,p.Exp);
	printf("Hp:%-10d/%-10dHpGen:%-20d\n",p.MaxHp,p.Hp,p.HpGen);
	printf("Pp:%-10d/%-10dPpGen:%-20d\n",p.MaxPp,p.Pp,p.PpGen); 
	printf("Atk:%-20dDef:%-20d\n",p.Atk,p.Def);
	printf("Speed:%-18dPower:%-20d\n",p.Speed,p.Power);
	
}

int ShowArmor()//장비창
{
	
	Line();
	ColorString(1,"-장비-\n");
	
	Line();	
	ColorString(15,"");
	printf("모자:%s\n",ItemName[p.Hat-1]);
	printf("갑옷:%s\n",ItemName[p.Body-1]);
	printf("바지:%s\n",ItemName[p.Leggings-1]);
	printf("신발:%s\n",ItemName[p.Shose-1]);
	printf("무기:%s\n",ItemName[p.Wepon-1]);
	printf("방패:%s\n",ItemName[p.Shiled-1]);
	
} 

int ShowInventory()//인벤토리
{
	
	
	
	Line();
	
	ColorString(1,"-인벤토리-\n");	
	
} 

int SelectItem()
{
	
	int Select = 0;
	
	int i = 0;

	Line();
	ColorString(10,"[메뉴와 호환되는 숫자를 입력하세요.]\n");
	
	while(i < 19){
		
		if(Item[i] > 0){
			
			Line();
			
			ColorString(15,"");
			
			printf("%d:%s[%d개]\n",i+1,ItemName[i],Item[i]);
			
			
			
		}
		i += 1;
		
	}
	
	scanf("%d", &Select);
	
	Select -= 1;
	
	if(Item[Select] > -1){
		
		Useitem(Select);
		
	}
	else{
		
		Line();
		ColorString(5,"아이템이 존재하지 않거나 갯수가 부족합니다!\n");
		
	}
		
}

int Useitem(int Num)
{

	if(Item[Num] > -1){
		
		if(Num > 0 && Num<5)
			HpPotion(HpPotionHeal[Num-1],Num-1);
			
		if(Num > 4 && Num<9)
			PpPotion(HpPotionHeal[Num-1],Num-1);
		
		switch(Num){
		
			case 0:
				Line();
				ColorString(4,"마을로 귀환합니다.\n");
				Sleep(800);
				Item[0] -= 1;
				City();
				break;
				
			case 1:
				break;
			
			case 2:
				break;
			
			case 3:
				break;
			
			case 4:
				break;
			
			case 5:
				break;
			
			case 6:
				break;
			
			case 7:
				break;
			
			case 8:
				break;	
				
			default:
				Line();
				ColorString(5,"아이템이 존재하지 않거나 갯수가 부족합니다!\n");
				SelectItem();
				
		
		}
		
	}
	
}

int HpPotion(int Hp, int Potion)
{
	
	Line();
	ColorString(1,"체력 물약을 사용하였습니다!\n");
	Sleep(800);
	
	p.Hp += Hp;
	if(p.Hp > p.MaxHp)
		p.Hp = p.MaxHp;
	
	Item[Potion+1] -= 1;
	
}

int PpPotion(int Pp, int Potion)
{
	
	Line();
	ColorString(1,"마나 물약을 사용하였습니다!\n");
	Sleep(800);
	
	p.Pp += Pp;
	if(p.Pp > p.MaxPp)
		p.Pp = p.MaxPp;
	
	Item[Potion+1] -= 1;
	
}

int ColorString(int Color,char String[])//색깔 택스트 출력 
{
		
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),Color);
	
	printf("%s",String);
		
	return 0;
		
}
/*베타 0.1
기본 프로그램 구현
/*베타 0.11
포션 아이템 추가
/*베타 0.12
기절시 경험치 0으로 초기화와 요구 경험치 2배 증가 
*/
