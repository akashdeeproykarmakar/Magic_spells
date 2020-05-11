#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
    if (Fireball* ss = dynamic_cast<Fireball*>(spell)) {
        ss->revealFirepower();
        return;
    }
    if (Frostbite* ss = dynamic_cast<Frostbite*>(spell)) {
        ss->revealFrostpower();
        return;
    }
    if (Thunderstorm* ss = dynamic_cast<Thunderstorm*>(spell)) {
        ss->revealThunderpower();
        return;
    }
    if (Waterbolt* ss = dynamic_cast<Waterbolt*>(spell)) {
        ss->revealWaterpower();
        return;
    }

    static int dp[1111][1111];
    string a = spell->revealScrollName();
    string b = SpellJournal::journal;
    int n = a.size(), m = b.size();
    auto chmax = [](int &a, int b) {
        if (a < b) a = b;
    };
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) dp[i][j] = 0;
    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            if (a[i - 1] == b[j - 1]) {                
                chmax(dp[i][j], dp[i - 1][j - 1] + 1);
            } 
            chmax(dp[i][j], dp[i][j - 1]);                       
            chmax(dp[i][j], dp[i - 1][j]);                       
            chmax(dp[i][j], dp[i - 1][j - 1]);
        }
    }
    cout << dp[n][m] << endl;




}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
