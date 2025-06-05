#include<bits/stdc++.h>

using namespace std;

class Labirint {
protected:
    string Nume, tip, efecteSpeciale;
    int putereBaza, coeficientPutere, coeficientViata;
public:

    virtual string getTip() {
        return tip;
    }

    virtual string getNume() {
        return Nume;
    }

    Labirint() {
        putereBaza = 0;
        coeficientPutere = 0;
        coeficientViata = 0;
        tip = "";
        efecteSpeciale = " ";
    }

    Labirint(int pb, int cp, int cv, string tp) {
        putereBaza = pb;
        coeficientViata = cv;
        coeficientPutere = cp;
        tip = move(tp);
    }

    virtual int calculPutere(int putere, int viata);
};

int Labirint::calculPutere(int putere, int viata) {
    return 0;
}

class Monstru {
    string nume, specie, inv, ap, sup;
    vector<Labirint *> ListaAbilitati;
    int putereAtac{}, puncteViata{}, i{}, j{};
public:


    Monstru() = default;

    string getSpecie() {
        return specie;
    }

    Monstru(int ix, int jx, string n, string s, int pa, int pv, string inv, string apa, string sup)
            : inv(move(inv)), ap(move(apa)), sup(move(sup)), nume(move(n)), specie(move(s)), putereAtac(pa),
              puncteViata(pv), i(ix), j(jx) {}

    void adaugaAbilitate(Labirint *a) {
        ListaAbilitati.push_back(a);
    }

    int getAtac() const {
        return putereAtac;
    }

    int getHp() const {
        return puncteViata;
    }

    Labirint *Abilitate(const string &tip, const string &comportament) {
        string name;
        if (tip == "SUPORT") {
            if (comportament == "NO_SUPPORT") {
                return new Labirint();
            }
            if (comportament == "SHAMAN") {
                int maxim = 0;
                for (auto &abilitate: ListaAbilitati) {
                    if (abilitate->getTip() == "BUFF")
                        if (maxim < abilitate->calculPutere(putereAtac, puncteViata)) {
                            maxim = abilitate->calculPutere(putereAtac, puncteViata);
                            name = abilitate->getNume();
                        }
                }
                for (auto &ab: ListaAbilitati) {
                    if (maxim == ab->calculPutere(putereAtac, puncteViata) && name == ab->getNume())
                        return ab;
                }
            }
            if (comportament == "CLERIC") {
                int maxim = 0;
                for (auto &ab: ListaAbilitati) {
                    if (ab->getTip() == "HEAL")
                        if (maxim < ab->calculPutere(putereAtac, puncteViata)) {
                            maxim = ab->calculPutere(putereAtac, puncteViata);
                            name = ab->getNume();
                        }
                }
                for (auto &ab: ListaAbilitati) {
                    if (maxim == ab->calculPutere(putereAtac, puncteViata) && name == ab->getNume())
                        return ab;
                }
            }
        }
        if (tip == "APARATOR") {
            if (comportament == "VIOLENT") {
                int maxim = 0;
                for (auto &ab: ListaAbilitati) {
                    if (ab->getTip() == "COMBAT")
                        if (maxim < ab->calculPutere(putereAtac, puncteViata)) {
                            maxim = ab->calculPutere(putereAtac, puncteViata);
                            name = ab->getNume();
                        }
                }
                for (auto &ab: ListaAbilitati) {
                    if (maxim == ab->calculPutere(putereAtac, puncteViata) && name == ab->getNume())
                        return ab;
                }
            }
        }
        if (tip == "INVADATOR") {
            if (comportament == "VIOLENT") {
                int maxim = 0;
                for (auto &ab: ListaAbilitati) {
                    if (ab->getTip() == "COMBAT")
                        if (maxim < ab->calculPutere(putereAtac, puncteViata)) {
                            maxim = ab->calculPutere(putereAtac, puncteViata);
                            name = ab->getNume();
                        }
                }
                for (auto &ab: ListaAbilitati) {
                    if (maxim == ab->calculPutere(putereAtac, puncteViata) && name == ab->getNume())
                        return ab;
                }
            }
        }

        return new Labirint();
    }

    void Misca(char a, int N, int M, char lab[100][100]) {
        if (puncteViata >= 1) {
            if (a == 'N' && i > 1 && lab[i - 1][j] != '#') i--;
            if (a == 'S' && i < N && lab[i + 1][j] != '#') i++;
            if (a == 'E' && j < M && lab[i][j + 1] != '#') j++;
            if (a == 'V' && j > 1 && lab[i][j - 1] != '#')j--;
        }
    }

    void flee(int M, int N, char labirint[100][100]) {
        if (i > 1 && labirint[i - 1][j] != '#') i--;
        else if (j < M && labirint[i][j + 1] != '#') j++;
        else if (i < N && labirint[i + 1][j] != '#') i++;
        else if (j > 1 && labirint[i][j - 1] != '#') j--;

    }


    bool aceeasiCamera(const Monstru &m) const {
        bool ok = (i == m.i && j == m.j);
        return ok;
    }

