#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <glpk.h>

// using json = nlohmann::json;

typedef struct Data{
    // Tempo minimio semanal do aluno i;
    std::vector<int> tau_i;
    // Disponibilidade do aluno i, no dia j, horário k;
    std::vector<std::vector<std::vector<int>>> mi_i_j_k;
    // Quantidade de workspaces;
    int omega;
    // Mapa aluno para indice;
    std::map<std::string, size_t> map_student_to_index_i;
    // // Mapa dia da semana para index;
    // std::map<std::string, size_t> map_day_to_index_j;
} Data;

Data parse_instance(std::string input){
        std::fstream fp;
        fp.open(input);
        if(!fp){
            exit(EXIT_FAILURE);
        }
        std::string n_alunos, omega, n_dias, n_horarios;
        while(char ch = fp.peek() != std::char_traits<char>::eof()){
            if(ch == '#'){
                fp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }else{
                // n_alunos << omega << n_dias << n_horarios << fp; 
                fp >> n_alunos >> omega >> n_dias >> n_horarios;
                std::cout << n_alunos << omega << n_dias << n_horarios << std::endl;
            }
        }
        return {};
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error: missing instance path." << std::endl;
        return EXIT_FAILURE;
    }
        
    Data instance = parse_instance(std::string(argv[2]));
    return EXIT_SUCCESS;
}   