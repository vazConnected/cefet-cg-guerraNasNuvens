function excluirArquivosDesnecessarios {
    echo -e "\nExcluindo arquivos desnecessarios..."

    rm -f $(pwd)/src/bibliotecas/telas.o

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

echo -e "\tCompilando src/main.c"
gcc -o src/cg-galaxian.out src/main.c src/bibliotecas/telas.o -lGL -lglut -lGLEW
if [ $? -ne 0 ]; then
    excluirArquivosDesnecessarios
    exit 1
fi

echo -e "\nCompilacao Finalizada!"
excluirArquivosDesnecessarios

echo -e "\nIniciando jogo..."
./src/cg-galaxian.out

echo -e "\nObrigado por jogar!\n"
rm -f $(pwd)/src/cg-galaxian.out

exit 0