    void combat(Monstru &Protector, char labirint[100][100], int N, int M) {

        if (this->getSpecie() != Protector.getSpecie()) {
            while (this->getHp() > 0 && Protector.getHp() > 0) {
                int in, an;
                in = this->Abilitate("INVADATOR", inv)->calculPutere(getAtac(), getHp());
                an = Protector.Abilitate("APARATOR", Protector.ap)->calculPutere(Protector.getAtac(),
                                                                                 Protector.getHp());
                Protector.puncteViata -= in;
                puncteViata -= an;
            }
        } else {
            int in, an;
            in = Abilitate("SUPORT", sup)->calculPutere(getAtac(), getHp());
            an = Protector.Abilitate("SUPORT", Protector.sup)->calculPutere(Protector.getAtac(), Protector.getHp());
            flee(M, N, labirint);
            if (Abilitate("SUPORT", sup)->getTip() == "BUFF") {
                Protector.putereAtac += in;
            } else if (Abilitate("SUPORT", sup)->getTip() == "HEAL") {
                Protector.puncteViata += in;
            }
            if (Protector.Abilitate("SUPORT", Protector.sup)->getTip() == "BUFF") {
                putereAtac += an;
            } else if (Protector.Abilitate("SUPORT", Protector.sup)->getTip() == "HEAL") {
                puncteViata += an;
            }
        }
    }

    void afiseaza() const {
        cout << nume << " " << specie << " " << putereAtac << " " << puncteViata << " " << i << " " << j << endl;
    }

    void citeste() {
        cin >> nume >> specie >> putereAtac >> puncteViata >> i >> j >> inv >> ap >> sup;
    }
};

class Combat : public Labirint {
public:
    Combat() : Labirint() {}

    Combat(int pb, int cp, int cv, string name) : Labirint(pb, cp, cv, "COMBAT") {
        Nume = move(name);
    }

    string getNume() override {
        return Nume;
    }

    string getTip() override {
        return tip;
    }

    int calculPutere(int Power, int Health) override {
        return putereBaza + coeficientPutere * Power / 100 + coeficientViata * Health / 100;
    }
};

class Heal : public Labirint {
public:
    Heal() : Labirint() {}

    Heal(int pb, int cp, int cv, string Name) : Labirint(pb, cp, cv, "HEAL") {
        Nume = move(Name);
    }

    string getNume() override {
        return Nume;
    }

    string getTip() override {
        return tip;
    }

    int calculPutere(int Power, int Health) override {
        return putereBaza + coeficientPutere * Power / 100 + coeficientViata * Health / 100;
    }
};

class Buff : public Labirint {
public:
    Buff() : Labirint() {}

    Buff(int pb, int cp, int cv, string n) : Labirint(pb, cp, cv, "BUFF") {
        Nume = move(n);
    }

    string getNume() override {
        return Nume;
    }

    string getTip() override {
        return tip;
    }

    int calculPutere(int Power, int Health) override {
        return putereBaza + coeficientPutere * Power / 100 + coeficientViata * Health / 100;
    }
};

class LabirintFactory {
private:
    LabirintFactory() {}

public:
    LabirintFactory(const LabirintFactory &) = delete;

    LabirintFactory &operator=(const LabirintFactory &) = delete;

    static LabirintFactory &getInstance() {
        static LabirintFactory instance;
        return instance;
    }

    Labirint *createLabirint(const string &tip, int pb, int cp, int cv, const string &name) {
        if (tip == "COMBAT") {
            return new Combat(pb, cp, cv, name);
        } else if (tip == "HEAL") {
            return new Heal(pb, cp, cv, name);
        } else if (tip == "BUFF") {
            return new Buff(pb, cp, cv, name);
        } else {
            return new Labirint();
        }
    }
};

int main() {
    int N, M, K, D;
    char poz;
    char labirint[100][100];
    cin >> N >> M >> K >> D;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> labirint[i][j];
        }
    }

    vector<Monstru> Monstrii;
    for (int i = 0; i < K; i++) {
        Monstru monstru;
        string nume;
        string specie, tip;
        int atac = 0, baza;
        int viata = 0;
        int x, y;
        int A;

        string c1, c2, c3;
        cin >> nume >> specie >> atac >> viata >> x >> y >> A >> c1 >> c2 >> c3;

        monstru = Monstru(x, y, nume, specie, atac, viata, c1, c2, c3);
        for (int j = 0; j < A; j++) {
            cin >> nume >> baza >> atac >> viata >> tip;
            monstru.adaugaAbilitate(LabirintFactory::getInstance().createLabirint(tip, baza, atac, viata, nume));
        }
        Monstrii.push_back(monstru);
    }

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < K; j++) {
            cin >> poz;
            Monstrii[j].Misca(poz, N, M, labirint);
            for (int k = 0; k < Monstrii.size(); k++) {
                if (Monstrii[j].aceeasiCamera(Monstrii[k]) && k != j && Monstrii[j].getHp() > 0 &&
                    Monstrii[k].getHp() > 0) {
                    Monstrii[j].combat(Monstrii[k], labirint, N, M);
                }
            }
        }
    }

    for (auto &Mn: Monstrii) {
        if (Mn.getHp() > 0)
            Mn.afiseaza();
    }

    return 0;
}

