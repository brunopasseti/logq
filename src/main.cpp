#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <glpk.h>
#include <OsiGlpkSolverInterface.hpp>
#include <OsiSolverInterface.hpp>
#include <CoinPackedMatrix.hpp>
#include <CoinPackedVector.hpp>
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

    int n_alunos, n_dias, n_horarios;
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
        data.n_alunos = std::atoi(n_alunos.data());
        data.n_dias = std::atoi(n_dias.data());
        data.n_horarios = std::atoi(n_horarios.data());
        data.tau_i = std::vector<int>(data.n_alunos, 0);
        data.mi_i_j_k = std::vector<std::vector<std::vector<int>>>(data.n_alunos, std::vector<std::vector<int>>(data.n_dias, std::vector<int>(data.n_horarios, 0)));
        std::cout << n_alunos << omega << n_dias << n_horarios << std::endl;
        data.omega = std::atoi(omega.data());
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
        for(size_t i = 0; i < data.n_alunos; i++){
            fp >> tmp;
            data.map_student_to_index_i.emplace(tmp, i);
            for(size_t j = 0; j < data.n_dias; j++){
                for(size_t k = 0; k < data.n_horarios; k++){
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
    OsiSolverInterface *problem = new OsiGlpkSolverInterface();
    Data instance = parse_instance(std::string(argv[argc-1]));
    /*
    /   MAX x_0_0_0 + x_0_0_1 + ....
    /
    /
    */
    int n_cols = instance.n_alunos*instance.n_dias*instance.n_horarios;
    double * objective = new double[n_cols];//the objective coefficients
    double * col_lb = new double[n_cols];//the column lower bounds
    double * col_ub = new double[n_cols];//the column upper bounds
    for(int i = 0; i < n_cols; i++){
        objective[i] = 1.0;
        col_lb[i] = 0.0;
        col_ub[i] = 1.0;
    }
    int n_rows = n_cols;
    CoinPackedMatrix * matrix = new CoinPackedMatrix(false,0,0);
    matrix->setDimensions(0, n_cols);
    for(int i = 0; i < instance.n_alunos; i++){
        for(int j = 0; j < instance.n_dias; j++){
            for(int k = 0; k < instance.n_horarios; k++){  
                int index = i + j*instance.n_alunos + k*instance.n_alunos*instance.n_dias;
                
            }
        }
    }
    delete problem;
    return EXIT_SUCCESS;
}   