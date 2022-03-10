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
        std::string n_alunos, omega, n_dias, n_horarios, tmp;
        char ch = fp.peek();
        while( ch == '#' || ch == '\n'){
            fp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ch = fp.peek();
        }
        fp >> n_alunos >> omega >> n_dias >> n_horarios;
        Data data{};
        data.tau_i = std::vector<int>(std::atoi(n_alunos.data()), 0);
        data.mi_i_j_k = std::vector<std::vector<std::vector<int>>>(std::atoi(n_alunos.data()), std::vector<std::vector<int>>(std::atoi(n_dias.data()), std::vector<int>(std::atoi(n_alunos.data()), 0)));
        std::cout << n_alunos << omega << n_dias << n_horarios << std::endl;
        data.omega = std::atoi(omega.data());
        size_t t_ndias = std::atoi(n_dias.data());
        size_t t_horarios = std::atoi(n_horarios.data());
        ch = fp.peek();
        while( ch == '#' || ch == '\n' || ch == ' '){
            fp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ch = fp.peek();
        }
        for(size_t i = 0; i < data.tau_i.size(); i++){
            fp >> tmp;
            data.tau_i[i] = std::atoi(tmp.data());
        }
        ch = fp.peek();
        while( ch == '#' || ch == '\n' || ch == ' '){
            fp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ch = fp.peek();
        }
        for(size_t i = 0; i < data.tau_i.size(); i++){
            fp >> tmp;
            data.map_student_to_index_i.emplace(tmp, i);
            for(size_t j = 0; j < t_ndias; j++){
                for(size_t k = 0; k < t_horarios; k++){
                    fp >> tmp;
                    data.mi_i_j_k[i][j][k] = std::atoi(tmp.data());
                }
            }
        }
        return data;
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error: missing instance path. Argc = " << argc << "." << std::endl;
        return EXIT_FAILURE;
    }
        
    Data instance = parse_instance(std::string(argv[argc-1]));
    return EXIT_SUCCESS;
}   