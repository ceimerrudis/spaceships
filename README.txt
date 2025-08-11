Rūdolfs Ceimers rc22006 
Uzdevums 5a
Programma izveidota valodā c ar GLFW un GLEW bibliotēkām. Manis rakstītais kods atrodas src folderī.
Programmā dodekaedru var pārvietot rotēt un mērogot un apskatīt caur novērotāja skata punktu (transformācijas vienmēr tiek veiktas pasaules koordinātēs)
Gaisma veidota ļoti primitīvi un izgaismo vieno modeļa daļu neatkarīgi no rotācijas.

Šī uzdevuma izpildē lietots kods no pirmā patstāvīgā darba.

Kompilācijai paredzēts izmantot CMake.
Kompilāciju veic palaižot šīs kommandas build folderī:
	cmake -G "MinGW Makefiles" ../
	cmake --build .
Protams ka jānorāda savs kompilators, vai jāļauj CMakam pašam izvēlēties noklusējumu.


Kontroles

lai pārvietotu objektu 
w, a, s, d, q, e

lai rotētu objektu 
u, h, j, k, y, o

lai mērogotu objektu
r, t,
f, g,
v, b

Lai nomainītu uz novērotāja skatapunktu (un atpakaļ)
p

