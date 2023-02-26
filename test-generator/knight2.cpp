#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void MadTroll(int &HP, int&HPmax, int &level, int &levelO, int &name, int &event, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)  {       
            if ((level>levelO)||name==1||name==2) {
                level = level + 1;
                if (level > 10) level = 10;
            }
            //if (level == levelO);
            if ((level<levelO)&&name==3) {
                int baseDamage;
                if (event==1) baseDamage=2;
                if (event==2) baseDamage=3;
                if (event==3) baseDamage=9;
                if (event==4) baseDamage=15;
                if (event==5) baseDamage=19;
                int damage = baseDamage * levelO * 5;
                HP -= damage;
                if (HP<=0) {
                    if (phoenixdown == 0) {
                        rescue=0;
                    }
                        else {
                            phoenixdown--;
                            HP=HPmax;
                        
                    }
                }
            }
        }

void MushMario(int & HP, int & level, int & phoenixdown, int & HPmax) {                
                int s1=0, a=99;
                int n1 = ((level + phoenixdown)%5 + 1)*3;
                for (int k=0; k<n1; k++)  {
                    if (a>0) s1+=a;
                    a-=2;
                    }
                    //cout<<s1;
                HP = HP + (s1%100)+1;
                int flag=0;
                while (flag==0)  {
                    for (int l=2; l<HP; l++)  {
                        if (HP%l==0) {HP++; flag=0; break;}
                        flag=1;
                        }
                }
                if (HP > HPmax) HP=HPmax;
            }
void MushFibo(int &HP)  {
                if (HP>1)  {
                    int arr[1000], m=2;
                    arr[0]=1; arr[1]=1;
                    int k=1;
                    while (k<HP)  {
                        arr[m]=arr[m-1]+arr[m-2];
                        k=arr[m];
                        //cout<<k<<" ";
                        m++;
                        }
                    HP=arr[m-2];
                }
                else HP=1;
                }
void Shaman(int &HP, int &level, int &levelO, int &remedy, int &tiny, int &frog, int &name)  {            
            if (tiny>=0 || frog>=0) ;
            else {
            if ((level>levelO)||name==1||name==2) {
                level+=2;
                if (level>10) level=10;
            }
            if ((level<levelO)&&name==3) {
                if (remedy>0) {
                    remedy--;
                    }
                else {
                    if (HP<5) HP=1;
                    else HP=HP/5;
                    tiny=0;
                    }
                }
            }
            }
void Vajsh(int &HP, int &level, int &levelO, int &levelbefore, int &tiny, int &frog, int &maidenkiss, int &name)  {
            if (tiny>=0 || frog>=0) ;
            else {
            if ((level>levelO)||name==1||name==2) {
                level+=2;
                if (level>10) level=10;
            }
            if ((level<levelO)&&name==3)  {
                if (maidenkiss>0) maidenkiss--;
                else {
                    frog=0;
                    levelbefore=level;
                    level=1;
                    }
                }
            }
        }
void Bowser(int &level, int &name, int &HP, int &remedy, int &maidenkiss, int &phoenixdown, int &rescue)  {
    if (name==1||(name==2&&level>=8)||(name==3&&level==10)) level=10;
    else {rescue=0;
        }
    }
void Asclepius(string file_other1, int & remedy, int & maidenkiss, int & phoenixdown, int &HP, int &HPmax, int &level, int &levelbefore, int &tiny, int &frog, int &asclepius)  {
    ifstream fin(file_other1);
    int r1,c1,arr[100][100];
    fin >> r1;
    fin >> c1;
    for (int m=0; m<r1; m++)  {
        for (int n=0; n<c1; n++)  {
             fin >> arr[m][n];
             }
        }
    for (int m=0; m<r1; m++)  {
        int l=0;
        for (int n=0; n<c1; n++)  {
            if (l==3) break;
            if (arr[m][n]==16) {remedy++; l++;}
            if (arr[m][n]==17) {maidenkiss++; l++;}
            if (arr[m][n]==18) {phoenixdown++; l++;}
            }
        }
        asclepius=1;
        if (tiny>=0&&remedy>0)  {
            remedy--;
            tiny=-1;
            HP=HP*5;
            if (HP>HPmax) HP=HPmax;
            }
        if (frog>=0 && maidenkiss>0)  {
            maidenkiss--;
            frog=-1;
            level=levelbefore;
            }
        if (remedy>99) remedy=99;
        if (maidenkiss>99) maidenkiss=99;
        if (phoenixdown>99) phoenixdown=99;
    }

