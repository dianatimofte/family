#include <iostream>
#include <string>
using namespace std;

struct copil {
    string nume;
    string nume_tata;
    string nume_mama;

};

struct vectPersoane {
    copil copii[100];
    int lungime;

};

struct vectArbore {
    string valori[10];
    int marime;

};
void adaugareStructura (string numeCopil, string numeTata, string numeMama, vectPersoane &v)
{
    v.copii[v.lungime].nume=numeCopil;
    v.copii[v.lungime].nume_tata=numeTata;
    v.copii[v.lungime].nume_mama=numeMama;
    v.lungime++;

}

string verificareParinti (string nume1, string nume2, vectPersoane v)
{
    int i;
    string grad=" ";
    for(i=0;i<v.lungime;i++)
    {
        if ((v.copii[i].nume==nume1) && ((v.copii[i].nume_tata==nume2)||(v.copii[i].nume_mama==nume2)))
        {
            grad="copil";
            return grad;
        }
        else if ((v.copii[i].nume==nume2) && ((v.copii[i].nume_tata==nume1)||(v.copii[i].nume_mama==nume1)))
        {
            grad="parinte";
            return grad;
        }
    }
    return grad;
}
string cautareCopilulParinteluiDat (string parinte, vectPersoane v)
{
    int i;
    for(i=0;i<v.lungime;i++)
    {
        if (v.copii[i].nume_tata==parinte) return v.copii[i].nume;
        else if (v.copii[i].nume_mama==parinte) return v.copii[i].nume;
    }
    return "";
}

string cautareDescendent (string nume, vectPersoane v)
{
    string descendent;
    while (nume!= "")
    {
        descendent=nume;
        nume=cautareCopilulParinteluiDat(nume, v);

    }
    return descendent;
}

int introducereParinti (string descen, int i, vectPersoane v, vectArbore &vA)
{
    int j;
    for(j=0;j<v.lungime;j++)
    {
        if(v.copii[j].nume==descen) {
                vA.valori[2*i]=v.copii[j].nume_mama;
                vA.valori[2*i+1]=v.copii[j].nume_tata;
                vA.marime=vA.marime+2;
                return 1;
        }
    }
    return 0;

}


vectArbore creareVectorArbore (string descen, vectPersoane v)
{
    int i=1;
    vectArbore vectorArbore;
    vectorArbore.marime=1;
    vectorArbore.valori[i]=descen;

    while ( introducereParinti(vectorArbore.valori[i], i, v, vectorArbore))
    {
        i++;
    }
    return vectorArbore;
}


int indicePersoanaCautata (string nume, vectArbore vA)
{
    for(int i=1;i<=vA.marime;i++)
        if(vA.valori[i]==nume) return i;
    return 0;
}

int indiciPersoanaInArbori(vectArbore A1, vectArbore A2, int &i, int &j)
{
    for(i=1;i<=A1.marime;i++)
        for(j=1;j<=A2.marime;j++)
        {
            if (A1.valori[i]==A2.valori[j])
                return 1;
        }
    return 0;
}

vectArbore Arbore(string nume, vectPersoane v)
{
    vectArbore vA;
    nume=cautareDescendent(nume,v);
    vA=creareVectorArbore(nume, v);
    return vA;

}

string gradulDeRudenie (string nume1, string nume2, vectPersoane v)
{
    string grad;
    string grad1;
    grad1=verificareParinti(nume1,nume2,v);
    if(grad1!=" ") return grad1;

    int i1, i2, j1, j2, da;
    vectArbore vA1, vA2;

    vA1=Arbore(nume1,v);
    vA2=Arbore(nume2,v);

    if (!(da=indiciPersoanaInArbori(vA1, vA2, i1, i2))) {grad="nu sunt rude"; return grad;}

    j1=indicePersoanaCautata(nume1, vA1);
    j2=indicePersoanaCautata(nume2, vA2);

    string a[10][10][10][10];

    cout<<i1<<"  " <<i2<< "  "<<j1<<" "<<j2;

    a[2][2][1][1]="frati"; a[2][4][1][2]="frati"; a[4][2][2][1]="frati"; a[4][4][2][2]="sora"; a[6][6][3][3]="frate";
    a[4][6][2][3]="sora"; a[6][4][3][2]="frate";

    a[1][1][2][3]="sotie"; a[1][1][3][2]="sot"; a[2][2][4][5]="sotie"; a[2][2][5][4]="sot"; a[1][1][4][5]="sotie";
    a[1][1][5][4]="sot"; a[3][3][6][7]="sotie"; a[3][3][7][6]="sot"; a[1][1][6][7]="sotie"; a[1][1][7][6]="sot";

    a[2][4][1][3]="cumnati"; a[6][2][2][1]="cumnati"; a[2][6][1][2]="cumnati"; a[4][2][3][1]="cumnati";

    a[2][4][1][1]="matusa/unchi"; a[4][4][2][1]="matusa"; a[6][6][3][1]="unchi";

    a[4][2][1][1]="nepot/nepoata"; a[4][4][1][2]="nepot/nepoata"; a[6][6][1][3]="nepot/nepoata";

    a[1][1][4][1]="bunica"; a[1][1][6][1]="bunica"; a[1][1][5][1]="bunic"; a[1][1][7][1]="bunic";

    a[1][1][1][4]="nepot"; a[1][1][1][6]="nepot"; a[1][1][1][5]="nepot"; a[1][1][1][7]="nepot";

    a[4][4][1][1]="veri"; a[6][6][1][1]="veri"; a[4][6][1][1]="veri"; a[6][4][1][1]="veri";



    return a[i1][i2][j1][j2];

}

int main()
{
    int i=0;
    int n;
    string copil, tata, mama;
    string persoana1, persoana2;
    string grad;

    vectPersoane vectorulDeStructuri;
    vectorulDeStructuri.lungime=0;
    cout << "Veti introduce inregistrari de forma copil, mama, tata:" << endl;
    cout<< "Cate structuri doriti sa adaugati? " << endl;
    cin>>n;
    while(i<n) {
        cout<<"Numele copilului: "; cin>>copil;
        cout<<"Numele mamei: "; cin>>mama;
        cout<<"Numele tatalui: "; cin>>tata;
        cout<<endl;
        adaugareStructura(copil, tata, mama, vectorulDeStructuri);
        i++;
    }


    cout<<"Pentru a gasi gradul de rudenie dintre doua persoane, introduceti numele primei persoane: ";
    cin>>persoana1;
    cout<<"si numele celei de-a doua persoane: ";
    cin>>persoana2;
    cout<<endl;

    grad=gradulDeRudenie(persoana1, persoana2, vectorulDeStructuri);
    cout<<grad;

    return 0;
}
