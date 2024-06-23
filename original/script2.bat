@echo off
echo File Branch_Vertices Time Verification > resultado2.txt
for /f %%f in ('dir /b Instancias2\Grafo_*.txt') do (	
	bin\Release\ArvoreGeradora.exe Instancias2\%%f >> resultado2.txt
)