void MushGhost(string file_other0, int &HP, int &HPmax, int &level, int &event, int remedy, int maidenkiss, int &phoenixdown, int &rescue)  {
    ifstream mush(file_other0);
    int n2, array[100];
    mush>>n2;
    string line2;
    getline(mush, line2);     getline(mush, line2);
    stringstream ss(line2);
    int y=0;
    string a[100];
    while (ss.good())  {
        string temporary;
        getline(ss,temporary,',');
        a[y++]=temporary;
        }
        for (int f=0; f<n2; f++)  {
            stringstream(a[f]) >> array[f];
            }
    // for (int a=0; a<10; a++)  {
    //     mush >> array[a]; 
    //     //cout<<array[a]<<"...";
    //     }
    int count=1;
    int eventbefore=event;
    while (event>9)  {
        event=event/10;
        count++;
    }
    int mslength=count-2;
    int s=1;
    for (int m=1; m<=mslength; m++)  {
        s=s*10;
        }
    int ms=eventbefore%s;
    for (int i=1; i<=mslength; i++)  {
        int mst=(ms%s)/(s/10);
        //cout<<mst<<" ";
        if (mst==1)  {
            int max=array[n2-1], min=array[n2-1], maxi=n2-1, mini=n2-1;
            for (int c=n2-1; c>=0; c--)  {
                if (array[c]>max) {max=array[c]; maxi=c;}
                if (array[c]<min) {min=array[c]; mini=c;}
            }
            //cout<<maxi<<" "<<mini<<" ";
        HP=HP-(maxi + mini);
        }
        //cout<<n2<<" ";
        // for (int g=0; g<n2; g++) {
        //     cout<<array[g]<<", ";
        //     }
        if (mst==2)  {
                int peak=array[0], pindex=0, mtx, mti;
                for (int k=0; k<n2; k++)  {
                    //cout<<array[k];
                if (array[k]>peak) {peak=array[k]; pindex=k;}
                }
                //cout<<peak<<" "<<pindex;
            int stricklydecrease=1,mountain=1;
            for (int k=0; k<n2-1; k++)  {
                if (array[k]<=array[k+1]) {stricklydecrease=0; break;}
                }
            for (int p=0; p<pindex; p++)  {
                if (array[p]>=array[p+1]) {mountain=0; break;}
                }
            for (int q=pindex; q<n2-1; q++)  {
                if (array[q]<=array[q+1]) {mountain=0; break;}
                }
            if (mountain==1 || stricklydecrease==1) {mtx=peak; mti=pindex;}
            else {mtx=-2; mti=-3;}
            // cout<<mountain<<" "<<stricklydecrease<<" ";
            // cout<<mtx<<" "<<mti<<" ";
            HP=HP-(mtx+mti);
            }
        int arrayafter[100];
        for (int k=0; k<n2; k++)  {
                if (array[k]<0) arrayafter[k]=(-array[k]*17+9)%257;
                else {arrayafter[k]=(array[k]*17+9)%257;}
                //cout<<arrayafter[k]<<", ";
                }
        if (mst==3)  {
                int max3=arrayafter[0], min3=arrayafter[0], maxi2=0, mini2=0;
            for (int k=0; k<n2; k++)  {
                if (max3<arrayafter[k]) {max3=arrayafter[k]; maxi2=k;}
                if (min3>arrayafter[k]) {min3=arrayafter[k]; mini2=k;}
                }
                //cout<<maxi2<<" "<<mini2<<" ";
            HP=HP-(maxi2+mini2);
            }
            if (mst==4)  {
                int max=arrayafter[0], max2_3x, max2_3i;
                for (int k=0; k<3; k++)  {
                    if (arrayafter[k]>max) max=arrayafter[k];
                }
                if (n2==1) {max2_3x=-5; max2_3i=-7;}
                else {
                    for (int g=0; g<3; g++)  {
                        if (arrayafter[g]<max) {max2_3x=arrayafter[g]; max2_3i=g; break;}
                        }
                    if (max==arrayafter[0]) {max2_3x=-5; max2_3i=-7;}
                    for (int l=0; l<3; l++)  {
                        if (arrayafter[l]>max2_3x && arrayafter[l]<max) {max2_3x=arrayafter[l]; max2_3i=l;}
                    }
                }
                //cout<<max2_3x<<" "<<max2_3i<<" ";
                if (max2_3x==max) {max2_3x=-5; max2_3i=-7;}
                if (max2_3i>2) {max2_3x=-5; max2_3i=-7;}
                HP=HP-(max2_3x+max2_3i);    
        }
                        if (HP<=0) {
            if (phoenixdown>0) {
                phoenixdown--;
                HP=HPmax;
                }
            else {
                rescue=0;
                //display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                return;
                }
            }
            if (HP>HPmax) HP=HPmax;
        ms=ms%(s/10);
        s=s/10;
        //cout<<HP<<" ";
        }
    }



