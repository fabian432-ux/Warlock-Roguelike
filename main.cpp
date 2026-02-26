#include <iostream>
using namespace std;
//base class
class Character{
private:
    int Health;
    int Attack;
    string Name;
public:
    int Money;
    int EachXTurn=3;
    //constructor
    Character(int Health,int Attack){
        setHealth(Health);
        setAttack(Attack);
    }
    //another constructor specific to the warlock class
    Character(int Health,int Attack,string Name){
        setHealth(Health);
        setAttack(Attack);
        setName(Name);
    }
    //setters
    void setName(string Name)
    {
        this->Name=Name;
    }
    void setHealth(int Health){
        this->Health=Health;
    }
    void setAttack(int Attack){
        this->Attack=Attack;
    }
    //getters
    string getName(){
        return Name;
    }
    int getAttack(){
        return Attack;
    }
    int getHealth(){
        return Health;
    }
    //methods of the class
    void IncreaseGold(Character&Clasa){
        Clasa.Money=Clasa.Money+1;
    }
    void LoseHp(int DmgTaken){
        Health=Health-DmgTaken;
    }
    //Anything that is not Warlock will attack
    virtual void attack(Character&target,Character&attacker){
        target.Health=target.Health-attacker.Attack;
    }
    //destructor
    ~Character(){}

};
//inheritance
class Monster : public Character{
public:
    //constructors specific so that demons will work(not necessary)
    Monster(): Character(0,0){}
    Monster(int Health,int Attack): Character(Health,Attack){}
};
//inheritance
class Warlock :public Character{
public:
    //public atributes
    int BlackMagic=1;
    int BonusDemon=0;
    Monster Demon3=Monster();
    Monster Demon2=Monster();
    Monster Demon1=Monster();
    //constructor in wich we set the hp and attack to a certain value
    Warlock(string name): Character(60,1,name){}
    //methods which will be used during the battle phase
    void IncreaseBlackMagic(){
        if(BlackMagic<3)
            BlackMagic++;
    }
    //first ability
    void MakeThemSuffer(Character&target, int CataMana){
        target.LoseHp(CataMana*3);
    }
    //creating demons so they can fight on our side
    void CDemon1(){
        Demon1=Monster(10+BonusDemon,2+BonusDemon);
    }
    void CDemon2(){
        Demon2=Monster(10+BonusDemon,2+BonusDemon);
    }
    void CDemon3(){
        Demon3=Monster(10+BonusDemon,2+BonusDemon);
    }
    //second ability wich will summon demons
    void SummonPortal(int BlackMagic)
    {
        for(int i=1;i<=BlackMagic;i++){

            if(DemonAlive1()==0){
                CDemon1();
                this->BlackMagic--;
            }
            else if(DemonAlive2()==0){
                CDemon2();
                this->BlackMagic--;
            }
            else if(DemonAlive3()==0){
                CDemon3();
                this->BlackMagic--;
            }
        }

    }
    //after each fight we reset the values
    void ResetDemons(){
        Demon1=Monster();
        Demon2=Monster();
        Demon3=Monster();
    }
    //we check if demons are alive
    bool DemonAlive1(){
        if(Demon1.getHealth()>0)
            return true;
        else
            return false;
    }
    bool DemonAlive2(){
        if(Demon2.getHealth()>0)
            return true;
        else
            return false;
    }
    bool DemonAlive3(){
        if(Demon3.getHealth()>0)
            return true;
        else
            return false;
    }
    //demons attack
    void Demon1Attack(Character&target){
        Demon1.attack(target,Demon1);
    }
    void Demon2Attack(Character&target){
        Demon2.attack(target,Demon2);
    }
    void Demon3Attack(Character&target){
        Demon3.attack(target,Demon3);
    }
    void MagicCircle(int&Imune){
        Imune=1;
    }
    //only the warlock will attack here.This is also the overriten function
    void attack(Character& target, Character& attacker) override {
        int damage = attacker.getAttack();
        target.LoseHp(damage);
        attacker.setHealth(attacker.getHealth()+3);
    }
    //destructor
    ~Warlock(){}

};
//inheritance
class Enemy : public Monster{
public:
    //constructors
    Enemy(int Health,int Attack):Monster(Health,Attack){}
    //here enemies will upgrade the stats
    void UpdateStats(int&Hp,int&Atk){
        Hp=Hp+5;
        Atk=Atk+5;
        setHealth(Hp+5);
        setAttack(Atk+5);
    }

};
//base shop class
class Items{
    //protected atributes
protected:
    int Cost;
    string Name;
public:
    //constructor with the cost and name of the items
    Items(int Cost,string Name){
        this->Cost=Cost;
        this->Name=Name;
    }
    //the method in which we buy a certain item
    void BuyItem(Character&Clasa,Items&IncreseMaxHpPermanent){
        Clasa.Money=Clasa.Money-IncreseMaxHpPermanent.Cost;

    }
};
//inharitance from the item class
class OneGold : public Items{
public:
    //atributes
    int MaxHp=0;
    int MaxAttk=0;
    //constructor in wich we set the cost and name
    OneGold() : Items(1,"OneGoldItem"){}
    //the permanent upgrade that will increase the stats of the warlock
    void IncreseMaxHpSpell(Warlock&Clasa,OneGold&IncreseMaxHpPermanent){
        MaxHp=MaxHp+15;
        MaxAttk=MaxAttk+8;
        Clasa.setHealth(Clasa.getHealth()+15);
        Clasa.setAttack(Clasa.getAttack()+8);
        IncreseMaxHpPermanent.BuyItem(Clasa,IncreseMaxHpPermanent);
    }

};
class TwoGold : public Items{
public:
    //atributes
    int BonusHpDemons;
    //constructor in wich we set the cost and name
    TwoGold(): Items(2,"TwoGoldItem"){}
    //the method in wich we upgrade the stats of our demons for the rest of the run
    void StrongerDemons(Warlock&Clasa,TwoGold&MakeDemonsStronger){
        BonusHpDemons=BonusHpDemons+5;
        Clasa.BonusDemon=Clasa.BonusDemon+5;
        MakeDemonsStronger.BuyItem(Clasa,MakeDemonsStronger);

    }
};
class ThreeGold :public Items{
public:
    //constructor in wich we set the cost and name
    ThreeGold(): Items(3,"ThreeGoldItem"){}
    //method in wich we decrease the time in wich we reuse the third ability
    void Insanity(Warlock&Clasa,ThreeGold Update){
        Clasa.EachXTurn=Clasa.EachXTurn-1;
        Update.BuyItem(Clasa,Update);
    }
};
//the shop in wich we buy certain items
void ShopPhase(OneGold&IncreaseHpPermanent,Warlock&Clasa,TwoGold&IncreseDemonHp,ThreeGold&Update){
    int Action;
    cout<<"Welcome to the shop "<<Clasa.getName()<<"!"<<endl;
    cout<<"You have "<<Clasa.Money<<" gold"<<endl;
    cout<<"Choose a item from the shop"<<endl;
    cout<<"Press 1 to upgrade you maximim hp by 15 and attack by 8 for 1 gold"<<endl<<"Press 2 to add +8/+8 yo your demons for the rest of the game for 2 gold"<<endl<<"Press 3 so the 'Magic circle' ability can be used more often for 3 gold"<<endl<<"Press 0 to exist the shop"<<endl;
    cin>>Action;
    if(Action==1 && Clasa.Money>=1){
        IncreaseHpPermanent.IncreseMaxHpSpell(Clasa,IncreaseHpPermanent);
        cout<<"You have increased your hp by "<<IncreaseHpPermanent.MaxHp<<" and attack by "<<IncreaseHpPermanent.MaxAttk;
    }
    if(Action==2 && Clasa.Money>=2){
        IncreseDemonHp.StrongerDemons(Clasa,IncreseDemonHp);
        cout<<"Your demons have "<<IncreseDemonHp.BonusHpDemons<<" extra stats for the rest of the game"<<endl;
    }
    if(Action==3 && Clasa.Money>=2){
        Update.Insanity(Clasa,Update);
        cout<<"It now takes one less turn to use Magic circle!"<<endl;
    }

}
//the demons that attack
void DemonAttack(Warlock&Clasa,Enemy&Enemy1){
    if(Clasa.DemonAlive1()==1)
        Clasa.Demon1Attack(Enemy1);
    if(Clasa.DemonAlive2()==1)
        Clasa.Demon2Attack(Enemy1);
    if(Clasa.DemonAlive3()==1)
        Clasa.Demon3Attack(Enemy1);
}
//every character attacks
void AttackPhase(Warlock&Clasa,Enemy&Enemy1,int Imune){
    if(Imune==0){
        if(Clasa.DemonAlive3()==1)
            Enemy1.attack(Clasa.Demon3,Enemy1);
        else if(Clasa.DemonAlive2()==1)
            Enemy1.attack(Clasa.Demon2,Enemy1);
        else if(Clasa.DemonAlive1()==1)
            Enemy1.attack(Clasa.Demon1,Enemy1);
        else
            Enemy1.attack(Clasa,Enemy1);
    }
    DemonAttack(Clasa,Enemy1);
    Clasa.attack(Enemy1,Clasa);
}
//the battlephase in which we use certain abilities to fight the enemies
void Battlefield(Warlock&Clasa,Enemy&Enemy1){
    int Turn=0;
    while(Clasa.getHealth()>0 && Enemy1.getHealth()>0)
    {
        cout<<"You have "<<Clasa.BlackMagic<<" BlackMana"<<endl;
        cout<<"You have "<<Clasa.getAttack()<<" attack and "<<Clasa.getHealth()<<" health"<<endl;
        cout<<"Enemy has "<<Enemy1.getAttack()<<" attack and "<<Enemy1.getHealth()<<" health"<<endl;
        if(Clasa.DemonAlive1()==1)
            cout<<"The first demon has "<<Clasa.Demon1.getAttack()<<" attack and "<<Clasa.Demon1.getHealth()<<" health"<<endl;
        if(Clasa.DemonAlive2()==1)
            cout<<"The second demon has "<<Clasa.Demon2.getAttack()<<" attack and "<<Clasa.Demon2.getHealth()<<" health"<<endl;
        if(Clasa.DemonAlive3()==1)
            cout<<"The third demon has "<<Clasa.Demon3.getAttack()<<" attack and "<<Clasa.Demon3.getHealth()<<" health"<<endl;
        int Imune=0;
        int Actiune;
        cout<<"Cast a spell"<<endl;
        cout<<"Press 1 to cast Make them suffer that will deal 6 magic damage to the opponent"<<endl<<"Press 2 to cast the Summoning portal which will summon demons equivalent to your black mana(max 3). "<<"You can summon "<<Clasa.BlackMagic<<endl<<"Press 3 to cast Magic Circle to get imune the next battle phase "<<Clasa.EachXTurn-Turn<<" turns until can be used"<<endl;
        cin>>Actiune;
        if(Actiune==1){
            cout<<"Casted:Make Them suffer! and you dealt 6 dmg! "<<endl;
            Clasa.MakeThemSuffer(Enemy1,2);
        }
        if(Actiune==2){
            cout<<"Casted:SummoningPortal to summon "<<Clasa.BlackMagic<<" Demons"<<endl;
            Clasa.SummonPortal(Clasa.BlackMagic);
        }
        if(Actiune==3 && Turn==Clasa.EachXTurn){
            cout<<"Casted:Magic Circle to be imune to the next attack"<<endl;
            Clasa.MagicCircle(Imune);
        }
        AttackPhase(Clasa,Enemy1,Imune);
        if(Actiune!=2){
            Clasa.IncreaseBlackMagic();
        }
        if(Clasa.EachXTurn==Turn && Actiune==3){
            Turn=0;
        }
        else if(Clasa.EachXTurn!=Turn){
            Turn++;
        }
    }
}
//the objects and the loop that goes untill you die or you beat 10 monsters
void FightingPhaseWarlock(Warlock&Clasa)
{
    int Hp=20,Atk=4;
    int i;
    Clasa.Money=0;
    OneGold IncreaseHpPermanent;
    IncreaseHpPermanent.MaxHp=0;
    TwoGold IncreseDemonStats;
    IncreseDemonStats.BonusHpDemons=0;
    ThreeGold Update;
    for(i=1;i<=10;i++)
    {
        cout<<"Fight number "<<i<<endl;
        Clasa.BlackMagic=1;
        Enemy Enemy1(Hp,Atk);
        Battlefield(Clasa,Enemy1);
        if(Clasa.getHealth()<=0){
            cout<<"You died"<<endl;
            break;
        }
        Enemy1.UpdateStats(Hp,Atk);
        Clasa.ResetDemons();
        Clasa.IncreaseGold(Clasa);
        ShopPhase(IncreaseHpPermanent,Clasa,IncreseDemonStats,Update);

    }
    if(i>10){
        cout<<"You Win"<<endl;
    }
}
//naming the warlock
void WarlockRun()
{
    cout<<"Choose the name of your Warlock:"<<endl;
    string Name;
    cin>>Name;
    Warlock Ilie(Name);
    cout<<"Let's see how far can you go!"<<endl;
    FightingPhaseWarlock(Ilie);
}
//the start
int main() {
    WarlockRun();
}
