#ifndef _Ter_H
// const int Tetris::figure[7][4] =
// {
//     0, 1, 2, 3, // I
//     0, 1, 5, 6, // Z
//     0, 4, 5, 6, // J
//     2, 6, 5, 4, // L
//     1, 2, 5, 6, // O
//     2, 1, 5, 4, // S
//     1, 4, 5, 6  // T
// };
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
        figure[0]=0;
        figure[1]=1;
        figure[2]=5;
        figure[3]=6;
        loai=2;
    }
};
class TerS:public Tetrimino
{
    public:
    TerS(){
        figure[0]=3;
        figure[1]=2;
        figure[2]=6;
        figure[3]=5;
        loai=3;
    }
};
class TerJ:public Tetrimino
{
    public:
    TerJ(){
        figure[0]=7;
        figure[1]=3;
        figure[2]=2;
        figure[3]=1;
        loai=4;
    }
};
class TerL:public Tetrimino
{
    public:
    TerL(){
        figure[0]=4;
        figure[1]=1;
        figure[2]=2;
        figure[3]=3;
        loai=5;
    }
};
class TerT:public Tetrimino
{
    public:
    TerT(){
        figure[0]=0;
        figure[1]=1;
        figure[2]=2;
        figure[3]=5;
        loai=6;
    }
};
class TerO:public Tetrimino
{
    public:
    TerO(){
        figure[0]=0;
        figure[1]=1;
        figure[2]=4;
        figure[3]=5;
        loai=7;
    }
};
#endif