void Merlin(string file_other2, int &HP, int &HPmax, int &merlinflag)  {
    int n9, k=0;
    string str;
    ifstream merlin(file_other2);
    merlin >> n9;
    while (merlin>>str)  {
        int hasmerlin=0;
        //cout<<str<<" ";
        for (int g=0; g<str.length(); g++)  {
            if ((str[g]=='M'||str[g]=='m') && str[g+1]=='e' && str[g+2]=='r' && str[g+3]=='l' && str[g+4]=='i' && str[g+5]=='n')  {
                HP=HP+3;
                hasmerlin=1;
                break;
                }
            }
            //cout<<hasmerlin<<" ";
        if (hasmerlin==0){
        int m=0, e=0, r=0, l=0, i=0, n=0;
        for (int t=0; t<str.length(); t++)  {
            if (str[t]=='m' || str[t]=='M') m=1;
            if (str[t]=='e' || str[t]=='E') e=1;
            if (str[t]=='r' || str[t]=='R') r=1;
            if (str[t]=='l' || str[t]=='L') l=1;
            if (str[t]=='i' || str[t]=='I') i=1;
            if (str[t]=='n' || str[t]=='N') n=1;
            } 
            //cout<<m<<e<<r<<l<<i<<n<<" ";
        if (m==1 && e==1 && r==1 && l==1 && i==1 && n==1) HP=HP+2;
        }
        if (HP>HPmax) HP=HPmax;
        k++;
        //cout<<HP<<" ";
    }
    merlinflag=1;
}

void Setup(string file_input, int &numberofevent)  {
    ifstream fileInput;
    fileInput.open(file_input);
    int k;
    while (fileInput >> k) numberofevent++;
    numberofevent-=5;
    }

