#ifndef _Ter_H
class Tetrimino
{
    protected:
    int figure[4];
    int loai;
    public:
    virtual int getloai(){return loai;};
    virtual int* getback(){
        int*a =new int[4];
        for(int i=0;i<4;i++)
        {
            a[i]=figure[i];
        }
        return a;
    }
    // friend class Tetris;
};
class TerI:public Tetrimino
{
    public:
    TerI(){
        figure[0]=0;
        figure[1]=1;
        figure[2]=2;
        figure[3]=3;
        loai=1;
    }
};
class TerZ:public Tetrimino
{
    public:
    TerZ(){
        figure[0]=6;
        figure[1]=5;
        figure[2]=1;
        figure[3]=0;
        loai=2;
    }
};
class TerS:public Tetrimino
{
    public:
    TerS(){
        figure[0]=5;
        figure[1]=6;
        figure[2]=2;
        figure[3]=3;
        loai=3;
    }
};
class TerJ:public Tetrimino
{
    public:
    TerJ(){
        figure[0]=1;
        figure[1]=2;
        figure[2]=3;
        figure[3]=7;
        loai=4;
    }
};
class TerL:public Tetrimino
{
    public:
    TerL(){
        figure[0]=2;
        figure[1]=1;
        figure[2]=0;
        figure[3]=4;
        loai=5;
    }
};
class TerT:public Tetrimino
{
    public:
    TerT(){
        figure[0]=5;
        figure[1]=1;
        figure[2]=2;
        figure[3]=0;
        loai=6;
    }
};
class TerO:public Tetrimino
{
    public:
    TerO(){
        figure[0]=1;
        figure[1]=2;
        figure[2]=5;
        figure[3]=6;
        loai=7;
    }
};
#endif