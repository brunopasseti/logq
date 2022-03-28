function solve2(instance::LogqInstance, verbose=true)
    model = Model(Cbc.Optimizer)
    A = 1:instance.A_size
    D = 1:instance.D_size
    H = 1:instance.H_size
    @variable(model, x[i=A, j=D, k=H] <= instance.μ[i][j][k], Bin)
    # @constraint(model, c[i=1:instance.A_size])
    @constraint(model, c1[i=A], sum(x[i, j, k] for j ∈ D for k in H) .>= instance.τ[i])
    @constraint(model, c2[j=D, k=H], sum(x[i, j, k] for i ∈ A) .<= instance.ω)
    # @constraint(model, c3[i=A, j=D, k=H], x[i, j, k] <= instance.μ[i][j][k])
    @objective(model, Max, sum(x[i, j, k] * instance.μ[i][j][k] for i ∈ A for j ∈ D for k in H))
    write_to_file(model, "debug.lp")
    optimize!(model)
    # print(model)
    # return
    if verbose
        println("Objective is: ", objective_value(model))
        println("Solution is:")
        for i ∈ A
            println(instance.names[i], ":")
            print("|")
            for j ∈ D
                print(instance.string_days[j], "|")
            end
            println("")
            for j ∈ D
                print("|")
                for k ∈ H
                    if Bool(value(x[i, j, k]))
                        print("   ✓   |")
                    else
                        print("   x   |")
                    end
                end
                println("")
            end
        end
    end
end

function solve(instance::LogqInstance)::Array{Float64,3}
    model = Model(Cbc.Optimizer)
    A = 1:instance.A_size
    D = 1:instance.D_size
    H = 1:instance.H_size
    @variable(model, x[i=A, j=D, k=H] <= instance.μ[i][j][k], Bin)
    # @constraint(model, c[i=1:instance.A_size])
    @constraint(model, c1[i=A], sum(x[i, j, k] for j ∈ D for k in H) .>= instance.τ[i])
    @constraint(model, c2[j=D, k=H], sum(x[i, j, k] for i ∈ A) .<= instance.ω)
    # @constraint(model, c3[i=A, j=D, k=H], x[i, j, k] <= instance.μ[i][j][k])
    @objective(model, Max, sum(x[i, j, k] * instance.μ[i][j][k] for i ∈ A for j ∈ D for k in H))
    write_to_file(model, "debug.lp")
    optimize!(model)
    return value.(x)
    # return
end


export solve