void Readfile(string file_input, string &str3)  {
    ifstream fileInput;
    fileInput.open(file_input);
    string str1,str2;
    getline(fileInput, str1);
    getline(fileInput, str2);
    getline(fileInput, str3);
    fileInput.close();
    }

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    
    freopen("test.ans", "w", stdout);

    int numberofevent=0;
    string file_other[5];
    string str3;
    Setup(file_input, numberofevent);
    Readfile(file_input, str3);
    int d=0;
        string tmp = "";
        for (int h=0; h<str3.length(); h++)  
        {
            if (str3[h] == ',')
            {
            file_other[d++] = tmp;
            tmp="";

            }
            else tmp += str3[h];
        }
        file_other[d] = tmp;   
        ifstream tc1;
    tc1.open(file_input);
    tc1 >> HP;
    tc1 >> level;
    tc1 >> remedy;
    tc1 >> maidenkiss;
    tc1 >> phoenixdown;
    int event,HPmax=HP,name=0,asclepius=0,merlinflag=0;
    int levelO, b, i=1, tiny=-1, frog=-1, levelbefore;
    if (HP==999) name=1;
    else {
        for (int k=2; k<HP; k++)  {
            if (HP%k==0) {
                name=3;
                break;
            }
        }
        if (name==0) name=2;
        if (HP==1) name=3;
    }
    while (tc1 >> event) {
        if (event == 0) {
            rescue = 1;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            return;
        }
            b = i % 10;
            if (i > 6) {
                if (b > 5) levelO = b;
                else levelO = 5;
            }
            else levelO = b;

        
        if (event==1) MadTroll(HP,HPmax,level,levelO,name,event,remedy,maidenkiss,phoenixdown,rescue);
        if (event==2) MadTroll(HP,HPmax,level,levelO,name,event,remedy,maidenkiss,phoenixdown,rescue);
        if (event==3) MadTroll(HP,HPmax,level,levelO,name,event,remedy,maidenkiss,phoenixdown,rescue);
        if (event==4) MadTroll(HP,HPmax,level,levelO,name,event,remedy,maidenkiss,phoenixdown,rescue);
        if (event==5) MadTroll(HP,HPmax,level,levelO,name,event,remedy,maidenkiss,phoenixdown,rescue);
        if (event==6) Shaman(HP, level, levelO, remedy, tiny, frog, name);
        if (event==7) Vajsh(HP,level,levelO,levelbefore,tiny,frog,maidenkiss,name);
        if (event==11) MushMario(HP, level, phoenixdown, HPmax);
        if (event==12) MushFibo(HP);
        if (event==15)  {
                if (tiny>=0)  {
                    tiny=-1;
                    HP=HP*5;
                    if (HP>HPmax) HP=HPmax;
                    }
                else {
                remedy++;
                if (remedy>99) remedy=99;
                }
                }
        if (event==16)  {
                if (frog>=0) {
                    level=levelbefore;
                    frog=-1;
                    }
                else {
                maidenkiss++;
                if (maidenkiss>99) maidenkiss=99;
                }
            }
        if (event==17)  {
                phoenixdown++;
                if (phoenixdown>99) phoenixdown=99;
                }
        if (event==99)  {
            Bowser(level,name,HP,remedy,maidenkiss,phoenixdown,rescue);
            if (rescue==0) {
                HP=0;
                display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
                return;
                }
            }
        if (event==19)  {
            if (asclepius==0) Asclepius(file_other[1], remedy, maidenkiss, phoenixdown,HP, HPmax, level, levelbefore, tiny, frog, asclepius);
            }
        if (event==18)  {
            if (merlinflag==1);
            else {
            Merlin(file_other[2],HP,HPmax,merlinflag);}
        }
        if (event>100)  {
            MushGhost(file_other[0], HP, HPmax,level, event,remedy,maidenkiss, phoenixdown, rescue);
            }
        

        if (frog>=0) {
            frog++;
            if (HP<=0 && phoenixdown>=1)  {
                phoenixdown--;
                level=levelbefore;
                frog=-1;
                }
            }

        if (tiny>=0) {
            tiny++;
            if (HP<=0 && phoenixdown>=1) {
                phoenixdown--;
                HP=HPmax;
                tiny=-1;
                }
        }
    //cout<<numberofevent<<" ";


        if (frog==4) {
            frog=-1;
            level=levelbefore;
        }
        if (tiny==4) {
            tiny=-1;
            HP*=5;
            if (HP>HPmax) HP=HPmax;
            }
//cout<<tiny<<"..."<<frog<<"...";
            if (HP > 0 && i<numberofevent) rescue = -1;
    if (HP<=0) rescue=0;
    if (HP>0 && i==numberofevent) rescue=1;
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        if (rescue == 0 || rescue==1) return;
            i++;
    }
}