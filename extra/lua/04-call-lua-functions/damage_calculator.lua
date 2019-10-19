print("damage_calculator loaded")

function getDamage(weapon, hits)
  print(string.format("Repositorio: %s", armory))
  local minDmg = armory[weapon]["minDmg"]
  local maxDmg = armory[weapon]["maxDmg"]
  print(string.format("Min dmg: %d, Max dmg: %d",
    minDmg, maxDmg))
  local totalDmg = 0
  for i=1, hits do
  	totalDmg = totalDmg + math.random(minDmg, maxDmg)
  end
  return totalDmg
end