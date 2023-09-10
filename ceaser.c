#include<stdio.h>
#include<string.h>

void split(char *str,char str_neo[100][100],int *m);
void encryption(char *str,int n);
void decryption(char *str,char str_neo[100][100],int m);

int main(void){
    char str[100];
    char str_neo[100][100];
    int s,n,m=0;
    printf("シーザー暗号の家にようこそ！\n暗号化と複合化どちらを行いますか?　暗号化:0 複合化:1 \n->");
    scanf("%d",&s);
    getchar();
    memset(str_neo,0,sizeof(str_neo));
    if(s==0){
        printf("暗号化する文をアルファベットで入力してください。\n->");
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        printf("何文字ずらしますか？->");
        scanf("%d",&n);
        encryption(str,n);
    }
    else if(s==1){
        printf("複合化する文を入力してください。\n->");
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        split(str,str_neo,&m);
        decryption(str,str_neo,m);
    }
    printf("終了します。\n");
}



void split(char *str,char str_neo[100][100],int *m){
    int i=0,j=0;
    while(1){
        if(i!=0 && str[i-1]=='\0' && str[i]=='\0'){
            break;
        }
        if(str[i]==' '){
            j=0;
            (*m)++;
        }
        else{
            str_neo[*m][j]=str[i];
            j++;
        }
        i++;
    }

}



void encryption(char *str,int n){   //暗号化
    char new_str[100];
    memset(new_str,0,sizeof(new_str));
    for (int i=0;i<strlen(str);i++){
        if(65<=str[i] && str[i]<=90){    //大文字のとき
            if(str[i]+n>90){    //Zを超えたとき
                new_str[i]=(str[i]+n-90)+64;
            }
            else{
                new_str[i]=str[i]+n;
            }
        }
        if(97<=str[i] && str[i]<=122){    //小文字のとき
            if(str[i]+n>122){    //zを超えたとき
                new_str[i]=(str[i]+n-122)+96;
            }
            else{
                new_str[i]=str[i]+n;
            }
        }
        if(str[i]==' '){    //スペース
            new_str[i]=' ';
        }
    }
    printf("暗号文:%s\n",new_str);
}



void decryption(char *str,char str_neo[100][100],int m){
    char new_str[100][100],new_str_x[100],new_str_y[100];
    memset(new_str,0,sizeof(new_str));
    memset(new_str_x,0,sizeof(new_str_x));
    memset(new_str_y,0,sizeof(new_str_y));
    int a=0,b=0,nothing=0,c;    //a:new_str_の添字　b:new_strの添字　xy:ずらす数  nothing:暗号文に一文字がない時を判断するための変数  c:正しい平文が見つかったかの答え
    //printf("%s\n%s\n%s",str_neo[0],str_neo[1],str_neo[2]);
    printf("平文の可能性が高いものを検索します。\n");
    for(int i=0;i<=m;i++){
        if(strlen(str_neo[i])==1){    //一字があるとき
            int x,y;
            if (65<=str_neo[i][0] && str_neo[i][0]<=90){    //大文字のとき何文字ずれか
                x='A'-str_neo[i][0];
                y='I'-str_neo[i][0];
            }
            else if(97<=str_neo[i][0] && str_neo[i][0]<=122){    //小文字のとき何文字ずれか
                x='a'-str_neo[i][0];
                y='i'-str_neo[i][0];
            }
            for(int j=0;j<=m;j++){    //ずらし
                for(int k=0;k<strlen(str_neo[j]);k++){
                    new_str_x[a]=str_neo[j][k]+x;
                    new_str_y[a]=str_neo[j][k]+y;
                    
                    if(65<=str_neo[j][k] && str_neo[j][k]<=90){    //その文字が大文字のとき
                        if(90<str_neo[j][k]+x ){    //Zを超えたとき（str_x）
                            new_str_x[a]=64+((str_neo[j][k]+x)-90);
                        }
                        else if(str_neo[j][k]+x<65){    //Aを超えたとき(str_x)
                            new_str_x[a]=91-(65-(str_neo[j][k]+x));
                        }
                        if(90<str_neo[j][k]+y){    //Zを超えたとき（str_y）
                            new_str_y[a]=64+((str_neo[j][k]+y)-90);
                        }
                        else if(str_neo[j][k]+y<65){    //Aを超えたとき(str_y)
                            new_str_y[a]=91-(65-(str_neo[j][k]+y));
                        }
                    }
                    else if(97<=str_neo[j][k] && str_neo[j][k]<=122){    //その文字が小文字のとき
                        if(122<str_neo[j][k]+x ){    //zを超えたとき（str_x）
                            new_str_x[a]=96+((str_neo[j][k]+x)-122);
                        }
                        else if(str_neo[j][k]+x<97){    //aを超えたとき(str_x)
                            new_str_x[a]=123-(97-(str_neo[j][k]+x));
                        }
                        if(122<str_neo[j][k]+y){    //zを超えたとき（str_y）
                            new_str_y[a]=96+((str_neo[j][k]+y)-122);
                        }
                        else if(str_neo[j][k]+y<97){    //aを超えたとき(str_y)
                            new_str_y[a]=123-(97-(str_neo[j][k]+y));
                        }
                    }
                    a++;
                }
                new_str_x[a]=' ';
                new_str_y[a]=' ';  
                a++;
            }
            printf("平文の候補は以下の二つです。\n");
            printf("(1)%s\n(2)%s\n",new_str_x,new_str_y);
            break;
        }
        else{
            nothing++;
        } 
    }

    if(nothing==m+1){
        printf("平文の候補は見つかりませんでした。\n");
    }
    else{
        printf("正しい平文は見つかりましたか？　Yes:0 No:1\n-≥");
        scanf("%d",&c);
        if(c==0){
            return ;
        }
    }
    printf("1~26文字ずらした全パターンを出力します。\n");
    for(int i=1;i<=26;i++){   //i:ずらす字数
        b=0;
        for(int j=0;j<=m;j++){    //ずらし [j][k]
            for(int k=0;k<strlen(str_neo[j]);k++){
                if(65<=str_neo[j][k] && str_neo[j][k]<=90){   //大文字のとき
                    if(65>str_neo[j][k]-i ){    //Aを超えたとき（str_x）
                        new_str[i][b]=91-(65-(str_neo[j][k]-i));
                    }
                    else{
                        new_str[i][b]=str_neo[j][k]-i;
                    }
                    b++;
                }
                else if(97<=str_neo[j][k] && str_neo[j][k]<=122){
                    if(97>str_neo[j][k]-i ){    //aを超えたとき（str_x）
                        new_str[i][b]=123-(97-(str_neo[j][k]-i));
                    }
                    else{
                        new_str[i][b]=str_neo[j][k]-i;
                    }  
                    b++;
                }
            }
            new_str[i][b]=' ';
            b++;
        }
        printf("%d:%s\n",i,new_str[i]);
    }
}
