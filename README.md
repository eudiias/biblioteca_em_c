# 📚 Sistema de Gestão de Biblioteca (Library System)

Este projeto é uma aplicação de linha de comando (CLI) desenvolvida em **Linguagem C**, como parte integrante da disciplina de **Estrutura de Dados** do curso de Desenvolvimento de Software Multiplataforma na **Fatec Osasco**.

O sistema foi projetado para gerir de forma eficiente o fluxo de uma biblioteca, abrangendo desde o registo de utilizadores até ao controlo de empréstimos de livros.

---

## 🛠️ Funcionalidades

O software oferece um conjunto de operações essenciais para a administração do acervo:

* **Gestão de Utilizadores:** Registo de novos leitores, listagem completa de utilizadores ativos e remoção de registos.
* **Controlo de Acervo:** Cadastro de livros, consulta de disponibilidade e exclusão de títulos do sistema.
* **Registo de Empréstimos:** Vinculação de um livro a um utilizador específico, permitindo o controlo de circulação de exemplares.

---

## 💻 Conceitos de Estrutura de Dados Aplicados

Para a construção deste projeto, foram explorados conceitos fundamentais da ciência da computação em C:

* **Tipos Abstratos de Dados (Structs):** Definição de estruturas organizadas para `Utilizador`, `Livro` e `Emprestimo`.
* **Manipulação de Ponteiros:** Gestão eficiente de memória e passagem de parâmetros entre funções.
* **Lógica de Programação:** Implementação de menus interativos e algoritmos de busca e remoção.
* **Modularização:** Organização do código em blocos lógicos para facilitar a manutenção e legibilidade.

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
* Compilador C (GCC, Clang ou MinGW).
* Ambiente de terminal (Bash, PowerShell ou CMD).

### Passo a Passo
1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/teu-usuario/nome-do-repositorio.git](https://github.com/teu-usuario/nome-do-repositorio.git)
    ```
2.  **Aceda à pasta do projeto:**
    ```bash
    cd nome-do-repositorio
    ```
3.  **Compile o código-fonte:**
    ```bash
    gcc main.c -o sistema_biblioteca
    ```
4.  **Execute a aplicação:**
    ```bash
    ./sistema_biblioteca
    ```

---

## 📂 Organização do Repositório

* `main.c`: Contém a lógica principal, structs e funções do sistema.
* `.gitignore`: Configurado para ignorar ficheiros binários e executáveis (`.exe`, `.o`).
* `README.md`: Documentação detalhada do projeto.

---

## 👨‍💻 Autor

**Carlos Dias**
* 📍 Estudante de Desenvolvimento de Software na **Fatec Osasco**.
* 🎯 Foco em: Back-end (Java/Spring Boot) e Engenharia de Software.
* 🚀 Atualmente à procura de oportunidades de estágio na área de tecnologia.

---
> *Este projeto demonstra a aplicação prática de conceitos de Estrutura de Dados e serve como base para estudos mais avançados em algoritmos complexos.*
