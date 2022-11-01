#include <iostream>
#include <cstring>

using namespace std;

/* Lucrarea prezinta o mini baza de date pentru un lant de cinematografe, unde pot fi adaugate sau sterse filme pentru a rula in acestea. */

class Cinema{

    //caracteristicile by default private ale obiectelor de tip Cinema sunt:
    int hopen;
    int id_c;
    char* locatie;
    char* zi;
public:
    Cinema(){} //constructor fara parametri

    //constructor pentru definirea caracteristicilor
    Cinema(char* locatie, char* zi, int hopen, int id_c)
    {   size_t len = strlen(locatie);
        this->locatie=new char[len+1];
        strcpy(this->locatie,locatie);
        size_t len1 = strlen(zi);
        this->zi=new char[len1+1];
        strcpy(this->zi, zi);
        this->hopen=hopen;
        this->id_c=id_c;

    }

    //setters si getters
    void sethopen(const int hopen)
    {
        this->hopen=hopen;
    }

    void setidc(const int id_c)
    {
        this->id_c=id_c;
    }

    int gethopen() const {return hopen;}
    int getidc() const {return id_c;}

    void setloc(char* locatie)
    {
        this->locatie = new char[strlen(locatie)+1];
        strcpy(this->locatie,locatie);
    }
    void setzi(char* zi)
    {
        this->zi = new char[strlen(zi)+1];
        strcpy(this->zi,zi);
    }

    char *getloc() const {return locatie;}
    char *getzi() const {return zi;}
    //destructor pentru eliberarea memoriei
    ~Cinema() {
        delete[] locatie;
        delete[] zi;
    }

    //constructor de copiere
    Cinema(const Cinema &c) {
        size_t len = strlen(c.locatie);
        locatie = new char[len + 1];
        strcpy(locatie, c.locatie);
        size_t len1 = strlen(c.zi);
        zi = new char[len1 + 1];
        strcpy(zi, c.zi);
        id_c=c.id_c;
        hopen = c.hopen;
    }

    //rescrierea operatorului =
    Cinema& operator=(const Cinema &rhs) {

        if (this != &rhs) // in op= sau in setName ar trebui sa existe acest check
        {
            setloc(rhs.locatie);
            setzi(rhs.zi);
        }
        this->hopen = rhs.hopen;
        this->id_c = rhs.id_c;
        return *this;
    }
    //supraincarcarea lui <<
    friend ostream& operator<<(ostream &os, Cinema &c) {

        if (!c.locatie) {
            os << "Not initialized\n";
            return os;
        }
        if (!c.zi) {
            os << "Not initialized\n";
            return os;
        }
        if (!c.id_c) {
            os << "Not initialized\n";
            return os;
        }
        os << "Cinematograful "<<c.id_c<<" de la adresa " << c.locatie << " este deschis " << c.zi << " de la ora "<<c.hopen <<endl;
        return os;
    }

};

class Film : public Cinema{
    char* titlu;
    int hplay;
public:
    Film(){}
    Film(const char* titlu, int hplay )
    {   size_t len = strlen(titlu);
        this->titlu=new char[len+1];
        strcpy(this->titlu,titlu);
        this->hplay=hplay;
    }
    void sethplay(const int hplay)
    {
        this->hplay=hplay;
    }

    int gethplay() const {return hplay;}

    void setTitlu(char* titlu)
    {
        this->titlu = new char[strlen(titlu)+1];
        strcpy(this->titlu,titlu);
    }

    char *gettitlu() const {return titlu;}
    ~Film(){delete[] titlu;}  //destructor pt eliberarea memoriei

    Film(const Film &film) {                 //constructor de copiere
        size_t len = strlen(film.titlu);
        titlu = new char[len + 1];
        strcpy(titlu, film.titlu);

        hplay = film.hplay;
    }

    Film& operator=(const Film &rhs) {

        if (this != &rhs)
            setTitlu(rhs.titlu);
        this->hplay = rhs.hplay;

        return *this;
    }

    Film& operator+=(const Film &rhs){
        this->hplay = this->hplay + rhs.hplay;
        return *this;
    }
    ///friend void deletefilm(Film (&f)[10], char elem[40],int index);

    //supraincarcarea operatorilor << si >>
    friend istream& operator>>(istream &is, Film &f) {

        char buf[100];
        is >> buf;
        f.setTitlu(buf);
        is >> f.hplay;
        return is;
    }

