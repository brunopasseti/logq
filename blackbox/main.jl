include("src/Logq.jl")
using .Logq

function main()
    instance = Logq.read_instance_json("./instances/teste.json")
    Logq.solve2(instance)
end