#include <iostream> //cout cin 
#include <fstream> //funcionar ifstream ofstream
#include <string> // funcionar o getline
#include <sstream> //para usar stringstream	
#include <locale.h> // funcionar o reconhecimento de caractéres em pt-br
#include <vector> //para usar função vector

using namespace std;

struct student { //strutura esqueleto para o registro de alunos
	string name;
	int age;
	int register_number;
	
};

void pause() { //pausa no programa até apertar enter
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void clear_screen() { // Limpa a tela e posiciona o cursor no topo
    cout << "\033[2J\033[H"; 
}

student student_info_gather() { // função que pega informação do usuário e retorna uma strutura com os dados do aluno
	student student_gather_handle;
	cout << "Digite o nome do aluno\n";
	cin.ignore();
	getline(cin, student_gather_handle.name);
	cout << "Digite a idade do aluno (somente numeros)\n";
	cin >> student_gather_handle.age;
	cout << "Digite a matricula do aluno (somente numeros e inferiores ao valor 2,1*10^9)\n";
	cin >> student_gather_handle.register_number;	
	return student_gather_handle;	
	}

void adc_student(student student_handle, bool its_a_edit) {	//função que envolve receber uma strutura de aluno para adicionar ou refazer o arquivo BD
	ofstream file;
	if (its_a_edit) file.open("BD/BD_NAP2_Register_students.txt");
	else file.open("BD/BD_NAP2_Register_students.txt", ios::app);
	file << student_handle.name << "\n";
	file << student_handle.age << "\n";
	file << student_handle.register_number << "\n";
	if(	file.fail()) pause();cout << "erro em abrir arquivo";
	file.close();		
	}
	
vector<student> read_students_file()
	{
	    vector<student> alunos;
    	ifstream file("BD/BD_NAP2_Register_students.txt");

    	while (file) {
        student vector_handle_lecture;
        if (!getline(file, vector_handle_lecture.name)) break;
        file >> vector_handle_lecture.age;
        file >> vector_handle_lecture.register_number;
        file.ignore(); // limpa \n
        alunos.push_back(vector_handle_lecture);
    	}
		file.close();
		return alunos;
	  }	
	  
void show_students(vector<student> alunos) {
		clear_screen();
    	cout << "------------------------" << endl;
		for (int i = 0; i < alunos.size(); i++)
		{
        cout << "Nome: " << alunos[i].name << endl;
        cout << "Idade: " << alunos[i].age << endl;
        cout << "Matrícula: " << alunos[i].register_number << endl;
        cout << "------------------------" << endl;
		}
		pause();
	}
	
void delete_students()
	{
	   	student vector_handle_delete; // struct de apoio para montar o novo vetor de struct
	   	string select_name; // string para guardar a referencia para deletar o registro
		vector<student> alunos = read_students_file(); // vetor que contem a atual BD de dados
		vector<student> student_new; // vetor que será salvo o novo DB de dados alterado
		cout << "digite o nome do aluno para ser deletado\n";
		cin.ignore();
	   	getline(cin, select_name);
	   	for (int i = 0; i < alunos.size(); i++)
		   {
	   		if (select_name != alunos[i].name)
			   {
   	   			vector_handle_delete.name = alunos[i].name;
				vector_handle_delete.age = alunos[i].age;
				vector_handle_delete.register_number = alunos[i].register_number;
				student_new.push_back(vector_handle_delete);	   
		   	   }
			}
		for (int i = 0; i < student_new.size(); i++)
			{
			if ( i == 0) adc_student(student_new[i],true);
			if (i != 0) adc_student(student_new[i],false);
	  	    }	   	
	}

void edit_students()
	{
	   	student vector_handle_edit, handle_edit; // vector_handle_edit é para guardar a informação do for que vai alterando e o handle_edit guarda a informação do que será corrigido
	   	string name_handle;
		vector<student> alunos = read_students_file();
		vector<student> student_new;
		cout << "digite o nome do aluno para ser alterado\n";
		cin.ignore();
	   	getline(cin, name_handle);
		cout << "digite o nome corrigido\n";
	   	getline(cin, handle_edit.name);
		cout << "digite a idade corrigida (somente numeros)\n";
	   	cin >> handle_edit.age;
		cout << "digite a matricula corrigida (somente numeros e inferiores ao valor 2,1*10^9) \n";
	   	cin >> handle_edit.register_number;

		for (int i = 0; i < alunos.size(); i++)
		{
			if (name_handle != alunos[i].name)
			{
			   	   	vector_handle_edit.name = alunos[i].name;
					vector_handle_edit.age = alunos[i].age;
					vector_handle_edit.register_number = alunos[i].register_number;
					student_new.push_back(vector_handle_edit);				
			}
			else
			{
			   	   	vector_handle_edit.name = handle_edit.name;
					vector_handle_edit.age = handle_edit.age;
					vector_handle_edit.register_number = handle_edit.register_number;
					student_new.push_back(vector_handle_edit);								
			}
		}
			for (int i = 0; i < student_new.size(); i++)
			{
			if ( i == 0) adc_student(student_new[i],true);
			if (i != 0) adc_student(student_new[i],false);
	  	    }	   	                                 
			show_students(student_new);
	}
	
bool login() { // login do sistema
	string user, senha;
	clear_screen();
	cout << "Digite o login\n";
	cin >> user;
	cout << "Digite a senha\n";
	cin >> senha;
    ifstream file("Admin/login.txt");
    string user_valid, senha_valid;
    
    if (!file.is_open()) {
	cout << "Erro no arquivo";
	return false;	
	} 
    
    getline(file, user_valid);
    getline(file, senha_valid);
    
    if (user == user_valid && senha != senha_valid) {
	cout << "Senha invalida";
	pause();
	return false;	
	} 
    if (user != user_valid) {
	cout << "Dados incorretos";
	pause();
	return false;	
	}

    return (user == user_valid && senha == senha_valid);
}	
	
void Menu(bool* encerrar_sistema){ // login do sistema
    int choice;
    bool login_control = true;

    do {
    	clear_screen();
		cout << "\n=== Sistema de controle de turma de 'Tecnicas de programação 1' ===\n";
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Adicionar aluno a turma\n";
        cout << "2. Exluir aluno da turma\n";
        cout << "3. Editar cadastro de aluno\n";
        cout << "4. Mostrar Alunos cadastrados\n";
        cout << "5. Sair (voltar ao login)\n";
        cout << "6. Fechar o sistema\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adc_student(student_info_gather(), false); // exemplo
                break;
            case 2:
                delete_students();
                break;
            case 3:
                edit_students();
                break;
            case 4:
                show_students(read_students_file());
                break;
            case 5:
                login_control = false;
                return; // volta para o while do main (login novamente)
            case 6:
                *encerrar_sistema = false;
                return; // encerra tudo
            default:
                cout << "Opção inválida. Tente novamente.\n";
        }

    } while (login_control); // continua até escolher sair ou fechar
}	

	
int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    bool loop_control = true;

    while (loop_control) 
	{
        if (login()) 
		{
		Menu(&loop_control);
        }
    }

    cout << "Programa encerrado.\n";
    return 0;
}