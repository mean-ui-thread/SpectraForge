# SpectraForge
Experimental rendering engine

# Build Requirement

- For Linux
  - clang/LLVM 14.x or better
  - cmake 3.17 or better
  - git 3.x or better
  - git-lfs
  - ninja build
  - Editor of your choice

- For Windows
  - cmake 3.17 or better
  - git 3.x or better
  - git-lfs
  - ninja
  - Visual Studio 17 2022 (For Windows only)
    - Optional: Clang/LLVM (highly recommended)
  - Editor of your choice

 - (Experimental) For Steam Deck
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/mean-ui-thread/SpectraForge/main/tools/scripts/setup-steam-deck.sh)
   ```
# Cloning the project

We recommend using ssh keys. Please follow these instructions

-[Generating a new SSH key and adding it to the SSH agent](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
-[Adding a new SSH key to your GitHub Account](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)

We are using Large File Storage (LFS) and git modules. Make sure you clone the repository accordingly:

```bash
git lfs clone --recursive git@github.com:mean-ui-thread/SpectraForge.git
```

# Generate and build the project

- For Clang/Ninja
  - Generating: 
    ```Shell
    cmake --preset ninja-clang-sse2
    ```
    - TEMPORARY HUNTER PATCH: Requires this patch applied to `.hunter/_Base/Download/Hunter/0.24.16/09668c2/Unpacked/cmake/modules/hunter_sanity_checks.cmake` for fixing the Ninja Multi-Config issue: https://github.com/cpp-pm/hunter/pull/677
  - Building:
    ```Shell
    cmake --build --preset ninja-clang-sse2-debug
    cmake --build --preset ninja-clang-sse2-release
    cmake --build --preset ninja-clang-sse2-profile
    ```
  - Testing:
    ```Shell
    ctest --preset ninja-clang-sse2-debug
    ctest --preset ninja-clang-sse2-release
    ctest --preset ninja-clang-sse2-profile
    ```

- For Visual Studio 17 2022
  - Generating:
    ```Shell
    cmake --preset vs-17-2022-sse2
    ```
  - Building:
    ```Shell
    cmake --build --preset vs-17-2022-sse2-debug
    cmake --build --preset vs-17-2022-sse2-release
    cmake --build --preset vs-17-2022-sse2-profile
    ```
  - Testing:
    ```Shell
    ctest --preset vs-17-2022-sse2-debug
    ctest --preset vs-17-2022-sse2-release
    ctest --preset vs-17-2022-sse2-profile
    ```

