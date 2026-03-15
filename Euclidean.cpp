#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int M = 1033;
const int DEGREE = 10;


int get_degree(unsigned int n) {
    if (n == 0) return -1;
    int deg = 0;
    while (n >>= 1) deg++;
    return deg;
}


void gf2_div(unsigned int a, unsigned int b, unsigned int &q, unsigned int &r) {
    q = 0;
    r = a;
    int deg_b = get_degree(b);
    int deg_r = get_degree(r);

    while (deg_r >= deg_b) {
        int shift = deg_r - deg_b;
        q |= (1 << shift);
        r ^= (b << shift); 
        deg_r = get_degree(r);
    }
}

unsigned int extended_gcd(unsigned int a, unsigned int m) {
    unsigned int r0 = m, r1 = a;
    unsigned int x0 = 0, x1 = 1;
    unsigned int q, r_next, x_next;

    cout << "Buoc tinh trung gian:\n";
    cout << "R\t\tQ\t\tX\n";
    cout << "------------------------------------------\n";

    while (r1 > 0) {
        gf2_div(r0, r1, q, r_next);
        
        unsigned int qx1 = 0;
        for (int i = 0; i <= 10; i++) {
            if ((q >> i) & 1) qx1 ^= (x1 << i);
        }
        
        x_next = x0 ^ qx1;

        r0 = r1;
        r1 = r_next;
        x0 = x1;
        x1 = x_next;

        cout << bitset<11>(r0) << "\t" << bitset<11>(q) << "\t" << bitset<11>(x0) << endl;
    }

    if (r0 == 1) return x0;
    return 0; 
}

int main() {
    unsigned int test_a = 523;
    unsigned int test_b = 1015;

    cout << "Tim nghich dao cua a = 523:\n";
    unsigned int inv_a = extended_gcd(test_a, M);
    cout << "=> a^-1 = " << inv_a << " (Nhi phan: " << bitset<10>(inv_a) << ")\n\n";

    cout << "Tim nghich dao cua b = 1015:\n";
    unsigned int inv_b = extended_gcd(test_b, M);
    cout << "=> b^-1 = " << inv_b << " (Nhi phan: " << bitset<10>(inv_b) << ")\n";

    return 0;
}
