<p align="center">
    <img src="/media/icon.png" alt="THex icon" width="90" height="90"/>
</p>

<h2 align="center"><b>THex</b></h2>
-

O THex é uma ferramenta de edicão para arquivos banários, via terminal, assim como **bvi** e **hexedit**, porém, com algumas features extras, e um interface vim-like.


# Features
-

- [x] Layout responsivo 
- [x] Ascii preview
- [x] Edicão nibble a nibble 
- [ ] Adicionar marcadores
- [ ] Preview de strings, numeros, flags, etc
- [ ] Swap files para marcadores e +
- [ ] Linguagem própria para esquemas e processamento de dados

# Build
-

Para gerar uma build, primeiro, clone o repositorio usando git:

```bash
git clone https://github.com/Raffa064/thex && cd thex
```

Antes de compilar o projeto, certifique-se de que o compilador, cmake e a biblioteca ncurses estejam instalados:

```bash
$ sudo apt install clang libncuses-dev cmake
```

Após isso, é necessário executar o cmake, para que ele gere os arquivos de configuracão:

```bash
$ cmake .
```

> [!TIP]
Esse comando deve ser executado sempre que adicionar e remover arquivos das pasras scr e inclue, ou quando alterar algo no [CMakeLists.txt](./CMakeLists.txt).

**Opcões de build:**
- `-DDEBUG`: Desabilita otimizacões do compilador, para gerar build mais rápido; ativa warnings e habilita debug com gdb.

Após isso, use o seguinte comando para gerar o executável:

```bash
$ cmake --build .
``` 

Pronto, agora é so utilizazr:

```$ ./thex test.bin```

> [!IMPORTANT]
Eu so testei usando o clang-19 pelo Termux (no android), portanto, num ambiente mínimo derivado, não equivalente, do Debian.
Caso encontre algum problema ao gerar a build ou durante a execucão, por favor, abra uma [issue](https://github.com/Raffa064/thex/issues) descrevendo o problema.

# Contribuicão

Caso queira contribuir, leia o [guia de contribuicão](./CONTRIBUTING.pt-br.md), e obrigado por suportar o projeto ;)

# Achou util? 

Por favor, deixe sua estrela, para dar mais visibilidade ao projeto!
