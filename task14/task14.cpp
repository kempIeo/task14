#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
const int ALPHABET_SIZE = 26;
using namespace std;

// 
struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};
// 
TrieNode* getNewNode(void)
{
    // Выделяем память под новый узел
    TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым указателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}
//
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}
//
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }
    node->isEndOfWord = true;
}
//
void insertfromfile(TrieNode* root, string filename)
{
    
    string word;
    ifstream in(filename);
    if (in.is_open())
    {
        while (!in.eof()) {
            getline(in, word);
            insert(root, word);
        }
      in.close();
    }
    else
    {
        cout << "no file with that name\n";
    }
    return;
}
//
bool search(struct TrieNode* root, string key)
{
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

//
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
    if (!root)
        return nullptr;
    if (depth == key.size()) {
        
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        
        if (isEmpty(root)) {
            delete (root);
            root = nullptr;
        }

        return root;
    }
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    return root;
}
//
bool moreareempty(TrieNode* root, int j)
{
    for (; j < ALPHABET_SIZE; j++)
    {
        if (root->children[j]) return false;
    }
    return true;
 }
//
void print(TrieNode* root, string& buf)
{
    if (root->isEndOfWord) cout <<buf<<endl;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        
        if (root->children[i])
        {
            buf.push_back(char(i + 'a'));
            if (isEmpty(root->children[i])) 
            {
                cout << buf << endl;
                if(!buf.empty())buf.pop_back();

               
            }
            else print(root->children[i], buf);
            if(moreareempty(root,i+1)&&!buf.empty()) buf.pop_back();
        }
   
    }
    
}
//
void findwords(TrieNode* root, string buf)
{
    TrieNode* temp = root;
    int i = 0;
    do {
        int index = buf[i++]-'a';
        if (!temp->children[index]) {
            cout << "Dictionary dont have this words\n";
            return;
        }
        else temp = temp->children[index];
    } while (i < buf.size());
    print(temp, buf);
}

int main()
{
    TrieNode* words=new TrieNode();
    insertfromfile(words, "dictionary.txt");
    string buf;
    char finish;
    do {
        cout << "Enter word\n";
        cin >> buf;
        cout << "Do you want to see words(y/n)\n";
        char a;
        cin >> a;
        switch (a)
        {
        case 'y':
        {
            char v;
            findwords(words, buf);
            do {
                cout << "finish (y/n)\n";
                cin >> v;
            } while (v != 'y');
            break;
        }
        case 'n':
        {
            break;
        }
        }
        cout << "close program (y/n)\n";
        cin >> finish;
       std::system("cls");
    } while (finish != 'y');

  
}

