# Hello Contributor!

Thank you very much for considering contributing to the project!

Any contribution is always welcome, and in this document, I will explain how you can contribute.

# Issues

You don’t need to modify the code. Reporting bugs, suggesting new features, or even sharing the project are all ways to contribute.

To report bugs or suggest new features, use the [issues](https://github.com/Raffa064/thex/issues) tab.

> [!TIP]  
When reporting an issue, be as descriptive as possible. If possible, include information about which version you are using and the environment in which you are trying to run it.

## Suggestions

For feature suggestions, please check if the feature has already been requested. Avoid duplicates.

# Pull Request

If you want to contribute code, you can follow the classic GitHub workflow:

- Fork the project
- Clone it to your local machine
```bash
$ git clone https://github.com/<Your Name>/<Your fork>
```
- Create a new branch from the `dev` branch (or any other name you prefer)
```bash
$ git checkout -b dev
```
- Implement the desired changes
- Commit your changes and push them to your fork
```bash
$ git commit -m "Added <feature>"
$ git push origin main # this pushes the changes to your fork
```
- When ready, open a `PR` (Pull Request) from your branch to the `main` branch of this repository

**Make sure your PR includes:**
- Code that follows the [Project Standards](#project-standards)
- A clear description of the fix or feature implemented
- Reference to any related `issue` (if applicable)
- Updated documentation (if necessary)

# Project Standards

The **project standards** are rules on how the code should be organized to avoid inconsistencies. If you want to contribute, it is important to follow them, or your **PR** may not be accepted by the `moderators`.

**Language**  
All code must be in English, from comments to class identifiers, variables, etc.

**Class and Struct Formatting**  
For better readability, every `class` or `struct` should be defined and named in *camel case*, and be as simple and descriptive as possible, like the examples below:

- `Editor` A class responsible for editing.
- `InputManager` A class that manages input.
- `UI` User Interface components.

**Methods and Functions**  
Every method or function must be defined in *snake case* and be descriptive about its function.

It is highly recommended to follow the **Single Responsibility Principle (SRP)**, where each function should only do one thing.

- `do_something`
- `is_some_state`
- `get_some_value`
- `set_some_value`

**Variables**  
Every variable should have descriptive names, in *camel case*, starting with a lowercase letter. Abbreviations may be used, but with proper explanation via comment, except for iterators.

Avoid variables with similar names (don’t use plural in list names).

- `sampleOfVarName`
- `fileBuffer or fBuffer`
- `i, j, or k for iterators`
- `something`
- `listOfSomething`
- `somethingList`

**Indentation**  
Indentation should be set to 2 spaces, other configurations can follow the standard ClangFormat formatting.

**Comments**  
Do not use comments for obvious things, write code that doesn’t need them. However, if necessary, for complex concepts or implicit logic, use descriptive comments in formal language without abbreviations.

```cpp
/*
  This function is responsible for ... because ... 
*/

void complexFunction() { ... }
```

**Headers**  
For every header file inside `include`, a `.cpp` implementation file should be created. Implementations directly in the header should only occur for very trivial things, such as default constructors, setters and getters, or some global static function (like [this one](./include/interface/pallete.h)).

**Commit Messages**  
For better organization, we use commit messages in the following format:
```git
Short summary of what was done

- List of implemented things
- List of bugs fixed
- List of modifications
```

> [!TIP]  
This is helpful because it makes it easier to understand what is being done with each commit.
