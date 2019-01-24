#define _XOPEN_SOURCE 500
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM_MIN 3
#define DIM_MAX 9
int board[DIM_MAX][DIM_MAX];
int d;
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
 
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }


    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    greet();

    
    init();

    while (true)
    {
        clear();

        draw();

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        if (won())
        {
            printf("ftw!\n");
            break;
        }

        printf("Tile to move: ");
        int tile = GetInt();
        
        if (tile == 0)
        {
            break;
        }

        fprintf(file, "%i\n", tile);
        fflush(file);

        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        usleep(500000);
    }
    
    fclose(file);

    return 0;
}


void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}


void init(void)
{   int counter = d*d-1;
    // TODO
    for(int i=0;i<d;i++)
    {   
        for(int j=0;j<d;j++)
        {  if(counter>=0)
            {
              board[i][j] = counter;
              if(d%2 ==0)
              {
                    board[d-1][d-2] = 2;
                    board[d-1][d-3] = 1;
                  
              }
              counter--;
            }
            
        }
    }
}


void draw(void)
{
    for(int i=0;i<d;i++)
    {   
        for(int j=0;j<d;j++)
        {  if(board[i][j]!=0)
            {
              printf("%d",board[i][j]);
            }
            else if (board[i][j]==0)
            {
                printf("_");
            }
           
        }
        printf("\n");
    }
}


bool move(int tile)
{   
       int i,j,a,b,swap;
    for( i=0;i<d;i++)
    {   
        for( j=0;j<d;j++)
      {  if(board[i][j]==0)
        {
            a=i;
            b=j;
        }
      }    
    }   
    for( i=0;i<d;i++)
    {   
        for( j=0;j<d;j++)
      { 
        if(board[i][j]==tile) 
        {  if(i==a&&j==b)
           return false;
            if((i==a&&j==(b-1))||(i==a&&j==(b+1))||(i==a+1&&j==b)||(i==(a-1)&&j==b))
            {
                if(i>=0&&j>=0&&i<d&&j<d)
                {
                    swap=board[a][b];
                    board[a][b]=board[i][j];
                    board[i][j]=swap;
                    return true;
                }
                else
                    return false;
            }
        }
      }
    }
    return false;
}


bool won(void)
{
   int i,j,counter=1,a[d][d],flag=0;
   for(i=0;i<d;i++)
   {
       for(j=0;j<d;j++)
       {
           a[i][j]=counter;
           counter++;
       }
   }
   a[d-1][d-1]=0;
   for(i=0;i<d;i++)
   {
       for(j=0;j<d;j++)
       {
           if(board[i][j]==a[i][j])
           {
               flag=0;
           }
           else if(board[i][j]!=a[i][j])
           {
               flag=1;
               return false;
               
           }
       }
   }
   if(flag==0)
   {return true;}
   
   return false;
}