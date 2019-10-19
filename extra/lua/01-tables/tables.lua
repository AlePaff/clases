-- Lua posee distintos tipos de datos
-- * booleanos
-- * numéricos (punto flotante)
-- * strings
-- * tablas (diccionarios)
-- * funciones
-- Una tabla es básicamente un mapa
-- En este ejemplo, las claves son strings

squirtle_table = {name = "squirtle", type = "water"}

-- Es equivalente a la expresión más verbosa
-- squirtle_table = {["name"] = "squirtle", ["type"] = "water"}

-- En este ejemplo, las claves son numéricas y los valores son otras tablas
-- Notar que los números van entre corchetes debido a que son claves numéricas
pokedex = {
  [1] = {
    name = "bulbasaur",
    type = "plant"
  },
  [4] = {
    ["name"] = "charmander",
    ["type"] = "fire"
  },
  [7] = squirtle_table
}

-- Puedo iterar sobre las entradas de una tabla
print("Tengo en mi pokedex:")
for k, v in pairs(pokedex) do
  print(string.format("Id: %s -> Nombre: %s, tipo: %s", k, v.name, v.type))
end

-- Otra curiosidad de las tablas es la forma de acceder a los atributos
-- Si declaramos la siguiente variable:
myAttr = "name"
-- Las siguientes formas de referir al atributo "name" son equivalentes
print(string.format("squirtle_table.name -> %s", squirtle_table.name))
print(string.format("squirtle_table[\"name\"] -> %s", squirtle_table["name"]))
print(string.format("squirtle_table[myAttr] -> %s", squirtle_table[myAttr]))

-- También puedo acceder a claves numéricas de una tabla
myPokemon = pokedex[1]
print(string.format("myPokemon -> Nombre: %s, tipo: %s", myPokemon.name, myPokemon.type))
