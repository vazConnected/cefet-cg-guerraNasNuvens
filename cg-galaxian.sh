function excluirArquivosDesnecessarios {
    echo -e "\nExcluindo arquivos desnecessarios..."

    rm -f $(pwd)/src/bibliotecas/telas.o
    rm -f $(pwd)/src/bibliotecas/listas.o
    rm -f $(pwd)/src/bibliotecas/fisicas.o

    echo -e "Feito!"
}

clear
echo -e "\nA compilacao da Guerra nas Nuvens foi iniciada!"

echo -e "\n\tCompilando src/bibliotecas/telas.c"
gcc -c -o src/bibliotecas/telas.o src/bibliotecas/telas.c -lGL -lGLEW -lglut
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\tCompilando src/bibliotecas/listas.c"
gcc -c -o src/bibliotecas/listas.o src/bibliotecas/listas.c -lGL -lGLEW -lglut
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\tCompilando src/bibliotecas/fisicas.c"
gcc -c -o src/bibliotecas/fisicas.o src/bibliotecas/fisicas.c -lGL -lGLEW -lglut
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\n\tCompilando src/main.c"
gcc -o src/cg-galaxian.out src/main.c src/bibliotecas/telas.o src/bibliotecas/fisicas.o src/bibliotecas/listas.o -lGL -lglut -lGLEW
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\nCompilacao finalizada!"
excluirArquivosDesnecessarios

echo -e "\nIniciando jogo..."
./src/cg-galaxian.out

echo -e "\nObrigado(a) por jogar!\n"
rm -f $(pwd)/src/cg-galaxian.out

exit 0