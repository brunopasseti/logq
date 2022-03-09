#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <glpk.h>

using json = nlohmann::json;

int main(void){
    glp_prob *lp;
    lp = glp_create_prob();
    glp_delete_prob(lp);
    glp_free_env();
    return EXIT_SUCCESS;
}