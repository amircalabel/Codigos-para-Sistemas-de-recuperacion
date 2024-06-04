#include <bits/stdc++.h>

using namespace std;

vector<vector<string>>document_coletion;
vector<vector<bool>>location_file;
vector<string>main_w;
vector<string>not_get_w{"a", "al","con","de","del","el","en","es","están","la","los","las",
			"su","un", "una", "unos", "unas","tiene","va","y","El","La","$"};

//Arbol de expresion logica
class node {
public:
    char value;
    node* left;
    node* right;
    node* next = NULL;
    node(char c)
    {
        this->value = c;
        left = NULL;
        right = NULL;
    }
    node()
    {
        left = NULL;
        right = NULL;
    }
    friend class Stack;
    friend class expression_tree;
};

class Stack {
    node* head = NULL;
 
public:
    void push(node*);
    node* pop();
    friend class expression_tree;
};

class expression_tree {
public:
    void inorder(node* x)
    {
        if (x == NULL)
            return;
        else {
            inorder(x->left);
            cout << x->value << "  ";
            inorder(x->right);
        }
    }
  vector<bool> decoding_req(vector<bool> index_f, vector<bool> index_s,char op)
  {
    vector<bool> pos_files;
    if(op == '&')
      {
	for(int i = 0; i <= index_f.size(); i++)
	  {
	    if(index_f[i] == true && index_s[i] == true)
	      pos_files.push_back(true);
	    else
	      {
		pos_files.push_back(false);
	      }
	  }
      }
    if(op == '|')
      {
	for(int i = 0; i <= index_f.size(); i++)
	  {
	    if(index_f[i] == false && index_s[i] == false)
	      pos_files.push_back(false);
	    else
	      {
		pos_files.push_back(true);
	      }
	  }
      }
    return pos_files;
  }
  vector<bool> getting_answer_re(node *x)
  {
    if(x->left == NULL && x->right == NULL)
      return location_file[x->value - '0'];
    return decoding_req(getting_answer_re(x->left),getting_answer_re(x->right),x->value);
  }
    
    node* buildTreeFromInorder(const string& inorder) {
        stack<node*> operators;
        stack<node*> operands;

        for (char c : inorder) {
            if (isOperator(c)) {
                while (!operators.empty() && precedence(operators.top()->value) >= precedence(c)) {
                    node* op = operators.top();
                    operators.pop();
                    node* right = operands.top();
                    operands.pop();
                    node* left = operands.top();
                    operands.pop();
                    op->left = left;
                    op->right = right;
                    operands.push(op);
                }
                operators.push(new node(c));
            } else {
                operands.push(new node(c));
            }
        }

        while (!operators.empty()) {
            node* op = operators.top();
            operators.pop();
            node* right = operands.top();
            operands.pop();
            node* left = operands.top();
            operands.pop();
            op->left = left;
            op->right = right;
            operands.push(op);
        }

        return operands.top();
    }

private:
    bool isOperator(char c) {
        return (c == '&' || c == '|');
    }

    int precedence(char op) {
        if (op == '|')
            return 1;
        if (op == '&')
            return 2;
        return 0;
    }
};
 
void Stack::push(node* x)
{
    if (head == NULL) {
        head = x;
    } else {
        x->next = head;
        head = x;
    }
}

node* Stack::pop()
{
    node* p = head;
    head = head->next;
    return p;
}

void read_documents()
{
  vector<string>current_document;
  string end_doc = "$",endall_doc="%",current_w;
  do{
    do
      {
	cin >> current_w;
	if(current_w == endall_doc) break;
	current_document.push_back(current_w);
      }while(current_w != end_doc );
    document_coletion.push_back(current_document);
    current_document.clear();
  } while(current_w != endall_doc);
}

bool is_not_main_w(string try_word)
{
  for(auto word : not_get_w)
    {
      if(word == try_word) return false;
    }
  return true;
}

bool getting_yet(string try_word)
{
  for(auto word : main_w)
    {
      if(word == try_word) return false; 
    }
  return true;
}

// Toma de las palabras esenciales
void getting_main_w()
{
  for(int i = 0; i <= document_coletion.size()-1; i++)
    {
      for(auto word : document_coletion[i])
	{
	  if(is_not_main_w(word))
	    {
	      if(getting_yet(word))
		{
		  main_w.push_back(word);
		}
	    }
	}
    }
  /* for(auto word : main_w)
     cout << word << endl;*/
}

//Funcion que localiza losarchivos en los docuentos
bool is_inthis_document(vector<string> vstring, string try_word)
{
  for(auto word : vstring)
    {
      if(word == try_word)
	return true;
    }
  return false;
}

//Funcion que rellena el vector de las pos
void fulling_location_file(size_t rows,size_t columns)
{
  vector<bool> aux;
   for(int j = 0; j <= columns; j++)
      aux.push_back(false);
  for(int i = 0; i <= rows; i++)
    location_file.push_back(aux);
}

//Funcion que posiciona los archivos en docs.
void setting_location_file()
{
  fulling_location_file(main_w.size()-1,document_coletion.size()-1);
  for(int i = 0; i <= main_w.size()-1; i++)
    {
      for(int j = 0; j <=  document_coletion.size()-1; j++)
	{
	  //cout << is_inthis_document(document_coletion[j],main_w[i]) << " ";
	  if(is_inthis_document(document_coletion[j],main_w[i]))
	    {
	      location_file[i][j] = true; 
	    }
	}
      cout << endl;
    }
  /*for(int i = 0; i <= location_file.size()-1; i++)
    {
      cout << main_w[i] << " ";
    for(auto location : location_file[i])
      {
	cout << location << " ";
      }
    cout << endl;
    }*/
}

//Funcion que devuelve la posicion de la palabra
char pos_of_word(string word)
{
  for(int i = 0;i <= main_w.size(); i++)
    {
      if(word == main_w[i]) return i + '0';
    }
  return 'e';
}

//Funcion que transforma la consulta en expresion de arbol
string encoding_expression(vector<string> request)
{
  
  string andd = "y", orr = "o",re_encod = " ";
  for(auto cchar : request)
    {
      if(cchar == andd)
	{
	  re_encod += "&";
	  continue;
	}
      if(cchar == orr)
	{
	  re_encod += "|";
	  continue;
	}
      re_encod += pos_of_word(cchar);
       
    }
  return re_encod;
}

//Funcion de toma de la consulta
void procesing_request()
{
  string current,end_doc = "$";
  vector<string> current_request;
  cout << "Insertar consulta:";
  cin >> current;
  while(current != end_doc)
    {
      current_request.push_back(current);
      cin >> current;
    }
   expression_tree et;
   node* root = et.buildTreeFromInorder(encoding_expression(current_request));
   cout << "Los archivos segun la consulta pueden ser hallados en:" << endl;
   for(int i = 0; i <= (et.getting_answer_re(root)).size(); i++)
     {
       if((et.getting_answer_re(root))[i] == true)
	 {
	   cout << "Documento #" << i << endl;
	 }
     }
}



// Funcion Principal
int main()
{
  read_documents();
  getting_main_w();
  setting_location_file();
  procesing_request();

  return 0;
}
