#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> KSA(const vector<int>& K, int N) {
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        S[i] = i;
    }
    
    int j = 0;
    int key_length = K.size();
    
    for (int i = 0; i < N; ++i) {
        j = (j + S[i] + K[i % key_length]) % N;
       
        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    
    return S;
}

vector<int> PRGA(vector<int> S, int length, int N) {
    vector<int> keystream(length);
    int i = 0;
    int j = 0;
    
    for (int k = 0; k < length; ++k) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        
        int t = (S[i] + S[j]) % N;
        keystream[k] = S[t];
    }
    
    return keystream;
}

vector<int> XOR_Process(const vector<int>& data, const vector<int>& keystream) {
    vector<int> result(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ keystream[i];
    }
    return result;
}

int main() {
    int N = 10;
    vector<int> K = {2, 4, 1, 7};
    string plaintext_str = "cybersecurity";
    
    vector<int> plaintext_ascii;
    for (char c : plaintext_str) {
        plaintext_ascii.push_back(static_cast<int>(c));
    }
    
    
    vector<int> S = KSA(K, N);
    
    cout << "Mang S sau KSA: [";
    for (size_t i = 0; i < S.size(); ++i) {
        cout << S[i] << (i == S.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl << endl;
    
    vector<int> keystream = PRGA(S, plaintext_ascii.size(), N);
    vector<int> ciphertext_ascii = XOR_Process(plaintext_ascii, keystream);
    
    cout << "--- KET QUA MA HOA ---" << endl;
    cout << "Ban ro: " << plaintext_str << endl;
    
    cout << "Dong khoa: ";
    for (int k : keystream) cout << k << " ";
    cout << endl;
    
    cout << "Ban ma (ASCII): ";
    for (int c : ciphertext_ascii) cout << c << " ";
    cout << endl;
    
    cout << "Ban ma (Text): ";
    for (int c : ciphertext_ascii) cout << static_cast<char>(c);
    cout << endl;

    return 0;
}
