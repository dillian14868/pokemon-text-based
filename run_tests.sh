./main.exe < tests/player_first.txt | diff -  tests/player_first.correct.txt
./main.exe < tests/enemy_first.txt | diff -  tests/enemy_first.correct.txt
./main.exe < tests/buy.txt | diff -  tests/buy.correct.txt
./main.exe < tests/run.txt | diff -  tests/run.correct.txt
./main.exe < tests/two_battles.txt | diff -  tests/two_battles.correct.txt
./main.exe < tests/catch_pokemon.txt | diff -  tests/catch_pokemon.correct.txt