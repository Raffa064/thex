# Olá Contribuidor!

Muito obrigado por considerar contribuir para o projeto!

Sua contribuição é sempre bem-vinda, e neste documento vou explicar como você pode fazer isso.

# Issues

Você não precisa mexer no código. Reportar bugs, sugerir novas features, ou até mesmo compartilhar o projeto já são formas de contribuir.

Para reportar bugs ou sugerir novas features, use a aba [issues](https://github.com/Raffa064/thex/issues).

> [!TIP]
Quando reportar algum problema, seja o mais descritivo possível. Se possível, envie informações sobre qual versão você está usando e em qual ambiente está tentando utilizá-lo.

## Sugestões

Para sugestões de features, por favor verifique se a feature em questão já não foi requisitada anteriormente. Evite duplicatas.

# Pull Request

Caso queira contribuir com código, você pode seguir o clássico workflow do GitHub:

- Faça um `fork` do projeto
- Clone-o para sua máquina local
- Crie uma nova branch a partir da branch `dev`
- Implemente as alterações desejadas
- Faça commit de suas alterações e envie para o seu fork
- Quando tiver pronto, abra um `PR` (Pull Request) do seu branch para a branch `main` deste repositório

Certifique-se de que o seu PR inclua:
- Código de acordo com os [Padrões do Projeto](#padrões-do-projeto)
- Uma descrição clara da correção ou feature implementada
- Referência a qualquer `issue` relacionada
- Documentação atualizada, se necessário

# Padrões de Projeto

Os **padrões do projeto** são regras sobre como o código deve ser organizado para que não haja inconsistências. Caso queira contribuir, é importante segui-los, ou seu PR pode não ser aceito pelos `moderadores`.

**Linguagem**
Todo o código deve estar em inglês, desde comentários até identificadores de classes, variáveis, etc.

**Formatação para Classes e Structs**

Para melhor legibilidade, toda `classe` ou `struct` deve ser definida e nomeada em *camel case*, e ser o mais simples e descritiva possível, como nos exemplos:

- `Editor` Alguma classe responsável por edição.
- `InputManager` Alguma classe que gerencia input.
- `UI` Componentes de interface (User Interface)

**Métodos e Funções**

Todo método ou função precisa ser definido em *snake case* e ser descritivo quanto à sua função.

É de grande valia manter o **Princípio da Responsabilidade Única (SRP)**, onde cada função deve fazer apenas uma única coisa.

- `do_something`
- `is_some_state`
- `get_some_value`
- `set_some_value`

**Variáveis**
Toda variável deve ter nomes descritivos, em *camel case*, começando com letra minúscula. Abreviações podem ser usadas, mas com a devida explicação via comentário, salvo em iteradores.

Evite variáveis com nomes semelhantes (não use o plural em nomes de listas).

- `sampleOfVarName`
- `fileBuffer ou fBuffer`
- `i, j, ou k para iteradores`
- `something`
- `listOfSomething`
- `somethingList`

**Identação**
A indentação deve ser configurada para 2 espaços, as demais configurações podem ser da formatação padrão do ClangFormat.

**Comentários**
Não use comentários para coisas óbvias, escreva código que não precise deles. Mas, caso seja necessário, como em conceitos complexos ou lógica implícita, use comentários descritivos, em linguagem formal, sem abreviações.

```cpp
/*
  This function is responsible for ... because ... 
*/

void complexFunction() { ... }
```

**Headers**

Para cada arquivo header, dentro de `include`, deve-se criar um arquivo de implementação em `.cpp`. Implementações diretamente no header devem ocorrer apenas quando forem algo muito trivial, como construtores padrão, setters e getters, ou alguma função estática global (como [esta](./include/interface/pallete.h)).

**OBS:** Embora atualmente o projeto omita o nome de parâmetros nos arquivos header, isso não é uma boa prática e, futuramente, isso precisa ser corrigido. Portanto, **não omita os nomes de parâmetros nos arquivos header**.

---

Essas correções ajustam alguns erros de digitação e melhoram a clareza e consistência do texto. Agora, seu guia está ainda mais claro para os contribuintes!
