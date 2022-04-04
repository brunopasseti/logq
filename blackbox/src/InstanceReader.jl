struct LogqInstance
    A_size::Integer
    ω::Integer
    D_size::Integer
    H_size::Integer
    τ::Vector{Integer}
    μ::Vector{Vector{Vector{Bool}}}

    string_days::Vector{String}
    names::Vector{String}
end

function read_instance_json(path::String)::LogqInstance

    include("src/InstanceSchema.jl")

    instance_as_json_obj = JSON.parsefile(path)
    if !isvalid(instance_as_json_obj, instance_schema_validator)
        @warn "Wrong schema when reading json." JSONSchema.validate(instance_as_json_obj, instance_schema_validator)
        throw(TypeError("function read_instance_json got json with invalid format", Nothing, JSONSchema.SingleIssue))
    end
    # JSON.print(instance_as_json_obj, 8)
    a_size = length(instance_as_json_obj["infos"])
    q_dias = instance_as_json_obj["quant_dias"]
    q_hora = instance_as_json_obj["quant_horarios"]
    q_work = instance_as_json_obj["quant_workspace"]
    tau = map(a -> a["quantidade_minima"], instance_as_json_obj["infos"])
    horarios_named = map(a -> a["horarios"], instance_as_json_obj["infos"])
    horarios = convert(Vector{Vector{Vector{Bool}}}, map(a -> collect(values(a)), values(horarios_named)))

    days_name = convert(Vector{String}, collect(keys(instance_as_json_obj["infos"][1]["horarios"])))

    names = map(a -> a["nome"], instance_as_json_obj["infos"])
    return LogqInstance(a_size, q_work, q_dias, q_hora, tau, horarios, days_name, names)
end

function read_instance_json(instance_as_json_dict::Dict{String,Any})::LogqInstance

    include("src/InstanceSchema.jl")
    if !isvalid(instance_as_json_dict, instance_schema_validator)
        @warn "Wrong schema when reading json." JSONSchema.validate(instance_as_json_dict, instance_schema_validator)
        throw(TypeError("function read_instance_json got json with invalid format", Nothing, JSONSchema.SingleIssue))
    end
    # JSON.print(instance_as_json_dict, 8)
    a_size = length(instance_as_json_dict["infos"])
    q_dias = instance_as_json_dict["quant_dias"]
    q_hora = instance_as_json_dict["quant_horarios"]
    q_work = instance_as_json_dict["quant_workspace"]
    tau = map(a -> a["quantidade_minima"], instance_as_json_dict["infos"])
    horarios_named = map(a -> a["horarios"], instance_as_json_dict["infos"])
    horarios = convert(Vector{Vector{Vector{Bool}}}, map(a -> collect(values(a)), values(horarios_named)))

    days_name = convert(Vector{String}, collect(keys(instance_as_json_dict["infos"][1]["horarios"])))

    names = map(a -> a["nome"], instance_as_json_dict["infos"])
    return LogqInstance(a_size, q_work, q_dias, q_hora, tau, horarios, days_name, names)
end


export read_instance_json