    friend ostream& operator<<(ostream &os, Film &f) {

        if (!f.titlu) {
            os << "Not initialized\n";
            return os;
        }
        os << "Filmul: '" << f.titlu << "'va rula la ora: " << f.hplay <<endl;
        return os;
    }


};

//Am creat o functie friend prin care sa se faca stergerea, doar ca am avut probleme la ea si am
//preferat sa las instructiunile in main pentru a putea executa stergerea.

/*
void deletefilm(Film (&f)[10], char elem[40]){
    int found=0;
    cout<<"Introduceti numele filmului pe care doriti sa il stergeti:"<<endl;

    for(int i=0; i<strlen(elem); i++)
    {
        if(strcmp(elem,f[i].gettitlu())==0)
        {
            for(int j=i; j<(strlen(elem)-1); j++)
                f[j] = f[j+1];
            found++;
            i--;

        }
    }
    if(found==0)
        cout<<"Filmul cautat nu se afla in lista noastra!"<<endl;
    else
        cout<<"Filmul a fost sters cu succes!"<<endl;

}

*/

int main(){
    Cinema c1("Calea Vacaresti 391","toata saptamana",10, 1); //se apeleaza constructorul; sunt create si initializate 3 obiecte de tipul Cinema
    Cinema c2("Bd. Timișoara 26","luni, joi",9, 2);
    Cinema c3("Str. Liviu Rebreanu 4","marti, joi, vineri",11, 3);
    //Cinema c4=c3;   ->pentru a demonstra functionalitatea constructorului de copiere
    //cout<<c4;
    Film f[10];
    f[0].setTitlu("Avatar");
    f[0].sethplay(16);
    f[0].setidc(2);
    //cout<<f[0];     ->pentru a demonstra functionalitatea operatorului supraincarcat
    int x, index=1;
    while(true)
    {
        //Meniul interactiv:
        cout << endl << "Apasati 0 pentru a parasi meniul!"<<endl;
        cout << "Apatati 1 pentru adaugare!"<<endl;
        cout << "Apasati 2 pentru afisarea listei de filme!"<<endl;
        cout << "Apasati 3 pentru a sterge unul dintre filmele din lista!"<<endl;
        cout << "Apasati 4 pentru a consulta lista de cinematografe deschise in Bucuresti!"<<endl;


        cin >> x;
        switch (x) {
            case 0:
                exit(0);
            case 1: {
                int ora;
                int id;
                char titlu[40];
                cout << "Introduceti titlul filmului:";
                cin >> titlu;    //problema la sirurile cu spatiu, get si getline imi dadeau erori ciudate
                cout << "Introduceti ora la care va rula filmul:";
                cin >> ora;
                if(ora<1 || ora>24) {
                    cout<<"Introduceti o ora valida!";
                    cin>>ora;
                }
                cout << "Introduceti cinematograful la care va rula filmul (1, 2, 3):";
                cin >> id;
                if(id<1 || id>3) {
                    cout << "Locatia nu exista! Alegeti locatia 1, 2 sau 3!" << endl;
                    cin >> id;
                }
                f[index].sethplay(ora);
                f[index].setTitlu(titlu);
                f[index].setidc(id);

                index++;
            }
                break;


            case 2: {
                if (index == 0) {
                    cout << "Nu exista niciun film in lista noastra!" << endl;
                    break;
                }
                for (int i = 0; i < index; i++)
                    cout << "Filmul '" << f[i].gettitlu() << "' ruleaza la ora " << f[i].gethplay() << " la cinematograful "<< f[i].getidc() <<endl;
            }
                break;

            case 3: {

                char elem[40];
                int found = 0;
                cout << "Introduceti numele filmului pe care doriti sa il stergeti:" << endl;
                cin >> elem;

                ///deletefilm(f,elem);
                ///index--;
                for (int i = 0; i < index; i++) {
                    if (strcmp(f[i].gettitlu(), elem) == 0) {
                        for (int j = i; j < (index - 1); j++)
                            f[j] = f[j + 1]; //se foloseste operatorul supraincarcat =
                        found++;
                        i--;
                        index--;

                    }
                }
                if (found == 0)
                    cout << "Filmul cautat nu se afla in lista noastra!" << endl;
                else
                    cout << "Filmul a fost sters cu succes!" << endl;
            }
                break;

            case 4: {
                cout << c1;
                cout << c2;
                cout << c3;
            }
                break;




        }
    }
return 0;
}
