-- Nums es un array de enteros
local myNums = {1, 1, 2, 3, 5, 8}

-- Iterar un array es iterar un mapa donde la clave es numérica
for i, v in pairs(myNums) do
    print(string.format("myNums[%d] -> %d", i, v))
end

-- La función sum recibe un array de números
function sum(nums)
    local result = 0
    -- itero sobre el array
    for i, v in pairs(nums) do
        result = result + v
    end
    return result
end

-- La función sumVariadic recibe una cantidad variable de argumentos
function sumVariadic(...)
    local result = 0
    -- Para Lua 5.1 itero sobre la variable "arg"
    -- Para Lua 5.3, itero sobre "{...}"
    for i, v in pairs({...}) do
        result = result + v
    end
    return result
end

-- Para pasar los argumentos variádicos de una funcion a otra, usamos
-- los puntos suspensivos (o unpack según la versión de Lua)
function printf(fmt, ...)
    print(string.format(fmt, ...))
end

mySum = sum(myNums)
printf("MySum -> %d", mySum)
myOtherSum = sumVariadic(1, 1, 2, 6, 24)
printf("MyOtherSum -> %d", myOtherSum)

-- Lua permite manejar funciones como variables
local p = printf
p("Type of p: %s", p)

-- Y permite usar closures

function transform(data, f)
    -- Transformación "identidad"
    -- Si el argumento f es nil, uso la función identidad
    local flocal = f or function(x) return x end
    result = {}
    for i, v in pairs(data) do
        result[i] = flocal(v)
    end
    return result
end

data = {1, 2, 5}
-- No le paso ninguna función, por lo que f será nil
data_transformed = transform(data)
printf("{%d, %d, %d}", data_transformed[1], data_transformed[2], data_transformed[3])

-- Transformación de multiplicación por 3
data_transformed = transform(data, function(x) return x*3 end)
printf("{%d, %d, %d}", data_transformed[1], data_transformed[2], data_transformed[3])
